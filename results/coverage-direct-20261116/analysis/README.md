# Coverage execution analysis

The CSVs align each run's coverage waypoints, first Nav2 global plan for each NavigateToPose goal, and Gazebo truth samples.

`nav2_first_plan_m` sums only the first `/plan` message per goal. `nav2_all_plan_messages_m` is diagnostic only and must not be treated as traveled distance. `geometric_straight_*` detects collinear plan poses after the fact; it is not a definitive CoverageDirect hit.

The trajectory PNGs show coverage waypoints by route, first Nav2 plans in gray, and the Gazebo truth trace in black.
