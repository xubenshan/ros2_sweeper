# 覆盖路径与 Nav2 执行一致性分析及验证报告

日期：2026-11-16

## 结论

当前 `PlanCoverage` 返回的 `nav_msgs/Path` 不是单纯的清扫带端点列表，而是由清扫带采样点、清扫带之间的 Wavefront 可行连接以及视线压缩后的转折点组成的稀疏候选轨迹。信息丢失发生在执行边界：`CleaningTaskManager` 保存 `response.path.poses`，随后 `NavigationExecutor` 对每个 pose 单独发送 `NavigateToPose`，Nav2 再用 Navfn 从机器人当前位姿重新计算全局路径。因此清扫顺序仍被保留，但 Wavefront 连接的精确几何及其规划代价并不约束实际路径。

最终生产选择是方案 A：继续使用 `NavigateToPose`、Navfn、RPP 和现有安全/恢复机制。实现并验证了一个方案 C-lite 的可选实验能力：只在主清扫 pass 中调用第二个 `CoverageDirect` 规划器，短于 1.20 m 且完整机器人 footprint 在全局 costmap 上逐点安全的直连段才被采用；补扫及跨区连接仍使用 `GridBased/Navfn`，任何不安全或较长路径自动回退 Navfn。五地图单次实验收益不一致，因此该能力保留为 `direct_sweep_navigation:=true` 显式开关，默认关闭。

## 真实调用链

1. `coverage_node.cpp::plan_route()` 构造 `CoveragePlan`，主 pass 调用 `sweep()`，补扫调用 `gaps()`，把 Cell 转成 `PoseStamped` 并填入 `response.path.poses`。
2. `CoveragePlan::append()` 在直线可达时添加终点；否则用 `Wavefront::path_to()` 生成连接，再以最远可视点压缩连接。
3. `connect_strips()` 计算两个定向清扫带端点间的可行 Wavefront 连接长度，执行近邻排序与局部改进；`gap_route()` 还按连接沿途新增覆盖量和行驶代价评分。
4. `CleaningTaskManager::request_plan()` 将完整 `response.path.poses` 存入 `current_.path`。
5. `tick()` 先执行已覆盖航点跳过和实时 costmap 目标调整，再只取 `current_.path[current_.next]`。
6. `NavigationExecutor::send()` 构造一个 `nav2_msgs/action/NavigateToPose` goal；Nav2 Planner Server 再规划，Controller Server 用 RPP 跟踪。

这证明“覆盖规划连接完全未使用”并不准确：它参与了排序、计划长度和中间 waypoint 生成；但其精确几何没有传到 Nav2 控制路径，确实存在执行层信息损失。

## 当前 Nav2 与 upstream

- 正常配置 `upstream/oomwoo_ws/oomwoo-one/config/navigation.yaml`：`GridBased = nav2_navfn_planner::NavfnPlanner`，`FollowPath = nav2_regulated_pure_pursuit_controller::RegulatedPurePursuitController`。
- benchmark 配置 `upstream/oomwoo_ws/oomwoo-ros2-tools/src/oomwoo_sim_support/config/nav2_params.yaml` 使用相同 Navfn + RPP，仅容差、lookahead、接近速度等参数不同。
- `benchmark_nav` 切换参数文件和启动方式，不切换算法。旧的 tight/loose 配置中存在 DWB，但当前 `sweeper.launch.py` 默认路径不会选它。
- 机器人几何统一来自 `robot_geometry.yaml`：机体半径 0.1745 m、清扫半径 0.20 m、轮半径 0.034 m、轮距 0.235 m。Gazebo URDF 使用 DiffDrive，bridge 包括 cmd_vel、odom、TF、scan、IMU、bumper、range/ToF。

## 重复行驶来源判断

按源码和静态五地图结果，主要来源不是单一因素：

