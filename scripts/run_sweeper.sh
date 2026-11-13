#!/usr/bin/env bash
set -eo pipefail
cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.."
source ros2_ws/install/setup.bash
export ROS_DOMAIN_ID="${ROS_DOMAIN_ID:-53}"
export ROS_AUTOMATIC_DISCOVERY_RANGE=LOCALHOST
export GZ_PARTITION="${GZ_PARTITION:-sweeper_${ROS_DOMAIN_ID}}"
if [[ -z "${DISPLAY:-}" ]]; then
  while IFS= read -r entry; do
    case "$entry" in
      DISPLAY=*|XAUTHORITY=*|XDG_RUNTIME_DIR=*) export "$entry" ;;
    esac
  done < <(systemctl --user show-environment)
fi
export QT_QPA_PLATFORM="${QT_QPA_PLATFORM:-xcb}"
exec ros2 launch robot_sweeper_bringup sweeper.launch.py "$@"
