#!/usr/bin/env python3
# SPDX-License-Identifier: Apache-2.0
"""Check that a rejected Nav2 cancel cannot leave a task resumable."""
import json
from pathlib import Path
import subprocess
import tempfile
import time

from action_msgs.msg import GoalStatus
from ament_index_python.packages import get_package_prefix, get_package_share_path
from lifecycle_msgs.srv import GetState
from nav2_msgs.action import NavigateToPose
from nav_msgs.msg import OccupancyGrid
import rclpy
from rclpy.action import ActionClient, ActionServer, CancelResponse
from rclpy.qos import DurabilityPolicy, QoSProfile
from robot_cleaning_interfaces.action import CleanTask
from std_srvs.srv import Trigger

from run_cleaning_benchmark import stop
from verify_navigation import wait


def main():
    rclpy.init()
    node = rclpy.create_node('nav_cancel_timeout_test')
    reached = []
    cancel_requests = []

    def navigator_state(_request, reply):
        reply.current_state.id = 3
        reply.current_state.label = 'active'
        return reply

    def reject_cancel(_goal):
        cancel_requests.append(time.monotonic())
        return CancelResponse.REJECT

    service = node.create_service(GetState, '/bt_navigator/get_state', navigator_state)
    server = ActionServer(
        node, NavigateToPose, '/navigate_to_pose', execute_callback=lambda _: None,
        handle_accepted_callback=reached.append, cancel_callback=reject_cancel)
    map_publisher = node.create_publisher(
        OccupancyGrid, '/map', QoSProfile(depth=1, durability=DurabilityPolicy.TRANSIENT_LOCAL))
    grid = OccupancyGrid()
    grid.header.frame_id = 'map'
    grid.info.width = grid.info.height = 10
    grid.info.resolution = .1
    grid.info.origin.orientation.w = 1.0
    grid.data = [0] * 100
    map_publisher.publish(grid)
    tasks = ActionClient(node, CleanTask, '/cleaning/task')
    pause = node.create_client(Trigger, '/cleaning/pause')
    resume = node.create_client(Trigger, '/cleaning/resume')
    package = 'robot_cleaning_manager'
    binary = Path(get_package_prefix(package)) / 'lib' / package / 'cleaning_task_manager_node'
    config = get_package_share_path(package) / 'config' / 'routes.yaml'
    process = None
    try:
        with tempfile.TemporaryDirectory(prefix='sweeper-cancel-') as directory:
            process = subprocess.Popen([
                str(binary), '--ros-args', '--params-file', str(config),
                '-p', f'checkpoint_dir:={directory}',
            ], start_new_session=True)
            wait(node, tasks.server_is_ready, 20, 'task server')
            sent = tasks.send_goal_async(CleanTask.Goal(
                task_id='cancel-fault', mode=CleanTask.Goal.REGIONS, regions=['north_west']))
            wait(node, sent.done, 15, 'task acceptance')
            task = sent.result()
            assert task.accepted
            outcome = task.get_result_async()
            wait(node, lambda: bool(reached), 25, 'Nav2 goal acceptance')
            started = time.monotonic()
            paused = pause.call_async(Trigger.Request())
            wait(node, paused.done, 5, 'pause request')
            assert paused.result().success
            wait(node, lambda: bool(cancel_requests), 5, 'Nav2 cancel request')
            resumed = resume.call_async(Trigger.Request())
            wait(node, resumed.done, 5, 'early resume request')
            assert not resumed.result().success
            wait(node, outcome.done, 12, 'bounded cancel failure')
            elapsed = time.monotonic() - started
            assert outcome.result().status == GoalStatus.STATUS_ABORTED
            assert outcome.result().result.reason == 'Nav2 did not acknowledge cancel; motion authority revoked'
            assert len(reached) == 1
            print(json.dumps({'action_status': outcome.result().status,
                              'reason': outcome.result().result.reason,
                              'failure_after_s': elapsed,
                              'navigation_goals': len(reached)}, indent=2))
    finally:
        stop(process)
        server.destroy()
        node.destroy_service(service)
        node.destroy_node()
        rclpy.try_shutdown()


if __name__ == '__main__':
    main()
