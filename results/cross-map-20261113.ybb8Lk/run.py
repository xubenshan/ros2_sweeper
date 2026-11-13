"""Run the unmodified project benchmark against frozen new fixtures."""
import argparse
import json
from pathlib import Path
import shutil
import sys

from scenes import ROOT, SCENES
import run_cleaning_benchmark as benchmark

FREEZE = Path(__file__).resolve().parent
PARAMETERS = json.loads((FREEZE / 'freeze/benchmark-arguments.json').read_text())

def copy_fixture(destination, scene, world_name):
    if world_name != 'default':
        raise ValueError(world_name)
    for name in ('scene.world', 'map.yaml', 'map.pgm', 'regions.yaml', 'geometry.json'):
        shutil.copyfile(FREEZE / 'scenes' / scene / name, destination / name)

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('scene', choices=SCENES)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--domain', type=int, required=True)
    args = parser.parse_args()
    if args.output.exists():
        parser.error('Choose a new output directory')
    benchmark.SCENARIOS = tuple(SCENES)
    benchmark.generate = copy_fixture
    benchmark.ROOT = FREEZE / 'launcher'
    args.output.mkdir(parents=True)
    for slot in range(1, 4):
        for attempt in range(1, 5):
            output = args.output / f'run-{slot}' / f'attempt-{attempt}'
            domain = args.domain + (slot - 1) * 4 + attempt - 1
            sys.argv = ['run_cleaning_benchmark.py', *PARAMETERS, '--scenario', args.scene,
                        '--runs', '1', '--startup-retries', '0', '--domain', str(domain),
                        '--output', str(output)]
            print(f'{args.scene}: run {slot}, attempt {attempt}, domain {domain}', flush=True)
            try:
                benchmark.main()
            except SystemExit as exc:
                if exc.code not in (0, 1):
                    raise
            report_path = output / args.scene / 'run-1/result.json'
            report = json.loads(report_path.read_text())
            report['effective_launch_command'] = [
                'enable_tof:=true' if arg == 'enable_tof:=false' else arg
                for arg in report['command']
            ]
            report_path.write_text(json.dumps(report, indent=2) + '\n')
            if report.get('measurement_valid') and report.get('action_status') in (4, 5, 6):
                (args.output / f'run-{slot}/valid-result.txt').write_text(
                    str(report_path.relative_to(args.output)) + '\n')
                break
        else:
            raise SystemExit(f'No valid simulation for {args.scene} run {slot}')
