# 清扫任务管理重构与基线实验设计

## 职责边界

`CleaningTaskManager` 保留 ROS 2 Action Server、订阅/服务入口和清扫任务的统一协调职责。
本轮提取三类无 ROS 副作用、可独立测试的逻辑：

- `TaskStateMachine`：类型安全的内部状态与合法转换表；对外仍发布原字符串。
- `PlanningRequestBuilder`：构造覆盖规划请求、失败排除项和剩余距离预算。
- `WaypointGuard`：costmap 坐标查询、连接段检查、转弯净空检查及邻近目标调整。

已有 `NavigationExecutor` 继续负责 Nav2 Action 生命周期与超时；`CheckpointStore` 负责原子持久化；
`CompletionDecision` 负责完成判定。协调器不再复制这些策略。

异步结果有两层隔离：规划响应同时校验任务 `generation`、当前 `PLANNING` 状态和取消标志；
导航响应同时校验 `NavigationExecutor` 内部序号和任务 `generation`。旧任务或已取消目标的延迟回调不能推进新任务。

## 状态机

内部状态为 `IDLE`、`WAITING_MAP`、`PLANNING`、`RUNNING`、`PAUSED`、`RECOVERING`、
`STOPPING`、`CANCELING`、`SUCCEEDED`、`FAILED`、`CANCELED`。

主要合法转换：

- `IDLE/终态 -> WAITING_MAP -> PLANNING -> RUNNING`
- `RUNNING -> PLANNING`（补扫）、`RUNNING <-> PAUSED`
- `RUNNING -> RECOVERING -> RUNNING/PLANNING/STOPPING`
- 任一活动阶段可进入 `CANCELING -> CANCELED`
- 规划、导航、检查点或依赖失败可进入 `FAILED`
- 仅 `RUNNING` 可按完成判定进入 `SUCCEEDED`

所有转换必须调用 `transition_to`；非法转换保留原状态并记录错误。

## 参数分类

| 参数 | 默认值 | 单位 | 分类 | 目的与影响 |
|---|---:|---|---|---|
| `robot_radius` | 0.175 | m | 物理 | 机器人本体半径；增大后可达空间减少 |
| `cleaning_radius` | 0.20 | m | 物理 | 单次轨迹的清扫半径；同时用于规划和运行时覆盖 |
| `safety_margin` | 0.005 | m | 导航/规划 | 本体外额外净空；增大会降低贴边能力 |
| `row_overlap` | 0.10 | 比例 | 规划 | 相邻清扫带重叠；增大通常提高覆盖但增加距离 |
| `waypoint_spacing` | 0.40 | m | 规划 | 单条清扫带的航点间距；过大降低路径约束，过小增加调度开销 |
| `turn_cost` | 0.20 | m/rad 等价代价 | 规划 | 优化算法的转向惩罚；不参与基线排序 |
| `coverage_completion_margin` | 0.01 | 比例 | 业务 | 正常提前完成前的运行时余量；补扫预算耗尽仍按业务目标判定 |
| `target_path_efficiency` | 0.80（launch） | 比例 | 规划预算 | 估算剩余补扫距离预算；不改变业务覆盖目标 |
| `minimum_gap_distance_budget_m` | 0.50 | m | 规划预算 | 防止剩余预算过小而无法形成有效补扫路径 |
| `waypoint_adjustment_radius_m` | 0.15 | m | 运行保护 | costmap 目标受阻时的邻域搜索半径 |
| `maximum_adjustment_connector_m` | 0.80 | m | 运行保护 | 仅对短连接目标做局部调整，避免偏离规划过远 |
| `turn_clearance_margin_m` | 0.035 | m | 运行保护 | 急转弯时轴向附加净空 |
| `turn_diagonal_clearance_m` | 0.025 | m | 运行保护 | 急转弯时对角附加净空 |
| `planning_timeout_s` | 35 | s | 生命周期 | 覆盖规划服务响应上限 |
| `startup_timeout_s` | 60 | s | 生命周期 | 地图、TF、Nav2 和规划服务的总就绪上限 |
| `nav_unavailable_grace_s` | 5 | s | 生命周期 | 任务中 Nav2 暂时不可用的容忍窗口 |

Nav2 控制器、代价地图和传感器参数继续留在 Nav2/launch 配置；覆盖率目标和真值评价口径不放入算法内部。
代码搜索未发现双房间、岛状障碍或窄通道固定坐标。区域坐标仅来自场景对应的 YAML。

## 基线隔离与公平性

`BaselineCoveragePlan` 是独立实现，只有显式设置 `planning_algorithm:=baseline` 才启用；默认值为
`optimized`。基线使用确定性的长轴弓字形清扫带和最近漏扫单元补偿，不使用生产算法的方向/相位搜索、
条带顺序优化、漏扫收益/路程排序或随机多起点搜索。

两种算法共享同一个静态地图、实时障碍掩码、机器人半径、清扫半径、区域、覆盖目标、Nav2、起点、
运行时覆盖跟踪和 Gazebo 真值评价。实验脚本把算法名称写入每轮 `result.json` 和汇总 CSV。

## 与 CoverageDirectPlanner A/B 的边界

Coverage Planner 的 `optimized`/`baseline` 对照与 CoverageDirectPlanner 的 Navfn 对照是两个
独立实验，不能把两者的结果混在同一张表中解释。最终直连 A/B 固定使用优化版 Coverage Planner，
只切换 `direct_sweep_navigation`：A 组为 Navfn，B 组为主清扫 pass 的 CoverageDirectPlanner；
补扫、gap 导航、RPP、costmap、恢复策略和安全控制保持不变。最终数据见
`results/coverage-direct-20261116/strict-ab/ab-report.md`。

CoverageDirectPlanner 的命中率必须来自 `createPlan()` 的运行时事件记录。路径几何共线只能说明
发布结果的形状，不能区分直线分支和 Navfn 恰好返回的近似直线路径。
