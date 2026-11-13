#!/usr/bin/env python3
# SPDX-License-Identifier: Apache-2.0
"""Exercise the live ROS graph using the same NavigateToPose interface as RViz."""
import argparse
import math
import time
import json

import rclpy
from action_msgs.msg import GoalStatus
from lifecycle_msgs.srv import GetState
from nav2_msgs.action import NavigateToPose
from nav_msgs.msg import OccupancyGrid, Odometry
from rclpy.action import ActionClient
from rclpy.qos import DurabilityPolicy, QoSProfile, qos_profile_sensor_data
from rclpy.time import Time
from sensor_msgs.msg import Imu, LaserScan
from tf2_ros import Buffer, TransformListener


def wait(node, condition, timeout, description):
    deadline = time.monotonic() + timeout
    while not condition():
        if time.monotonic() >= deadline:
            raise RuntimeError(f'Timed out waiting for {description}')
        rclpy.spin_once(node, timeout_sec=0.1)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--goal', type=float, nargs=2)
    parser.add_argument('--timeout', type=float, default=100)
    args = parser.parse_args()
    rclpy.init()
    node = rclpy.create_node('verify_sweeper_navigation')
    received = {}
    latched = QoSProfile(depth=1, durability=DurabilityPolicy.TRANSIENT_LOCAL)
    for msg_type, name, qos in (
        (LaserScan, 'scan', qos_profile_sensor_data), (Imu, 'imu', qos_profile_sensor_data),
        (Odometry, 'odom', qos_profile_sensor_data), (OccupancyGrid, 'map', latched),
    ):
        node.create_subscription(
            msg_type, '/' + name, lambda msg, key=name: received.update({key: msg}), qos)
    buffer = Buffer()
    listener = TransformListener(buffer, node)
    client = ActionClient(node, NavigateToPose, '/navigate_to_pose')

    def position():
        translation = buffer.lookup_transform('map', 'base_footprint', Time()).transform.translation
        return translation.x, translation.y

    try:
        wait(node, lambda: len(received) == 4 and buffer.can_transform(
            'map', 'base_footprint', Time()) and buffer.can_transform(
                'base_link', 'base_scan', Time()), args.timeout, 'sensors, map and TF')
        scan = received['scan']
        finite = sum(math.isfinite(value) and scan.range_min <= value <= scan.range_max
                     for value in scan.ranges)
        assert finite > 0 and scan.header.frame_id == 'base_scan'
        assert received['odom'].header.frame_id == 'odom'
        assert received['odom'].child_frame_id == 'base_footprint'
        assert received['imu'].header.frame_id == 'imu_link'
        info = received['map'].info
        details = {'scan_samples': len(scan.ranges), 'finite_ranges': finite,
                   'scan_frame': scan.header.frame_id, 'imu_frame': received['imu'].header.frame_id,
                   'odom_child': received['odom'].child_frame_id,
                   'map_size': [info.width, info.height], 'resolution': info.resolution,
                   'start': position()}
        if args.goal:
            lifecycle = node.create_client(GetState, '/bt_navigator/get_state')
            wait(node, lifecycle.service_is_ready, args.timeout, 'Nav2 lifecycle service')
            end = time.monotonic() + args.timeout
            while True:
                state = lifecycle.call_async(GetState.Request())
                wait(node, state.done, 10, 'Nav2 lifecycle state')
                if state.result().current_state.id == 3:
                    break
                if time.monotonic() >= end:
                    raise RuntimeError('Nav2 did not become active')
                rclpy.spin_once(node, timeout_sec=.25)
            wait(node, client.server_is_ready, args.timeout, 'NavigateToPose')
            goal = NavigateToPose.Goal()
            goal.pose.header.frame_id = 'map'
            goal.pose.pose.position.x, goal.pose.pose.position.y = args.goal
            goal.pose.pose.orientation.w = 1.0
            accepted = client.send_goal_async(goal)
            wait(node, accepted.done, args.timeout, 'goal response')
            handle = accepted.result()
            assert handle.accepted
            result = handle.get_result_async()
            wait(node, result.done, args.timeout, 'goal result')
            response = result.result()
            details.update(goal=args.goal, finish=position(), action_status=response.status,
                           navigation_error=response.result.error_code)
            assert response.status == GoalStatus.STATUS_SUCCEEDED, details
            assert math.dist(details['start'], details['finish']) > 0.25, details
        details['tf_publishers'] = sorted({
            endpoint.node_name for endpoint in node.get_publishers_info_by_topic('/tf')})
        print(json.dumps(details, ensure_ascii=False, indent=2))
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
