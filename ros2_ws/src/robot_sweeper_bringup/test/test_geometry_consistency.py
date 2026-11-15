# SPDX-License-Identifier: Apache-2.0
import copy
import importlib.util
import math
import os
from pathlib import Path
import xml.etree.ElementTree as ET

import pytest
import xacro
import yaml


SOURCE_ROOT = Path(os.environ['SWEEPER_SOURCE_ROOT'])
MODEL_ROOT = SOURCE_ROOT / 'upstream' / 'oomwoo_ws' / 'oomwoo-one'
GEOMETRY_FILE = MODEL_ROOT / 'config' / 'robot_geometry.yaml'
ROBOT_XACRO = MODEL_ROOT / 'urdf' / 'robot.urdf.xacro'
LAUNCH_FILE = SOURCE_ROOT / 'robot_sweeper_bringup' / 'launch' / 'sweeper.launch.py'


def load_launch_module():
    spec = importlib.util.spec_from_file_location('sweeper_launch_geometry_test', LAUNCH_FILE)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def expanded_robot(geometry_file=GEOMETRY_FILE):
    document = xacro.process_file(
        str(ROBOT_XACRO),
        mappings={
            'geometry_file': str(geometry_file),
            'odom_source': 'robot_wheels',
            'enable_tof': 'true',
        },
    ).toxml()
    return ET.fromstring(document)


def wheel_dimensions(robot, side):
    cylinder = robot.find(
        f"./link[@name='wheel_{side}_link']/visual/geometry/cylinder")
    assert cylinder is not None
    return float(cylinder.attrib['radius']), float(cylinder.attrib['length'])


def wheel_joint_y(robot, side):
    origin = robot.find(f"./joint[@name='wheel_{side}_joint']/origin")
    assert origin is not None
    return float(origin.attrib['xyz'].split()[1])


def body_envelope_radius(robot):
    body = robot.find("./link[@name='base_link']")
    assert body is not None
    maximum = 0.0
    collisions = [
        collision for collision in body.findall('collision')
        if collision.attrib.get('name', '').startswith('bumper_')
    ]
    assert collisions
    for collision in collisions:
        origin = collision.find('origin')
        box = collision.find('geometry/box')
        assert origin is not None and box is not None
        x, y, _ = (float(value) for value in origin.attrib['xyz'].split())
        _, _, yaw = (float(value) for value in origin.attrib['rpy'].split())
        width, thickness, _ = (float(value) for value in box.attrib['size'].split())
        for dx in (-width / 2.0, width / 2.0):
            for dy in (-thickness / 2.0, thickness / 2.0):
                px = x + math.cos(yaw) * dx - math.sin(yaw) * dy
                py = y + math.sin(yaw) * dx + math.cos(yaw) * dy
                maximum = max(maximum, math.hypot(px, py))
    return maximum


def assert_expanded_geometry(robot, geometry):
    left_radius, left_width = wheel_dimensions(robot, 'left')
    right_radius, right_width = wheel_dimensions(robot, 'right')
    assert left_radius == pytest.approx(geometry['wheel_radius'])
    assert right_radius == pytest.approx(geometry['wheel_radius'])
    assert left_width == pytest.approx(geometry['wheel_width'])
    assert right_width == pytest.approx(geometry['wheel_width'])
    separation = wheel_joint_y(robot, 'left') - wheel_joint_y(robot, 'right')
    assert separation == pytest.approx(geometry['wheel_separation'])
    assert body_envelope_radius(robot) == pytest.approx(geometry['robot_radius'], abs=1e-6)

    plugin = robot.find(".//plugin[@filename='gz-sim-diff-drive-system']")
    assert plugin is not None
    assert float(plugin.findtext('wheel_separation')) == pytest.approx(
        geometry['wheel_separation'])
    assert float(plugin.findtext('wheel_radius')) == pytest.approx(geometry['wheel_radius'])


def test_geometry_drives_xacro_gazebo_and_runtime_consumers():
    launch = load_launch_module()
    geometry = launch.load_robot_geometry(GEOMETRY_FILE)
    consumers = launch.application_geometry_parameters(geometry)
    rewrites = launch.navigation_geometry_rewrites(geometry)

    assert_expanded_geometry(expanded_robot(), geometry)
    assert consumers['planner']['robot_radius'] == geometry['robot_radius']
    assert consumers['planner']['cleaning_radius'] == geometry['cleaning_radius']
    assert consumers['manager']['cleaning_radius'] == geometry['cleaning_radius']
    assert consumers['meter']['cleaning_radius'] == geometry['cleaning_radius']
    assert consumers['meter']['robot_radius'] == geometry['robot_radius']
    assert rewrites[
        'local_costmap.local_costmap.ros__parameters.robot_radius'] == str(
        geometry['robot_radius'])
    assert rewrites[
        'global_costmap.global_costmap.ros__parameters.robot_radius'] == str(
        geometry['robot_radius'])


def test_runtime_configs_do_not_redeclare_physical_geometry():
    with open(SOURCE_ROOT / 'robot_coverage_planner' / 'config' / 'regions.yaml',
              encoding='utf-8') as config_file:
        planner = yaml.safe_load(config_file)['coverage_planner']['ros__parameters']
    with open(SOURCE_ROOT / 'robot_cleaning_manager' / 'config' / 'task_manager.yaml',
              encoding='utf-8') as config_file:
        manager = yaml.safe_load(config_file)['cleaning_task_manager']['ros__parameters']
    assert 'robot_radius' not in planner
    assert 'cleaning_radius' not in planner
    assert 'cleaning_radius' not in manager

    nav_files = [
        MODEL_ROOT / 'config' / 'navigation.yaml',
        SOURCE_ROOT / 'upstream' / 'oomwoo_ws' / 'oomwoo-ros2-tools' /
        'src' / 'oomwoo_sim_support' / 'config' / 'nav2_params.yaml',
    ]
    for nav_file in nav_files:
        with open(nav_file, encoding='utf-8') as config_file:
            config = yaml.safe_load(config_file)
        for costmap_name in ('local_costmap', 'global_costmap'):
            parameters = config[costmap_name][costmap_name]['ros__parameters']
            assert 'robot_radius' not in parameters


def test_changing_one_yaml_updates_every_consumer(tmp_path):
    with open(GEOMETRY_FILE, encoding='utf-8') as config_file:
        document = yaml.safe_load(config_file)
    modified = copy.deepcopy(document)
    modified['base']['radius_m'] = 0.19
    modified['drive_wheels']['radius_m'] = 0.04
    modified['drive_wheels']['width_m'] = 0.014
    modified['drive_wheels']['center_separation_m'] = 0.26
    modified['cleaning']['radius_m'] = 0.23
    changed_file = tmp_path / 'robot_geometry.yaml'
    changed_file.write_text(yaml.safe_dump(modified), encoding='utf-8')

    launch = load_launch_module()
    geometry = launch.load_robot_geometry(changed_file)
    consumers = launch.application_geometry_parameters(geometry)
    assert_expanded_geometry(expanded_robot(changed_file), geometry)
    assert consumers['planner']['robot_radius'] == 0.19
    assert consumers['planner']['cleaning_radius'] == 0.23
    assert consumers['manager']['cleaning_radius'] == 0.23
    assert consumers['meter'] == {'cleaning_radius': 0.23, 'robot_radius': 0.19}
    assert launch.navigation_geometry_rewrites(geometry)[
        'global_costmap.global_costmap.ros__parameters.robot_radius'] == '0.19'
