"""Plot the benchmark's final coverage grid and its reported coverage over distance."""
import csv
import json
from pathlib import Path
import re
import sys
import tempfile

import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap
from matplotlib.font_manager import fontManager
from fontTools import subset
from fontTools.ttLib import TTCollection
from matplotlib.lines import Line2D
from matplotlib.patches import Patch, Rectangle
import numpy as np
from PIL import Image
import yaml

from oomwoo_sim_support.coverage_meter_node import _dilate, _flood_fill, _nearest_free

folder = Path(sys.argv[1])
out = Path(__file__).resolve().parent
report = json.loads((folder / 'result.json').read_text())
grid = json.loads((folder / 'coverage-grids.json').read_text())
meta = yaml.safe_load((out / 'living_room.yaml').read_text())
assert report['measurement_valid']
width, height = grid['width'], grid['height']
res = grid['resolution']
ox, oy = grid['origin']
pixels = np.flipud(np.array(Image.open(out / meta['image']).convert('L')))
assert pixels.shape == (height, width)
assert np.allclose(meta['origin'], [ox, oy, 0]) and np.isclose(meta['resolution'], res)
with (folder / 'pose-comparison.csv').open() as stream:
    poses = list(csv.DictReader(stream))
log = (folder / 'launch.log').read_text()
start_y, start_x = map(int, re.search(r'serviceable cells from start \((\d+), (\d+)\)', log).groups())
occupancy = (255.0 - pixels) / 255.0
free = occupancy < meta['free_thresh']
occupied = occupancy > meta['occupied_thresh']
reachable = _flood_fill(free, _nearest_free(free, start_x, start_y))
cleaning_radius, robot_radius, edge_margin = .20, .1745, .15
drivable = reachable & ~_dilate(~free, round(robot_radius / res))
target = _dilate(drivable, round(cleaning_radius / res)) & reachable
target &= ~_dilate(~free, round(edge_margin / res))
covered = np.asarray(grid['truth']).reshape(height, width) == 100
assert np.count_nonzero(target) == report['truth_target_cells']
assert not np.any(covered & ~target)
assert abs(covered.sum() / target.sum() - report['ratio']) < 1e-6

cols = ['#f0f3f7', '#384454', '#f6af78', '#44ae9d']
floor = np.zeros((height, width), dtype=np.uint8)
floor[occupied] = 1
floor[target] = 2
floor[covered] = 3
extent = (ox, ox + width * res, oy, oy + height * res)
route = np.array([(float(p['stamp_ns']) / 1e9, float(p['truth_x']), float(p['truth_y']))
                  for p in poses if p['state'] == 'RUNNING'])
rows = np.array([(float(m[2]), 100 * float(m[1]))
                 for m in re.finditer(
                     r'COVERAGE_REPORT coverage=([\d.]+).*?path_m=([\d.]+)', log)])
if not len(route) or not len(rows):
    raise ValueError('The benchmark did not retain the required trajectory or metric samples')

# Matplotlib reads the first face in a font collection. Register the SC
# face separately, with just the characters used in this figure.
font_tmp = tempfile.TemporaryDirectory()
font_path = Path(font_tmp.name) / 'NotoSansCJKsc.otf'
collection = TTCollection('/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc')
font = next(face for face in collection.fonts if face['name'].getDebugName(1) == 'Noto Sans CJK SC')
subsetter = subset.Subsetter()
subsetter.populate(text=Path(__file__).read_text() + ''.join(chr(i) for i in range(32, 127)))
subsetter.subset(font)
font.save(font_path)
fontManager.addfont(font_path)

plt.rcParams.update({'font.family': 'sans-serif',
                     'font.sans-serif': ['Noto Sans CJK SC', 'DejaVu Sans'],
                     'axes.unicode_minus': False, 'font.size': 11,
                     'axes.labelcolor': '#425066', 'text.color': '#172d43'})
