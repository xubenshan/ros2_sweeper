// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <functional>
#include <optional>
#include <vector>

#include <geometry_msgs/msg/point.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>

namespace robot_cleaning_manager
{
using PointCost = std::function<int(const geometry_msgs::msg::Point &)>;

struct WaypointGuardConfig
{
  double adjustment_radius_m{0.15};
  double maximum_adjustment_connector_m{0.80};
  double turn_clearance_margin_m{0.035};
  double turn_diagonal_clearance_m{0.025};
  double short_connector_guard_m{1.20};
};

class WaypointGuard
{
public:
  explicit WaypointGuard(WaypointGuardConfig config = {});

  static bool has_grid_geometry(const nav_msgs::msg::OccupancyGrid & grid);
  static int cost_at(
    const nav_msgs::msg::OccupancyGrid & grid, const geometry_msgs::msg::Point & point);
  static bool is_between_on_line(
    const std::vector<geometry_msgs::msg::PoseStamped> & path, std::size_t index);
  static bool is_sharp_turn(
    const geometry_msgs::msg::PoseStamped & from,
    const std::vector<geometry_msgs::msg::PoseStamped> & path, std::size_t index);
  static bool clear_connector(
    double resolution, const PointCost & point_cost,
    const geometry_msgs::msg::PoseStamped & from,
    const geometry_msgs::msg::PoseStamped & to, bool allow_unknown = false);

  int turn_clearance_cost(
    const PointCost & point_cost, const geometry_msgs::msg::Point & point) const;
  std::optional<geometry_msgs::msg::PoseStamped> nearby_clear_goal(
    const nav_msgs::msg::OccupancyGrid & grid, double sampling_resolution,
    const PointCost & goal_cost, const PointCost & connector_cost,
    const geometry_msgs::msg::PoseStamped & start,
    const geometry_msgs::msg::PoseStamped & goal) const;

  const WaypointGuardConfig & config() const noexcept {return config_;}

private:
  WaypointGuardConfig config_;
};
}  // namespace robot_cleaning_manager
