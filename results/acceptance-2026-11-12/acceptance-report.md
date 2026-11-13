# ROS 2 Sweeper Engineering Acceptance

Date: 2026-11-12

## Verdict

The task-completion decision defect is fixed and covered by unit tests. All five ROS 2 packages build, and all 30 tests pass. Nine valid static Gazebo runs were completed, three per layout. Six runs reached the independent 90% truth-coverage target; two Action-success runs ended just below it, and one narrow-layout run correctly aborted at 89.71% truth coverage. The narrow layout remains inefficient, and Nav2 lifecycle startup remains intermittent. This is a partial acceptance, not a full pass.

Gazebo truth metrics below are independent evaluation only. Runtime coverage is the cleaning manager's TF/grid estimate and is the value used for task decisions. Action success therefore does not imply that the independent truth evaluator passed.

## Static Gazebo Runs

All valid runs used the same generated map, whole-map task scope, 90% requested coverage, robot configuration, and benchmark parameters. Invalid Nav2-start attempts are excluded from the nine metric samples and retained in the raw result folders.

| Layout / run | Runtime coverage | Truth coverage | Truth distance | Efficiency | Revisit | Gap passes | Action | Result |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | --- | --- |
| Multi-room 1 | 90.51% | 89.31% | 12.67 m | 86.32% | 17.89% | 3 | SUCCEEDED | Runtime target reached; truth target missed |
| Multi-room 2 | 91.20% | 90.86% | 12.35 m | 88.54% | 18.40% | 3 | SUCCEEDED | Truth target reached |
| Multi-room 3 | 91.03% | 90.51% | 12.33 m | 88.70% | 14.33% | 3 | SUCCEEDED | Truth target reached |
| Islands 1 | 90.94% | 91.90% | 12.78 m | 76.66% | 21.63% | 3 | SUCCEEDED | Truth target reached; 5 navigation goals skipped |
| Islands 2 | 90.75% | 92.98% | 11.02 m | 88.97% | 9.14% | 3 | SUCCEEDED | Truth target reached; 10 navigation goals skipped |
| Islands 3 | 91.01% | 91.58% | 10.01 m | 97.88% | 5.01% | 3 | SUCCEEDED | Truth target reached; 10 navigation goals skipped |
| Narrow 1 | 92.03% | 92.23% | 13.98 m | 67.32% | 27.01% | 2 | SUCCEEDED | Truth target reached; 6 navigation goals skipped |
| Narrow 2 | 90.31% | 89.97% | 14.35 m | 65.61% | 31.52% | 3 | SUCCEEDED | Runtime target reached; truth target missed; 6 goals skipped |
| Narrow 3 | 89.64% | 89.71% | 14.41 m | 65.31% | 33.15% | 3 | ABORTED | Gap budget exhausted below target; 7 goals skipped |

Layout means over the three valid samples:

| Layout | Mean truth coverage | Mean truth distance | Mean efficiency | Mean revisit | Distance at first 90% truth coverage |
| --- | ---: | ---: | ---: | ---: | ---: |
| Multi-room | 90.23% | 12.45 m | 87.85% | 16.87% | 12.23 m, 2/3 runs |
| Islands | 92.16% | 11.27 m | 87.84% | 11.93% | 10.54 m, 3/3 runs |
| Narrow | 90.64% | 14.25 m | 66.08% | 30.56% | 12.61 m, 1/3 runs |

The route-planner polyline is reported separately in each `result.json`; it is not substituted for executed Gazebo distance. The benchmark records distance at first truth coverage thresholds when reached. The CSV/JSON reports and full launch logs are under `static-3x/`.

## Defect Fix

The manager previously treated its optional completion margin as mandatory even after the gap-fill budget was exhausted. It could consequently abort a task whose runtime estimate had met the requested business target. Completion now has three outcomes:

- Estimate at or above `min(1.0, target + margin)`: finish successfully with margin.
- Gap budget exhausted and estimate at or above the unchanged business target: finish successfully and state that the margin was not reached.
- Gap budget exhausted below the business target: abort and report the unmet target and exhausted budget.

The default 1 percentage-point margin remains intact. The requested target was not lowered. Nav2 failure, skipped-goal counts, and the last navigation failure remain in the result reason. Gazebo truth is not consumed by the runtime manager.

Evidence: `completion_decision.hpp`, `completion_decision_test.cpp`, and `cleaning_task_manager.cpp`. Four decision tests pass. The multi-room run 1 and narrow run 2 illustrate why Action status and truth acceptance are separate: both Actions succeeded on runtime estimates above 90%, while truth was below 90%. Narrow run 3 remained an Action abort because both estimates were below target.

## Dynamic Obstacle and Recovery Tests

