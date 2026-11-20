# CoverageAware Nav2 Planner 实验报告

日期：2026-11-17。实验工程为 `/home/xbs/ros2_sweeper_resume_project`，默认规划器仍为
Navfn；`coverage_aware_navigation:=true` 仅作为 C 组显式实验开关。真实里程、达到 90%
覆盖的里程和重复率均来自 Gazebo 真值轨迹，不使用 Nav2 `/plan` 长度之和代替。

## 实现摘要

`CoverageDirectPlanner` 继续继承 `nav2_navfn_planner::NavfnPlanner`。`direct` 策略保留旧的
短直连加 Navfn 回退行为；`coverage_aware` 策略先生成 Navfn 参考路线，再在 costmap 上运行
带方向状态的非负代价 A*。候选包括不同覆盖奖励的路线，以及经过高未覆盖潜力中间栅格的
有限绕行路线。

覆盖网格通过 transient-local `/cleaning/covered_grid` 快照接入，语义为 `100=已覆盖`、
`0=目标但未覆盖`、负值为非目标区域。覆盖收益按清扫半径内目标栅格估计并去重。数据未收到、
过期、时间戳不合格、frame/尺寸/分辨率/原点不一致或端点无效时回退 Navfn。候选逐段逐采样点
执行完整 footprint 碰撞检查。

候选选择约束为：最大绕行比例 1.25、最大额外距离 0.75 m、最小新增面积 0.0025 m2、
每米额外距离至少 0.05 m2 新增面积，以及至少 0.03 m 的综合评分改善。等长或更短候选也
不能降低参考路线的估计覆盖面积。

## C 组最终样本

| 场景 | Action | Gazebo 真值覆盖率 | 达到 90% 真值里程 | 最终真值里程 | 重复率 | 路径效率 | Nav 目标成功率 | 采用次数 | 候选数 | 平均规划耗时 |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| 双房间 | 1/1 | 92.46% | 11.24 m | 12.50 m | 14.10% | 87.51% | 100% | 0 | 845 | 46.99 ms |
| 岛状障碍 | 1/1 | 92.28% | 10.29 m | 11.22 m | 11.22% | 87.35% | 100% | 0 | 728 | 41.50 ms |
| 窄通道 | Action 成功，验收失败 | 89.77% | 未达到 | 11.39 m | 15.46% | 82.62% | 100% | 3 | 777 | 40.01 ms |
| 复杂家具 | 超时中止 | 约 41% 时无进展 | 未达到 | 不可用 | 不可用 | 不可用 | 不可用 | 不可用 | 不可用 | 不可用 |
| L 形多房间 | 未运行 | 未运行 | 未运行 | 未运行 | 未运行 | 未运行 | 未运行 | 未运行 | 未运行 | 未运行 |

双房间和岛状障碍的 C 组运行成功，但覆盖感知候选没有被采用，所有最终路径均为
Navfn 参考路线或其正常 Nav2 重规划结果，因此不能宣称覆盖感知策略在这两个场景改善了
最终里程。窄通道出现 3 次候选采用，估计新增覆盖总量为 0.47 m2、相对参考路线额外距离
统计为 -0.051 m；但整个任务的真值覆盖率为 89.77%，不能作为达到 90% 的有效成功样本。

家具场景在约 480 s 时覆盖率停在 41%，状态在 `RUNNING/PLANNING` 间停滞，已主动终止并
保留日志。该结果只作为超时/失败诊断，不进入收益平均值。

## A/B 历史对照

以下数据来自 `results/coverage-direct-20261116/strict-ab/ab-report.md`，不是本轮新运行：

| 场景 | A Navfn 真值覆盖 | A 90%里程 | A 最终里程 | B Direct 真值覆盖 | B 90%里程 | B 最终里程 |
|---|---:|---:|---:|---:|---:|---:|
| 双房间 | 90.40% | 12.22 m | 12.39 m | 90.97% | 12.31 m | 13.39 m |
| 岛状障碍 | 92.28% | 11.22 m | 11.52 m | 91.65% | 9.99 m | 11.05 m |
| 窄通道 | 91.04% | 14.86 m | 15.85 m | 92.05% | 13.63 m | 15.12 m |
| L 形多房间 | 91.54% | 18.14 m | 18.86 m | 90.70% | 18.83 m | 19.25 m |
| 复杂家具 | 89.57% | 未达到 | 16.82 m | 91.39% | 16.17 m | 16.79 m |

A/B 数据本身已经说明旧 Direct 策略跨地图收益不稳定，因此默认策略保持 Navfn。
由于 A/B 与 C 不是同一次运行，且 C 目前每个场景只有一个样本，不能进行统计显著性结论。

## 可观测性结论

C 组最终运行中：

- 覆盖搜索参与次数：双房间 92/93，岛状障碍 80/81，窄通道 85/90。
- 候选生成数量：双房间 845，岛状障碍 728，窄通道 777。
- Navfn 回退原因以 `mixed_constraints` 为主，另有 stale、detour 和 none_generated。
- 规划耗时约 40--47 ms/请求；中间点候选使候选数量显著增加，但没有在双房间和岛状障碍
  产生采用路径，说明还需要进一步优化候选排序和收益标定。

