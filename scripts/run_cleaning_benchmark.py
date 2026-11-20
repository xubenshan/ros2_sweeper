#!/usr/bin/env python3
# SPDX-License-Identifier: Apache-2.0
"""Run a real Gazebo cleaning task and collect task and ground-truth metrics."""
import argparse
from collections import Counter, deque
import csv
import json
import math
import os
from pathlib import Path
import re
import signal
import statistics
import subprocess
import time

from action_msgs.msg import GoalStatus, GoalStatusArray
from generate_sweeper_scenarios import generate
from geometry_msgs.msg import PoseStamped
from nav2_msgs.action import NavigateToPose
from nav_msgs.msg import OccupancyGrid, Path as NavPath
import rclpy
from rclpy.action import ActionClient
from rclpy.time import Time
from rclpy.qos import DurabilityPolicy, QoSProfile, qos_profile_sensor_data
from robot_cleaning_interfaces.action import CleanTask
from robot_cleaning_interfaces.srv import BeginCoverage, PlanCoverage
from rosgraph_msgs.msg import Clock
from ros_gz_interfaces.msg import Contacts
from sensor_msgs.msg import LaserScan
from std_msgs.msg import Bool, Float32, String
from std_srvs.srv import Trigger
from tf2_ros import Buffer, TransformException, TransformListener

from verify_navigation import wait


ROOT = Path(__file__).resolve().parents[1]
SCENARIOS = ('multi_room', 'dynamic', 'narrow', 'islands', 'living_room')
LAYOUTS = ('multi_room', 'islands', 'narrow')


class Measurements:
    def __init__(self, node, observe_costmaps=False):
        latched = QoSProfile(depth=1, durability=DurabilityPolicy.TRANSIENT_LOCAL)
        self.values = {}
        self.metric_samples = Counter()
        self.costmap_samples = Counter()
        self.goals = {}
        self.states = Counter()
        self.last_state = ''
        self.recovery_started = None
        self.recovery_times = []
        self.clock = None
        self.scans = 0
        self.contacts = 0
        self.scan_times = []
        self.feedback = None
        for key in ('ratio', 'efficiency', 'revisit_ratio'):
            node.create_subscription(
                Float32, f'/coverage_meter/{key}',
                lambda msg, key=key: self.on_metric(key, msg), 10)
        node.create_subscription(Bool, '/coverage_meter/sim_unstable',
                                 lambda msg: self.values.update(sim_unstable=msg.data), latched)
        node.create_subscription(Clock, '/clock', self.on_clock, qos_profile_sensor_data)
        node.create_subscription(LaserScan, '/scan', self.on_scan, qos_profile_sensor_data)
        node.create_subscription(String, '/cleaning/state', self.on_state, latched)
        node.create_subscription(GoalStatusArray, '/navigate_to_pose/_action/status',
                                 self.on_goals, latched)
        if observe_costmaps:
            for scope in ('local', 'global'):
                node.create_subscription(
                    OccupancyGrid, f'/{scope}_costmap/costmap',
                    lambda msg, scope=scope: self.on_costmap(scope, msg), latched)
        for side in ('left', 'right'):
            node.create_subscription(Contacts, f'/bumper_{side}/contact',
                                     self.on_contact, qos_profile_sensor_data)

    def on_metric(self, key, message):
        self.values[key] = float(message.data)
        self.metric_samples[key] += 1

    def on_clock(self, message):
        self.clock = message.clock.sec + message.clock.nanosec / 1e9

    def on_costmap(self, scope, message):
        if message.info.width and message.info.height and message.data:
            self.costmap_samples[scope] += 1

    def on_scan(self, message):
        if any(math.isfinite(value) for value in message.ranges):
            self.scans += 1
            self.scan_times.append(time.monotonic())

    def on_goals(self, message):
        for status in message.status_list:
            self.goals[bytes(status.goal_info.goal_id.uuid)] = status.status

    def on_state(self, message):
        if message.data != self.last_state:
            self.states[message.data] += 1
            if message.data == 'RECOVERING':
                self.recovery_started = time.monotonic()
            elif self.recovery_started is not None:
                self.recovery_times.append(time.monotonic() - self.recovery_started)
                self.recovery_started = None
            self.last_state = message.data

    def on_contact(self, message):
        if message.contacts:
            self.contacts += 1


