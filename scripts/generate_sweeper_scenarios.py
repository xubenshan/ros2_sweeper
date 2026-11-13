#!/usr/bin/env python3
# SPDX-License-Identifier: Apache-2.0
"""Generate aligned Gazebo and occupancy-map fixtures from common dimensions."""
from pathlib import Path
import json
import sys
from xml.etree import ElementTree as ET


def child(parent, tag, text=None, **attributes):
    entry = ET.SubElement(parent, tag, attributes)
    if text is not None:
        entry.text = str(text)
    return entry


def box(world, name, x, y, width, depth, height):
    model = child(world, 'model', name=name)
    child(model, 'static', 'true')
    child(model, 'pose', f'{x} {y} {height / 2} 0 0 0')
    link = child(model, 'link', name='link')
    for kind in ('collision', 'visual'):
        geometry = child(child(link, kind, name=kind), 'geometry')
        child(child(geometry, 'box'), 'size', f'{width} {depth} {height}')


def generate(output, scenario, world_name='default'):
    output.mkdir(parents=True, exist_ok=True)
    root = ET.Element('sdf', version='1.8')
    world = child(root, 'world', name=world_name)
    physics = child(world, 'physics', name='sweeper', type='ode')
    child(physics, 'max_step_size', 0.005)
    child(physics, 'real_time_factor', 1)
    child(physics, 'real_time_update_rate', 200)
    for key, system in (
        ('physics', 'Physics'), ('user-commands', 'UserCommands'),
        ('scene-broadcaster', 'SceneBroadcaster'), ('contact', 'Contact'),
        ('imu', 'Imu'), ('sensors', 'Sensors'),
    ):
        plugin = child(world, 'plugin', filename=f'gz-sim-{key}-system',
                       name=f'gz::sim::systems::{system}')
        if key == 'sensors':
            child(plugin, 'render_engine', 'ogre2')
    light = child(world, 'light', name='sun', type='directional')
    child(light, 'pose', '0 0 5 0 0 0')
    child(light, 'direction', '-0.5 0.1 -1')
    child(light, 'diffuse', '0.95 0.95 0.95 1')
    box(world, 'floor', 0, 0, 8, 8, 0.1)
    world.find('model/pose').text = '0 0 -0.05 0 0 0'

    walls = [
        ('west_wall', -1.64, 0, .16, 2.36), ('east_wall', 1.64, 0, .16, 2.36),
        ('north_wall', 0, 1.14, 3.28, .16), ('south_wall', 0, -1.14, 3.28, .16),
    ]
    if scenario == 'multi_room':
        walls += [('divider_north', 0, .75, .12, .66),
                  ('divider_south', 0, -.75, .12, .66),
                  ('wardrobe', 1.2, .72, .32, .28)]
    elif scenario == 'dynamic':
        walls += [('fixture', .92, -.7, .42, .32)]
        box(world, 'moving_box', .10, -.70, .26, .28, .35)
    elif scenario == 'narrow':
        walls += [('partition_north', .02, .76, .32, .65),
                  ('partition_south', -.05, -.74, .32, .64),
                  ('furniture', .91, .64, .47, .36),
                  ('leg', -.98, -.51, .12, .12)]
    elif scenario == 'islands':
        walls += [('island_west', -.38, .25, .39, .38),
                  ('island_south', .62, -.38, .47, .30),
                  ('island_north', .69, .55, .29, .28)]
    else:
        raise ValueError(scenario)
    for name, x, y, width, height in walls:
        box(world, name, x, y, width, height, .43)

    ET.indent(root)
    ET.ElementTree(root).write(output / 'scene.world', encoding='utf-8', xml_declaration=True)
    width, height, resolution = 72, 52, .05
    ox, oy = -1.80, -1.30
    pixels = bytearray()
    for row in range(height - 1, -1, -1):
        y = oy + (row + .5) * resolution
        for column in range(width):
            x = ox + (column + .5) * resolution
            occupied = any(abs(x - cx) <= wx / 2 and abs(y - cy) <= wy / 2
                           for _, cx, cy, wx, wy in walls)
            pixels.append(0 if occupied else 205 if abs(x) > 1.65 or abs(y) > 1.16 else 254)
    (output / 'map.pgm').write_bytes(f'P5\n{width} {height}\n255\n'.encode() + pixels)
    (output / 'map.yaml').write_text(
        'image: map.pgm\nmode: trinary\nresolution: 0.05\n'
        'origin: [-1.80, -1.30, 0.0]\nnegate: 0\noccupied_thresh: 0.65\nfree_thresh: 0.196\n')
    # Keep the fault cases focused on the doorway or moving-obstacle track.
    # The multi-room fixture still sweeps both rooms end to end.
    scopes = {
        'multi_room': {'west': [-1.55, -1.05, -0.06, 1.05],
                       'east': [0.06, -1.05, 1.55, 1.05]},
        'dynamic': {'west': [-1.35, -0.45, -0.06, 0.48],
                    'east': [0.06, -0.40, 1.18, 0.54]},
        'narrow': {'west': [-1.26, -0.23, -0.06, 0.34],
                   'east': [0.06, -0.23, 1.20, 0.34]},
        'islands': {'west': [-1.55, -1.05, 0.0, 1.05],
                    'east': [0.0, -1.05, 1.55, 1.05]},
    }
    regions = {'coverage_planner': {'ros__parameters': {
        'region_names': ['west', 'east'], 'regions': scopes[scenario]}}}
    (output / 'regions.yaml').write_text(json.dumps(regions, indent=2) + '\n')


if __name__ == '__main__':
    for name in ('multi_room', 'dynamic', 'narrow', 'islands'):
        generate(Path(sys.argv[1]) / name, name)
