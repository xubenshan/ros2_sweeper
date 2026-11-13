#!/usr/bin/env bash
set -eo pipefail
cd /home/xbs/ros2_sweeper_resume_project
export RMW_IMPLEMENTATION=rmw_fastrtps_cpp
out="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
./scripts/run_cleaning_benchmark.sh --scenario living_room --runs 1 \
  --domain 67 --gui --compare-poses --target 0.90 --odom-source robot_wheels \
  --open-floor --collision-aware-nav --clearance-control --sweep-goal-tolerance 0.10 \
  --precise-gap-navigation --guard-gap-goals --refine-sweep --target-gap-coverage \
  --gap-efficiency-target 0.80 --output "$out" 2>&1 | tee "$out/benchmark.log"