1. 末端补扫与必要通道往返。L 形地图从 85% 到 90% 的里程明显跳升；直连实验也不能消除这一拓扑成本。
2. 清扫带顺序和连接方式。已有 optimized 与简单 baseline 对比在双房间、岛状、窄通道、家具分别降低真值里程约 39.6%、41.6%、7.9%、23.0%，说明覆盖层优化是主要杠杆；L 形却回归 3.3%，说明拓扑依赖显著。
3. 每个 waypoint 的 Navfn 重规划可能与 Coverage 预期连接不同，并可能让相邻 A-B、B-C 路径共享通道。
4. 必须经过同一门洞/窄通道的往返属于必要重复，不能通过惩罚已覆盖区域无限消除。
5. 补扫 pass 会再次穿越已覆盖区以抵达残余岛。

动态障碍不是上述结论的前提；本报告的五地图主比较均为静态障碍场景。

已有优化包括：覆盖刷盘栅格判定、主清扫只跳过共线冗余点、补扫连接沿途覆盖收益评分、目标覆盖/距离预算、Wavefront 可行连接代价、清扫带方向与顺序优化、全局/局部 costmap 阻挡目标调整或延后、连续失败后提前补扫重规划。这些机制保留不变。

## 方案比较与选择

| 方案 | 收益 | 复杂度/成本 | 安全与恢复 | 结论 |
|---|---|---|---|---|
| A NavigateToPose | 完整复用 Navfn、BT recovery、RPP、costmap、取消/暂停/超时；可继续优化排序、补扫和已覆盖点 | 低到中 | 最成熟 | 生产选择 |
| B FollowPath + NavigateToPose | 连续且已验证的短清扫段可更贴近 Coverage 几何 | 高；需路径连续性、方向、运动学、全 footprint 校验、阻挡检测、分段、取消竞争和 NavigateToPose 回退 | FollowPath 本身不重新生成绕障路径；控制器判碰撞后仍需上层恢复 | 暂不采用 |
| C 扩展全局规划器 | 可把参考路线/覆盖代价纳入 Nav2，同时保留 Controller/BT | 中到高；参考路线软约束和已覆盖代价层易导致窄通道不可达或计算增加 | 可保留 Nav2 安全机制 | 仅实现 C-lite 实验插件，默认关闭 |

不选择整条 Coverage Path 直接交给 FollowPath：当前 path 是稀疏候选轨迹，不保证每段拥有控制器所需的密度、曲率连续性和实时局部可行性；FollowPath 不会自动计算替代全局路径。要安全采用必须先按连接语义分段、全 footprint 验证、重采样、检查转角/最小半径，并在 controller abort、阻挡、暂停、取消时回退 NavigateToPose。

## 修改内容

- `robot_coverage_planner/src/coverage_direct_planner.cpp`
  - 参数化最大直连长度、最大代价和采样步长。
  - 每 2.5 cm 检查中心 cost 与完整机器人 footprint；越界/碰撞/取消立即拒绝直连。
  - 不满足条件时调用原 Navfn。
- `robot_sweeper_bringup/launch/sweeper.launch.py`
  - 直连模式不再替换 `GridBased`，而是追加第二个 `CoverageDirect` 插件。
  - 生成只用于主清扫 pass 的 BT，明确 `planner_id=CoverageDirect` 和有效 goal checker。
  - 精确补扫 BT 保持 `GridBased/Navfn`；实验开关默认 `false`。
- `robot_cleaning_manager/src/cleaning_task_manager.cpp`
  - 增加 `sweep_behavior_tree` 参数；主清扫和补扫按 pass 选择不同 BT。
  - 保留 generation guard、取消、暂停、检查点、超时、定位健康和恢复状态机。
- `scripts/run_cleaning_benchmark.py`
  - 记录 `/plan` 的每个 Nav2 全局路径及所有 pose。
  - 输出 Coverage 计划长度（含各补扫 pass）、Nav2 每目标首条全局路径长度、全部重规划消息长度和 Gazebo 真值轨迹长度。
  - 新增 `nav2-global-plans.csv`、`nav2-global-plan-poses.csv`、扩展 summary 字段。