## 故障定位复核（2026-11-17）

本节基于原始 `coverage-direct-planner-events.csv`、`launch.log` 和本轮独立复现实验。复现实验
分别保存在 `results/coverage-aware-20261117-fault-repro-*`，不覆盖前述数据。家具场景每种配置
只有一个样本，结论是故障诊断而非统计比较。

### 候选未采用的实际原因

最终 C 组拒绝汇总如下。拒绝类别按请求决策分类，底层候选拒绝计数会因一个请求包含多个候选而
大于规划请求数。

| 场景 | 请求/参与 | 候选 | 采用 | 请求级主要结果 | 候选级拒绝计数（绕行/收益/评分/安全） |
|---|---:|---:|---:|---|---:|
| 双房间 | 93/92 | 845 | 0 | mixed_constraints 88，detour 4，stale 1 | 732/79/7/27 |
| 岛状障碍 | 81/80 | 728 | 0 | mixed_constraints 78，stale 1，none_generated 1，detour 1 | 617/63/14/34 |
| 窄通道 | 90/85 | 777 | 3 | mixed_constraints 77，stale 5，detour 4，none_generated 1 | 644/63/3/39 |
| 复杂家具复测 C | 300/287 | 2435 | 2 | mixed_constraints 261，none_generated 20，stale 13，detour 4 | 2080/199/28/110 |

双房间/岛状的典型请求中，最优候选本身可能比 Navfn 更长且估算新增覆盖更少，例如双房间
参考 0.385 m / 0.1925 m2，最佳候选 0.421 m / 0.1825 m2；因此它会被面积约束拒绝。另一些请求
满足面积条件却无法同时满足评分改善和其他限制，最终归为 mixed_constraints。算法不是没有运行，
而是多数局部点到点请求的安全候选相对参考路径没有足够的综合优势。扩大搜索权重或绕行上限会
改变风险偏好，现有证据不支持仅为提高采用率而这样做。

覆盖网格发布端采用 transient-local、depth 1，语义为 `100=已覆盖`、`0=目标未覆盖`、
`-1=非目标`；规划器使用 `map` frame 快照，校验尺寸、分辨率、原点、frame 和接收后 2 秒时效。
本轮事件记录有少量 stale 回退，没有证据显示覆盖语义颠倒或索引错位是低采用率的主因。

窄通道 3 次采用均是比参考路径短约 1.5--2.1 cm，而非付费绕行；规划时预计总新增面积 0.47 m2。
对应全任务 Action 虽成功，仍有 1 个航点失败，结果原因记录为补扫限制内未达完成余量，真值覆盖
89.77%，不得记作达到 90%。因此这是覆盖任务/补扫执行未达标，不足以证明所选局部路线造成漏扫。

### 复杂家具 Navfn/C 复现

两次复测均为 living_room、整图任务、`optimized` Coverage Planner、`robot_wheels` 里程、启用
ToF、480 秒墙钟上限、同一地图和机器人起点。先前不带 `collision_aware_nav` 的 Navfn 运行与 C
配置不完全一致；Launch 中启用覆盖感知会额外打开 RPP collision detection，并把 costmap inflation
半径至少设为 0.20 m。为控制这一混杂因素，又运行了显式 `--collision-aware-nav` 的 Navfn 匹配对照。

| 配置 | Action/超时 | 真值覆盖 | 真值里程 | 航点完成/失败 | costmap 延后 | Contact recovery | 定位 LOST |
|---|---|---:|---:|---:|---:|---:|---:|
| Navfn 默认安全配置 | 480 s 超时取消 | 84.81% | 41.94 m | 110/5 | 0 | 14 | 0 |
| Navfn 匹配 collision-aware | 480 s 超时取消 | 88.83% | 38.33 m | 99/13 | 11 | 1 | 0 |
| CoverageAware 匹配配置 | 480 s 超时取消 | 74.72% | 29.56 m | 73/17 | 16 | 2 | 1 |

CoverageAware 日志在约 74.6% 时连续出现 RPP `detected collision ahead` 和 `Controller patience
exceeded`，之后任务记录为 `PAUSED completed=73 next=92/108`；Localization Health Monitor 随后
报告 `pose stale while robot is moving` 并转为 `Localization LOST`，暂停期间覆盖率和里程基本不再
变化，最终由 benchmark 的 480 秒上限取消 Action。也就是说 480 秒不是 planner 自身超时。
匹配 Navfn 未出现定位 LOST，且到达 88.83%，但也因时限未完成；C 组明确更差的单样本结果与任务
暂停/定位健康链条同时发生。现有采样没有局部 costmap 栅格快照、每个 waypoint 的终态明细或
同一时刻的 TF/速度 rosbag，因而不能证明是候选路径导致了碰撞，也不能排除自定义 BT、controller
重规划负载与计算开销的间接影响。

