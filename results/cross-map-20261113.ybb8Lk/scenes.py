"""Generate new layouts from the same collision boxes used to rasterize the maps."""
import json
from pathlib import Path
import sys
import tempfile
from xml.etree import ElementTree as ET

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'scripts'))
from generate_sweeper_scenarios import box, generate as generate_reference

SCENES = {
    'l_shape': {
        'rooms': [(-1.8, -1.30, 1.8, .40), (-1.8, .40, -.20, 1.70)],
        # 0.10 m walls centered at the outline. Partitions leave 0.90 m
        # east-west and 0.90 m north-south clear openings.
        'boxes': [
            ('west_wall', -1.8, .20, .10, 3.10, .48),
            ('south_wall', 0, -1.30, 3.70, .10, .48),
            ('east_wall', 1.8, -.45, .10, 1.80, .48),
            ('east_north_wall', .8, .40, 2.10, .10, .48),
            ('upper_east_wall', -.20, 1.05, .10, 1.40, .48),
            ('upper_north_wall', -1, 1.70, 1.70, .10, .48),
            ('north_door_west_jamb', -1.675, .40, .25, .10, .48),
            ('north_door_east_jamb', -.425, .40, .45, .10, .48),
            ('east_door_south_jamb', .20, -1.075, .10, .45, .48),
            ('east_door_north_jamb', .20, .225, .10, .35, .48),
        ],
    },
    'furniture': {
        'rooms': [(-1.8, -1.45, 1.8, 1.45)],
        'boxes': [
            ('west_wall', -1.8, 0, .10, 3.00, .48),
            ('east_wall', 1.8, 0, .10, 3.00, .48),
            ('north_wall', 0, 1.45, 3.70, .10, .48),
            ('south_wall', 0, -1.45, 3.70, .10, .48),
            ('wall_sideboard', -1.54, .94, .42, .90, .60),
            ('sectional_back', .89, 1.17, 1.38, .46, .52),
            ('sectional_return', 1.35, .70, .46, .48, .45),
            ('low_coffee_table', -.29, -.01, .76, .52, .25),
            ('bench', .83, -1.22, 1.05, .36, .38),
            ('chair', -1.32, -.94, .34, .40, .40),
        ],
    },
}

def generate(output, scenario, world_name='default'):
    geometry = SCENES[scenario]
    output.mkdir(parents=True, exist_ok=True)
    with tempfile.TemporaryDirectory() as scratch:
        reference = Path(scratch)
        generate_reference(reference, 'multi_room', world_name)
        tree = ET.parse(reference / 'scene.world')
    world = tree.getroot().find('world')
    for model in list(world.findall('model')):
        if model.get('name') != 'floor':
            world.remove(model)
    for name, x, y, width, depth, height in geometry['boxes']:
        box(world, name, x, y, width, depth, height)
    ET.indent(tree)
    tree.write(output / 'scene.world', encoding='utf-8', xml_declaration=True)

    width, height, resolution = 80, 72, .05
    ox, oy = -2.0, -1.65
    pixels = bytearray()
    for row in range(height - 1, -1, -1):
        y = oy + (row + .5) * resolution
        for column in range(width):
            x = ox + (column + .5) * resolution
            occupied = any(abs(x - cx) <= wx / 2 and abs(y - cy) <= wy / 2
                           for _, cx, cy, wx, wy, _ in geometry['boxes'])
            indoors = any(x0 <= x <= x1 and y0 <= y <= y1
                          for x0, y0, x1, y1 in geometry['rooms'])
            pixels.append(0 if occupied else 254 if indoors else 205)
    (output / 'map.pgm').write_bytes(f'P5\n{width} {height}\n255\n'.encode() + pixels)
    (output / 'map.yaml').write_text(
        'image: map.pgm\nmode: trinary\nresolution: 0.05\n'
        'origin: [-2.0, -1.65, 0.0]\nnegate: 0\noccupied_thresh: 0.65\nfree_thresh: 0.196\n')
    # Whole-map tasks use ALL. Keep shared planner values; region coordinates
    # are available for inspection but do not restrict the benchmark.
    import yaml
    config_path = ROOT / 'ros2_ws/src/robot_coverage_planner/config/regions.yaml'
    params = yaml.safe_load(config_path.read_text())['coverage_planner']['ros__parameters']
    params['region_names'] = [f'room_{i}' for i in range(1, len(geometry['rooms']) + 1)]
    params['regions'] = dict(zip(params['region_names'], geometry['rooms']))
    (output / 'regions.yaml').write_text(json.dumps(
        {'coverage_planner': {'ros__parameters': params}}, indent=2) + '\n')
    (output / 'geometry.json').write_text(json.dumps(geometry, indent=2) + '\n')

if __name__ == '__main__':
    for name in SCENES:
        generate(Path(sys.argv[1]) / name, name)