- Dynamic Gazebo benchmark, one run: 61 Gazebo obstacle pose updates; six sweep goals deferred by the live costmap; two gap passes; Action `SUCCEEDED`; runtime coverage 91.54%; truth coverage 91.28%; executed distance 14.76 m; efficiency 79.61%; revisit 18.73%. The obstacle was moved during cleaning and parked outside the task map, after which cleaning completed. This confirms one integrated run, not a three-run dynamic benchmark.
- Gazebo handoff/checkpoint test: Nav2 displacement 0.234 m; edge-following displacement 0.181 m; teleoperation displacement 0.122 m; 87 covered cells restored exactly after manager restart; coverage increased to 159 cells after resuming; final Action cancellation status was `CANCELED`.
- Gazebo navigation fault test: an out-of-map Nav2 goal returned `ABORTED` with error code 204. Shutting down Nav2 during cleaning caused zero commanded velocity within 1.77 seconds; CleanTask returned `ABORTED` with reason `Nav2 stopped during the cleaning task`.
- Nav2 cancel rejection test uses a controlled ROS Action server, not Gazebo: task transitions through `PAUSED` and `STOPPING`, aborts after 8.13 seconds with `Nav2 did not acknowledge cancel; motion authority revoked`, and sends only one navigation goal.
- Dynamic replan test uses a controlled Nav2 Action server and costmap publisher, not Gazebo: six navigation failures were injected, gap replanning occurred, the blocked region was replanned after obstacle removal, and the test canceled the task successfully. This is integration logic coverage, not physical Gazebo evidence.
- Action lifecycle test on the running Gazebo/Nav2 graph: normal fixed-route task succeeded; pause and resume services worked; persisted task state restored after manager restart and proceeded to another waypoint; the task then returned `CANCELED` on request.

## Startup Reliability

The benchmark now waits by polling the Nav2 lifecycle state and `/navigate_to_pose` Action Server, with a bounded 90-second deadline. It also reports early launch exit and the last observed lifecycle state. It does not use a fixed sleep as a readiness substitute.

Startup is still not reliable enough to claim a fix. During the nine valid static runs, five launch attempts failed before retry succeeded: one multi-room attempt, two islands attempts, and two narrow attempts. Logs show the lifecycle manager failing its asynchronous `bt_navigator/get_state` request during activation; the manager then aborts bringup. The additional service-readiness gate was tried and reverted because it did not prevent the same failure. No speculative launch change is retained. Root cause of the underlying Nav2 lifecycle request failure remains unresolved.

## Build and Tests

- ROS 2 Jazzy VM: `/home/xbs/robot_sweeper`, sourcing `/home/xbs/oomwoo_ws` as underlay.
- Build: all five packages succeeded: `robot_cleaning_interfaces`, `robot_motion_safety`, `robot_cleaning_manager`, `robot_coverage_planner`, `robot_sweeper_bringup`.
- Tests: `colcon test` succeeded; `colcon test-result --verbose` reported 30 tests, 0 errors, 0 failures, 0 skipped.
- Test logs: `build-final.log`, `colcon-test-final.log`, `colcon-test-result-final.log`.
- VM package prefix was `/home/xbs/robot_sweeper/ros2_ws/install/robot_cleaning_manager`; the deployed source checksums matched the local edited sources.

## Reproduction

Run from `/home/xbs/robot_sweeper` on the Ubuntu Jazzy VM:

```bash
source /opt/ros/jazzy/setup.bash
source /home/xbs/oomwoo_ws/install/setup.bash
./scripts/run_cleaning_benchmark.sh \
  --scenario layouts --runs 3 --target .90 --timeout 450 --startup-retries 2 \
  --no-gui --open-floor --collision-aware-nav --clearance-control \
  --sweep-goal-tolerance .10 --precise-gap-navigation --guard-gap-goals \
  --finish-main-before-gap --gap-progress-timeout 18 --gap-retries 0 \
  --refine-sweep --target-gap-coverage --gap-efficiency-target .80 \
  --domain 121 --output results/acceptance-2026-11-12/static-3x
```

Other tested commands:

```bash
ROS_DOMAIN_ID=172 python3 scripts/verify_gazebo_handoff.py results/acceptance-2026-11-12/gazebo-handoff
ROS_DOMAIN_ID=173 python3 scripts/verify_navigation_faults.py --output results/acceptance-2026-11-12/navigation-faults
ROS_DOMAIN_ID=162 python3 scripts/verify_coverage_replan.py --during-gap
ROS_DOMAIN_ID=161 python3 scripts/verify_cancel_timeout.py
```

## Remaining Issues

1. Nav2 lifecycle startup still intermittently fails; lifecycle-manager activation root cause is not established.
2. Narrow layout is not robustly accepted: one of three truth results was below 90%, one Action aborted, mean truth distance was 14.25 m, mean efficiency 66.08%, and mean revisit 30.56%.
3. Runtime coverage can overestimate Gazebo truth near the target. One multi-room and one narrow run returned Action success while independent truth was just below 90%.
4. Dynamic obstacle integration was run once. Repeated dynamic tests and a Gazebo-observed, explicitly isolated then reopened region are still needed.
5. Navigation timeout was not observed in these Gazebo runs (zero timeout events). Cancel-acknowledgement timeout was verified only against a controlled ROS Action server.

## Change Summary

- Added a pure completion-decision helper and four unit tests.
- Connected the decision helper to task completion and gap-budget exhaustion handling; preserved the configured business target and margin.
- Fixed the test target include path so the new header is found by `ament_cmake_gtest`.
- Improved benchmark Nav2 readiness polling and launch-exit diagnostics.
- Added an output-directory argument to `verify_navigation_faults.py` so new evidence can be saved without overwriting prior results.
- No coverage planner algorithm or scenario-specific map-coordinate logic was changed in this pass.
