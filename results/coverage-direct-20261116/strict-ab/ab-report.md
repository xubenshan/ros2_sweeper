# Strict CoverageDirectPlanner A/B Validation

Date: 2026-11-17

## Experimental control

Group A disabled `direct_sweep_navigation` and used Navfn. Group B enabled
`CoverageDirectPlanner` only for the sweep behavior tree. Both groups used the
same optimized coverage algorithm, generated or frozen map assets, initial
pose, robot geometry, RPP controller, costmaps, goal tolerance, gap settings,
recovery policy, target coverage, and `--compare-poses` diagnostics.

The direct planner is not used by gap navigation. Each run records the actual
`CoverageDirectPlanner::createPlan()` decision, rather than inferring a hit
from the geometry of a published `/plan`.

## Results

The machine-readable table is `ab-summary.csv`. `final_truth_path_mean_m` and
`path_to_90_mean_m` are computed from Gazebo truth. Replanning messages and
their path lengths are diagnostic only and are not added to traveled distance.

| Scene | Group | n | Task success | Truth coverage | 90% path | Final truth path | Revisit | Direct hits / requests |
|---|---:|---:|---:|---:|---:|---:|---:|---:|
| Multi-room | A | 1 | 1/1 | 90.40% | 12.22 m | 12.39 m | 14.20% | - |
| Multi-room | B | 1 | 1/1 | 90.97% | 12.31 m | 13.39 m | 18.78% | 22/110 (20.0%) |
| Islands | A | 2 | 2/2 | 92.28% | 11.22 m | 11.52 m | 15.28% | - |
| Islands | B | 2 | 2/2 | 91.65% | 9.99 m | 11.05 m | 13.65% | 11/178 (6.2%) |
| Narrow | A | 3 | 2/3 | 91.04% | 14.86 m | 15.85 m | 36.81% | - |
| Narrow | B | 3 | 1/3 | 92.05% | 13.63 m | 15.12 m | 34.22% | 24/293 (8.2%) |
| L-shape | A | 1 | 1/1 | 91.54% | 18.14 m | 18.86 m | 26.67% | - |
| L-shape | B | 1 | 1/1 | 90.70% | 18.83 m | 19.25 m | 33.99% | 24/134 (17.9%) |
| Furniture | A | 1 | 1/1 | 89.57% | n/a | 16.82 m | 25.41% | - |
| Furniture | B | 1 | 1/1 | 91.39% | 16.17 m | 16.79 m | 25.45% | 16/136 (11.8%) |

The islands and narrow groups have repeated samples. The other three scenes
have one valid run per group in this final matrix, so their differences are
observations, not stable performance claims. The old L-shape run using the
`baseline` coverage algorithm is excluded because it changed a second
experimental variable.

## Planner decisions

Across the instrumented B runs, direct planning was uncommon and safety
checks dominated the outcome. Islands recorded 11 direct successes in 178
requests (6.2%); narrow recorded 24/293 (8.2%); L-shape 24/134 (17.9%);
furniture 16/136 (11.8%); and multi-room 22/110 (20.0%). Most non-successful
attempts were rejected by the footprint check and then fell back to Navfn.
The planner therefore acts as a selective short-connector optimization, not
as a replacement for Navfn. It must not be judged by collinearity of `/plan`.

## Stage-level interpretation

The aligned records use `map` for coverage waypoints, Nav2 `/plan`, and the
Gazebo truth topic. TF is queried as `map <- base_footprint` at each truth
simulation timestamp. `world` is a Gazebo coordinate space and is not
subtracted directly from ROS coordinates. The coordinate-alignment analysis
reports approximately 3.5--4.0 cm median TF/truth residual on the five-map
series, with larger tails in furniture runs; this is not evidence by itself
of an AMCL frame offset.

The main repeated-travel sources are:

- **Islands:** live-costmap waypoint adjustment and deferred sweep goals alter
  the later route. The robot also has to use the side corridor around islands;
  gap passes and their order account for much of the final difference. The
  direct connector cannot remove this topology cost.
- **Narrow:** the sweep repeatedly returns through the only usable passage.
  Three gap passes, deferred/adjusted goals, and skipped goals after failed
  navigation attempts dominate the tail. A direct hit rate below 10% cannot
  explain away this necessary corridor traffic.
- **L-shape:** the central connection between arms is revisited during gap
  filling. In the paired single runs, B had more gap travel and higher
  revisit despite 24 direct hits, which is evidence against making the plugin
  the default based on this map.
- **Furniture:** the direct run reached 90% truth coverage with nearly the
  same final mileage and revisit rate. The A run stopped below 90% truth
  coverage even though the task Action returned success, showing that task
  completion and truth acceptance must remain separate metrics.
- **Multi-room:** B did not reduce final mileage and had higher revisit. The
  direct planner shortened selected local connectors but did not control gap
  ordering or region transitions.

## Decision

No additional source change is justified by this matrix. The existing
implementation remains a safe opt-in strategy: it is loaded only when
`direct_sweep_navigation:=true`, uses exact costmap and footprint checks, and
falls back to Navfn for long, blocked, cancelled, or otherwise rejected
requests. Relaxing the footprint threshold, replacing NavigateToPose with
FollowPath, or rewriting the coverage order would not be evidence-driven.

For the stable default, keep Navfn as the default. Keep CoverageDirectPlanner
available for controlled experiments and maps where repeated runs demonstrate
a benefit. The highest-value next experiment is not a navigation rewrite; it
is a controlled study of gap-pass ordering and waypoint deferral while
retaining the same safety checks.
