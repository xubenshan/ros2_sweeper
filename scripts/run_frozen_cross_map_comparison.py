#!/usr/bin/env python3
"""Run one comparison algorithm against the previously frozen new-map fixtures."""
import argparse
import json
from pathlib import Path
import shutil
import sys

import run_cleaning_benchmark as benchmark


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--fixture-root', type=Path, required=True)
    parser.add_argument('--scene', choices=('l_shape', 'furniture'), required=True)
    parser.add_argument('--algorithm', choices=('optimized', 'baseline'), required=True)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--domain', type=int, required=True)
    parser.add_argument('--runs', type=int, default=1)
    args = parser.parse_args()
    fixture = args.fixture_root.resolve()
    output = args.output.resolve()
    if output.exists():
        parser.error('Choose a new output directory')
    parameters = json.loads((fixture / 'freeze/benchmark-arguments.json').read_text())

    def copy_fixture(destination, scene, world_name):
        if world_name != 'default':
            raise ValueError(f'Unexpected world name: {world_name}')
        for name in ('scene.world', 'map.yaml', 'map.pgm', 'regions.yaml', 'geometry.json'):
            shutil.copyfile(fixture / 'scenes' / scene / name, destination / name)

    benchmark.SCENARIOS = (args.scene,)
    benchmark.generate = copy_fixture
    benchmark.ROOT = fixture / 'launcher'
    sys.argv = [
        'run_cleaning_benchmark.py', *parameters,
        '--scenario', args.scene,
        '--runs', str(args.runs),
        '--startup-retries', '1',
        '--domain', str(args.domain),
        '--coverage-algorithm', args.algorithm,
        '--output', str(output),
    ]
    benchmark.main()


if __name__ == '__main__':
    main()
