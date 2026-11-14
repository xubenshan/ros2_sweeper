# ROS 2 自主清扫机器人

![ROS 2 Jazzy](https://img.shields.io/badge/ROS%202-Jazzy-22314E?logo=ros)
![Ubuntu 24.04](https://img.shields.io/badge/Ubuntu-24.04-E95420?logo=ubuntu&logoColor=white)
![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus)
![Nav2](https://img.shields.io/badge/Navigation-Nav2-0A66C2)
![Gazebo](https://img.shields.io/badge/Simulation-Gazebo-F58113)

> 这是我为机器人软件开发岗位准备的简历项目。目标不只是让机器人“能动”，而是让它能够自主生成清扫路线、执行清扫任务、识别漏扫区域，并在导航失败或遇到障碍时继续完成任务。

## 演示

![Gazebo、RViz 与覆盖验收预览](docs/assets/sweeper-demo.gif)

上图包含 Gazebo 客厅、RViz 机器人模型、整屋覆盖结果和跨地图验收结果。

## 项目实现的功能

- 根据栅格地图自动生成覆盖清扫路线。
- 通过 Nav2 `NavigateToPose` Action 执行清扫航点。
- 根据 TF 位姿更新已清扫区域，识别漏扫并动态补扫。
- 支持任务暂停、恢复、取消和检查点续扫。
- 处理导航失败、超时、Nav2 退出和动态障碍。
- 对导航、手动控制、恢复和急停速度指令进行安全仲裁。
- 使用 Gazebo 真值轨迹独立统计覆盖率、实际里程和路径效率。

## 我在项目中做的工作

项目使用 [makerspet/oomwoo](https://github.com/makerspet/oomwoo) 作为机器人模型和 Gazebo 仿真底座。我主要完成了其上的清扫应用层：

1. 使用 C++17 和 ROS 2 Action 实现清扫任务管理器。
2. 实现覆盖路径规划、漏扫识别和动态补扫。
3. 用 `enum class` 重构任务状态机，统一管理状态转换。
4. 处理任务取消与导航结果竞争、旧任务回调延迟到达等异步问题。
5. 实现速度指令仲裁、急停、碰撞停车和心跳看门狗。
6. 搭建 Gazebo 自动化测试，并增加简单弓字形 baseline 进行算法对照。

## 项目架构

![ROS 2 自主清扫系统架构](docs/assets/system-architecture.drawio.svg)

```text
CleanTask Action
    -> CleaningTaskManager
    -> Coverage Planner
    -> NavigationExecutor
    -> Nav2
    -> Motion Safety
    -> Gazebo Robot
```

- `CleaningTaskManager`：任务的统一协调入口。
- `Coverage Planner`：生成初始清扫路线和补扫路线。
- `NavigationExecutor`：向 Nav2 发送航点并处理导航结果。
- `Motion Safety`：管理速度指令优先级和安全停车。
- Gazebo 真值只用于验收，不参与机器人运行时决策。

## 面试中可以重点介绍的内容

### 1. ROS 2 Action 与任务状态机

清扫任务执行时间长，需要持续反馈进度，还需要支持取消，因此使用 Action 而不是 Service。状态机负责约束 `PLANNING`、`RUNNING`、`PAUSED`、`RECOVERING` 等状态之间的转换。

为了防止旧任务的导航或规划回调改变新任务，系统对任务和导航请求都进行代次校验。

### 2. 覆盖规划与动态补扫

初始路线根据地图可达区域、机器人净空和清扫宽度生成。任务执行过程中，系统根据 TF 位姿更新覆盖网格，将剩余漏扫区域聚合，再结合可达性、覆盖收益和行驶代价生成补扫路线。

### 3. 怎么证明算法有效

项目不使用规划路线代替真实执行轨迹，而是使用 Gazebo 真值位姿独立计算覆盖率和行驶里程。同时实现了一套独立的简单弓字形 baseline，使用相同地图、Nav2 参数和验收方式与当前算法对比。

## 仿真结果

### 代码与回归测试

- 5 个清扫应用包构建成功。
- `231 tests, 0 errors, 0 failures, 11 skipped`。
- 已验证暂停恢复、取消、检查点续扫、导航失败、Nav2 退出和动态障碍恢复。

### 优化算法与 baseline

| 五张地图平均 | 当前算法 | baseline |
|---|---:|---:|
| Gazebo 真值覆盖率 | 91.68% | 91.20% |
| 实际行驶里程 | 15.55 m | 20.09 m |
| 到达 90% 覆盖的里程 | 14.49 m | 17.96 m |
| 路径效率 | 74.51% | 56.61% |
| 重复行驶率 | 25.63% | 39.55% |

- 10/10 轮 Action 执行成功，10/10 轮 Gazebo 真值覆盖率达到 90%。
- 当前算法平均少行驶 4.54 m，路径效率提高 17.90 个百分点。
- L 形地图中 baseline 反而少行驶 0.60 m，说明跨区域顺序仍有优化空间。

动态障碍测试中，障碍物位姿更新 62 次，发生 1 次导航失败并恢复，最终 Action 成功，Gazebo 真值覆盖率为 91.54%。

[查看完整 baseline 对照数据](results/refactor-baseline-20261113/experiments/comparison.md)

## 技术栈

- C++17、Python 3、CMake、colcon、GTest
- ROS 2 Jazzy、`rclcpp`、Action、Service、Topic、TF2、Lifecycle
- Nav2、AMCL、SLAM Toolbox、costmap
- Gazebo Harmonic、`ros_gz_bridge`
- 栅格地图、弓字形覆盖、Wavefront 连接、可达性检查

## 运行项目

```bash
cd /home/xbs/ros2_sweeper_resume_project/ros2_ws
source /opt/ros/jazzy/setup.bash
colcon build --symlink-install --parallel-workers 3
source install/setup.bash

cd ..
python3 scripts/run_cleaning_benchmark.py \
  --scenario multi_room \
  --runs 1 \
  --whole-map \
  --gui \
  --coverage-algorithm optimized \
  --output results/readme-demo
```

## 项目边界

- 目前只完成 Gazebo 仿真，没有实体机器人测试证据。
- baseline 对照为每种算法、每张地图一轮有效仿真，不代表统计显著性结论。
- 窄通道的重复行驶仍偏高，L 形房间的跨区域顺序仍可优化。
- OOMWOO 提供的模型、驱动和仿真资产保留原许可证和来源，不作为个人从零开发的内容。

## 详细文档

- [任务管理器重构与 baseline 设计](docs/refactor_and_baseline.md)
- [完整验收报告](results/refactor-baseline-20261113/report.md)
- [优化算法与 baseline 逐场景数据](results/refactor-baseline-20261113/experiments/comparison.md)
