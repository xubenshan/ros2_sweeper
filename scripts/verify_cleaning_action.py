#!/usr/bin/env python3
# SPDX-License-Identifier: Apache-2.0
"""Exercise the cleaning lifecycle against a running Gazebo/Nav2 launch."""
import json
import os
from pathlib import Path
import signal
import subprocess
import tempfile
import time

import rclpy
from action_msgs.msg import GoalStatus
from ament_index_python.packages import get_package_prefix, get_package_share_path
from rclpy.action import ActionClient
from robot_cleaning_interfaces.action import CleanTask
from std_srvs.srv import Trigger

from verify_navigation import wait


def main():
    rclpy.init()
    node = rclpy.create_node('verify_cleaning_action')
    action = ActionClient(node, CleanTask, '/cleaning/task')
    pause = node.create_client(Trigger, '/cleaning/pause')
    resume = node.create_client(Trigger, '/cleaning/resume')
    feedback = []
    manager = None

    def stop_manager():
        nonlocal manager
        if manager is not None and manager.poll() is None:
            manager.send_signal(signal.SIGINT)
            try:
                manager.wait(timeout=8)
            except subprocess.TimeoutExpired:
                manager.kill()
                manager.wait()
        manager = None

    def start_manager(directory):
        nonlocal manager
        package = 'robot_cleaning_manager'
        prefix = Path(get_package_prefix(package))
        config = get_package_share_path(package) / 'config' / 'routes.yaml'
        manager = subprocess.Popen(
            [str(prefix / 'lib' / package / 'cleaning_task_manager_node'),
             '--ros-args', '--params-file', str(config), '-p', 'use_sim_time:=true',
             '-p', f'checkpoint_dir:={directory}'], env=os.environ)

    def task(task_id, regions, from_checkpoint=False):
        wait(node, action.server_is_ready, 30, 'cleaning action')
        request = CleanTask.Goal()
        request.task_id = task_id
        request.mode = CleanTask.Goal.REGIONS
        request.regions = regions
        request.target_coverage = 0.85
        request.resume_checkpoint = from_checkpoint
        feedback.clear()
        future = action.send_goal_async(request, feedback_callback=lambda msg: feedback.append(msg.feedback))
        wait(node, future.done, 15, 'goal acceptance')
        goal = future.result()
        assert goal.accepted
        return goal, goal.get_result_async()

    def call(client, retry=False):
        wait(node, client.service_is_ready, 15, 'task service')
        deadline = time.monotonic() + 20
        while True:
            response = client.call_async(Trigger.Request())
            wait(node, response.done, 10, 'service response')
            if response.result().success:
                return
            if not retry or time.monotonic() > deadline:
                raise RuntimeError(response.result().message)
            rclpy.spin_once(node, timeout_sec=.3)

    def progressed(state, count=0):
        return bool(feedback and feedback[-1].state == state
                    and feedback[-1].completed_waypoints >= count)

    try:
        with tempfile.TemporaryDirectory(prefix='sweeper-action-') as directory:
            start_manager(directory)
            _, result = task('full-route', ['north_west'])
            wait(node, result.done, 165, 'successful cleaning route')
            done = result.result()
            assert done.status == GoalStatus.STATUS_SUCCEEDED, done
            assert done.result.completed_waypoints == 3 and done.result.path_length_m > 0.5, done
            _, old_result = task('restart-route', ['north_east', 'north_west'])
            wait(node, lambda: progressed('RUNNING'), 30, 'running task')
            call(pause)
            wait(node, lambda: progressed('PAUSED'), 10, 'paused feedback')
            call(resume, retry=True)
            wait(node, lambda: progressed('RUNNING', 1), 75, 'resumed progress')
            call(pause)
            wait(node, lambda: progressed('PAUSED', 1), 10, 'paused checkpoint')
            completed = feedback[-1].completed_waypoints
            assert (Path(directory) / 'restart-route.checkpoint').exists()
            assert not old_result.done()
            stop_manager()
            wait(node, lambda: not action.server_is_ready(), 15, 'old server exit')
            start_manager(directory)
            goal, restored = task('restart-route', ['north_east', 'north_west'], True)
            wait(node, lambda: progressed('RUNNING', completed), 45, 'checkpoint restore')
            wait(node, lambda: progressed('RUNNING', completed + 1), 85,
                 'new waypoint after restoring the checkpoint')
            after_restart = feedback[-1].completed_waypoints
            canceled = goal.cancel_goal_async()
            wait(node, canceled.done, 12, 'cancel acknowledgement')
            assert canceled.result().goals_canceling
            wait(node, restored.done, 20, 'canceled task result')
            assert restored.result().status == GoalStatus.STATUS_CANCELED
            print(json.dumps({'successful_waypoints': done.result.completed_waypoints,
                              'successful_path_m': done.result.path_length_m,
                              'pause_resume': True, 'checkpoint_restored_at': completed,
                              'completed_after_restart': after_restart, 'cancel_status': restored.result().status}, indent=2))
    finally:
        stop_manager()
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
