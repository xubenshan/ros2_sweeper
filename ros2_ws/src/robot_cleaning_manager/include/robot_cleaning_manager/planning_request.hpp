// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include <geometry_msgs/msg/point.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <robot_cleaning_interfaces/srv/plan_coverage.hpp>

namespace robot_cleaning_manager
{
struct PlanningRequestOptions
{
  double cleaning_radius_m{0.20};
  double target_path_efficiency{0.0};
  double minimum_gap_distance_budget_m{0.50};
};

struct PlanningRequestContext
{
  std::vector<std::string> regions;
  geometry_msgs::msg::PoseStamped start;
  bool gap_fill{false};
  float target_coverage{0.90F};
  double distance_traveled_m{0.0};
  nav_msgs::msg::OccupancyGrid covered;
  std::vector<geometry_msgs::msg::Point> failure_exclusions;
  std::vector<geometry_msgs::msg::Point> deferred_gap_goals;
  std::size_t current_path_size{0};
  bool ignore_failure_exclusions{false};
};

class PlanningRequestBuilder
{
public:
  explicit PlanningRequestBuilder(PlanningRequestOptions options);
  robot_cleaning_interfaces::srv::PlanCoverage::Request build(
    const PlanningRequestContext & context) const;

private:
  PlanningRequestOptions options_;
};
}  // namespace robot_cleaning_manager
