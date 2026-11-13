#!/usr/bin/env bash
set -eo pipefail
source /opt/ros/jazzy/setup.bash
while IFS= read -r entry; do
    case "$entry" in
        DISPLAY=*|XAUTHORITY=*|XDG_RUNTIME_DIR=*) export "$entry" ;;
    esac
done < <(systemctl --user show-environment)
export QT_QPA_PLATFORM=xcb
cd /home/xbs/ros2_sweeper_resume_project/results/cross-map-20261113.ybb8Lk
while tmux has-session -t sweeper-generalization 2>/dev/null; do
    pid=$(pgrep -f '^python3 -u .*cross-map-.*/run.py furniture' | head -1 || true)
    domain=$(sed -n 's/^furniture: run [0-9]*, attempt [0-9]*, domain \([0-9]*\)$/\1/p' furniture.log | tail -1)
    if [[ -n "$pid" && -n "$domain" ]]; then
        export GZ_PARTITION="sweeper_benchmark_${domain}_${pid}"
        gz sim -g -v 2 >> gui-watch.log 2>&1 || true
    fi
    sleep 2
done