class PoseComparison:
    """Read-only execution trace for coverage, Nav2 plans and simulator truth."""

    def __init__(self, node, compare_poses=False):
        self.compare_poses = compare_poses
        self.buffer = Buffer() if compare_poses else None
        self.listener = TransformListener(self.buffer, node) if compare_poses else None
        self.pending = deque(maxlen=40)
        self.rows = []
        self.last_stamp = None
        self.task_grid = None
        self.truth_grid = None
        self.waypoints = []
        self.route_count = 0
        self.goal_count = 0
        self.global_plans = []
        self.global_plan_poses = []
        self.plan_count_by_goal = Counter()
        self.planner_events = []
        self.navigation_goals = []
        latched = QoSProfile(depth=1, durability=DurabilityPolicy.TRANSIENT_LOCAL)
        if compare_poses:
            node.create_subscription(PoseStamped, '/ground_truth/pose', self.on_truth, 10)
        node.create_subscription(NavPath, '/cleaning/path', self.on_route, latched)
        node.create_subscription(PoseStamped, '/cleaning/current_goal', self.on_goal, latched)
        node.create_subscription(NavPath, '/plan', self.on_global_plan, 10)
        node.create_subscription(String, '/coverage_direct_planner/events',
                                 self.on_planner_event, 100)
        node.create_subscription(String, '/cleaning/navigation_goals',
                                 self.on_navigation_goal, 100)
        node.create_subscription(OccupancyGrid, '/cleaning/covered_grid',
                                 lambda msg: setattr(self, 'task_grid', msg), latched)
        node.create_subscription(OccupancyGrid, '/coverage_meter/covered_grid',
                                 lambda msg: setattr(self, 'truth_grid', msg), 10)

    def on_route(self, msg):
        self.route_count += 1
        stamp = Time.from_msg(msg.header.stamp).nanoseconds
        for index, goal in enumerate(msg.poses):
            p = goal.pose.position
            self.waypoints.append((stamp, 'planned', self.route_count, index, p.x, p.y))

    def on_goal(self, msg):
        self.goal_count += 1
        p = msg.pose.position
        stamp = Time.from_msg(msg.header.stamp).nanoseconds
        self.waypoints.append((stamp, 'submitted', self.route_count, '', p.x, p.y))

    @staticmethod
    def path_length(poses):
        return sum(math.hypot(b.pose.position.x - a.pose.position.x,
                              b.pose.position.y - a.pose.position.y)
                   for a, b in zip(poses, poses[1:]))

    @staticmethod
    def is_straight(poses):
        if len(poses) < 2:
            return False
        start = poses[0].pose.position
        end = poses[-1].pose.position
        dx, dy = end.x - start.x, end.y - start.y
        length = math.hypot(dx, dy)
        if length < 1e-6:
            return False
        # CoverageDirectPlanner samples an exact segment. NavFn paths normally
        # contain grid-induced lateral deviation, even when their lengths match.
        return max(abs(dy * (pose.pose.position.x - start.x) -
                       dx * (pose.pose.position.y - start.y)) / length
                   for pose in poses) <= 1e-4

    def on_global_plan(self, msg):
        # Ignore a transient-local plan left over before the first cleaning goal.
        if not self.goal_count or not msg.poses:
            return
        self.plan_count_by_goal[self.goal_count] += 1
        replan = self.plan_count_by_goal[self.goal_count]
        stamp = Time.from_msg(msg.header.stamp).nanoseconds
        length = self.path_length(msg.poses)
        straight = self.is_straight(msg.poses)
        start, end = msg.poses[0].pose.position, msg.poses[-1].pose.position
        self.global_plans.append((stamp, self.goal_count, replan, len(msg.poses), length,
                                  straight, start.x, start.y, end.x, end.y))
        for index, pose in enumerate(msg.poses):
            point = pose.pose.position
            self.global_plan_poses.append(
                (stamp, self.goal_count, replan, index, point.x, point.y))

    def on_planner_event(self, message):
        try:
            event = json.loads(message.data)
        except (TypeError, ValueError):
            return
        if isinstance(event, dict) and 'stamp_ns' in event:
            self.planner_events.append(event)

    def on_navigation_goal(self, message):
        try:
            event = json.loads(message.data)
        except (TypeError, ValueError):
            return
        if isinstance(event, dict) and 'stamp_ns' in event:
            self.navigation_goals.append(event)

    def on_truth(self, msg):
        stamp = Time.from_msg(msg.header.stamp)
        if self.last_stamp is None or stamp.nanoseconds - self.last_stamp >= 100_000_000:
            self.pending.append(msg)
            self.last_stamp = stamp.nanoseconds

    def sample(self, state):
        if not self.compare_poses:
            return
        while self.pending:
            truth = self.pending[0]
            stamp = Time.from_msg(truth.header.stamp)
            try:
                pose = self.buffer.lookup_transform(truth.header.frame_id, 'base_footprint', stamp)
            except TransformException:
                if self.last_stamp - stamp.nanoseconds > 500_000_000:
                    self.pending.popleft()
                    continue
                break
            self.pending.popleft()
            p, q = pose.transform.translation, truth.pose.position
            self.rows.append((stamp.nanoseconds, state, p.x, p.y, q.x, q.y,
                              math.hypot(p.x - q.x, p.y - q.y)))

    def report(self, folder):
        with (folder / 'pose-comparison.csv').open('w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(('stamp_ns', 'state', 'tf_x', 'tf_y', 'truth_x', 'truth_y', 'error_m'))
            writer.writerows(self.rows)
        with (folder / 'waypoints.csv').open('w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(('stamp_ns', 'type', 'route', 'index', 'x', 'y'))
            writer.writerows(self.waypoints)
        with (folder / 'nav2-global-plans.csv').open('w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(('stamp_ns', 'goal', 'plan_for_goal', 'poses', 'path_m',
                             'straight', 'start_x', 'start_y', 'goal_x', 'goal_y'))
            writer.writerows(self.global_plans)
        with (folder / 'navigation-goals.csv').open('w', newline='') as file:
            fields = ('stamp_ns', 'sequence', 'task_id', 'stage', 'pass',
                      'index', 'attempt', 'adjusted', 'x', 'y',
                      'behavior_tree')
            writer = csv.DictWriter(file, fieldnames=fields)
            writer.writeheader()
            writer.writerows(self.navigation_goals)
        with (folder / 'nav2-global-plan-poses.csv').open('w', newline='') as file:
            writer = csv.writer(file)
            writer.writerow(('stamp_ns', 'goal', 'plan_for_goal', 'index', 'x', 'y'))
            writer.writerows(self.global_plan_poses)
        submitted = [
            (goal_number, row) for goal_number, row in enumerate(
                (row for row in self.waypoints if row[1] == 'submitted'), start=1)]
        event_fields = ('stamp_ns', 'request_id', 'strategy', 'sequence', 'goal', 'route',
                        'stage', 'pass', 'index', 'attempt', 'adjusted',
                        'decision', 'attempted_direct', 'fallback',
                        'start_x', 'start_y', 'goal_x', 'goal_y',
                        'length_m', 'reference_length_m', 'selected_length_m',
                        'extra_distance_m', 'new_area_m2', 'planning_ms',
                        'reference_new_area_m2', 'best_candidate_length_m',
                        'best_candidate_new_area_m2', 'best_candidate_score_m',
                        'rejected_detour', 'rejected_area', 'rejected_score',
                        'rejected_safety',
                        'candidate_count', 'coverage_search_participated', 'reject_reason', 'request_count',
                        'direct_attempts', 'direct_successes', 'distance_rejections',
                        'costmap_rejections', 'footprint_rejections', 'navfn_fallbacks')
        event_rows = []
        for event in self.planner_events:
            target_x = float(event.get('goal_x', 0.0))
            target_y = float(event.get('goal_y', 0.0))
            candidates = []
            for goal_event in self.navigation_goals:
                distance = math.hypot(float(goal_event.get('x', 0.0)) - target_x,
                                      float(goal_event.get('y', 0.0)) - target_y)
                delta = int(event['stamp_ns']) - int(goal_event.get('stamp_ns', 0))
                if distance <= 0.12 and delta >= -1_000_000_000:
                    candidates.append((max(delta, 0), distance, goal_event))
            matched_goal = min(candidates, default=None,
                               key=lambda item: (item[0], item[1]))
            goal_event = matched_goal[2] if matched_goal else None
            matched = min(submitted, key=lambda item: math.hypot(
                float(item[1][4]) - target_x, float(item[1][5]) - target_y), default=None)
            goal_number, goal = matched if matched else ('', None)
            event_rows.append({
                'stamp_ns': int(event['stamp_ns']),
                'request_id': event.get('request_id', ''),
                'strategy': event.get('strategy', ''),
                'sequence': goal_event.get('sequence', '') if goal_event else '',
                'goal': goal_number, 'route': goal[2] if goal else '',
                'stage': goal_event.get('stage', '') if goal_event else '',
                'pass': goal_event.get('pass', '') if goal_event else '',
                'index': goal_event.get('index', '') if goal_event else '',
                'attempt': goal_event.get('attempt', '') if goal_event else '',
                'adjusted': goal_event.get('adjusted', '') if goal_event else '',
                'decision': event.get('decision', ''),
                'attempted_direct': event.get('attempted_direct', ''),
                'fallback': event.get('fallback', ''),
                'start_x': event.get('start_x', ''), 'start_y': event.get('start_y', ''),
                'goal_x': event.get('goal_x', ''), 'goal_y': event.get('goal_y', ''),
                'length_m': event.get('length_m', ''),
                'reference_length_m': event.get('reference_length_m', ''),
                'selected_length_m': event.get('selected_length_m', ''),
                'extra_distance_m': event.get('extra_distance_m', ''),
                'new_area_m2': event.get('new_area_m2', ''),
                'planning_ms': event.get('planning_ms', ''),
                'reference_new_area_m2': event.get('reference_new_area_m2', ''),
                'best_candidate_length_m': event.get('best_candidate_length_m', ''),
                'best_candidate_new_area_m2': event.get('best_candidate_new_area_m2', ''),
                'best_candidate_score_m': event.get('best_candidate_score_m', ''),
                'rejected_detour': event.get('rejected_detour', ''),
                'rejected_area': event.get('rejected_area', ''),
                'rejected_score': event.get('rejected_score', ''),
                'rejected_safety': event.get('rejected_safety', ''),
                'candidate_count': event.get('candidate_count', ''),
                'coverage_search_participated': event.get('coverage_search_participated', ''),
                'reject_reason': event.get('reject_reason', ''),
                'request_count': event.get('request_count', ''),
                'direct_attempts': event.get('direct_attempts', ''),
                'direct_successes': event.get('direct_successes', ''),
                'distance_rejections': event.get('distance_rejections', ''),
                'costmap_rejections': event.get('costmap_rejections', ''),
                'footprint_rejections': event.get('footprint_rejections', ''),
                'navfn_fallbacks': event.get('navfn_fallbacks', ''),
            })
        with (folder / 'coverage-direct-planner-events.csv').open('w', newline='') as file:
            writer = csv.DictWriter(file, fieldnames=event_fields)
            writer.writeheader()
            writer.writerows(event_rows)
        errors = sorted(row[-1] for row in self.rows if row[1] == 'RUNNING')
        report = {'running_samples': len(errors)}
        if errors:
            report.update(median_error_m=statistics.median(errors),
                          p95_error_m=errors[math.ceil(.95 * len(errors)) - 1],
                          max_error_m=errors[-1])
        initial = [row for row in self.global_plans if row[2] == 1]
        report.update(
            nav2_global_plan_messages=len(self.global_plans),
            nav2_goals_with_plan=len(initial),
            nav2_replans=max(0, len(self.global_plans) - len(initial)),
            nav2_initial_plan_m=sum(row[4] for row in initial),
            nav2_all_plan_messages_m=sum(row[4] for row in self.global_plans),
            nav2_straight_initial_plans=sum(row[5] for row in initial),
            nav2_straight_initial_plan_ratio=(sum(row[5] for row in initial) / len(initial)
                                              if initial else None),
            coverage_direct_planner_events=len(event_rows),
            coverage_direct_successes=sum(
                row['decision'] == 'direct_success' for row in event_rows),
            coverage_direct_rejections=sum(
                str(row['attempted_direct']).lower() == 'true' and
                row['decision'] != 'direct_success' for row in event_rows),
            coverage_navfn_fallbacks=sum(
                str(row['fallback']).lower() == 'true' for row in event_rows),
            coverage_navfn_bypasses=sum(
                row['decision'] == 'navfn_fallback' for row in event_rows),
            coverage_navfn_exceptions=sum(
                row['decision'] in ('navfn_exception', 'direct_rejected_navfn_exception')
                for row in event_rows),
            coverage_aware_requests=sum(
                row['strategy'] == 'coverage_aware' for row in event_rows),
            coverage_aware_participated=sum(
                str(row['coverage_search_participated']).lower() == 'true' for row in event_rows),
            coverage_aware_selected=sum(
                row['decision'] == 'coverage_selected' for row in event_rows),
            coverage_aware_candidates_generated=sum(
                int(row['candidate_count']) for row in event_rows
                if str(row['candidate_count']).strip()),
            coverage_aware_new_area_m2=sum(
                float(row['new_area_m2']) for row in event_rows
                if str(row['new_area_m2']).strip()),
            coverage_aware_extra_distance_m=sum(
                float(row['extra_distance_m']) for row in event_rows
                if str(row['extra_distance_m']).strip()),
            coverage_aware_planning_ms_mean=(statistics.mean(
                float(row['planning_ms']) for row in event_rows
                if str(row['planning_ms']).strip()) if any(
                    str(row['planning_ms']).strip() for row in event_rows) else None),
            coverage_aware_fallback_reasons=dict(Counter(
                row['decision'] for row in event_rows
                if row['strategy'] == 'coverage_aware' and
                row['decision'].startswith('coverage_fallback_'))),
        )
        task, truth = self.task_grid, self.truth_grid
        if (task is not None and truth is not None and task.header.frame_id == truth.header.frame_id
            and task.info.resolution == truth.info.resolution and task.info.origin == truth.info.origin
            and task.info.width == truth.info.width and task.info.height == truth.info.height):
            (folder / 'coverage-grids.json').write_text(json.dumps({
                'frame': task.header.frame_id,
                'resolution': task.info.resolution,
                'width': task.info.width,
                'height': task.info.height,
                'origin': [task.info.origin.position.x, task.info.origin.position.y],
                'runtime': list(task.data),
                'truth': list(truth.data),
            }) + '\n')
            report.update(estimate_only_cells=sum(a == 100 and b != 100 for a, b in zip(task.data, truth.data)),
                          truth_only_cells=sum(b == 100 and a != 100 for a, b in zip(task.data, truth.data)))
        return report


def stop(process):
    if process is None or process.poll() is not None:
        return
    process.send_signal(signal.SIGINT)
    try:
        process.wait(timeout=12)
    except subprocess.TimeoutExpired:
        os.killpg(process.pid, signal.SIGTERM)
        try:
            process.wait(timeout=5)
        except subprocess.TimeoutExpired:
            os.killpg(process.pid, signal.SIGKILL)
            process.wait()


def stop_gazebo_partition(partition):
    # Some Gazebo server/GUI children outlive their ros_gz_sim wrapper.
    tag = f'GZ_PARTITION={partition}'.encode()
    for signum in (signal.SIGTERM, signal.SIGKILL):
        for directory in Path('/proc').iterdir():
            if not directory.name.isdigit():
                continue
            try:
                argv = (directory / 'cmdline').read_bytes().split(b'\0')
                if not argv[0].startswith(b'gz sim '):
                    continue
                environment = (directory / 'environ').read_bytes().split(b'\0')
                if tag in environment:
                    os.kill(int(directory.name), signum)
            except (OSError, IndexError):
                pass
        if signum == signal.SIGTERM:
            time.sleep(.5)


def run(scenario, args, folder, domain):
    folder.mkdir(parents=True, exist_ok=True)
    os.environ['ROS_DOMAIN_ID'] = str(domain)
    partition = f'sweeper_benchmark_{domain}_{os.getpid()}'
    os.environ['GZ_PARTITION'] = partition
    launch_args = ['implementation:=cpp', 'mode:=localize', 'evaluate:=true',
                   f'gui:={str(args.gui).lower()}', 'rviz:=false',
                   f'coverage_algorithm:={args.coverage_algorithm}']
    fixture_world_name = scenario if scenario == 'dynamic' else 'default'
    if scenario == 'living_room':
        launch_args += ['enable_tof:=true']
    else:
        generate(folder, scenario, fixture_world_name)
        launch_args += [
            f'world:={folder / "scene.world"}', f'map:={folder / "map.yaml"}',
            f'regions:={folder / "regions.yaml"}', 'x:=-1.08', 'y:=0.25',
            'enable_tof:=false',
        ]
    launch_args += [f'odom_source:={args.odom_source}']
    if scenario == 'living_room' or args.whole_map:
        launch_args += ['benchmark_nav:=true']
    launch_args += [
        f'tof_costmap:={str(args.tof_costmap).lower()}',
        f'collision_aware_nav:={str(args.collision_aware_nav).lower()}',
        f'clearance_control:={str(args.clearance_control).lower()}',
        f'precise_gap_navigation:={str(args.precise_gap_navigation).lower()}',
        f'early_gap_replan:={str(not args.finish_main_before_gap).lower()}',
        f'gap_progress_timeout_s:={args.gap_progress_timeout}',
        f'gap_navigation_retries:={args.gap_retries}',
        f'max_gap_passes:={args.max_gap_passes}',
    ]
    if args.baseline_nav_params:
        launch_args += [f'nav_params:={args.baseline_nav_params}']
    if args.sweep_safety_margin is not None:
        launch_args += [f'sweep_safety_margin:={args.sweep_safety_margin}']
    if args.gap_safety_margin is not None:
        launch_args += [f'gap_safety_margin:={args.gap_safety_margin}']
    if args.sweep_goal_tolerance is not None:
        launch_args += [f'sweep_goal_tolerance:={args.sweep_goal_tolerance}']
    if args.gap_goal_tolerance is not None:
        launch_args += [f'gap_goal_tolerance:={args.gap_goal_tolerance}']
    if args.safe_gap:
        launch_args += ['safe_gap:=true']
    if args.target_gap_coverage:
        launch_args += ['target_gap_coverage:=true']
    if args.gap_efficiency_target:
        launch_args += [f'gap_efficiency_target:={args.gap_efficiency_target}']
    if args.guard_gap_goals:
        launch_args += ['guard_gap_goals:=true']
    if args.open_floor:
        launch_args += ['open_floor:=true']
    if args.continuous_coverage_tracking:
        launch_args += ['continuous_coverage_tracking:=true']
    if args.refine_sweep:
        launch_args += ['refine_sweep:=true']
    if args.static_sweep:
        launch_args += ['sweep_use_live_costmap:=false']
    if args.direct_sweep_navigation is not None:
        launch_args += [
            f'direct_sweep_navigation:={str(args.direct_sweep_navigation).lower()}']
    if args.coverage_aware_navigation:
        launch_args += ['coverage_aware_navigation:=true']
    whole_map = scenario == 'living_room' or args.whole_map
    report = {'scenario': scenario, 'domain': domain, 'command': launch_args,
              'coverage_algorithm': args.coverage_algorithm,
              'task_scope': 'all' if whole_map else 'regions',
              'requested_coverage': args.target,
              'rmw': rclpy.get_rmw_implementation_identifier(),
              'nav_ready': False, 'measurement_valid': False}
    launch = None
    moving = None
    rclpy.init()
    node = rclpy.create_node('sweeper_benchmark')
    observe_costmaps = args.open_floor
    measure = Measurements(node, observe_costmaps)
    execution_trace = PoseComparison(node, args.compare_poses)
    client = ActionClient(node, CleanTask, '/cleaning/task')
    nav_client = ActionClient(node, NavigateToPose, '/navigate_to_pose')
    begin = node.create_client(BeginCoverage, '/cleaning/begin_coverage')
    planner = node.create_client(PlanCoverage, '/cleaning/plan_coverage')
    output = folder / 'launch.log'
    with output.open('w') as log:
        startup_begin = time.monotonic()
        try:
            launch = subprocess.Popen([str(ROOT / 'scripts/run_sweeper.sh'), *launch_args],
                                      stdout=log, stderr=subprocess.STDOUT, start_new_session=True)
            wait(node, lambda: client.server_is_ready() and measure.scans > 0 and measure.clock
                 or launch.poll() is not None, 110, 'Gazebo, lidar and cleaning action')
            if launch.poll() is not None:
                raise RuntimeError('Launch exited before the robot was ready')
            lifecycle = node.create_client(Trigger, '/lifecycle_manager_navigation/is_active')
            deadline = time.monotonic() + 90
            state_request = None
            request_deadline = 0.0
            last_lifecycle_state = 'service unavailable'
            while time.monotonic() < deadline:
                if launch.poll() is not None:
                    raise RuntimeError(f'Launch exited while waiting for Nav2 (code {launch.returncode})')
                if state_request is not None and state_request.done():
                    last_lifecycle_state = 'active' if state_request.result().success else 'inactive'
                    state_request = None
                if (last_lifecycle_state == 'active' and nav_client.server_is_ready()):
                    report['nav_ready'] = True
                    break
                if state_request is not None and time.monotonic() >= request_deadline:
                    lifecycle.remove_pending_request(state_request)
                    state_request = None
                if state_request is None and lifecycle.service_is_ready():
                    state_request = lifecycle.call_async(Trigger.Request())
                    request_deadline = time.monotonic() + 2.0
                rclpy.spin_once(node, timeout_sec=.10)
            if not report['nav_ready']:
                raise RuntimeError(
                    f'Nav2 not ready before cleaning: lifecycle={last_lifecycle_state}, '
                    f'navigate_to_pose_server={nav_client.server_is_ready()}')
            report['nav_ready'] = False
            wait(node, lambda: begin.service_is_ready() and planner.service_is_ready(),
                 15, 'coverage tracker and planner services')
            if observe_costmaps:
                before = measure.costmap_samples.copy()
                wait(node, lambda: all(measure.costmap_samples[scope] >= before[scope] + 2
                                       for scope in ('local', 'global')),
                     15, 'fresh local and global costmaps')
            report['nav_ready'] = True
            report['startup_wall_time_s'] = time.monotonic() - startup_begin
            if args.startup_only:
                report['success'] = True
                (folder / 'result.json').write_text(json.dumps(report, indent=2) + '\n')
                print(json.dumps(report, indent=2), flush=True)
                return report
            goal = CleanTask.Goal()
            goal.task_id = f'{scenario}-{domain}-{int(time.time())}'
            goal.mode = CleanTask.Goal.ALL if whole_map else CleanTask.Goal.REGIONS
            if goal.mode == CleanTask.Goal.REGIONS:
                goal.regions = ['west', 'east']
            goal.target_coverage = args.target
            start_wall = time.monotonic()
            start_sim = measure.clock

            def feedback(message):
                measure.feedback = message.feedback

            pending = client.send_goal_async(goal, feedback_callback=feedback)
            wait(node, pending.done, 15, 'cleaning goal response')
            handle = pending.result()
            if not handle.accepted:
                raise RuntimeError('Cleaning goal was rejected')
            result = handle.get_result_async()
            next_motion = start_wall + 5
            motion_parked = False
            next_output = start_wall + 30
            pause, resume = (node.create_client(Trigger, f'/cleaning/{name}')
                             for name in ('pause', 'resume'))
            interrupted = False
            while not result.done() and time.monotonic() - start_wall < args.timeout:
                rclpy.spin_once(node, timeout_sec=.10)
                execution_trace.sample(measure.last_state)
                now = time.monotonic()
                if scenario == 'dynamic' and not motion_parked and now >= next_motion and (
                    moving is None or moving.poll() is not None
                ):
                    sim_elapsed = measure.clock - start_sim
                    motion_parked = sim_elapsed >= 95
                    obstacle_x = 2.4 if motion_parked else .10
                    position = 0.0 if motion_parked else .72 * math.sin(sim_elapsed * .28)
                    moving = subprocess.Popen(
                        ['gz', 'service', '-s', f'/world/{fixture_world_name}/set_pose',
                         '--reqtype', 'gz.msgs.Pose', '--reptype', 'gz.msgs.Boolean',
                         '--timeout', '1000', '--req',
                         f'name: "moving_box" position {{ x: {obstacle_x} y: {position} z: 0.175 }} '
                         'orientation { w: 1 }'], stdout=log, stderr=subprocess.STDOUT)
                    next_motion = now + 1.6
                if (scenario == 'multi_room' and args.exercise_pause and not interrupted
                    and measure.feedback is not None and measure.feedback.completed_waypoints >= 2
                    and measure.last_state == 'RUNNING'):
                    stopped = pause.call_async(Trigger.Request())
                    wait(node, stopped.done, 10, 'pause service')
                    report['pause'] = stopped.result().success
                    wait(node, lambda: measure.last_state == 'PAUSED', 10, 'PAUSED')
                    end = time.monotonic() + 15
                    while time.monotonic() < end:
                        resumed = resume.call_async(Trigger.Request())
                        wait(node, resumed.done, 5, 'resume service')
                        if resumed.result().success:
                            report['resume'] = True
                            break
                        rclpy.spin_once(node, timeout_sec=.3)
                    interrupted = True
                if now >= next_output:
                    print(f'{scenario}: wall={now-start_wall:.0f}s state={measure.last_state} '
                          f'truth={measure.values.get("ratio", 0):.1%} '
                          f'efficiency={measure.values.get("efficiency", 0):.1%}', flush=True)
                    next_output = now + 30
                if launch.poll() is not None:
                    raise RuntimeError('Gazebo launch stopped during the task')
            timed_out = not result.done()
            if timed_out:
                handle.cancel_goal_async()
                wait(node, result.done, 15, 'cancel after benchmark timeout')
            response = result.result()
            elapsed = time.monotonic() - start_wall
            sim_elapsed = measure.clock - start_sim
            before = measure.metric_samples.copy()
            keys = ('ratio', 'efficiency', 'revisit_ratio')
            deadline = time.monotonic() + 10.0
            fresh_metrics = False
            while time.monotonic() < deadline and launch.poll() is None:
                rclpy.spin_once(node, timeout_sec=.2)
                if all(measure.metric_samples[key] >= before[key] + 2 for key in keys):
                    fresh_metrics = True
                    break
            execution_trace.sample(measure.last_state)
            trace_report = execution_trace.report(folder)
            report.update({key: value for key, value in trace_report.items()
                           if key.startswith(('nav2_', 'coverage_'))})
            if args.compare_poses:
                report['pose_comparison'] = {
                    key: value for key, value in trace_report.items()
                    if not key.startswith(('nav2_', 'coverage_'))}
            counts = Counter(measure.goals.values())
            finished_goals = sum(counts[s] for s in (4, 5, 6))
            report.update(
                action_status=response.status, success=response.result.success,
                reason=response.result.reason, timed_out=timed_out,
                measurement_valid=bool(measure.states['RUNNING'] and fresh_metrics and
                                       not measure.values.get('sim_unstable')),
                task_coverage=response.result.coverage, task_path_m=response.result.path_length_m,
                completed_waypoints=response.result.completed_waypoints,
                failed_waypoints=response.result.failed_waypoints, wall_time_s=elapsed,
                sim_time_s=sim_elapsed,
                real_time_factor=sim_elapsed / elapsed,
                nav_goals_succeeded=counts[GoalStatus.STATUS_SUCCEEDED],
                nav_goals_canceled=counts[GoalStatus.STATUS_CANCELED],
                nav_goals_failed=counts[GoalStatus.STATUS_ABORTED],
                nav_goal_success_rate=counts[GoalStatus.STATUS_SUCCEEDED] / finished_goals
                if finished_goals else None,
                states=dict(measure.states), contact_messages=measure.contacts,
                recovery_durations_s=measure.recovery_times,
                scan_hz_wall=(len(measure.scan_times) - 1) /
                (measure.scan_times[-1] - measure.scan_times[0]) if measure.scans > 1 else None,
                **measure.values)
        except (RuntimeError, ValueError) as error:
            report.update(success=False, error=str(error), **measure.values)
        finally:
            if moving is not None and moving.poll() is None:
                moving.terminate()
                moving.wait()
            stop(launch)
            stop_gazebo_partition(partition)
            node.destroy_node()
            rclpy.try_shutdown()
    log_text = output.read_text(errors='replace')
    rows = re.findall(
        r'COVERAGE_REPORT coverage=(\d+\.\d+) efficiency=(\d+\.\d+) '
        r'revisit_ratio=(\d+\.\d+) path_m=(\d+\.\d+) ideal_m=(\d+\.\d+) '
        r'reachable_cells=(\d+)', log_text)
    if rows:
        report['truth_path_m'] = float(rows[-1][3])
        report['ideal_path_m'] = float(rows[-1][4])
        report['truth_target_cells'] = int(rows[-1][5])
        at_coverage = {}
        for target in (.70, .80, .85, .90):
            first = next((row for row in rows if float(row[0]) >= target), None)
            if first:
                coverage, efficiency, revisit, distance = map(float, first[:4])
                at_coverage[f'{target:.2f}'] = {'coverage': coverage, 'efficiency': efficiency,
                                              'revisit_ratio': revisit, 'truth_path_m': distance}
                report[f'path_to_{target * 100:.0f}_m'] = distance
        report['at_coverage'] = at_coverage
    target_row = re.search(
        r'COVERAGE_REPORT coverage=(\d+\.\d+) efficiency=(\d+\.\d+) '
        r'[^\n]*?path_m=(\d+\.\d+) [^\n]*?target_hit=True t_target=(\d+(?:\.\d+)?)',
        log_text)
    if target_row:
        coverage, efficiency, distance, sim_seconds = map(float, target_row.groups())
        report['at_truth_target'] = {
            'coverage': coverage, 'efficiency': efficiency,
            'truth_path_m': distance, 'sim_time_s': sim_seconds,
        }
    main_plan = re.search(r'gap_fill=0 waypoints=(\d+) planned_m=(\d+\.\d+)', log_text)
    if main_plan:
        report['planned_waypoints'] = int(main_plan[1])
        report['planned_path_m'] = float(main_plan[2])
    gap_plans = re.findall(r'gap_fill=1 waypoints=([1-9]\d*) planned_m=(\d+\.\d+)', log_text)
    report['gap_passes'] = len(gap_plans)
    report['gap_plans'] = [{'waypoints': int(count), 'planned_m': float(length)}
                           for count, length in gap_plans]
    report['coverage_planned_path_m_total'] = report.get('planned_path_m', 0.0) + sum(
        plan['planned_m'] for plan in report['gap_plans'])
    report['deferred_sweep_waypoints'] = sum(map(
        int, re.findall(r'Deferred (\d+) sweep waypoints blocked by live costmap', log_text)))
    report['adjusted_sweep_waypoints'] = log_text.count('Adjusted sweep waypoint ')
    report['deferred_gap_waypoints'] = sum(map(
        int, re.findall(r'Deferred (\d+) gap waypoints blocked by live costmap', log_text)))
    report['adjusted_gap_waypoints'] = log_text.count('Adjusted gap waypoint ')
    report['navigation_timeouts'] = log_text.count('goal timed out')
    report['no_progress'] = log_text.count(': no progress')
    report['contact_recoveries_started'] = log_text.count('Collision on ')
    report['contact_recoveries_completed'] = log_text.count('Recovery complete,')
    report['contact_recoveries_cleared'] = log_text.count('Recovery complete, contact=clear')
    report['contact_recovery_clear_rate'] = (
        report['contact_recoveries_cleared'] / report['contact_recoveries_started']
        if report['contact_recoveries_started'] else None)
    if scenario == 'dynamic':
        report['moving_obstacle_updates'] = log_text.count('data: true')
        if not report['moving_obstacle_updates']:
            report.update(success=False, error='Gazebo did not acknowledge obstacle motion')
    if scenario == 'multi_room' and args.exercise_pause and not (
        report.get('pause') and report.get('resume')
    ):
        report.update(success=False, error='Pause/resume scenario did not complete')
    if whole_map:
        report['performance_passed'] = bool(
            report['measurement_valid'] and report['success'] and not report['timed_out'] and
            report.get('ratio', 0) >= .90 and report.get('efficiency', 0) >= .80)
    (folder / 'result.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2), flush=True)
    return report


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--scenario', choices=(*SCENARIOS, 'all', 'layouts'), default='living_room')
    parser.add_argument('--runs', type=int, default=1)
    parser.add_argument('--odom-source', choices=('robot_wheels', 'ground_truth'),
                        default='robot_wheels')
    parser.add_argument('--compare-poses', action='store_true',
                        help='Record time-aligned TF versus Gazebo truth for diagnostics')
    parser.add_argument('--whole-map', action='store_true',
                        help='Compare whole-map cleaning in generated scenes')
    parser.add_argument('--require-performance', action='store_true',
                        help='Require three successful runs per layout at 90%% coverage and 80%% efficiency')
    parser.add_argument('--startup-only', action='store_true',
                        help='Check lifecycle and action readiness without starting cleaning')
    parser.add_argument('--startup-retries', type=int, default=1)
    parser.add_argument('--domain', type=int, default=61)
    parser.add_argument('--target', type=float, default=.90)
    parser.add_argument('--coverage-algorithm', choices=('optimized', 'baseline'),
                        default='optimized',
                        help='Select the production planner or the isolated comparison baseline')
    parser.add_argument('--timeout', type=float, default=1800)
    parser.add_argument('--output', type=Path, default=Path('results/benchmark'))
    parser.add_argument('--gui', action=argparse.BooleanOptionalAction, default=True)
    parser.add_argument('--tof-costmap', action=argparse.BooleanOptionalAction, default=True)
    parser.add_argument('--collision-aware-nav', action='store_true')
    parser.add_argument('--clearance-control', action='store_true',
                        help='Regulate speed by obstacle clearance and keep collision prediction on')
    parser.add_argument('--sweep-safety-margin', type=float,
                        help='Extra clearance beyond the robot radius for the main sweep')
    parser.add_argument('--gap-safety-margin', type=float,
                        help='Extra clearance beyond the robot radius for gap sweeps')
    parser.add_argument('--sweep-goal-tolerance', type=float,
                        help='Position tolerance in meters for the normal goal checker')
    parser.add_argument('--gap-goal-tolerance', type=float,
                        help='Position tolerance in meters for the precise gap goal checker')
    parser.add_argument('--safe-gap', action='store_true',
                        help='Keep extra clearance in gaps and prefer uncovered interior floor')
    parser.add_argument('--target-gap-coverage', action='store_true',
                        help='Optimize gap routes for the remaining coverage target')
    parser.add_argument('--gap-efficiency-target', type=float, default=0.0,
                        help='Use remaining travel at this efficiency to guide gap selection')
    parser.add_argument('--guard-gap-goals', action='store_true',
                        help='Check and adjust gap goals with local and global costmaps')
    parser.add_argument('--open-floor', action='store_true',
                        help='Sweep the interior floor, leaving the edge band for edge cleaning')
    parser.add_argument('--continuous-coverage-tracking', action='store_true',
                        help='Use continuous brush geometry in runtime coverage tracking')
    parser.add_argument('--refine-sweep', action='store_true',
                        help='Refine interior sweep waypoints against travel and swept floor')
    parser.add_argument('--static-sweep', action='store_true',
                        help='Generate the initial sweep from the static map for comparison')
    parser.add_argument('--direct-sweep-navigation', action=argparse.BooleanOptionalAction,
                        default=None,
                        help='Prefer collision-checked straight connectors with NavFn fallback')
    parser.add_argument('--coverage-aware-navigation', action='store_true',
                        help='Use the opt-in coverage-aware global planner for sweep goals')
    parser.add_argument('--precise-gap-navigation', action='store_true')
    parser.add_argument('--finish-main-before-gap', action='store_true')
    parser.add_argument('--gap-progress-timeout', type=int, default=35)
    parser.add_argument('--gap-retries', type=int, default=1)
    parser.add_argument('--max-gap-passes', type=int, default=3)
    parser.add_argument('--exercise-pause', action='store_true')
    parser.add_argument('--baseline-nav-params', default='')
    args = parser.parse_args()
    scenarios = {'all': SCENARIOS[:3], 'layouts': LAYOUTS}.get(args.scenario, (args.scenario,))
    if args.scenario == 'layouts':
        args.whole_map = True
    if args.require_performance and (
        args.startup_only or args.runs < 3 or not (args.whole_map or args.scenario == 'living_room')
    ):
        parser.error('--require-performance requires whole-map tasks and at least three runs')
    if args.static_sweep and not args.open_floor:
        parser.error('--static-sweep requires --open-floor')
    if args.refine_sweep and not args.open_floor:
        parser.error('--refine-sweep requires --open-floor')
    if args.gap_efficiency_target and not (args.open_floor and args.target_gap_coverage):
        parser.error('--gap-efficiency-target requires --open-floor and --target-gap-coverage')
    if (args.runs < 1 or not 0 < args.target <= 1 or args.timeout <= 0
        or (args.sweep_safety_margin is not None and
            (not math.isfinite(args.sweep_safety_margin) or args.sweep_safety_margin < 0))
        or (args.gap_safety_margin is not None and
            (not math.isfinite(args.gap_safety_margin) or args.gap_safety_margin < 0))
        or (args.sweep_goal_tolerance is not None and
            (not math.isfinite(args.sweep_goal_tolerance) or args.sweep_goal_tolerance <= 0))
        or (args.gap_goal_tolerance is not None and
            (not math.isfinite(args.gap_goal_tolerance) or args.gap_goal_tolerance <= 0))
        or not 0 <= args.gap_efficiency_target <= 1 or args.max_gap_passes < 0
        or args.gap_progress_timeout < 1 or args.gap_retries < 0
        or args.startup_retries < 0 or args.domain < 0
        or args.domain + len(scenarios) * args.runs * (args.startup_retries + 1) > 232):
        parser.error('Invalid run count, target, timeout or domain range')
    output = args.output.resolve()
    output.mkdir(parents=True, exist_ok=True)
    reports = []
    domain = args.domain
    for scenario in scenarios:
        for run_index in range(1, args.runs + 1):
            folder = output / scenario / f'run-{run_index}'
            report = {}
            for attempt in range(args.startup_retries + 1):
                attempt_folder = folder if attempt == 0 else folder / f'retry-{attempt}'
                report = run(scenario, args, attempt_folder, domain)
                domain += 1
                if report['nav_ready']:
                    break
            reports.append(report)
    summary = {}
    for scenario in scenarios:
        relevant = [r for r in reports if r['scenario'] == scenario and r.get('measurement_valid')]
        summary[scenario] = {}
        for field in ('ratio', 'efficiency', 'truth_path_m', 'revisit_ratio',
                      'path_to_85_m', 'path_to_90_m', 'nav_goal_success_rate'):
            values = [r[field] for r in relevant if r.get(field) is not None]
            if values:
                summary[scenario][field] = {'mean': statistics.mean(values),
                                            'min': min(values), 'max': max(values), 'n': len(values)}
    (output / 'summary.json').write_text(json.dumps(summary, indent=2) + '\n')
    fields = ['scenario', 'coverage_algorithm', 'task_scope', 'action_status', 'success',
              'measurement_valid', 'performance_passed', 'reason',
              'ratio', 'efficiency', 'revisit_ratio', 'truth_path_m',
              'path_to_70_m', 'path_to_80_m', 'path_to_85_m', 'path_to_90_m',
              'truth_target_cells', 'ideal_path_m', 'planned_path_m',
              'coverage_planned_path_m_total', 'planned_waypoints',
              'nav2_initial_plan_m', 'nav2_global_plan_messages', 'nav2_replans',
              'nav2_straight_initial_plan_ratio',
              'coverage_aware_requests', 'coverage_aware_participated',
              'coverage_aware_selected', 'coverage_aware_candidates_generated',
              'coverage_aware_new_area_m2', 'coverage_aware_extra_distance_m',
              'coverage_aware_planning_ms_mean', 'coverage_aware_fallback_reasons',
              'task_coverage', 'task_path_m', 'wall_time_s', 'real_time_factor', 'nav_goal_success_rate',
              'navigation_timeouts', 'gap_passes', 'deferred_sweep_waypoints',
              'adjusted_sweep_waypoints', 'deferred_gap_waypoints', 'adjusted_gap_waypoints',
              'contact_recoveries_started',
              'contact_recoveries_cleared', 'pause', 'resume', 'error']
    with (output / 'summary.csv').open('w', newline='') as file:
        writer = csv.DictWriter(file, fieldnames=fields, extrasaction='ignore')
        writer.writeheader()
        writer.writerows(reports)
    passed = all(r['success'] for r in reports)
    if args.require_performance:
        passed = all(r['performance_passed'] for r in reports)
    raise SystemExit(0 if passed else 1)


if __name__ == '__main__':
    main()
