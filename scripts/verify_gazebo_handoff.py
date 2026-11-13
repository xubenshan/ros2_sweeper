#!/usr/bin/env python3
# SPDX-License-Identifier: Apache-2.0
"""Exercise live Nav2, LiDAR wall following, teleop and a coverage checkpoint."""
import json
import math
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import time

from action_msgs.msg import GoalStatus
from ament_index_python.packages import get_package_prefix
from geometry_msgs.msg import Twist
from lifecycle_msgs.srv import GetState
from nav2_msgs.action import NavigateToPose
from nav_msgs.msg import Odometry
import rclpy
from rclpy.action import ActionClient
from rclpy.qos import DurabilityPolicy, QoSProfile, qos_profile_sensor_data
from robot_cleaning_interfaces.action import CleanTask
from robot_cleaning_interfaces.msg import CoverageStatus
from std_msgs.msg import Bool, String
from std_srvs.srv import Trigger

from generate_sweeper_scenarios import generate
from run_cleaning_benchmark import ROOT, stop, stop_gazebo_partition
from verify_navigation import wait


def verify(node, checkpoints, report):
    latched = QoSProfile(depth=1, durability=DurabilityPolicy.TRANSIENT_LOCAL)
    state = {}
    samples = []
    feedback = []
    manager = None
    for topic in ('/motion/source', '/contour_follower/state', '/cleaning/state'):
        node.create_subscription(String, topic, lambda msg, key=topic: state.update(
            {key: msg.data}), latched)
    node.create_subscription(Odometry, '/odom', lambda msg: state.update(
        odom=(msg.pose.pose.position.x, msg.pose.pose.position.y)), qos_profile_sensor_data)
    node.create_subscription(Twist, '/cmd_vel', lambda msg: state.update(
        cmd=(msg.linear.x, msg.angular.z)), 10)
    node.create_subscription(CoverageStatus, '/cleaning/coverage_status', samples.append, latched)
    control = node.create_publisher(String, '/motion/control', 10)
    edge_enable = node.create_publisher(Bool, '/contour_follower/enable', 10)
    teleop = node.create_publisher(Twist, '/cmd_vel_teleop', 10)
    nav = ActionClient(node, NavigateToPose, '/navigate_to_pose')
    task = ActionClient(node, CleanTask, '/cleaning/task')
    lifecycle = node.create_client(GetState, '/bt_navigator/get_state')
    pause = node.create_client(Trigger, '/cleaning/pause')

    def ready():
        if not lifecycle.service_is_ready():
            return False
        reply = lifecycle.call_async(GetState.Request())
        wait(node, reply.done, 8, 'Nav2 lifecycle reply')
        return reply.result().current_state.id == 3

    def set_source(name, expected):
        control.publish(String(data=name))
        wait(node, lambda: state.get('/motion/source') == expected, 10, expected + ' authority')

    def result_of(future, timeout, label):
        wait(node, future.done, timeout, label)
        return future.result()

    def start_manager():
        nonlocal manager
        package = 'robot_cleaning_manager'
        binary = Path(get_package_prefix(package)) / 'lib' / package / 'cleaning_task_manager_node'
        manager = subprocess.Popen([
            str(binary), '--ros-args', '-p', 'use_sim_time:=true',
            '-p', 'use_coverage_planner:=true', '-p', f'checkpoint_dir:={checkpoints}',
        ], start_new_session=True, stdout=sys.stderr)
        wait(node, task.server_is_ready, 25, 'cleaning task server')

    def send_cleaning(restore=False):
        feedback.clear()
        handle = result_of(task.send_goal_async(CleanTask.Goal(
            task_id='gazebo-grid-restart', mode=CleanTask.Goal.ALL, target_coverage=.995,
            resume_checkpoint=restore), feedback_callback=lambda msg: feedback.append(msg.feedback)),
            15, 'cleaning action acceptance')
        assert handle.accepted
        return handle

    def covered(msg):
        return {i for i, value in enumerate(msg.covered.data) if value == 100}

    wait(node, lambda: 'odom' in state and edge_enable.get_subscription_count(), 85, 'Gazebo and edge node')
    wait(node, ready, 80, 'active Nav2')
    wait(node, nav.server_is_ready, 10, 'Nav2 action')
    assert {item.node_name for item in node.get_publishers_info_by_topic('/cmd_vel')} == {'cmd_vel_arbiter'}
    report['cmd_vel_publisher'] = 'cmd_vel_arbiter'
    set_source('nav', 'nav')
    before = state['odom']
    goal = NavigateToPose.Goal()
    goal.pose.header.frame_id = 'map'
    goal.pose.pose.position.x, goal.pose.pose.position.y = -.65, -.71
    goal.pose.pose.orientation.w = 1.
    handle = result_of(nav.send_goal_async(goal), 12, 'navigation acceptance')
    assert handle.accepted
    driven = result_of(handle.get_result_async(), 60, 'navigation before handoff')
    assert driven.status == GoalStatus.STATUS_SUCCEEDED, driven
    report['nav_displacement_m'] = math.dist(before, state['odom'])
    assert report['nav_displacement_m'] >= .20

    set_source('edge', 'edge')
    edge_enable.publish(Bool(data=True))
    wait(node, lambda: state.get('/contour_follower/state') == 'FOLLOW'
         and state.get('cmd', (0, 0))[0] > .03, 30, 'live contour following')
    before = state['odom']
    wait(node, lambda: math.dist(before, state['odom']) >= .18, 20, 'edge displacement')
    report['edge_displacement_m'] = math.dist(before, state['odom'])
    report['edge_state'] = state['/contour_follower/state']

    set_source('teleop', 'teleop')
    edge_enable.publish(Bool(data=False))
    before = state['odom']
    reverse = Twist()
    reverse.linear.x = -.13
    deadline = time.monotonic() + 12
    while math.dist(before, state['odom']) < .12 and time.monotonic() < deadline:
        teleop.publish(reverse)
        rclpy.spin_once(node, timeout_sec=.02)
        time.sleep(.03)
    report['teleop_displacement_m'] = math.dist(before, state['odom'])
    assert report['teleop_displacement_m'] >= .12
    wait(node, lambda: state.get('cmd') == (0., 0.), 2, 'teleop watchdog stop')
    set_source('auto', 'none')
    report['teleop_watchdog_stopped'] = True

    try:
        start_manager()
        send_cleaning()
        wait(node, lambda: feedback and feedback[-1].completed_waypoints >= 2 and
             samples and len(covered(samples[-1])) >= 30, 100, 'covered grid and two waypoints')
        assert result_of(pause.call_async(Trigger.Request()), 10, 'pause response').success
        wait(node, lambda: feedback and feedback[-1].state == 'PAUSED', 15, 'paused checkpoint')
        completed = feedback[-1].completed_waypoints
        checkpoint = Path(checkpoints) / 'gazebo-grid-restart.checkpoint'
        assert checkpoint.is_file()
        stop(manager)
        wait(node, lambda: not task.server_is_ready(), 15, 'previous manager exit')
        with checkpoint.open('rb') as stream:
            stream.readline()
            stream.readline()
            for _ in range(int(stream.readline())):
                stream.readline()
            saved = {i for i, value in enumerate(stream.read(int(stream.readline()))) if value == 100}
        assert len(saved) >= 30
        initial_stamp = samples[-1].covered.header.stamp
        samples.clear()
        start_manager()
        restored = send_cleaning(True)
        wait(node, lambda: any(sample.covered.header.stamp != initial_stamp and
                              saved == covered(sample) for sample in samples),
             40, 'exact coverage grid restored')
        wait(node, lambda: feedback and feedback[-1].completed_waypoints > completed and
             samples and len(covered(samples[-1])) > len(saved), 100, 'new coverage after restart')
        report.update(covered_before_restart=len(saved), covered_restored=len(saved),
                      covered_after_resuming=len(covered(samples[-1])),
                      waypoints_before_restart=completed,
                      waypoints_after_resuming=feedback[-1].completed_waypoints)
        assert result_of(restored.cancel_goal_async(), 12, 'cancel response').goals_canceling
        canceled = result_of(restored.get_result_async(), 20, 'cancel result')
        assert canceled.status == GoalStatus.STATUS_CANCELED
        report['cancel_status'] = canceled.status
    finally:
        stop(manager)


def main():
    output = Path(sys.argv[1]).resolve()
    generate(output, 'multi_room')
    partition = f'sweeper_handoff_{os.getpid()}'
    os.environ['GZ_PARTITION'] = partition
    rclpy.init()
    node = rclpy.create_node('verify_gazebo_handoff')
    report = {}
    with tempfile.TemporaryDirectory(prefix='sweeper-gazebo-checkpoint-') as checkpoints, (
        output / 'launch.log'
    ).open('w') as log:
        launch = subprocess.Popen([
            str(ROOT / 'scripts/run_sweeper.sh'), 'implementation:=cpp', 'task_manager:=false',
            'edge_controller:=true', 'gui:=false', 'enable_tof:=false', 'x:=-1.02', 'y:=-0.71',
            f'world:={output / "scene.world"}', f'map:={output / "map.yaml"}',
        ], stdout=log, stderr=subprocess.STDOUT, start_new_session=True)
        try:
            verify(node, checkpoints, report)
            report['success'] = True
        except (AssertionError, RuntimeError) as error:
            report.update(success=False, error=str(error))
            raise
        finally:
            stop(launch)
            stop_gazebo_partition(partition)
            node.destroy_node()
            rclpy.shutdown()
            (output / 'result.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
