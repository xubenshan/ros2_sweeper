# SPDX-License-Identifier: Apache-2.0
"""Run the OOMWOO model with mapping or saved-map Nav2."""
from pathlib import Path
import shlex
import tempfile
import xml.etree.ElementTree as ET

from ament_index_python.packages import get_package_share_path
from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument, EmitEvent, GroupAction, IncludeLaunchDescription,
    LogInfo, OpaqueFunction, RegisterEventHandler, SetEnvironmentVariable,
)
from launch.event_handlers import OnProcessExit, OnShutdown
from launch.events import Shutdown
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node, SetRemap
from launch_ros.parameter_descriptions import ParameterValue
from nav2_common.launch import RewrittenYaml

import xacro
import yaml

OPEN_FLOOR_EDGE_MARGIN_M = 0.15
SAFE_GAP_MARGIN_M = 0.065
GAP_EDGE_PRIORITY_MARGIN_M = 0.15
DEFAULT_PLANNER_SAFETY_MARGIN_M = 0.005
CLEARANCE_CONTROLLER_PROFILE = {
    'use_cost_regulated_linear_velocity_scaling': 'true',
    'inflation_cost_scaling_factor': None,
    'cost_scaling_dist': '0.30',
    'cost_scaling_gain': '0.70',
    'min_approach_linear_velocity': '0.07',
    'regulated_linear_scaling_min_speed': '0.06',
    'lookahead_dist': '0.22',
}
FRONT_TOF_PROFILE = {
    'topic': '/tof_front/points',
    'data_type': 'PointCloud2',
    'min_obstacle_height': '0.025',
    'max_obstacle_height': '0.15',
    'obstacle_min_range': '0.02',
    'obstacle_max_range': '0.75',
    'raytrace_max_range': '0.85',
    'observation_persistence': '0.40',
    'marking': 'true',
    'clearing': 'true',
}


def include(package, launch_file, **arguments):
    path = get_package_share_path(package) / 'launch' / launch_file
    return IncludeLaunchDescription(
        PythonLaunchDescriptionSource(str(path)), launch_arguments=arguments.items())


def load_robot_geometry(path):
    with open(path, encoding='utf-8') as geometry_file:
        document = yaml.safe_load(geometry_file)
    if not isinstance(document, dict) or document.get('schema_version') != 1:
        raise ValueError('robot_geometry.yaml must use schema_version 1')
    try:
        frames = document['frames']
        geometry = {
            'map_frame': str(frames['global']),
            'odom_frame': str(frames['odom']),
            'base_footprint_frame': str(frames['base_footprint']),
            'base_link_frame': str(frames['base_link']),
            'robot_radius': float(document['base']['radius_m']),
            'wheel_radius': float(document['drive_wheels']['radius_m']),
            'wheel_width': float(document['drive_wheels']['width_m']),
            'wheel_separation': float(document['drive_wheels']['center_separation_m']),
            'cleaning_radius': float(document['cleaning']['radius_m']),
        }
    except (KeyError, TypeError, ValueError) as error:
        raise ValueError('robot_geometry.yaml is missing a required geometry field') from error
    frame_values = [value for key, value in geometry.items() if key.endswith('_frame')]
    numeric_values = [value for key, value in geometry.items() if not key.endswith('_frame')]
    if any(not value for value in frame_values) or any(value <= 0.0 for value in numeric_values):
        raise ValueError('robot_geometry.yaml frames must be non-empty and dimensions positive')
    return geometry


def navigation_geometry_rewrites(geometry):
    radius = str(geometry['robot_radius'])
    return {
        'local_costmap.local_costmap.ros__parameters.robot_radius': radius,
        'global_costmap.global_costmap.ros__parameters.robot_radius': radius,
        'local_costmap.local_costmap.ros__parameters.global_frame': geometry['odom_frame'],
        'local_costmap.local_costmap.ros__parameters.robot_base_frame':
            geometry['base_link_frame'],
        'global_costmap.global_costmap.ros__parameters.global_frame': geometry['map_frame'],
        'global_costmap.global_costmap.ros__parameters.robot_base_frame':
            geometry['base_link_frame'],
    }