C 复测共有 300 个规划请求，287 次进入覆盖搜索，只采用 2 次；平均规划 136.45 ms，累计预计
新增面积仅 0.135 m2，采用路线相对 Navfn 总计短 0.047 m。该数据不支持“新增覆盖值得额外绕行”，
且规划计算耗时比简单地图高。C 的 17 个失败/16 个延后航点与匹配 Navfn 的 13/11 相近，但只各
一次运行，不能作显著性推断。

### 插件内部修复及验证范围

`coverage_plan()` 原来在持有 global costmap mutex 时完成全部 A* 候选搜索和评分，且对候选路径的
footprint 检查也在该长临界区内。现已调整为：仅在锁内复制 costmap、读取端点和参考路径栅格；释放
锁后执行候选搜索； footprint 检查时再短暂加锁，并确认 costmap 几何没有变化；坐标从已捕获的
原点/分辨率还原。若几何变化或完整 footprint 检查失败，该候选仍被拒绝并回退 Navfn。没有更改
评分、绕行约束、footprint 标准或默认规划器。该修复减少搜索期间阻塞 costmap 更新的机会，但尚未
完成修改后 Gazebo A/B/C 性能复测，不能声称它修复家具停滞。

实际命令与验证：

```bash
python3 scripts/run_cleaning_benchmark.py --scenario living_room --runs 1 --domain 81 --timeout 480 --output results/coverage-aware-20261117-fault-repro-navfn --no-gui --compare-poses
python3 scripts/run_cleaning_benchmark.py --scenario living_room --runs 1 --domain 83 --timeout 480 --output results/coverage-aware-20261117-fault-repro-navfn-matched --no-gui --compare-poses --collision-aware-nav
python3 scripts/run_cleaning_benchmark.py --scenario living_room --runs 1 --domain 82 --timeout 480 --output results/coverage-aware-20261117-fault-repro-coverage-aware --no-gui --compare-poses --coverage-aware-navigation
python3 scripts/run_cleaning_benchmark.py --scenario narrow --runs 1 --domain 84 --timeout 300 --output results/coverage-aware-20261117-post-lockfix --no-gui --compare-poses --coverage-aware-navigation
colcon build --packages-select robot_coverage_planner
colcon test --packages-select robot_coverage_planner
```

修改后构建通过，planner package 22 个 gtest 全通过。现有 C 组复杂家具实测在修改前完成，修改后
另完成窄通道 Gazebo 集成 smoke test：Action 成功、16/16 导航目标成功、0 个失败航点；61 个规划
请求中 59 次参与搜索、生成 553 个候选并采用 5 次，平均规划 35.44 ms。旧 Direct 插件同场景
单次复测也成功：14/14 导航目标成功、0 个失败航点、14 次直连成功、44 次 Navfn 回退，真值轨迹
3.43 m，任务覆盖 91.26%、重复率 0；CoverageAware 对应 3.86 m、任务覆盖 91.62%、重复率
6.49%。两者各一例，绝对差异约 0.43 m，不能当作稳定收益或显著差异。该场景 benchmark 是
`REGIONS` scope，报告的全地图 Gazebo 真值覆盖率为 38.05% 不能与整图 90% 验收比较；Action 的
区域任务完成状态只说明所选区域任务完成。该单次 smoke test 证明锁粒度修改后的规划器可运行，
不是与修改前窄通道整图样本的性能对照，也没有覆盖家具故障回归。

## 数据限制与归因结论

当前不能提供完整、同版本、同配置、每场景至少三次的 A/B/C 数据：旧 A/B 属于前一日期与实验
配置；C 的双房间、岛状、窄通道各一例，家具复测 A/C 各一例且均超时，L 形 C 未运行；本轮也未
运行 B Direct。故不把这些结果拼成一张具有因果含义的 A/B/C 性能表。

当前结论是：覆盖感知规划器未产生稳定清扫收益，首要算法原因有直接事件证据支持，即大量局部
请求缺少能同时满足安全、收益、绕行和评分门槛的优胜候选，且全局任务的清扫顺序/补扫收益无法由
单段点到点规划充分控制。家具场景的暂停直接伴随 RPP 碰撞预测失败与 Localization LOST；匹配
Navfn 的一次运行没有复现定位 LOST，但未达到清扫目标，仍有失败航点。因此家具问题不能仅靠
CoverageAware 插件内部调参修复。下一步优先为 Navfn/C 增加逐航点结果、local costmap、TF/速度
同步 rosbag 和定位健康事件关联，并复测至少 3 个配对种子；同时检查任务管理器对 live-costmap
延后航点的重试/终止条件。覆盖感知插件应继续作为可选实验策略，Navfn 保持默认。

## 结论

本轮已经完成覆盖感知规划器的工程实现、数据快照与失效回退、非负候选搜索、清扫半径收益
计算、绕行约束、完整 footprint 检查、事件观测和 Gazebo 验证。实验没有证明新策略在当前
参数和地图集合上稳定减少总里程或补扫里程，因此不将其设为默认；Navfn 继续作为默认全局
规划器，旧 `direct` 和新 `coverage_aware` 均保持独立可选。
