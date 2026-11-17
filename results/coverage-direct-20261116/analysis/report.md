# Coverage Execution Analysis

Date: 2026-11-16

## Scope and provenance

This report analyzes the five final single-run experiments under
`results/coverage-direct-20261116/`:

- `final3-multi-room`
- `final-islands`
- `final-narrow`
- `final-l-shape-v2`
- `final-furniture`

Each run contains `waypoints.csv`, `nav2-global-plans.csv`,
`nav2-global-plan-poses.csv`, `pose-comparison.csv`, `result.json`, and the
Gazebo launch log. The analysis output is in the sibling `analysis/` folder.

## Coordinate and time alignment

All three sources use the `map` frame and simulation nanosecond timestamps:

1. `waypoints.csv` records the coverage planner route at planning time and
   the goals actually submitted to `NavigateToPose`.
2. `nav2-global-plans.csv` records every `/plan` message, grouped by goal and
   plan generation. `nav2-global-plan-poses.csv` contains the corresponding
   pose samples.
3. `pose-comparison.csv` records the manager TF pose and Gazebo truth pose at
   roughly 10 Hz. The truth pose is used for traveled distance and revisit
   metrics.

The analysis assigns each first Nav2 plan to the most recent coverage route
whose planning timestamp precedes the plan timestamp. This separates the
initial sweep from later gap-fill routes without treating a plan message as
robot motion.

The TF-to-truth position error is small enough for this alignment: the median
error is 0.035--0.040 m across the five runs and the maximum is 0.089--0.156 m.

## Distance accounting

`execution-summary.csv` reports three different quantities:

- `coverage_planned_m`: the main sweep planner's reported route length.
- `nav2_first_plan_m`: the sum of only the first global plan for each submitted
  goal. This is a planning diagnostic, not traveled distance.
- `truth_path_m`: the independent Gazebo truth distance and the authoritative
  execution metric.

`nav2_all_plan_messages_m` is intentionally diagnostic only. It includes
periodic replans of paths the robot has not yet traversed and therefore must
not be interpreted as mileage. The final runs produced 90--152 replans and
the all-message sum was 2.4--3.9 times the first-plan sum.

## Stage-level findings

The route-level output is in `execution-stages.csv`:

| Scene | Route 1 first plans | Gap routes first plans | Truth path | Revisit |
| --- | ---: | ---: | ---: | ---: |
| multi_room | 14.18 m / 32 goals | 3.56 m / 6 goals | 12.89 m | 17.58% |
| islands | 14.10 m / 32 goals | 3.11 m / 6 goals | 11.70 m | 17.19% |
| narrow | 11.84 m / 26 goals | 8.59 m / 18 goals | 15.27 m | 32.92% |
| l_shape | 17.76 m / 39 goals | 11.24 m / 19 goals | 19.87 m | 34.17% |
| furniture | 18.13 m / 38 goals | 5.78 m / 11 goals | 16.50 m | 22.88% |

The narrow and L-shaped layouts spend a larger share of first-plan distance in
gap routes. Their higher revisit ratios are therefore primarily associated
with reaching residual cells through already traversed corridors, not with a
single long straight connector.

The trajectory PNGs show the same relationship spatially: the black truth
trace follows the room topology and repeatedly crosses doorways or central
aisles, while the colored coverage routes are sparse waypoint geometry and the
gray lines are Nav2's first global paths.

## Cause classification

### A. Coverage route

The planner route is not just lane endpoints. `CoveragePlan::append()` inserts
grid-feasible Wavefront connections and compresses visible portions, so route
ordering and connection cost already influence the candidate path. Route 1 is
the main sweep; routes 2--4 are later gap-fill plans in these runs.

The main route is not sufficient to reach the final target in narrow and
L-shaped maps. These runs generated 8.59 m and 11.24 m of first-plan gap-route
distance respectively, and their truth revisit ratios were 32.92% and 34.17%.
That is consistent with topology-driven return travel and residual coverage,
not evidence that all repeated travel is a planner defect.

### B. Nav2 global planning

The manager sends each coverage pose as a separate `NavigateToPose` goal.
Nav2 recomputes a global path from the current robot pose, so the exact
Wavefront connector geometry is not passed as a controller path. The first
Nav2 plan sum exceeds the coverage route length in every final run, while the
truth distance is lower than the first-plan sum. RPP, goal tolerance, and
replanning therefore change the executed geometry.

The current `straight` column in the five final runs is only a post-hoc
collinearity test. It cannot prove that `CoverageDirectPlanner` returned the
path because Navfn can also produce a near-collinear path. Those five runs
predate the runtime decision instrumentation.

The separately instrumented islands v10 run provides the direct evidence:
102 `createPlan()` calls, 92 direct attempts, 7 direct returns, 85 footprint
rejections, 10 distance-limit bypasses, 0 costmap rejections, and 95 Navfn
fallbacks. Thus the direct hit rate was 7/92 = 7.6% among attempts, or 7/102
= 6.9% of plugin calls. The event stream is matched to navigation goals by
simulation timestamp and target position; gap goals use a different behavior
tree and do not invoke this sweep-only plugin. The plugin now also records a
request-level event when Navfn throws or is cancelled, while preserving the
original exception semantics.

### C. Control and execution

The truth trace is shorter than the first-plan sum, which is consistent with
controller corner cutting and stopping at goal tolerance. The benchmark Nav2
configuration uses RPP with a 0.25 m lookahead and a 0.20 m XY goal tolerance;
the normal upstream configuration uses a 0.40 m lookahead and tighter goal
tolerances. These settings affect how closely the robot follows sparse
waypoint geometry, but the existing five runs do not isolate their causal
effect from map topology.

### D. Task management

The logs show live-costmap waypoint adjustment and deferral, plus additional
gap passes. This is most pronounced in narrow and L-shaped runs. These actions
preserve safety and task completion but can add necessary return travel. No
navigation goals failed in the five final runs; therefore the observed
regressions are not explained by retry loops or failed-goal recovery.

## Interpretation of the first-round regressions

The direct connector experiment changed execution only selectively. The
geometric straight-plan fraction among first plans was approximately 15.8% in
multi-room, 13.2% in islands, 6.8% in narrow, 10.3% in L-shape, and 6.1% in
furniture. This is too small and too topology-dependent to expect a uniform
improvement.

The islands regression is consistent with a coverage-layer mismatch: the main
planned route is short, but the run still adjusts 10 sweep goals, performs
three gap routes, and ends at 17.19% revisit. The direct connector cannot
remove obstacle-induced detours or the need to revisit access corridors.

The L-shape regression is dominated by the topology of the central connector:
the run uses 19 gap-route goals and reaches 34.17% revisit. Shortening local
connectors does not eliminate the required passage between arms.

Furniture improves total truth mileage, but its 90% milestone is nearly flat
because the residual cells are reached late. This points to the timing and
ordering of gap fill rather than a simple global-path length problem.

## Decision

No second-round runtime code change is justified by these data. The current
direct planner remains an explicit opt-in experiment and keeps Navfn fallback,
RPP, costmap checks, cancellation, and recovery. A stronger change would need
controlled A/B runs that isolate one factor at a time:

1. same coverage route with direct planner disabled/enabled;
2. same route with RPP lookahead and goal tolerance changed independently;
3. same route with gap-fill ordering or distance budget changed;
4. repeated runs per map, not a single run.

The highest-value next experiment is repeated fixed-condition A/B testing,
not relaxing the footprint check. The v10 result shows that the dominant
decision is a safety rejection (`footprint_blocked`), so changing that gate
without controller and clearance validation would trade mileage for risk.