def application_geometry_parameters(geometry):
    return {
        'planner': {
            'robot_radius': geometry['robot_radius'],
            'cleaning_radius': geometry['cleaning_radius'],
            'base_frame': geometry['base_footprint_frame'],
            'odom_frame': geometry['odom_frame'],
        },
        'manager': {
            'cleaning_radius': geometry['cleaning_radius'],
            'map_frame': geometry['map_frame'],
            'base_frame': geometry['base_footprint_frame'],
        },
        'meter': {
            'cleaning_radius': geometry['cleaning_radius'],
            'robot_radius': geometry['robot_radius'],
        },
        'localization': {
            'map_frame': geometry['map_frame'],
            'base_frame': geometry['base_footprint_frame'],
        },
    }


def configure_navigation_params(
    params, context, use_tof, collision_aware, clearance_control, sweep_goal_tolerance,
    direct_sweep_navigation, coverage_aware_navigation, geometry,
):
    with open(params, encoding='utf-8') as config_file:
        config = yaml.safe_load(config_file)
    rewrites = navigation_geometry_rewrites(geometry)
    # RewrittenYaml only converts scalar values; planner_plugins is added to the
    # generated YAML below so the ROS parameter keeps its native list type.
    if sweep_goal_tolerance:
        controller_params = config['controller_server']['ros__parameters']
        checker = controller_params.get('goal_checker_plugins', ['goal_checker'])[0]
        rewrites[f'controller_server.ros__parameters.{checker}.xy_goal_tolerance'] = (
            sweep_goal_tolerance)
    if collision_aware:
        controller = 'controller_server.ros__parameters.FollowPath'
        rewrites[f'{controller}.use_collision_detection'] = 'true'
        rewrites[f'{controller}.max_allowed_time_to_collision_up_to_carrot'] = '0.5'
        if clearance_control:
            local = config['local_costmap']['local_costmap']['ros__parameters']
            scaling = local.get('inflation_layer', {}).get('cost_scaling_factor', 10.0)
            profile = dict(CLEARANCE_CONTROLLER_PROFILE)
            profile['inflation_cost_scaling_factor'] = str(float(scaling))
            for key, value in profile.items():
                rewrites[f'{controller}.{key}'] = value
    for name in ('local_costmap', 'global_costmap'):
        costmap = config.get(name, {}).get(name, {}).get('ros__parameters', {})
        prefix = f'{name}.{name}.ros__parameters'
        if collision_aware and 'inflation_layer' in costmap.get('plugins', ()):
            inflation = costmap.get('inflation_layer', {}).get('inflation_radius', 0.0)
            rewrites[f'{prefix}.inflation_layer.inflation_radius'] = str(
                max(inflation, 0.30 if clearance_control else 0.20))
        obstacle = costmap.get('obstacle_layer', {})
        if (not use_tof or 'obstacle_layer' not in costmap.get('plugins', ()) or
                not obstacle.get('enabled', True)):
            continue
        sources = obstacle.get('observation_sources', '').split()
        if 'front_tof' in sources:
            continue
        prefix = f'{prefix}.obstacle_layer'
        rewrites[f'{prefix}.observation_sources'] = ' '.join([*sources, 'front_tof'])
        for key, value in FRONT_TOF_PROFILE.items():
            rewrites[f'{prefix}.front_tof.{key}'] = value
    rewritten = RewrittenYaml(
        source_file=params, param_rewrites=rewrites, convert_types=True).perform(context)
    if direct_sweep_navigation or coverage_aware_navigation:
        with open(rewritten, encoding='utf-8') as config_file:
            rewritten_config = yaml.safe_load(config_file)
        planner_parameters = rewritten_config['planner_server']['ros__parameters']
        planners = planner_parameters['planner_plugins']
        planner_id = 'CoverageAware' if coverage_aware_navigation else 'CoverageDirect'
        if planner_id not in planners:
            planners.append(planner_id)
        planner_parameters[planner_id] = {
            'plugin': 'robot_coverage_planner::CoverageDirectPlanner',
            'strategy': 'coverage_aware' if coverage_aware_navigation else 'direct',
        }
        if coverage_aware_navigation:
            planner_parameters[planner_id].update({
                'coverage_cleaning_radius': 0.20,
                'max_detour_ratio': 1.25,
                'max_detour_distance': 0.75,
                'coverage_weight': 0.35,
                'min_coverage_gain_m2': 0.0025,
                'min_coverage_gain_per_extra_meter': 0.05,
                'min_score_gain_m': 0.03,
            })
        if not coverage_aware_navigation:
            planner_parameters[planner_id].update({
                'maximum_direct_length': 1.20,
                'maximum_direct_cost': 220,
                'sampling_step': 0.025,
            })
        with open(rewritten, 'w', encoding='utf-8') as config_file:
            yaml.safe_dump(rewritten_config, config_file, sort_keys=False)
    return rewritten


