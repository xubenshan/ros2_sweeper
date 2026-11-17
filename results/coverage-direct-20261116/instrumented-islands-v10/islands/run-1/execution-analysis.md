# Islands v10 execution alignment

Run directory: `results/coverage-direct-20261116/instrumented-islands-v10/islands/run-1`. All timestamps are simulation nanoseconds. Truth distance is computed from time windows of the Gazebo truth trace; `/plan` lengths are diagnostic only and are not added as traveled distance.

| Segment | Goals | Truth distance (m) | Planner events | Direct success | Direct rejected | Navfn fallback | Deferred count |
|---|---:|---:|---:|---:|---:|---:|---:|
| sweep | 29 | 9.384 | 102 | 7 | 85 | 95 | 6 |
| sweep_adjusted | 7 | 1.373 | 19 | 0 | 19 | 19 | 0 |
| sweep_original | 22 | 8.011 | 83 | 7 | 66 | 76 | 6 |
| gap | 4 | 1.734 | 0 | 0 | 0 | 0 | 0 |
| deferred_jump | 1 | 2.179 | 18 | 0 | 8 | 18 | 6 |

The main skipped-waypoint jump is sequence 27, from planned index 25 to index 32. Its execution window contains 2.179 m of truth motion and 18 `/plan` messages. Six sweep waypoints were deferred according to the task-manager log.

The jump is a task-layer deferral, not a navigation retry: there were no
failed or timed-out goals and no recovery episodes in this run. The robot
went from `(0.275, -0.725)` to `(1.225, 0.275)` with a 2.179 m truth window.
The map overlay shows this motion following the accessible right-side aisle
around the island obstacles. The 18 global plans in that window sum to
26.425 m, which is a replanning diagnostic and not 26.425 m of travel.

The four-goal gap pass adds 1.734 m after the sweep. Its first connection to
`(1.225, -0.375)` is a residual-floor access move along the right corridor;
the data do not isolate it as avoidable without an A/B run that changes gap
ordering while keeping the safety guards enabled. The seven adjusted sweep
windows account for 1.373 m. They are safety-driven target substitutions,
not failed-goal recovery, and their avoidable fraction is not identifiable
from this single run.

As a separate centerline-grid diagnostic, approximately 68% of sweep-window
motion and 71% of gap-window motion revisited previously traversed centerline
cells at 5 cm resolution. This is directional evidence of corridor return
travel, not the authoritative coverage-meter revisit metric; it should not be
used to label all of that motion as waste because island bypasses and access
to residual floor necessarily reuse corridors.

The planner counters for this run are 102 requests, 92 direct attempts, 7 direct successes, 85 footprint rejections, 10 distance rejections, 0 costmap rejections, and 95 Navfn fallbacks. The 95 fallbacks include both the 85 rejected direct attempts and the 10 requests rejected before attempting a direct path because they exceeded the 1.20 m direct connector limit.

No planner exception event was observed in v10. The current plugin preserves
Navfn's exception behavior but emits a final request event before rethrowing,
so future cancellation or planner-failure runs will not silently lose a
request from the decision log.
