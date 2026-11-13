#!/usr/bin/env python3
# SPDX-License-Identifier: Apache-2.0
"""Exercise invalid goals and Nav2 shutdown on a dedicated Gazebo graph."""
import argparse
import json
import os
from pathlib import Path
import subprocess
import time

import rclpy
from action_msgs.msg import GoalStatus
from geometry_msgs.msg import Twist
from lifecycle_msgs.srv import GetState
from nav2_msgs.action import NavigateToPose
from nav2_msgs.srv import ManageLifecycleNodes
from rclpy.action import ActionClient
from robot_cleaning_interfaces.action import CleanTask

from generate_sweeper_scenarios import generate
from run_cleaning_benchmark import ROOT, stop, stop_gazebo_partition
from verify_navigation import wait


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--output', default='results/navigation-faults')
    output = Path(parser.parse_args().output).resolve()
    domain = os.environ.get('ROS_DOMAIN_ID', '88')
    os.environ['ROS_DOMAIN_ID'] = domain
    os.environ['ROS_AUTOMATIC_DISCOVERY_RANGE'] = 'LOCALHOST'
    partition = f'sweeper_fault_{os.getpid()}'
    os.environ['GZ_PARTITION'] = partition
    output.mkdir(parents=True, exist_ok=True)
    generate(output, 'multi_room')
    rclpy.init()
    node = rclpy.create_node('verify_navigation_faults')
    nav = ActionClient(node, NavigateToPose, '/navigate_to_pose')
    tasks = ActionClient(node, CleanTask, '/cleaning/task')
    lifecycle = node.create_client(GetState, '/bt_navigator/get_state')
    shutdown = node.create_client(ManageLifecycleNodes, '/lifecycle_manager_navigation/manage_nodes')
    commands = []
    node.create_subscription(Twist, '/cmd_vel', lambda m: commands.append(
        (time.monotonic(), m.linear.x, m.angular.z)), 10)

    def ready():
        wait(node, lambda: lifecycle.service_is_ready() and tasks.server_is_ready(),
             100, 'Nav2 and cleaning manager')
        end = time.monotonic() + 90
        while time.monotonic() < end:
            future = lifecycle.call_async(GetState.Request())
            wait(node, future.done, 5, 'navigator lifecycle')
            if future.result().current_state.id == 3 and nav.server_is_ready():
                return
            rclpy.spin_once(node, timeout_sec=.25)
        raise RuntimeError('Nav2 was never activated')

    def submit(client, request):
        pending = client.send_goal_async(request)
        wait(node, pending.done, 10, 'goal acceptance')
        assert pending.result().accepted
        return pending.result().get_result_async()

    launch = None
    with (output / 'launch.log').open('w') as log:
        try:
            launch = subprocess.Popen([
                str(ROOT / 'scripts/run_sweeper.sh'), 'implementation:=cpp', 'enable_tof:=false',
                f'world:={output / "scene.world"}', f'map:={output / "map.yaml"}',
                f'regions:={output / "regions.yaml"}', 'x:=-1.08', 'y:=0.25',
            ], stdout=log, stderr=subprocess.STDOUT, start_new_session=True)
            ready()
            impossible = NavigateToPose.Goal()
            impossible.pose.header.frame_id = 'map'
            impossible.pose.pose.position.x = 12.0
            impossible.pose.pose.position.y = 12.0
            impossible.pose.pose.orientation.w = 1.0
            invalid = submit(nav, impossible)
            wait(node, invalid.done, 100, 'invalid goal result')
            assert invalid.result().status == GoalStatus.STATUS_ABORTED
            request = CleanTask.Goal()
            request.task_id = 'nav-fault'
            request.mode = CleanTask.Goal.REGIONS
            request.regions = ['west', 'east']
            request.target_coverage = .9
            task = submit(tasks, request)
            wait(node, lambda: commands and abs(commands[-1][1]) > .08, 55, 'moving robot')
            started = time.monotonic()
            transition = shutdown.call_async(ManageLifecycleNodes.Request(
                command=ManageLifecycleNodes.Request.SHUTDOWN))
            wait(node, lambda: commands and commands[-1][0] >= started and
                 abs(commands[-1][1]) < 1e-6 and abs(commands[-1][2]) < 1e-6,
                 10, 'zero after Nav2 shutdown')
            zero = time.monotonic() - started
            wait(node, transition.done, 20, 'Nav2 shutdown response')
            assert transition.result().success
            wait(node, task.done, 25, 'cleaning task termination')
            outcome = task.result()
            assert outcome.status == GoalStatus.STATUS_ABORTED
            assert outcome.result.reason == 'Nav2 stopped during the cleaning task', outcome
            report = {'invalid_goal_status': invalid.result().status,
                      'invalid_goal_error_code': invalid.result().result.error_code,
                      'nav2_shutdown': True, 'time_to_zero_wall_s': zero,
                      'cleaning_action_status': outcome.status,
                      'reason': outcome.result.reason}
            (output / 'result.json').write_text(json.dumps(report, indent=2) + '\n')
            print(json.dumps(report, indent=2), flush=True)
        finally:
            stop(launch)
            stop_gazebo_partition(partition)
            node.destroy_node()
            rclpy.try_shutdown()


if __name__ == '__main__':
    main()