- `scripts/verify_cancel_timeout.py`
  - 从统一机器人几何配置加载必需参数，并发布受控定位健康状态，使取消竞争测试与当前 manager 前置条件一致。

未修改 `CleanTask.action` 或其他接口定义。

## 五地图实验

“旧优化基线”来自 `results/refactor-baseline-20261113/experiments/comparison.csv`；“选择性直连实验”来自本次最终安全实现。每个场景仅 1 次，不足以作统计显著性结论。

| 场景 | 旧覆盖率 | 实验覆盖率 | 旧/实验里程 m | 旧/实验 90%里程 m | 旧/实验重复率 | 结果 |
|---|---:|---:|---:|---:|---:|---|
| 双房间 | 90.29% | 90.97% | 13.79 / 12.89 | 13.59 / 12.82 | 21.88% / 17.58% | 改善 |
| 岛状障碍 | 92.79% | 91.71% | 10.10 / 11.70 | 9.64 / 11.46 | 7.46% / 17.19% | 回归 |
| 窄通道 | 91.43% | 91.10% | 16.09 / 15.27 | 15.39 / 14.32 | 37.51% / 32.92% | 改善，但既有性能门限未通过 |
| L 形多房间 | 91.49% | 91.40% | 18.80 / 19.87 | 17.62 / 19.37 | 30.77% / 34.17% | 回归 |
| 复杂家具 | 92.38% | 90.75% | 18.98 / 16.50 | 16.20 / 16.37 | 30.52% / 22.88% | 总里程改善，90%里程略回归 |

五个实验任务均成功结束，Nav2 目标成功率均为 100%，无导航超时和接触恢复。因为跨地图并非一致改善，实验能力不设为默认。

最终默认配置双房间烟雾测试：真值覆盖 91.49%，真值里程 13.32 m，90% 覆盖里程 11.95 m，重复率 17.00%，42/42 Nav2 目标成功，无超时和接触恢复。路径口径为 Coverage Planner 15.52 m（初始 11.17 m + 三次补扫）、Nav2 每目标首条全局路径合计 19.25 m、Gazebo 真值 13.32 m。Nav2 `all plan messages` 不能视为行驶里程，因为 100 次周期重规划会重复累计尚未行驶的路径。

## 构建与回归

- 全工作区 `colcon build --symlink-install --parallel-workers 3`：22 packages passed。
- 本项目最终相关测试：85 tests，0 errors，0 failures（manager 56、coverage planner 19、bringup 7、motion safety 3）。
- 暂停/恢复：Gazebo 双房间通过，任务状态序列包含 `PAUSED -> RUNNING -> SUCCEEDED`。
- 取消竞争：Nav2 拒绝 cancel 时 8.10 s 内任务 `ABORTED`，原因是 motion authority revoked，未发送第二个导航目标。
- 实时阻挡：主清扫与补扫重规划均通过；局部 costmap 阻挡移除后区域可重新规划；测试最后主动取消，Action 状态为 CANCELED。
- Nav2 故障：越界目标 ABORTED；运行中关闭 Nav2 后 0.300 s 内输出零速度，CleanTask ABORTED，原因为 `Nav2 stopped during the cleaning task`。
- 速度安全：源仲裁、watchdog、急停、bumper、恢复中暂停、心跳丢失均通过；watchdog 0.285 s，急停输出零速度约 0.0006 s。
- 定位健康：manager/localization 单元测试通过；Gazebo 真值与定位中位误差约 0.04 m。实验迭代中确实捕获并修复过 footprint 检查不足导致的碰撞恢复和定位陈旧链路。

全量 260-test 运行中，3 个未改动的 upstream `ament_xmllint` 测试在 60 s 超时（`explore_lite`、`oomwoo_bringup`、`oomwoo_msgs`）。单独执行 `ament_xmllint` 仍挂起且不生成 xUnit，属于远程 XML schema/tooling 阻塞，不是 XML 断言失败；本次修改相关四包的独立测试全部通过。

## 结果位置

