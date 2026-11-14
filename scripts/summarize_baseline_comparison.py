#!/usr/bin/env python3
"""Create the reproducible optimized-versus-baseline result tables."""
import argparse
import csv
import json
from pathlib import Path


SCENARIO_ORDER = ('multi_room', 'islands', 'narrow', 'l_shape', 'furniture')
DISPLAY = {
    'multi_room': '双房间',
    'islands': '岛状障碍',
    'narrow': '窄通道',
    'l_shape': 'L 形多房间',
    'furniture': '复杂家具',
}


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('experiment_root', type=Path)
    args = parser.parse_args()
    root = args.experiment_root.resolve()
    selected = {}
    for result_file in root.rglob('result.json'):
        result = json.loads(result_file.read_text())
        key = (result.get('scenario'), result.get('coverage_algorithm'))
        if (key[0] not in SCENARIO_ORDER or key[1] not in ('optimized', 'baseline')):
            continue
        if not result.get('measurement_valid'):
            continue
        if key in selected:
            raise RuntimeError(f'duplicate valid result for {key}: {result_file}')
        result['result_file'] = str(result_file.relative_to(root.parent.parent))
        selected[key] = result
    expected = {(scene, algorithm) for scene in SCENARIO_ORDER
                for algorithm in ('optimized', 'baseline')}
    if selected.keys() != expected:
        raise RuntimeError(f'missing results: {sorted(expected - selected.keys())}')

    rows = []
    for scene in SCENARIO_ORDER:
        for algorithm in ('optimized', 'baseline'):
            result = selected[(scene, algorithm)]
            rows.append({
                'scene': scene,
                'scene_zh': DISPLAY[scene],
                'algorithm': algorithm,
                'action_status': result['action_status'],
                'action_success': result['success'],
                'measurement_valid': result['measurement_valid'],
                'truth_coverage': result['ratio'],
                'runtime_coverage': result['task_coverage'],
                'coverage_error_pp': 100 * (result['task_coverage'] - result['ratio']),
                'truth_path_m': result['truth_path_m'],
                'path_to_90_m': result.get('path_to_90_m'),
                'path_efficiency': result['efficiency'],
                'revisit_ratio': result['revisit_ratio'],
                'gap_passes': result['gap_passes'],
                'completed_waypoints': result['completed_waypoints'],
                'failed_waypoints': result['failed_waypoints'],
                'nav_goal_success_rate': result['nav_goal_success_rate'],
                'termination_reason': result['reason'],
                'result_file': result['result_file'],
            })

    csv_path = root / 'comparison.csv'
    with csv_path.open('w', newline='') as stream:
        writer = csv.DictWriter(
            stream, fieldnames=rows[0].keys(), lineterminator="\n")
        writer.writeheader()
        writer.writerows(rows)
    (root / 'comparison.json').write_text(json.dumps(rows, indent=2, ensure_ascii=False) + '\n')

    lines = [
        '# 覆盖规划基线对照结果', '',
        '所有数值均来自本轮 Gazebo 真值轨迹；每个场景、每种算法一轮有效仿真。', '',
        '| 场景 | 算法 | Action | 真值覆盖率 | 运行时覆盖率 | 实际里程 | 到 90% 里程 | 路径效率 | 重复行驶率 | 补扫轮次 |',
        '|---|---|---:|---:|---:|---:|---:|---:|---:|---:|',
    ]
    for row in rows:
        lines.append(
            f"| {row['scene_zh']} | {row['algorithm']} | "
            f"{'成功' if row['action_success'] else '失败'} | "
            f"{row['truth_coverage']:.2%} | {row['runtime_coverage']:.2%} | "
            f"{row['truth_path_m']:.2f} m | {row['path_to_90_m']:.2f} m | "
            f"{row['path_efficiency']:.2%} | {row['revisit_ratio']:.2%} | "
            f"{row['gap_passes']} |")
    lines.extend(['', '## 优化算法相对基线', '',
        '| 场景 | 到 90% 节省里程 | 最终节省里程 | 效率变化 | 重复行驶率变化 |',
        '|---|---:|---:|---:|---:|'])
    for scene in SCENARIO_ORDER:
        optimized = selected[(scene, 'optimized')]
        baseline = selected[(scene, 'baseline')]
        lines.append(
            f"| {DISPLAY[scene]} | "
            f"{baseline['path_to_90_m'] - optimized['path_to_90_m']:+.2f} m | "
            f"{baseline['truth_path_m'] - optimized['truth_path_m']:+.2f} m | "
            f"{100 * (optimized['efficiency'] - baseline['efficiency']):+.2f} pp | "
            f"{100 * (optimized['revisit_ratio'] - baseline['revisit_ratio']):+.2f} pp |")
    lines.extend(['',
        '正的“节省里程”表示优化算法更短；重复行驶率变化为负表示优化算法更少重复。',
        'L 形场景中基线到达 90% 的里程更短，原始结果予以保留。', ''])
    report = '\n'.join(lines)
    (root / 'comparison.md').write_text(report)
    print(report)


if __name__ == '__main__':
    main()
