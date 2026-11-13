#!/usr/bin/env python3
# SPDX-License-Identifier: Apache-2.0
"""Verify that coverage defers or replans goals blocked by a live obstacle."""
import argparse
from copy import deepcopy
import json
from pathlib import Path
import subprocess
import tempfile
import time

from action_msgs.msg import GoalStatus
from ament_index_python.packages import get_package_prefix
from geometry_msgs.msg import PoseStamped, TransformStamped
from lifecycle_msgs.srv import GetState
from nav2_msgs.action import NavigateToPose
from nav_msgs.msg import OccupancyGrid, Path as NavPath
import rclpy
from rclpy.action import ActionClient, ActionServer
from rclpy.qos import DurabilityPolicy, QoSProfile
from robot_cleaning_interfaces.action import CleanTask
from robot_cleaning_interfaces.srv import PlanCoverage
from tf2_ros import StaticTransformBroadcaster

from run_cleaning_benchmark import stop
from verify_navigation import wait


def main():
    parser = argparse.ArgumentParser()
    modes = parser.add_mutually_exclusive_group()
    modes.add_argument('--during-gap', action='store_true')
    modes.add_argument('--defer-blocked', action='store_true')
    parser.add_argument('--local-costmap', action='store_true')
    args = parser.parse_args()
    if args.local_costmap and not args.during_gap:
        parser.error('--local-costmap requires --during-gap')
    rclpy.init()
    node = rclpy.create_node('coverage_replan_test')
    latched = QoSProfile(depth=1, durability=DurabilityPolicy.TRANSIENT_LOCAL)
    paths = []
    nav_goals = []
    processes = []
    injected = 0 if args.defer_blocked else (6 if args.during_gap else 4)
    obstacle_active = args.defer_blocked

    def navigator_state(_request, reply):
        reply.current_state.id = 3
        reply.current_state.label = 'active'
        return reply

    def navigate(goal):
        nonlocal obstacle_active
        nav_goals.append(goal.request.pose.pose.position.x)
        if len(nav_goals) == 1 and not obstacle_active:
            obstacle_active = True
            publish_costmap()
        if len(nav_goals) <= injected:
            goal.abort()
        else:
            goal.succeed()
        return NavigateToPose.Result()

    node.create_service(GetState, '/bt_navigator/get_state', navigator_state)
    nav = ActionServer(node, NavigateToPose, '/navigate_to_pose', navigate)
    node.create_subscription(NavPath, '/cleaning/path', paths.append, latched)
    task_client = ActionClient(node, CleanTask, '/cleaning/task')

    grid = OccupancyGrid()
    grid.header.frame_id = 'map'
    grid.info.width, grid.info.height = 36, 30
    grid.info.resolution = .10
    grid.info.origin.orientation.w = 1.0
    grid.data = [0] * (grid.info.width * grid.info.height)
    map_pub = node.create_publisher(OccupancyGrid, '/map', latched)
    map_pub.publish(grid)
    node.create_timer(.25, lambda: map_pub.publish(grid))

    obstacle_x = 1.45
    costmap = OccupancyGrid()
    costmap.header.frame_id = 'map'
    costmap.info = deepcopy(grid.info)
    if args.local_costmap:
        costmap.header.frame_id = 'local_odom'
        costmap.info.origin.position.x = -.35
    blocked = list(grid.data)
    for y in range(grid.info.height):
        columns = range(14, grid.info.width) if args.defer_blocked else (14,)
        for x in columns:
            blocked[y * grid.info.width + x] = 99 if args.local_costmap else 100
    costmap_topic = '/local_costmap/costmap' if args.local_costmap else '/global_costmap/costmap'
    costmap_pub = node.create_publisher(OccupancyGrid, costmap_topic, latched)

    def publish_costmap():
        costmap.header.stamp = node.get_clock().now().to_msg()
        costmap.data = blocked if obstacle_active else grid.data
        costmap_pub.publish(costmap)

    node.create_timer(.25, publish_costmap)
    transform = TransformStamped()
    transform.header.frame_id = 'map'
    transform.child_frame_id = 'base_footprint'
    transform.transform.translation.x = .8
    transform.transform.translation.y = .8
    transform.transform.rotation.w = 1.0
    tf = StaticTransformBroadcaster(node)
    if args.local_costmap:
        map_to_odom = TransformStamped()
        map_to_odom.header.frame_id = 'map'
        map_to_odom.child_frame_id = 'local_odom'
        map_to_odom.transform.translation.x = .35
        map_to_odom.transform.rotation.w = 1.0
        tf.sendTransform([transform, map_to_odom])
    else:
        tf.sendTransform(transform)
    try:
        with tempfile.TemporaryDirectory(prefix='sweeper-replan-') as directory:
            manager_parameters = [
                '-p', 'use_coverage_planner:=true', '-p', f'checkpoint_dir:={directory}',
            ]
            if args.during_gap:
                manager_parameters += [
                    '-p', 'gap_navigation_retries:=0', '-p', 'gap_failure_replan_threshold:=2',
                ]
            if args.defer_blocked:
                manager_parameters += ['-p', 'defer_blocked_sweep_goals:=true']
            planner_parameters = []
            if args.local_costmap:
                planner_parameters += ['-p', 'edge_margin:=.10', '-p', 'gap_use_local_costmap:=true']
            for package, executable, parameters in (
                ('robot_coverage_planner', 'coverage_planner_node', planner_parameters),
                ('robot_cleaning_manager', 'cleaning_task_manager_node', manager_parameters),
            ):
                binary = Path(get_package_prefix(package)) / 'lib' / package / executable
                processes.append(subprocess.Popen(
                    [str(binary), '--ros-args', *parameters], start_new_session=True))
            wait(node, task_client.server_is_ready, 15, 'task server')
            planner = node.create_client(PlanCoverage, '/cleaning/plan_coverage')
            wait(node, planner.service_is_ready, 15, 'planner')
            wait(node, lambda: map_pub.get_subscription_count() >= 2, 10, 'map subscribers')
            wait(node, lambda: costmap_pub.get_subscription_count() >= (2 if args.defer_blocked else 1),
                 10, 'costmap subscribers')
            map_pub.publish(grid)
            start = PoseStamped()
            start.header.frame_id = 'map'
            start.pose.position.x = start.pose.position.y = .8
            start.pose.orientation.w = 1.0
            request = PlanCoverage.Request(start=start)
            deadline = time.monotonic() + 5
            while time.monotonic() < deadline:
                probe = planner.call_async(request)
                wait(node, probe.done, 5, 'planner readiness probe')
                if probe.result().success:
                    break
                time.sleep(.1)
            assert probe.result().success, probe.result().reason
            sent = task_client.send_goal_async(CleanTask.Goal(
                task_id='blocked-aisle', mode=CleanTask.Goal.ALL, target_coverage=.90))
            wait(node, sent.done, 10, 'task acceptance')
            task = sent.result()
            assert task.accepted
            result = task.get_result_async()
            expected_paths = 3 if args.during_gap else 2
            wait(node, lambda: len(paths) >= expected_paths or result.done(), 30, 'replacement route')
            assert len(paths) >= expected_paths and not result.done(), (
                result.result().result.reason if result.done() else 'Missing replacement route')
            assert len(nav_goals) >= injected
            original, *replans = paths[:expected_paths]
            replanned = replans[-1]
            assert any(point.pose.position.x > obstacle_x for point in original.poses)
            assert all(route.poses and all(point.pose.position.x < obstacle_x for point in route.poses)
                       for route in replans)
            if args.defer_blocked:
                assert nav_goals and all(x < obstacle_x for x in nav_goals)
            task.cancel_goal_async()
            wait(node, result.done, 8, 'task cancellation')
            assert result.result().status == GoalStatus.STATUS_CANCELED
            if args.defer_blocked:
                assert result.result().result.failed_waypoints > 0
            reopened = False
            if args.during_gap:
                remaining = OccupancyGrid(header=grid.header, info=grid.info)
                remaining.data = [100 if i % grid.info.width < 14 else 0
                                  for i in range(len(grid.data))]
                request = PlanCoverage.Request(start=start, gap_fill=True, covered=remaining)
                obstacle_active = False
                publish_costmap()
                deadline = time.monotonic() + 5
                while time.monotonic() < deadline:
                    probe = planner.call_async(request)
                    wait(node, probe.done, 5, 'plan after the obstacle leaves')
                    response = probe.result()
                    if response.success and any(p.pose.position.x > obstacle_x for p in response.path.poses):
                        reopened = True
                        break
                assert reopened, 'Planner did not recover access after removing the obstacle'
            print(json.dumps({
                'navigation_failures_injected': injected,
                'obstacle_costmap': costmap_topic,
                'replanned_during_gap_fill': args.during_gap,
                'deferred_live_blocked_waypoints': args.defer_blocked,
                'obstacle_inserted_during_task': not args.defer_blocked,
                'reopened_region_replanned': reopened,
                'unreachable_waypoints_before_replan': result.result().result.failed_waypoints,
                'original_waypoints': len(original.poses),
                'replacement_waypoints': len(replanned.poses),
                'replacement_stays_on_reachable_side_of_live_obstacle': True,
                'action_status': result.result().status,
            }, indent=2))
    finally:
        for process in reversed(processes):
            stop(process)
        nav.destroy()
        node.destroy_node()
        rclpy.try_shutdown()


if __name__ == '__main__':
    main()
