# SPDX-License-Identifier: Apache-2.0
import os
from pathlib import Path

import yaml


SOURCE_ROOT = Path(os.environ['SWEEPER_SOURCE_ROOT'])
BRINGUP_ROOT = SOURCE_ROOT / 'robot_sweeper_bringup'
RVIZ_FILE = BRINGUP_ROOT / 'rviz' / 'cleaning.rviz'
LAUNCH_FILE = BRINGUP_ROOT / 'launch' / 'sweeper.launch.py'


def displays_by_name(displays):
    result = {}
    for display in displays:
        result[display['Name']] = display
        result.update(displays_by_name(display.get('Displays', [])))
    return result


def test_cleaning_rviz_contains_required_task_layers():
    config = yaml.safe_load(RVIZ_FILE.read_text(encoding='utf-8'))
    displays = displays_by_name(config['Visualization Manager']['Displays'])

    assert displays['RobotModel']['Enabled']
    assert displays['Cleaning']['Enabled']
    expected_topics = {
        'Runtime Covered Grid': '/cleaning/covered_grid',
        'Gazebo Truth Covered Grid': '/coverage_meter/covered_grid',
        'Coverage Plan': '/cleaning/planner_path',
        'Active Task Route': '/cleaning/path',
        'Current Cleaning Goal': '/cleaning/current_goal',
    }
    for name, topic in expected_topics.items():
        assert displays[name]['Topic']['Value'] == topic

    assert displays['Runtime Covered Grid']['Enabled']
    assert not displays['Gazebo Truth Covered Grid']['Enabled']
    assert displays['Coverage Plan']['Enabled']
    assert displays['Active Task Route']['Enabled']
    assert displays['Current Cleaning Goal']['Enabled']


def test_launch_defaults_to_dedicated_cleaning_rviz():
    launch = LAUNCH_FILE.read_text(encoding='utf-8')
    assert "DeclareLaunchArgument('rviz_config', default_value='')" in launch
    assert "bringup / 'rviz' / 'cleaning.rviz'" in launch
    assert "arguments=['-d', rviz_config]" in launch
