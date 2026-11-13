#!/usr/bin/env python3
# SPDX-License-Identifier: Apache-2.0
"""Inject velocity-source, contact, estop and heartbeat faults into the arbiter."""
import json
from pathlib import Path
import subprocess
import time

import rclpy
from ament_index_python.packages import get_package_prefix
from geometry_msgs.msg import Twist
from ros_gz_interfaces.msg import Contact, Contacts
from std_msgs.msg import Empty, String
from std_srvs.srv import SetBool

from run_cleaning_benchmark import stop
from verify_navigation import wait


def main():
    rclpy.init()
    node = rclpy.create_node('verify_motion_safety')
    nav = node.create_publisher(Twist, '/motion/nav', 10)
    teleop = node.create_publisher(Twist, '/cmd_vel_teleop', 10)
    edge = node.create_publisher(Twist, '/cmd_vel_edge', 10)
    reverse = node.create_publisher(Twist, '/cmd_vel_recovery', 10)
    control = node.create_publisher(String, '/motion/control', 10)
    state = node.create_publisher(String, '/cleaning/state', rclpy.qos.QoSProfile(
        depth=1, durability=rclpy.qos.DurabilityPolicy.TRANSIENT_LOCAL))
    heartbeat = node.create_publisher(Empty, '/cleaning/heartbeat', 10)
    bumper = node.create_publisher(Contacts, '/bumper_left/contact', 10)
    estop = node.create_client(SetBool, '/motion/estop')
    observed = []
    node.create_subscription(Twist, '/cmd_vel', lambda msg: observed.append(
        (time.monotonic(), msg.linear.x, msg.angular.z)), 10)
    process = None

    def drive(publisher, speed, duration, beat=False):
        deadline = time.monotonic() + duration
        while time.monotonic() < deadline:
            message = Twist()
            message.linear.x = speed
            publisher.publish(message)
            if beat:
                heartbeat.publish(Empty())
            rclpy.spin_once(node, timeout_sec=.025)
            time.sleep(.012)

    def latest_zero():
        return observed and abs(observed[-1][1]) < 1e-6 and abs(observed[-1][2]) < 1e-6

    def set_estop(enabled):
        request = SetBool.Request(data=enabled)
        future = estop.call_async(request)
        wait(node, future.done, 3, 'estop response')
        assert future.result().success

    try:
        binary = Path(get_package_prefix('robot_motion_safety')) / 'lib/robot_motion_safety/cmd_vel_arbiter'
        process = subprocess.Popen([str(binary)], start_new_session=True)
        wait(node, lambda: estop.service_is_ready() and observed and nav.get_subscription_count()
             and state.get_subscription_count(), 10, 'arbiter')
        state.publish(String(data='RUNNING'))
        drive(nav, .13, .45, beat=True)
        wait(node, lambda: observed[-1][1] > .1, 3, 'navigation authority')
        control.publish(String(data='teleop'))
        drive(teleop, .24, .55)
        wait(node, lambda: observed[-1][1] > .20, 3, 'teleop authority')
        began = time.monotonic()
        wait(node, latest_zero, 1, 'stale teleop watchdog')
        watchdog = time.monotonic() - began
        assert watchdog <= .45
        control.publish(String(data='edge'))
        drive(edge, .20, .35)
        wait(node, lambda: observed[-1][1] > .15, 3, 'edge authority')
        started = time.monotonic()
        set_estop(True)
        wait(node, latest_zero, .25, 'estop output')
        estop_latency = time.monotonic() - started
        drive(edge, .20, .20)
        assert latest_zero()
        set_estop(False)
        state.publish(String(data='RUNNING'))
        drive(nav, .18, .35, beat=True)
        wait(node, lambda: observed[-1][1] > .15, 3, 'navigation after estop')
        bumper.publish(Contacts(contacts=[Contact()]))
        wait(node, latest_zero, .25, 'bumper stop')
        state.publish(String(data='RECOVERING'))
        drive(reverse, -.12, .40, beat=True)
        wait(node, lambda: observed[-1][1] < -.08, 3, 'reverse recovery authority')
        state.publish(String(data='PAUSED'))
        wait(node, latest_zero, .25, 'pause during recovery')
        state.publish(String(data='RUNNING'))
        drive(nav, .13, .35, beat=True)
        wait(node, lambda: observed[-1][1] > .10, 3, 'navigation after recovery')
        drive(nav, .13, .65)
        assert latest_zero()
        print(json.dumps({'source_handoff': True, 'watchdog_wall_s': watchdog,
                          'estop_wall_s': estop_latency, 'contact_stop': True,
                          'recovery_pause': True, 'heartbeat_loss': True}, indent=2))
    finally:
        stop(process)
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
