# 清扫任务管理重构与覆盖规划基线验收报告

日期：2026-11-14
开发分支：`codex/task-manager-refactor-baseline`
重构前版本：`03f04dce2aa6f3e7df1153dd19a5fae91633642d`

## 1. 原任务管理器的问题

`cleaning_task_manager.cpp` 原为 1170 行，单个类同时处理 Action Server、字符串状态、规划请求构造、
Nav2 调度、costmap 航点保护、覆盖反馈、检查点、碰撞恢复和完成判定。主要问题不是行数本身，而是：

- 状态由多个异步回调直接写字符串，非法转换无法约束。
- 规划距离预算、排除项和补扫请求组装嵌在 ROS 回调中，难以独立测试。
- costmap 坐标换算、连接段检测和邻近航点搜索与任务生命周期耦合。
- 35/60/5 秒以及 0.15/0.80/0.035 等值缺少集中名称和单位说明。
- 规划响应、导航响应、取消和任务切换虽已有部分代次保护，但边界规则未形成显式状态模型。

## 2. 重构后的结构

`CleaningTaskManager` 仍是唯一协调入口，保留 Action、ROS 通信和生命周期编排；文件为 1094 行，
没有为追求行数机械拆分。提取的组件均包含实际策略并可独立测试：

- `TaskStateMachine`：内部 `enum class TaskState`、合法转换和终态判断。
- `PlanningRequestBuilder`：覆盖规划请求、失败排除、暂存障碍目标和补扫距离预算。
- `WaypointGuard`：栅格/costmap 查询、连接段碰撞检查、急转弯净空和目标邻域调整。
- 继续复用 `NavigationExecutor`、`CheckpointStore`、`CompletionDecision`、`ReplanPolicy`、
  `RecoveryExecutor`，没有复制已有职责。

规划回调必须同时满足任务代次相同、状态仍为 `PLANNING` 且任务未取消；Nav2 回调同时使用
`NavigationExecutor` 内部序号和任务代次。旧任务的延迟结果不会推进新任务。

## 3. 状态机

状态集合：`IDLE`、`WAITING_MAP`、`PLANNING`、`RUNNING`、`PAUSED`、`RECOVERING`、
`STOPPING`、`CANCELING`、`SUCCEEDED`、`FAILED`、`CANCELED`。

主要转换：

- `IDLE/终态 -> WAITING_MAP -> PLANNING -> RUNNING`
- `RUNNING -> PLANNING`：初始路线结束或动态漏扫触发补扫
- `RUNNING <-> PAUSED`：暂停与恢复
- `RUNNING -> RECOVERING -> RUNNING/PLANNING/STOPPING`：导航或碰撞恢复
- `RUNNING/PAUSED/RECOVERING -> STOPPING -> FAILED`：运动权限或 Nav2 异常
- 任意活动异步阶段 `-> CANCELING -> CANCELED`
- `RUNNING -> SUCCEEDED`：完成判定通过

对外 `/cleaning/state` 与 Action Feedback 仍发布原有大写字符串，Action 接口未修改。

受控测试发现并修复了一处真实边界：暂停后 Nav2 不确认取消时，状态必须允许
`PAUSED -> STOPPING -> FAILED`。修复后 Action 在 8.11 秒内 ABORTED，并撤销运动权限。

## 4. 参数和阈值

关键参数说明见 `docs/refactor_and_baseline.md` 和
`robot_cleaning_manager/config/task_manager.yaml`。分类如下：

- 物理：`robot_radius=0.175 m`、`cleaning_radius=0.20 m`。
- 覆盖规划：`row_overlap=0.10`、`waypoint_spacing=0.40 m`、`turn_cost=0.20`。
- 生命周期：导航 90 s、规划 35 s、依赖启动 60 s、Nav2 短暂不可用 5 s。
- 业务：覆盖目标 90%，正常完成余量 1 个百分点，最小补扫距离预算 0.50 m。
- costmap 运行保护：目标调整半径 0.15 m、最大短连接 0.80 m、转弯净空 0.035/0.025 m。
- 实验评价：Gazebo 真值覆盖、真值里程、理想面积/清扫宽度和重复行驶口径只存在于评价节点，
  不参与运行时任务决策。