fig = plt.figure(figsize=(11, 7.1), facecolor='white')
layout = fig.add_gridspec(2, 2, left=.075, right=.96, top=.83, bottom=.14, wspace=.27,
                          hspace=.35, width_ratios=(1.05, 1), height_ratios=(1, .22))
ax = fig.add_subplot(layout[:, 0])
chart = fig.add_subplot(layout[0, 1])
key = fig.add_subplot(layout[1, 1])
fig.text(.076, .925, '正式客厅 · 整屋清扫复测', size=22, weight='bold')
fig.text(.077, .872,
         f"真值覆盖率 {report['ratio']:.2%}    ·    路径效率 {report['efficiency']:.2%}"
         f"    ·    实际里程 {report['truth_path_m']:.2f} m",
         size=13, color='#40576b')

ax.imshow(floor, origin='lower', extent=extent, cmap=ListedColormap(cols),
          interpolation='nearest', vmin=0, vmax=3)
# Keep lines disconnected if the recorded samples have a time gap.
route_x, route_y = route[:, 1].copy(), route[:, 2].copy()
discontinuous = np.flatnonzero(np.diff(route[:, 0]) > .75) + 1
route_x[discontinuous] = np.nan
route_y[discontinuous] = np.nan
ax.plot(route_x, route_y, color='#174b79', alpha=.67, lw=.9)
ax.scatter(route[0, 1], route[0, 2], s=40, color='white', edgecolor='#174b79', zorder=4)
ax.scatter(route[-1, 1], route[-1, 2], s=40, color='#174b79', edgecolor='white', zorder=4)
ax.add_patch(Rectangle((-.40, -.23), .80, .26, fill=False, linestyle='--',
                       linewidth=1.3, edgecolor='#732d57', zorder=4))
ax.set(title='覆盖栅格与 Gazebo 实际轨迹', xlabel='地图 X（m）', ylabel='地图 Y（m）')
ax.set_aspect('equal')
ax.spines[['top', 'right']].set_visible(False)
ax.set_xticks([-2, -1, 0, 1, 2])
ax.set_yticks([-2, -1, 0, 1, 2])

curve_color = '#13796f'
chart.plot(rows[:, 0], rows[:, 1], color=curve_color, lw=2.2)
chart.axhline(report['requested_coverage'] * 100, color='#b05933', ls='--', lw=1)
chart.scatter(report['truth_path_m'], report['ratio'] * 100, s=50, color=curve_color, zorder=3)
chart.text(.02, .935, f"覆盖目标 {report['requested_coverage']:.0%}",
           transform=chart.transAxes, fontsize=10, color='#a6502b')
chart.set(xlim=(0, max(rows[:, 0]) * 1.075), ylim=(0, 102), title='覆盖率随实际里程变化',
          xlabel='累计实际里程（m）', ylabel='真值覆盖率（%）')
chart.set_yticks([0, 20, 40, 60, 80, 100])
chart.grid(axis='y', color='#dfe6ed')
chart.set_axisbelow(True)
chart.spines[['top', 'right']].set_visible(False)

key.axis('off')
key.legend(handles=[Patch(color=cols[3], label='已覆盖'), Patch(color=cols[2], label='漏扫'),
                    Patch(color=cols[1], label='障碍'), Patch(color=cols[0], label='未纳入统计'),
                    Line2D([], [], color='#174b79', lw=1.5, label='机器人轨迹'),
                    Line2D([], [], color='#732d57', ls='--', label='茶几与沙发间通道核心区')],
           ncol=2, loc='center left', frameon=False, columnspacing=1.35)
fig.text(.077, .055, f"覆盖 {covered.sum():,} / {target.sum():,} 格。每格 5 厘米，"
         f"清扫宽度 40 厘米。路径效率 = {report['ideal_path_m']:.2f} m ÷ 实际里程。",
         size=10, color='#40576b')
fig.savefig(out / 'living-room-coverage.png', dpi=175)
font_tmp.cleanup()
