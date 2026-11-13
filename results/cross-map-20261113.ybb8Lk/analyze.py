"""Summarize valid benchmark runs and render the final Gazebo coverage grids."""
import csv
import json
from pathlib import Path
import re
import statistics
from collections import Counter

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
from matplotlib.lines import Line2D
from matplotlib.patches import Patch
import numpy as np
from PIL import Image
from scipy.ndimage import label
import yaml

from oomwoo_sim_support.coverage_meter_node import _dilate, _flood_fill

ROOT = Path(__file__).resolve().parent
RESULTS = ROOT / 'runs'
SCENES = {'l_shape': 'L-shaped rooms', 'furniture': 'Furniture layout'}
COLORS = ['#eff2f6', '#394859', '#fab677', '#5bbaa7']
ACTION = {4: 'SUCCEEDED', 5: 'CANCELED', 6: 'ABORTED'}
FIELDS = ('scene', 'run', 'attempt', 'action', 'ratio', 'task_coverage',
          'truth_path_m', 'efficiency', 'revisit_ratio', 'gap_passes',
          'nav_goals_failed', 'navigation_timeouts', 'failed_waypoints',
          'deferred_sweep_waypoints', 'deferred_gap_waypoints', 'contact_messages',
          'planned_waypoints', 'before_first_gap_coverage', 'truth_target_cells',
          'missing_clusters', 'largest_missing_clusters', 'pose_p95_m',
          'reason', 'wall_time_s', 'sim_time_s', 'path_to_90_m',
          'initial_room_order', 'planned_waypoints_by_route', 'gap_goals_by_room',
          'swept_cells_by_room', 'log_relative_to_output')


def figure_for(ax, scene, slot, report, folder, metadata, mask, geometry):
    log = (folder / 'launch.log').read_text()
    start_y, start_x = map(int, re.search(
        r'serviceable cells from start \((\d+), (\d+)\)', log).groups())
    grid = json.loads((folder / 'coverage-grids.json').read_text())
    width, height, res = grid['width'], grid['height'], grid['resolution']
    ox, oy = grid['origin']
    assert mask.shape == (height, width) and np.isclose(res, metadata['resolution'])
    assert np.allclose([ox, oy], metadata['origin'][:2])
    occupancy = (255.0 - mask) / 255.0
    free = occupancy < metadata['free_thresh']
    reachable = _flood_fill(free, (start_y, start_x))
    centers = reachable & ~_dilate(~free, round(.1745 / res))
    target = _dilate(centers, round(.20 / res)) & reachable & ~_dilate(~free, round(.15 / res))
    covered = np.array(grid['truth']).reshape(height, width) == 100
    assert target.sum() == report['truth_target_cells']
    assert not np.any(covered & ~target)
    assert abs(covered.sum() / target.sum() - report['ratio']) < 1e-6
    missing = target & ~covered
    clusters, n = label(missing)
    largest = sorted(np.bincount(clusters.ravel())[1:].tolist(), reverse=True)[:5]
    floor = np.zeros_like(mask)
    floor[occupancy > metadata['occupied_thresh']] = 1
    floor[target] = 2
    floor[covered] = 3
    ax.imshow(floor, origin='lower', extent=(ox, ox + width * res, oy, oy + height * res),
              interpolation='nearest', cmap=ListedColormap(COLORS), vmin=0, vmax=3)
    with (folder / 'pose-comparison.csv').open() as stream:
        poses = np.array([[int(p['stamp_ns']) / 1e9, float(p['truth_x']), float(p['truth_y'])]
                          for p in csv.DictReader(stream) if p['state'] == 'RUNNING'])
    xs, ys = poses[:, 1].copy(), poses[:, 2].copy()
    gaps = np.flatnonzero(np.diff(poses[:, 0]) > .75) + 1
    xs[gaps] = np.nan
    ys[gaps] = np.nan
    ax.plot(xs, ys, color='#174c7c', alpha=.77, lw=.9)
    ax.scatter(xs[0], ys[0], s=25, color='white', edgecolor='#174c7c', zorder=3)
    ax.scatter(xs[-1], ys[-1], s=25, color='#174c7c', edgecolor='white', zorder=3)
    ax.set_title(f"{SCENES[scene]} / run {slot}\n"
                 f"{report['ratio']:.2%} coverage · {report['efficiency']:.2%} efficiency · "
                 f"{ACTION[report['action_status']]}", fontsize=11, pad=9)
    ax.set(xlim=(-1.96, 1.96), ylim=(-1.6, 1.82),
           xticks=[-1, 0, 1], yticks=[-1, 0, 1], xlabel='X (m)', ylabel='Y (m)')
    ax.spines[['top', 'right']].set_visible(False)
    first_gap = re.search(r'gap_fill=1 waypoints=[1-9]', log)
    pre = log[:first_gap.start()] if first_gap else log
    before = re.findall(r'COVERAGE_REPORT coverage=([\d.]+)', pre)
    with (folder / 'waypoints.csv').open() as stream:
        planned = [p for p in csv.DictReader(stream) if p['type'] == 'planned']

    def room(x, y):
        if scene == 'furniture':
            return 'furniture_room'
        if y > .45:
            return 'north'
        if x > .25:
            return 'east'
        return 'west'

    route_sizes = Counter(p['route'] for p in planned)
    room_order = []
    gap_rooms = Counter()
    for p in planned:
        zone = room(float(p['x']), float(p['y']))
        if p['route'] != '1':
            gap_rooms[zone] += 1
        elif not room_order or room_order[-1] != zone:
            room_order.append(zone)
    swept = {}
    for y, x in zip(*np.nonzero(target)):
        zone = room(ox + (x + .5) * res, oy + (y + .5) * res)
        counts = swept.setdefault(zone, {'covered': 0, 'target': 0})
        counts['target'] += 1
        counts['covered'] += int(covered[y, x])
    return {
        'before_first_gap_coverage': float(before[-1]) if before else None,
        'missing_clusters': n,
        'largest_missing_clusters': largest,
        'pose_p95_m': report.get('pose_comparison', {}).get('p95_error_m'),
        'initial_room_order': ' -> '.join(room_order),
        'planned_waypoints_by_route': dict(route_sizes),
        'gap_goals_by_room': dict(gap_rooms),
        'swept_cells_by_room': swept,
    }


