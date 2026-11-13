#!/usr/bin/env bash
set -eo pipefail
cd ~/robot_sweeper
source ros2_ws/install/setup.bash
source results/reliability-2026-11-12/use-cyclonedds.sh
out="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
python3 -u scripts/run_cleaning_benchmark.py --scenario living_room --runs 1 \
  --domain 57 --gui --compare-poses --target 0.90 --odom-source robot_wheels \
  --open-floor --collision-aware-nav --clearance-control --sweep-goal-tolerance 0.10 \
  --precise-gap-navigation --guard-gap-goals --refine-sweep --target-gap-coverage \
  --gap-efficiency-target 0.80 --output "$out" 2>&1 | tee "$out/benchmark.log"