重构保留所有默认数值。代码检查未发现双房间、岛状障碍或窄通道固定坐标；场景区域仅来自 YAML。

## 5. 主要源码修改

- `robot_cleaning_manager/src/cleaning_task_manager.cpp`：接入状态机、规划请求构造器和航点保护器；
  集中状态转换；参数具名化；保持协调入口。
- `task_state.hpp/.cpp`：状态集合、转换表、对外字符串映射。
- `planning_request.hpp/.cpp`：规划请求与距离预算。
- `waypoint_guard.hpp/.cpp`：costmap 航点几何保护。
- `navigation_executor.cpp`：进展阈值、生命周期新鲜度和取消时限改为具名内部常量。
- `baseline_coverage_plan.hpp/.cpp`：隔离的确定性弓字形基线和最近漏扫补偿。
- `coverage_node.cpp`：新增 `planning_algorithm=optimized|baseline`，默认 `optimized`。
- `coverage_plan.cpp`：关键算法阈值具名化，数值不变。
- `sweeper.launch.py`：参数配置文件、算法选择和控制/ToF 配置分组。
- `run_cleaning_benchmark.py`：记录算法名称和统一对照结果。
- 新增状态机、规划请求、航点保护和基线算法测试。

## 6. 构建与行为回归

- 5 个 ROS 2 包构建成功。
- `colcon test-result`：231 tests，0 errors，0 failures，11 skipped。
- 速度仲裁：导航/遥控源切换、急停、碰撞停止、恢复暂停、心跳丢失全部通过。
- Nav2 异常：无效目标、运行中 Nav2 关闭、速度归零和 Action ABORTED 通过。
- 取消未确认：8.11 s 内进入 `STOPPING -> FAILED`，没有错误恢复为可运行任务。
- 动态补扫：注入 4 次导航失败后，从 70 个原始航点重新规划为 19 个可达补扫航点。
- 真实 Gazebo 检查点：覆盖单元 128 精确恢复，继续运行后增加到 178；暂停、重启续扫和取消通过。
- 真实 Gazebo 动态障碍：62 次障碍物更新，1 次导航失败后恢复；Action 成功，真值覆盖 91.54%，
  实际里程 16.23 m，效率 72.40%，重复行驶率 27.93%。

## 7. 基线算法

基线采用：

1. 根据可达中心栅格的长轴生成固定方向弓字形清扫带。
2. 行间距、机器人半径、清扫半径、任务区域与生产算法完全相同。
3. 障碍分割段之间用同一可达栅格 Wavefront 连接并做视线压缩。
4. 补扫按可达距离选择最近的未覆盖地面，不使用生产算法的覆盖收益/行驶代价排序、多权重搜索、
   方向/相位搜索或条带顺序优化。
5. 只有显式 `coverage_algorithm:=baseline` 才启用；生产默认路径不受影响。

## 8. 五地图 Gazebo 对照

每个场景、每种算法一轮有效仿真，使用相同地图、起点、Nav2、机器人参数、覆盖目标和 Gazebo
真值评价。10/10 Action 成功，10/10 真值覆盖达到 90%。

