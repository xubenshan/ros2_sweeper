#!/usr/bin/env bash
set -e
args=()
for arg in "$@"; do
    if [[ "$arg" == enable_tof:=false ]]; then
        arg=enable_tof:=true
    fi
    args+=("$arg")
done
exec /home/xbs/ros2_sweeper_resume_project/scripts/run_sweeper.sh "${args[@]}"
