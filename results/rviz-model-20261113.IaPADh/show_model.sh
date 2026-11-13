#!/usr/bin/env bash
set -eo pipefail
cd /home/xbs/ros2_sweeper_resume_project
source ros2_ws/install/setup.bash
export ROS_DOMAIN_ID=69 ROS_AUTOMATIC_DISCOVERY_RANGE=LOCALHOST
while IFS= read -r entry; do
    case "$entry" in
        DISPLAY=*|XAUTHORITY=*|XDG_RUNTIME_DIR=*) export "$entry" ;;
    esac
done < <(systemctl --user show-environment)
export QT_QPA_PLATFORM=xcb
out="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
share="$(ros2 pkg prefix oomwoo_one)/share/oomwoo_one"
xacro "$share/urdf/robot.urdf.xacro" odom_source:=robot_wheels enable_tof:=true > "$out/oomwoo_one.urdf"
python3 - "$share/rviz/inspect_urdf.rviz" "$out/oomwoo-model.rviz" <<'PY'
import sys
from pathlib import Path
import yaml
source, destination = map(Path, sys.argv[1:])
config = yaml.safe_load(source.read_text())
view = config['Visualization Manager']
grid, model, tf = view['Displays']
grid.update({'Cell Size': .1, 'Plane Cell Count': 12, 'Color': '100; 112; 128', 'Alpha': .35})
model.update({'Alpha': 1.0, 'Visual Enabled': True, 'Collision Enabled': False})
tf.update({'Value': False, 'Enabled': False})
view['Global Options']['Background Color'] = '40; 47; 57'
view['Views']['Current'].update({'Distance': .65, 'Pitch': .57, 'Yaw': .66,
                                  'Focal Point': {'X': 0, 'Y': 0, 'Z': .055}})
config['Window Geometry'].update({'Width': 1024, 'Height': 725})
destination.write_text(yaml.safe_dump(config, sort_keys=False))
PY
ros2 run robot_state_publisher robot_state_publisher "$out/oomwoo_one.urdf" >"$out/robot-state.log" 2>&1 &
state_pid=$!
ros2 run joint_state_publisher joint_state_publisher >"$out/joint-state.log" 2>&1 &
joint_pid=$!
trap 'kill "$state_pid" "$joint_pid" 2>/dev/null || true' EXIT
ros2 run rviz2 rviz2 -d "$out/oomwoo-model.rviz" 2>&1 | tee "$out/rviz.log"