def main():
    fig, axes = plt.subplots(2, 3, figsize=(13.6, 8.5), layout='constrained', squeeze=False)
    fig.suptitle('Cross-map Gazebo validation  /  Coverage and executed trajectory',
                 weight='bold', fontsize=17)
    records = []
    for row, scene in enumerate(SCENES):
        assets = ROOT / 'scenes' / scene
        meta = yaml.safe_load((assets / 'map.yaml').read_text())
        mask = np.flipud(np.asarray(Image.open(assets / 'map.pgm')))
        geometry = json.loads((assets / 'geometry.json').read_text())
        for index in range(3):
            slot = index + 1
            ax = axes[row, index]
            pointer = RESULTS / scene / f'run-{slot}' / 'valid-result.txt'
            if not pointer.exists():
                ax.set_axis_off()
                continue
            result_file = RESULTS / scene / pointer.read_text().strip()
            report = json.loads(result_file.read_text())
            assert report['measurement_valid']
            data = figure_for(ax, scene, slot, report, result_file.parent, meta, mask, geometry)
            records.append(dict(report, **data, scene=scene, run=slot,
                                attempt=result_file.parts[-4],
                                action=ACTION[report['action_status']],
                                log_relative_to_output=str(result_file.relative_to(ROOT))))
    handles = [Patch(facecolor=c, label=s) for c, s in zip(
        COLORS, ['Outside evaluation', 'Obstacle', 'Missed', 'Covered'])]
    handles += [Line2D([], [], color='#174c7c', label='Gazebo trajectory')]
    fig.legend(handles=handles, loc='upper center', ncol=5,
               bbox_to_anchor=(.5, -.04), frameon=False)
    fig.savefig(ROOT / 'coverage-atlas.png', dpi=160, bbox_inches='tight')
    (ROOT / 'run-analysis.json').write_text(json.dumps(records, indent=2) + '\n')
    with (ROOT / 'run-metrics.csv').open('w', newline='') as stream:
        writer = csv.DictWriter(stream, FIELDS, extrasaction='ignore')
        writer.writeheader()
        writer.writerows(records)
    for scene in SCENES:
        samples = [r for r in records if r['scene'] == scene]
        if samples:
            print(scene, 'valid', len(samples),
                  'truth-pass', sum(r['ratio'] >= .90 for r in samples),
                  'action-pass', sum(r['action_status'] == 4 for r in samples),
                  {key: round(statistics.mean(r[key] for r in samples), 5)
                   for key in ('ratio','task_coverage','truth_path_m','efficiency','revisit_ratio')})
            for sample in samples:
                print(sample['run'], sample['action'], sample['before_first_gap_coverage'],
                      sample['ratio'], sample['efficiency'], sample['revisit_ratio'],
                      sample['gap_goals_by_room'], sample['swept_cells_by_room'])

if __name__ == '__main__':
    main()