- 默认配置：`results/coverage-direct-20261116/final-default-multi-room/`
- 选择性直连五地图：`final3-multi-room/`、`final-islands/`、`final-narrow/`、`final-l-shape-v2/`、`final-furniture/`
- 导航故障：`results/coverage-direct-20261116/regression-navigation-faults/result.json`
- 每个 run 包含 `result.json`、`launch.log`、`waypoints.csv`、`nav2-global-plans.csv`、`nav2-global-plan-poses.csv` 和可选 `pose-comparison.csv`。

## 最终收尾结论（2026-11-17）

### 两类实验分开解释

第一类实验比较 Coverage Planner 的 `optimized` 与 `baseline`，用于衡量清扫带顺序、
可行连接和动态补扫策略相对简单弓字形基线的变化。第二类实验固定优化版 Coverage Planner，
只切换 `direct_sweep_navigation`，用于衡量 CoverageDirectPlanner 相对 Navfn 的独立影响。
`strict-ab/ab-summary.csv` 是第二类实验的最终汇总，不应与本报告上方的单次探索表直接拼接。

### CoverageDirectPlanner 严格 A/B

| 场景 | Navfn A：样本/成功 | A 真值覆盖 | A 最终里程 | A 重复率 | Direct B：样本/成功 | B 真值覆盖 | B 最终里程 | B 重复率 |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| 双房间 | 1/1 | 90.40% | 12.39 m | 14.20% | 1/1 | 90.97% | 13.39 m | 18.78% |
| 岛状障碍 | 2/2 | 92.28% | 11.52 m | 15.28% | 2/2 | 91.65% | 11.05 m | 13.65% |
| 窄通道 | 2/3 | 91.04% | 15.85 m | 36.81% | 1/3 | 92.05% | 15.12 m | 34.22% |
| L 形多房间 | 1/1 | 91.54% | 18.86 m | 26.67% | 1/1 | 90.70% | 19.25 m | 33.99% |
| 复杂家具 | 1/1 | 89.57% | 16.82 m | 25.41% | 1/1 | 91.39% | 16.79 m | 25.45% |

岛状障碍和窄通道有重复样本但任务层行为仍有差异；其余场景每组只有一个有效样本。
因此这些数字只支持“未观察到跨地图稳定收益”，不能证明某一策略的统计显著优势。窄通道还包含
未达到任务完成条件的运行，Action 成功与 Gazebo 真值覆盖达到 90% 必须分开报告。

直线命中统计来自 `createPlan()`：双房间 22/110（20.0%）、岛状障碍 11/178（6.2%）、
窄通道 24/293（8.2%）、L 形 24/134（17.9%）、复杂家具 16/136（11.8%）。非命中请求
主要因完整 footprint 检查拒绝后回退 Navfn；没有证据支持放宽 footprint 或 costmap 安全阈值。

### 最终选择与限制

Navfn 保持默认全局规划器。CoverageDirectPlanner 保留为显式实验开关，原因是双房间和 L 形出现
退化，岛状障碍和窄通道的改善没有足够样本证明稳定，复杂家具只显示近似相同的最终里程。
窄通道的必经通道往返、岛状障碍的航点调整/推迟与 gap pass、L 形的跨臂连接和补扫顺序，
仍是主要重复行驶来源；这些是任务层和地图拓扑因素，不能用 `/plan` 消息次数或路径长度求和替代
真实里程，也不应通过放宽导航安全检查来压低重复率。

本轮没有继续新增导航架构或地图专用逻辑。已保留取消、暂停恢复、检查点、定位健康监控、速度
仲裁、急停和异常恢复能力。完整构建和 85 个相关单元测试通过；全工作区历史测试中仍有 3 个
未修改 upstream `ament_xmllint` 测试因 XML schema/tooling 在 60 秒内挂起，不能描述为失败断言。
Gazebo 级暂停、取消、定位异常和急停回归已保留已有真实记录，但未在本轮重新跑完全部组合；
这些限制必须在发布或面试说明中保留。
