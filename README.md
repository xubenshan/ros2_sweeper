# ROS 2 室内扫地机器人自主导航与覆盖清扫系统

## 项目定位

这是一个基于 ROS 2 Jazzy、Nav2 与 Gazebo 的室内移动机器人清扫系统。项目把 OOMWOO 上游机器人模型、Gazebo 场景和基础导航组件，与清扫任务应用层整合到同一个 ROS 2 工作区，形成一个可整体构建、启动和验证的项目目录。

VM 上的整合目录为 `/home/xbs/ros2_sweeper_resume_project`。原始 `/home/xbs/oomwoo_ws` 与 `/home/xbs/robot_sweeper` 保持原样，整合目录是两者源码和验收材料的独立副本。

`upstream/oomwoo_ws` 保留 OOMWOO 上游组件及其许可证；`robot_cleaning_*` 和 `robot_sweeper_bringup` 是本清扫项目的应用层包。简历中应把上游组件描述为集成基础，不应把上游仓库的实现归为个人原创。

## 统一目录结构

```text
ros2_sweeper_resume_project/
├── .gitignore
├── README.md
├── ros2_ws/
│   ├── src/
│   │   ├── upstream/oomwoo_ws/       # OOMWOO 机器人、Gazebo 与基础 ROS 组件
│   │   ├── robot_cleaning_interfaces/ # Action、Service、Message 接口
│   │   ├── robot_cleaning_manager/    # 清扫任务状态机、Nav2 Action、检查点
│   │   ├── robot_coverage_planner/    # 栅格覆盖规划、补扫和运行时覆盖统计
│   │   ├── robot_motion_safety/       # 速度仲裁、急停及指令看门狗
│   │   └── robot_sweeper_bringup/     # Gazebo、Nav2、桥接与节点启动
│   ├── build/                         # colcon 生成
│   ├── install/                       # colcon 生成
│   └── log/                           # colcon 生成
├── scripts/                           # 构建、启动、benchmark、故障验证
└── results/                           # 验收日志、地图、原始数据和旧脚本快照
```

## 模块协作

```text
CleanTask Action
  -> cleaning_task_manager
  -> PlanCoverage Service
  -> coverage_planner 生成覆盖/补扫路线
  -> Nav2 NavigateToPose 执行航点
  -> TF 位姿更新运行时覆盖网格
  -> motion_safety 仲裁速度命令
  -> ros_gz_bridge 与 Gazebo 机器人交互
```

运行时任务决策使用机器人定位和覆盖网格估算；Gazebo 真值只用于离线验收，不参与实际清扫决策。Nav2 导航 Action 成功与清扫业务目标完成是两个不同判断。

## 简历事实摘要

- 将 OOMWOO 差速机器人仿真底座与清扫应用层集成，基于 ROS 2 Action、Service 和 Topic 组织异步任务执行、路径规划、覆盖状态更新及安全速度仲裁。
- 在栅格地图上实现扫线覆盖与漏扫补扫规划；清扫任务管理器支持暂停、恢复、取消、检查点续扫，并区分 Nav2 导航结果与业务覆盖目标结果。
- 在 Gazebo 多房间、岛状障碍、窄通道三种布局完成 9 轮有效静态验证；独立真值覆盖率达到 90% 的样本为 6/9。三种布局的平均真值覆盖率分别为 90.23%、92.16%、90.64%。
- 完成 1 轮动态障碍集成验证：障碍物运动期间有 6 个清扫航点被延后，之后通过补扫完成；该动态场景尚无重复轮次统计。

以上数据来自 `results/acceptance-2026-11-12/acceptance-report.md`。窄通道只有 1/3 轮达到 90% 独立真值覆盖率；Nav2 生命周期启动仍有间歇性失败，因此不应表述为所有场景稳定达标。

## 独立整屋复测

茶几与沙发通道扩大后的整屋仿真只有 1 轮：Gazebo 真值覆盖率 92.24%，运行时估算 90.46%，实际里程 45.85 m，补扫 3 轮，Action `SUCCEEDED`。达到 90% 真值覆盖时里程为 42.02 m、效率 81.06%；任务终止时效率为 74.29%。VM 当时运行源码与 Mac 工作区有一处补扫重规划逻辑差异，因此这次结果不能作为字节级源码复现或跨轮稳定性证明。

原始证据位于 `results/whole-house-wide-gap-2026-11-12/`。该结果与三场景静态验收分开统计。

## 构建与验证

在 Ubuntu 24.04、ROS 2 Jazzy 环境中，从项目根目录运行：

```bash
source /opt/ros/jazzy/setup.bash
cd ros2_ws
colcon build --symlink-install --parallel-workers 3
colcon test
colcon test-result --verbose
```

构建后启动仿真：

```bash
cd ..
source /opt/ros/jazzy/setup.bash
./scripts/run_sweeper.sh
```

完整静态 benchmark 参数与版本记录保存在 `results/acceptance-2026-11-12/`。运行新实验时请使用新的输出目录，不要覆盖历史验收证据。

## 本次统一工作区验证

2026-11-12 将原 VM 的两个源码工作区合并为本目录后，`colcon list` 发现 22 个包且无重名；22 个包全量构建成功。清扫应用的 5 个包单独运行 `colcon test --packages-select` 成功，实际执行的 26 个测试用例全部通过；其中 `robot_cleaning_interfaces` 与 `robot_sweeper_bringup` 没有单元测试用例。

全量 22 包测试共 227 个测试，43 个失败、11 个跳过，因此不能称为全仓测试通过。失败集中在上游 `explore_lite`、`kaiaai`、`kaiaai_teleop`、`oomwoo_sim_support` 的 lint/格式规则；`oomwoo_sim_support` 另有两项测试在隔离测试环境中找不到 `oomwoo_gazebo` 包。清扫应用层的 26 个已执行测试没有失败。完整逐包结果保存在 `ros2_ws/build/*/test_results/` 与 `ros2_ws/log/`。

## 验收边界

- 现有静态验收统计是 9 轮有效 Gazebo 样本，不包含启动失败后重试的无效样本。
- 动态障碍和扩大通道后的整屋结果均为单轮仿真，不代表稳定性统计。
- 项目目前是仿真验证，没有实体机器人运行证据。
- OOMWOO 上游包的许可证和来源目录应随项目保留；个人贡献应聚焦在清扫接口、任务管理、覆盖规划、安全仲裁及其集成验证。