def configure(context):
    def value(name):
        return LaunchConfiguration(name).perform(context)

    model = get_package_share_path('oomwoo_one')
    bringup = get_package_share_path('robot_sweeper_bringup')
    geometry_file = model / 'config' / 'robot_geometry.yaml'
    geometry = load_robot_geometry(geometry_file)
    geometry_parameters = application_geometry_parameters(geometry)
    gazebo = get_package_share_path('oomwoo_gazebo')
    support = get_package_share_path('oomwoo_sim_support')
    world = gazebo / 'worlds' / value('world')
    world_name = ET.parse(world).getroot().find('world').attrib['name']
    map_file = value('map') or str(support / 'maps' / 'living_room.yaml')
    mode = value('mode')
    sim_time = value('use_sim_time') == 'true'
    gui = value('gui') == 'true'
    seed_x = float(value('initial_x') or value('x'))
    seed_y = float(value('initial_y') or value('y'))
    seed_yaw = float(value('initial_yaw') or value('yaw'))
    benchmark_nav = value('benchmark_nav') == 'true'
    params = value('nav_params') or str(
        support / 'config' / 'nav2_params.yaml' if benchmark_nav else
        model / 'config' / 'navigation.yaml')
    if value('implementation') == 'legacy':
        if mode != 'localize':
            raise ValueError('Legacy coverage uses an existing map')
        if world_name != 'default':
            raise ValueError('The upstream legacy bridge requires an SDF world named default')
        return [include('oomwoo_sim_support', 'coverage_regression.launch.py',
                        world=str(world), map=map_file, gui=value('gui'),
                        x_pose=value('x'), y_pose=value('y'), yaw=value('yaw'))]

    use_tof = (value('implementation') == 'cpp' and value('enable_tof') == 'true'
               and value('tof_costmap') == 'true')
    clearance_control = value('clearance_control') == 'true'
    direct_sweep_navigation = value('direct_sweep_navigation') == 'true'
    coverage_aware_navigation = value('coverage_aware_navigation') == 'true'
    if direct_sweep_navigation and coverage_aware_navigation:
        raise RuntimeError('Choose either direct_sweep_navigation or coverage_aware_navigation')
    collision_aware = (clearance_control or direct_sweep_navigation or coverage_aware_navigation or
                       value('collision_aware_nav') == 'true')
    sweep_goal_tolerance = value('sweep_goal_tolerance')
    params = configure_navigation_params(
        params, context, use_tof, collision_aware, clearance_control, sweep_goal_tolerance,
        direct_sweep_navigation, coverage_aware_navigation, geometry)

    robot = xacro.process_file(str(model / 'urdf' / 'robot.urdf.xacro'), mappings={
        'odom_source': value('odom_source'), 'enable_tof': value('enable_tof'),
        'geometry_file': str(geometry_file)}).toxml()
    gz_args = ('-r -v 2 ' if gui else '-s -r --headless-rendering -v 2 ') + shlex.quote(str(world))
    bridge_config = model / 'config' / 'gz_bridge.yaml'
    bridge_cleanup = []
    if world_name != 'default':
        bridge_dir = tempfile.TemporaryDirectory(prefix='sweeper-bridge-')
        with bridge_config.open(encoding='utf-8') as config_file:
            mappings = yaml.safe_load(config_file)
        for mapping in mappings:
            topic = mapping.get('gz_topic_name', '')
            if topic.startswith('/world/default/'):
                mapping['gz_topic_name'] = topic.replace('/world/default/', f'/world/{world_name}/', 1)
        bridge_config = Path(bridge_dir.name) / bridge_config.name
        bridge_config.write_text(yaml.safe_dump(mappings), encoding='utf-8')

        def clean_bridge(_context):
            bridge_dir.cleanup()
            return []

        bridge_cleanup.append(RegisterEventHandler(OnShutdown(on_shutdown=[
            OpaqueFunction(function=clean_bridge)])))
    spawn = Node(
        package='ros_gz_sim', executable='create', output='screen',
        arguments=['-world', world_name, '-name', 'oomwoo_one',
                   '-topic', 'robot_description', '-timeout', '60',
                   '-x', value('x'), '-y', value('y'), '-z', '0.06',
                   '-Y', value('yaw'), '-allow_renaming', 'false'])
    stack = [*bridge_cleanup,
        SetEnvironmentVariable('GZ_SIM_RESOURCE_PATH', str(gazebo / 'models')),
        include('ros_gz_sim', 'gz_sim.launch.py', gz_args=gz_args, on_exit_shutdown='true'),
        Node(package='robot_state_publisher', executable='robot_state_publisher',
             parameters=[{'robot_description': ParameterValue(robot, value_type=str),
                          'use_sim_time': sim_time}], output='screen'),
        Node(package='ros_gz_bridge', executable='parameter_bridge', output='screen',
             parameters=[{'config_file': str(bridge_config),
                          'use_sim_time': sim_time}]),
    ]

    gap_tree = ''
    sweep_tree = ''
    pose_tree = ''
    through_tree = ''
    gap_controller = {}
    tree_dir = None
    bt_dir = get_package_share_path('nav2_bt_navigator') / 'behavior_trees'
    with open(params, encoding='utf-8') as nav_file:
        controller = yaml.safe_load(nav_file)['controller_server']['ros__parameters']
    checkers = controller.get('goal_checker_plugins', ['goal_checker'])

    def customized_tree(template, filename, checker='', planner=''):
        nonlocal tree_dir
        if tree_dir is None:
            tree_dir = tempfile.TemporaryDirectory(prefix='sweeper-bt-')
        behavior = ET.parse(bt_dir / template)
        if checker:
            for follow in behavior.iter('FollowPath'):
                follow.set('goal_checker_id', checker)
        if planner:
            for sequence in behavior.iter('PipelineSequence'):
                for selector in list(sequence):
                    if selector.tag == 'PlannerSelector':
                        sequence.remove(selector)
            for compute in behavior.iter('ComputePathToPose'):
                compute.set('planner_id', planner)
        destination = Path(tree_dir.name) / filename
        behavior.write(destination, encoding='utf-8', xml_declaration=True)
        return str(destination)

    if direct_sweep_navigation:
        sweep_tree = customized_tree(
            'navigate_to_pose_w_replanning_and_recovery.xml',
            'navigate_coverage_sweep.xml', checker=checkers[0], planner='CoverageDirect')
    elif coverage_aware_navigation:
        sweep_tree = customized_tree(
            'navigate_to_pose_w_replanning_and_recovery.xml',
            'navigate_coverage_aware_sweep.xml', checker=checkers[0], planner='CoverageAware')

    if benchmark_nav and mode == 'localize' and value('implementation') == 'cpp' and (
        value('precise_gap_navigation') == 'true'
    ):
        pose_template = 'navigate_to_pose_w_replanning_and_recovery.xml'
        gap_tree = customized_tree(
            pose_template, 'navigate_gap.xml', checker='coverage_gap_checker')
        pose_tree = customized_tree(pose_template, 'navigate_pose.xml', checker=checkers[0])
        through_tree = customized_tree(
            'navigate_through_poses_w_replanning_and_recovery.xml',
            'navigate_through.xml', checker=checkers[0])
        gap_controller = {
            'goal_checker_plugins': [*checkers, 'coverage_gap_checker'],
            'coverage_gap_checker.plugin': 'nav2_controller::SimpleGoalChecker',
            'coverage_gap_checker.xy_goal_tolerance': float(value('gap_goal_tolerance')),
            'coverage_gap_checker.yaw_goal_tolerance': 3.2,
            'coverage_gap_checker.stateful': True,
        }

    if tree_dir is not None:
        def clean_tree(_context):
            tree_dir.cleanup()
            return []

        stack.append(RegisterEventHandler(OnShutdown(on_shutdown=[
            OpaqueFunction(function=clean_tree)])))

    def after_spawn(event, _context):
        if event.returncode:
            return [LogInfo(msg='Could not spawn oomwoo_one'),
                    EmitEvent(event=Shutdown(reason='Gazebo spawn failed'))]
        if mode == 'none':
            return []
        nav = include('nav2_bringup', 'navigation_launch.py',
                      use_sim_time=value('use_sim_time'), params_file=params,
                      use_composition='False', autostart='true')
        result = []
        amcl_settings = {'use_sim_time': sim_time, 'set_initial_pose': True,
                         'initial_pose.x': seed_x, 'initial_pose.y': seed_y,
                         'initial_pose.yaw': seed_yaw}
        if benchmark_nav:
            amcl_settings.update(update_min_d=0.15, update_min_a=0.10,
                                 z_hit=0.95, z_rand=0.05, max_beams=120)
        if mode == 'localize':
            result.extend([
                Node(package='nav2_map_server', executable='map_server', name='map_server',
                     parameters=[{'yaml_filename': map_file, 'use_sim_time': sim_time}],
                     output='screen'),
                Node(package='nav2_amcl', executable='amcl', name='amcl', output='screen',
                     parameters=[params, amcl_settings]),
                Node(package='nav2_lifecycle_manager', executable='lifecycle_manager',
                     name='lifecycle_manager_localization', output='screen',
                     parameters=[{'use_sim_time': sim_time, 'autostart': True,
                                  'node_names': ['map_server', 'amcl']}]),
            ])
            seed = Node(package='oomwoo_sim_support', executable='initialpose_pub', output='screen',
                        parameters=[{'use_sim_time': sim_time, 'x': seed_x,
                                     'y': seed_y, 'yaw': seed_yaw}])
            result.append(seed)
        else:
            result.append(include('nav2_bringup', 'slam_launch.py',
                                  use_sim_time=value('use_sim_time'), params_file=params,
                                  autostart='true'))
        safety = value('implementation') == 'cpp' and value('safety') == 'true'
        nav_output = '/motion/nav' if safety else value('nav_output')
        if benchmark_nav and mode == 'localize':
            bt_dir = get_package_share_path('nav2_bt_navigator') / 'behavior_trees'
            servers = [('nav2_controller', 'controller_server'),
                       ('nav2_planner', 'planner_server'),
                       ('nav2_behaviors', 'behavior_server'),
                       ('nav2_bt_navigator', 'bt_navigator')]
            navigation = [
                Node(package=package, executable=name, name=name, output='screen',
                     parameters=[params, {'use_sim_time': sim_time}] +
                     ([gap_controller] if name == 'controller_server' and gap_controller else []) +
                     ([{'default_nav_to_pose_bt_xml': pose_tree or str(
                         bt_dir / 'navigate_to_pose_w_replanning_and_recovery.xml'),
                        'default_nav_through_poses_bt_xml': through_tree or str(
                            bt_dir / 'navigate_through_poses_w_replanning_and_recovery.xml')}]
                      if name == 'bt_navigator' else []),
                     remappings=[('cmd_vel', nav_output)])
                for package, name in servers
            ]
            navigation.append(Node(
                package='nav2_lifecycle_manager', executable='lifecycle_manager',
                name='lifecycle_manager_navigation', output='screen',
                parameters=[{'use_sim_time': sim_time, 'autostart': True, 'bond_timeout': 0.0,
                             'node_names': [name for _, name in servers]}]))
            result.insert(0, RegisterEventHandler(OnProcessExit(
                target_action=seed, on_exit=navigation)))
        else:
            nav_group = GroupAction([SetRemap(src='/cmd_vel', dst=nav_output), nav])
            if mode == 'localize':
                result.insert(0, RegisterEventHandler(OnProcessExit(
                    target_action=seed, on_exit=[nav_group])))
            else:
                result.append(nav_group)
        if safety:
            result.append(Node(package='robot_motion_safety', executable='cmd_vel_arbiter',
                               parameters=[{'use_sim_time': sim_time}], output='screen'))
            if value('edge_controller') == 'true':
                result.append(Node(
                    package='oomwoo_clean', executable='contour_follower',
                    parameters=[{'use_sim_time': sim_time, 'auto_start': False}],
                    remappings=[('cmd_vel', '/cmd_vel_edge')], output='screen'))
        if mode == 'slam' and value('explore') == 'true':
            result.append(include('oomwoo_bringup', 'explore.launch.py',
                                  use_sim_time=value('use_sim_time')))
        if value('implementation') == 'cpp':
            coverage = get_package_share_path('robot_coverage_planner')
            regions = value('regions') or str(coverage / 'config' / 'regions.yaml')
            with open(regions, encoding='utf-8') as region_file:
                coverage_parameters = yaml.safe_load(region_file)['coverage_planner']['ros__parameters']
            planner_overrides = {'use_sim_time': sim_time,
                                 **geometry_parameters['planner'],
                                 'planning_algorithm': value('coverage_algorithm'),
                                 'target_gap_coverage': value('target_gap_coverage') == 'true',
                                 'gap_use_local_costmap': value('guard_gap_goals') == 'true',
                                 'continuous_coverage_tracking':
                                     value('continuous_coverage_tracking') == 'true'}
            open_floor = value('open_floor') == 'true'
            if open_floor:
                planner_overrides['edge_margin'] = OPEN_FLOOR_EDGE_MARGIN_M
                planner_overrides['refine_sweep'] = value('refine_sweep') == 'true'
                planner_overrides['sweep_use_live_costmap'] = value('sweep_use_live_costmap') == 'true'
            if value('sweep_safety_margin'):
                planner_overrides['sweep_safety_margin'] = float(value('sweep_safety_margin'))
            safe_gap = value('safe_gap') == 'true'
            if safe_gap:
                planner_overrides.update(
                    gap_safety_margin=max(
                        SAFE_GAP_MARGIN_M,
                        float(coverage_parameters.get(
                            'safety_margin', DEFAULT_PLANNER_SAFETY_MARGIN_M))),
                    gap_edge_priority_margin=GAP_EDGE_PRIORITY_MARGIN_M,
                )
            if value('gap_safety_margin'):
                planner_overrides['gap_safety_margin'] = float(value('gap_safety_margin'))
            result.append(Node(
                package='robot_cleaning_manager',
                executable='localization_health_monitor_node',
                parameters=[{'use_sim_time': sim_time,
                             'covariance_required': mode == 'localize',
                             **geometry_parameters['localization']}], output='screen'))
            result.append(Node(package='robot_coverage_planner', executable='coverage_planner_node',
                               parameters=[regions, planner_overrides], output='screen'))
            if value('task_manager') == 'true':
                manager_config = (get_package_share_path('robot_cleaning_manager') /
                                  'config' / 'task_manager.yaml')
                result.append(Node(package='robot_cleaning_manager', executable='cleaning_task_manager_node',
                     parameters=[str(manager_config),
                                 {'use_sim_time': sim_time, 'use_coverage_planner': True,
                                  **geometry_parameters['manager'],
                                  'defer_blocked_sweep_goals': open_floor,
                                  'adjust_blocked_gap_goals': value('guard_gap_goals') == 'true',
                                  'sweep_behavior_tree': sweep_tree,
                                  'gap_behavior_tree': gap_tree,
                                  'early_gap_replan': value('early_gap_replan') == 'true',
                                  'gap_progress_timeout_s': int(value('gap_progress_timeout_s')),
                                  'gap_navigation_retries': int(value('gap_navigation_retries')),
                                  'max_gap_passes': int(value('max_gap_passes')),
                                  'coverage_completion_margin': float(value('coverage_completion_margin')),
                                  'target_path_efficiency': float(value('gap_efficiency_target')),
                                  'gap_failure_replan_threshold': 2 if safe_gap else 0}],
                     output='screen'))
        if value('evaluate') == 'true':
            result.extend([
                Node(package='oomwoo_sim_support', executable='ground_truth', output='screen',
                     parameters=[{'use_sim_time': sim_time, 'spawn_x': seed_x,
                                  'spawn_y': seed_y, 'spawn_yaw': seed_yaw}],
                     remappings=[('~/pose', '/ground_truth/pose')]),
                Node(package='oomwoo_sim_support', executable='coverage_meter', output='screen',
                     parameters=[{'use_sim_time': sim_time,
                                  **geometry_parameters['meter'],
                                  'coverage_target': 0.90}],
                     remappings=[('cleaning_active', '/cleaning/active')]),
            ])
        if value('rviz') == 'true':
            rviz_config = value('rviz_config') or str(bringup / 'rviz' / 'cleaning.rviz')
            result.append(Node(
                package='rviz2', executable='rviz2', output='screen',
                arguments=['-d', rviz_config],
                parameters=[{'use_sim_time': sim_time}]))
        return result

    return stack + [RegisterEventHandler(OnProcessExit(
        target_action=spawn, on_exit=after_spawn)), spawn]


