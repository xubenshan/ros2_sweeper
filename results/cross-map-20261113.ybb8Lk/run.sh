#!/usr/bin/env bash
set -eo pipefail
frozen="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
cd /home/xbs/ros2_sweeper_resume_project
source ros2_ws/install/setup.bash
source /home/xbs/robot_sweeper/results/reliability-2026-11-12/use-cyclonedds.sh
exec python3 -u "$frozen/run.py" "$@"
