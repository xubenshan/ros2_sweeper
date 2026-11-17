# Coordinate and Timestamp Alignment

The benchmark records coverage waypoints and Nav2 global plans in `map`.
Gazebo truth is published with `header.frame_id=map`; its node applies a
startup SE(2) offset from the odometry source to the configured spawn pose.
The pose comparison uses each truth message timestamp to query
`map <- base_footprint`, so the two pose columns are compared at matching
simulation timestamps in the same frame.

The Gazebo `world` frame is not a ROS TF frame in this experiment. The
`ground_truth` node publishes a `PoseStamped` in `map` after applying its
startup SE(2) offset from `/odom_truth` (wheel mode) or `/odom` (truth mode)
to the configured spawn pose. The benchmark therefore queries `map <-
base_footprint` at the truth message timestamp; it does not subtract a
`world` pose from a `map` pose. `odom` remains an intermediate TF frame used
by Nav2's local costmap.

This report also independently fits `truth ~= R(tf) + t` as a diagnostic. The
fit is near identity and reduces, but does not eliminate, the residual. That
is evidence against an unmodelled fixed frame offset being the explanation for
the original 3.5--4.0 cm values. The remaining residual includes timestamp
interpolation, TF publication latency and controller/localization error; the
fitted transform is not applied to coverage or mileage metrics.

The original report's 0.035--0.040 values are metres, not metres times
100; they correspond to approximately 3.5--4.0 centimetres.

See `coordinate-alignment.csv` and the five `coordinate-alignment-*.png`
plots for per-scene fit parameters and visual overlay checks.