| 场景 | 算法 | 真值覆盖率 | 实际里程 | 到 90% 里程 | 路径效率 | 重复行驶率 |
|---|---|---:|---:|---:|---:|---:|
| 双房间 | optimized | 90.29% | 13.79 m | 13.59 m | 79.31% | 21.88% |
| 双房间 | baseline | 90.57% | 22.84 m | 16.36 m | 47.89% | 48.42% |
| 岛状障碍 | optimized | 92.79% | 10.10 m | 9.64 m | 97.01% | 7.46% |
| 岛状障碍 | baseline | 92.47% | 17.29 m | 16.94 m | 56.69% | 37.80% |
| 窄通道 | optimized | 91.43% | 16.09 m | 15.39 m | 58.52% | 37.51% |
| 窄通道 | baseline | 90.24% | 17.47 m | 17.47 m | 53.88% | 44.57% |
| L 形多房间 | optimized | 91.49% | 18.80 m | 17.62 m | 70.74% | 30.77% |
| L 形多房间 | baseline | 91.64% | 18.20 m | 16.87 m | 73.09% | 22.12% |
| 复杂家具 | optimized | 92.38% | 18.98 m | 16.20 m | 66.96% | 30.52% |
| 复杂家具 | baseline | 91.10% | 24.66 m | 22.14 m | 51.52% | 44.84% |

五图平均：优化算法真值覆盖 91.68%、实际里程 15.55 m、到 90% 里程 14.49 m、效率 74.51%、
重复行驶率 25.63%；基线分别为 91.20%、20.09 m、17.96 m、56.61%、39.55%。

结论：优化算法在五图平均上少走 4.54 m，效率高 17.90 个百分点，重复行驶率低 13.92 个百分点；
优势主要来自方向/相位选择、条带访问顺序和按覆盖收益选择补扫。但 L 形单轮中基线到 90% 少走
0.75 m，说明当前跨区域访问顺序和补扫选择并非在所有拓扑上占优，该结果没有被过滤或调参覆盖。

路径效率公式为 `可服务面积 / 清扫宽度 / 实际真值里程`。它适合同地图同条件横向比较，但把转弯、
跨房间连接和障碍绕行都视为损失，因此复杂布局的绝对值会偏低。重复行驶率按约 0.25 m 轨迹块判断
新增覆盖是否低于理想清扫带的四分之一，反映低收益通行，但不是精确的几何重复面积。

## 9. 剩余局限

- 每个算法每张地图只有一轮，足以形成可复现工程对照，但不足以做统计显著性结论。
- 两种算法所有场景都用完 3 次补扫；补扫终止效率仍有优化空间。
- 窄通道的优化算法效率仅 58.52%、重复行驶率 37.51%，必要绕行和可优化重复尚未完全分离。
- L 形场景生产算法不如基线，表明跨区域顺序/补扫代价模型仍有适用边界。
- 任务管理器仍承担较多 ROS 接线代码；继续拆分只有在新增策略时才有价值，不建议为行数再拆转发类。
- 11 个跳过项为现有测试环境标记项；本轮执行项无失败。

## 10. 复现命令

```bash
cd /home/xbs/ros2_sweeper_resume_project/ros2_ws
source /opt/ros/jazzy/setup.bash
colcon build --packages-select robot_cleaning_interfaces robot_cleaning_manager \
  robot_coverage_planner robot_motion_safety robot_sweeper_bringup --symlink-install
colcon test --packages-select robot_cleaning_interfaces robot_cleaning_manager \
  robot_coverage_planner robot_motion_safety robot_sweeper_bringup
colcon test-result --verbose

cd /home/xbs/ros2_sweeper_resume_project
python3 scripts/run_cleaning_benchmark.py --scenario layouts --runs 1 --whole-map \
  --no-gui --coverage-algorithm optimized --output results/optimized
python3 scripts/run_cleaning_benchmark.py --scenario layouts --runs 1 --whole-map \
  --no-gui --coverage-algorithm baseline --output results/baseline
python3 scripts/summarize_baseline_comparison.py \
  results/refactor-baseline-20261113/experiments
```

完整原始日志、逐轮 JSON、轨迹、覆盖栅格和汇总位于
`results/refactor-baseline-20261113/`。本轮结论支持结束新增功能开发，进入源码学习和面试准备；
L 形跨区域顺序和窄通道重复行驶应作为已知局限，而不应继续针对地图刷参数。