def generate_launch_description():
    boolean = ['true', 'false']
    return LaunchDescription([
        DeclareLaunchArgument('world', default_value='living_room.world'),
        DeclareLaunchArgument('map', default_value=''),
        DeclareLaunchArgument('mode', default_value='localize', choices=['none', 'slam', 'localize']),
        DeclareLaunchArgument('implementation', default_value='core', choices=['core', 'legacy', 'cpp']),
        DeclareLaunchArgument('x', default_value='0.32'),
        DeclareLaunchArgument('y', default_value='1.59'),
        DeclareLaunchArgument('yaw', default_value='0.0'),
        DeclareLaunchArgument('initial_x', default_value=''),
        DeclareLaunchArgument('initial_y', default_value=''),
        DeclareLaunchArgument('initial_yaw', default_value=''),
        DeclareLaunchArgument('gui', default_value='true', choices=boolean),
        DeclareLaunchArgument('rviz', default_value='false', choices=boolean),
        DeclareLaunchArgument('rviz_config', default_value=''),
        DeclareLaunchArgument('explore', default_value='false', choices=boolean),
        DeclareLaunchArgument('enable_tof', default_value='true', choices=boolean),
        DeclareLaunchArgument('tof_costmap', default_value='true', choices=boolean),
        DeclareLaunchArgument('collision_aware_nav', default_value='true', choices=boolean),
        DeclareLaunchArgument('clearance_control', default_value='true', choices=boolean),
        DeclareLaunchArgument('precise_gap_navigation', default_value='true', choices=boolean),
        DeclareLaunchArgument('early_gap_replan', default_value='true', choices=boolean),
        DeclareLaunchArgument('gap_progress_timeout_s', default_value='35'),
        DeclareLaunchArgument('gap_navigation_retries', default_value='1'),
        DeclareLaunchArgument('max_gap_passes', default_value='3'),
        DeclareLaunchArgument('gap_efficiency_target', default_value='0.8'),
        DeclareLaunchArgument('coverage_completion_margin', default_value='0.01'),
        DeclareLaunchArgument('use_sim_time', default_value='true', choices=boolean),
        DeclareLaunchArgument('odom_source', default_value='robot_wheels',
                              choices=['robot_wheels', 'ground_truth']),
        DeclareLaunchArgument('nav_params', default_value=''),
        DeclareLaunchArgument('benchmark_nav', default_value='false', choices=boolean),
        DeclareLaunchArgument('regions', default_value=''),
        DeclareLaunchArgument('sweep_safety_margin', default_value=''),
        DeclareLaunchArgument('gap_safety_margin', default_value=''),
        DeclareLaunchArgument('sweep_goal_tolerance', default_value='0.10'),
        DeclareLaunchArgument('gap_goal_tolerance', default_value='0.10'),
        DeclareLaunchArgument('safe_gap', default_value='false', choices=boolean),
        DeclareLaunchArgument('target_gap_coverage', default_value='true', choices=boolean),
        DeclareLaunchArgument('coverage_algorithm', default_value='optimized',
                              choices=['optimized', 'baseline']),
        DeclareLaunchArgument('guard_gap_goals', default_value='true', choices=boolean),
        DeclareLaunchArgument('open_floor', default_value='true', choices=boolean),
        DeclareLaunchArgument('continuous_coverage_tracking', default_value='false', choices=boolean),
        DeclareLaunchArgument('refine_sweep', default_value='true', choices=boolean),
        DeclareLaunchArgument('sweep_use_live_costmap', default_value='true', choices=boolean),
        # Optional experiment: preserve short, collision-checked sweep connectors.
        # CoverageDirectPlanner falls back to NavFn for unsafe or longer transits.
        DeclareLaunchArgument('direct_sweep_navigation', default_value='false', choices=boolean),
        DeclareLaunchArgument('coverage_aware_navigation', default_value='false', choices=boolean),
        DeclareLaunchArgument('safety', default_value='true', choices=boolean),
        DeclareLaunchArgument('task_manager', default_value='true', choices=boolean),
        DeclareLaunchArgument('evaluate', default_value='false', choices=boolean),
        DeclareLaunchArgument('edge_controller', default_value='false', choices=boolean),
        DeclareLaunchArgument('nav_output', default_value='/cmd_vel'),
        OpaqueFunction(function=configure),
    ])
