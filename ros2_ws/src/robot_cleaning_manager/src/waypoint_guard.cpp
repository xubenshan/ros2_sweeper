// SPDX-License-Identifier: Apache-2.0
#include "robot_cleaning_manager/waypoint_guard.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace robot_cleaning_manager
{
namespace
{
constexpr int kLethalCost = 99;
constexpr int kMaximumAdjustmentCost = 97;
constexpr double kCostTieBreakWeightM = 0.002;
constexpr double kCollinearityToleranceM = 0.025;
constexpr double kSharpTurnThresholdRad = 1.0;
constexpr double kMinimumHeadingSegmentM = 0.06;
constexpr double kTau = 6.28318530718;

std::pair<int, int> cell_at(
  const nav_msgs::msg::OccupancyGrid & grid, const geometry_msgs::msg::Point & point)
{
  const auto & origin = grid.info.origin;
  const auto & q = origin.orientation;
  const double yaw = std::atan2(2 * (q.w * q.z + q.x * q.y),
      1 - 2 * (q.y * q.y + q.z * q.z));
  const double dx = point.x - origin.position.x;
  const double dy = point.y - origin.position.y;
  return {
    static_cast<int>(std::floor(
      (std::cos(yaw) * dx + std::sin(yaw) * dy) / grid.info.resolution)),
    static_cast<int>(std::floor(
      (-std::sin(yaw) * dx + std::cos(yaw) * dy) / grid.info.resolution))};
}
}  // namespace

WaypointGuard::WaypointGuard(WaypointGuardConfig config)
: config_(config)
{
  if (!std::isfinite(config_.adjustment_radius_m) || config_.adjustment_radius_m < 0.0 ||
    !std::isfinite(config_.maximum_adjustment_connector_m) ||
    config_.maximum_adjustment_connector_m <= 0.0 ||
    !std::isfinite(config_.turn_clearance_margin_m) || config_.turn_clearance_margin_m < 0.0 ||
    !std::isfinite(config_.turn_diagonal_clearance_m) ||
    config_.turn_diagonal_clearance_m < 0.0 ||
    !std::isfinite(config_.short_connector_guard_m) || config_.short_connector_guard_m <= 0.0)
  {
    throw std::invalid_argument("invalid waypoint guard configuration");
  }
}

bool WaypointGuard::has_grid_geometry(const nav_msgs::msg::OccupancyGrid & grid)
{
  const auto & info = grid.info;
  return std::isfinite(info.resolution) && info.resolution > 0 && info.width && info.height &&
         grid.data.size() == static_cast<std::size_t>(info.width) * info.height;
}

int WaypointGuard::cost_at(
  const nav_msgs::msg::OccupancyGrid & grid, const geometry_msgs::msg::Point & point)
{
  const auto [x, y] = cell_at(grid, point);
  if (x < 0 || y < 0 || x >= static_cast<int>(grid.info.width) ||
    y >= static_cast<int>(grid.info.height))
  {
    return -1;
  }
  return grid.data[y * grid.info.width + x];
}

bool WaypointGuard::clear_connector(
  double resolution, const PointCost & point_cost,
  const geometry_msgs::msg::PoseStamped & from,
  const geometry_msgs::msg::PoseStamped & to, bool allow_unknown)
{
  const auto & start = from.pose.position;
  const auto & goal = to.pose.position;
  const auto length = std::hypot(goal.x - start.x, goal.y - start.y);
  const auto steps = static_cast<int>(std::clamp(
      std::ceil(2.0 * length / resolution), 1.0, 1024.0));
  for (int i = 1; i <= steps; ++i) {
    const double part = static_cast<double>(i) / steps;
    geometry_msgs::msg::Point sample;
    sample.x = start.x + part * (goal.x - start.x);
    sample.y = start.y + part * (goal.y - start.y);
    const auto cost = point_cost(sample);
    if (cost >= kLethalCost || (!allow_unknown && cost < 0)) {
      return false;
    }
  }
  return true;
}

std::optional<geometry_msgs::msg::PoseStamped> WaypointGuard::nearby_clear_goal(
  const nav_msgs::msg::OccupancyGrid & grid, double sampling_resolution,
  const PointCost & goal_cost, const PointCost & connector_cost,
  const geometry_msgs::msg::PoseStamped & start,
  const geometry_msgs::msg::PoseStamped & goal) const
{
  const auto & from = start.pose.position;
  const auto & intended = goal.pose.position;
  if (start.header.frame_id != grid.header.frame_id ||
    std::hypot(intended.x - from.x, intended.y - from.y) >
    config_.maximum_adjustment_connector_m)
  {
    return std::nullopt;
  }
  std::optional<geometry_msgs::msg::PoseStamped> best;
  double best_score = std::numeric_limits<double>::infinity();
  const double step = grid.info.resolution;
  const int span = static_cast<int>(std::min(
      6.0, std::floor(config_.adjustment_radius_m / step + 1e-6)));
  for (int dy = -span; dy <= span; ++dy) {
    for (int dx = -span; dx <= span; ++dx) {
      const double offset = std::hypot(dx, dy) * step;
      if (offset > config_.adjustment_radius_m + 1e-6) {
        continue;
      }
      auto candidate = goal;
      candidate.pose.position.x += dx * step;
      candidate.pose.position.y += dy * step;
      const auto cost = goal_cost(candidate.pose.position);
      const double score = offset + kCostTieBreakWeightM * cost;
      if (cost >= 0 && cost <= kMaximumAdjustmentCost && score < best_score &&
        clear_connector(sampling_resolution, connector_cost, start, candidate))
      {
        best_score = score;
        best = candidate;
      }
    }
  }
  return best;
}

bool WaypointGuard::is_between_on_line(
  const std::vector<geometry_msgs::msg::PoseStamped> & path, std::size_t index)
{
  if (index == 0 || index + 1 >= path.size()) {
    return false;
  }
  const auto & a = path[index - 1].pose.position;
  const auto & b = path[index].pose.position;
  const auto & c = path[index + 1].pose.position;
  const double dx = c.x - a.x;
  const double dy = c.y - a.y;
  const double along = (b.x - a.x) * dx + (b.y - a.y) * dy;
  return along > 0.0 && along < dx * dx + dy * dy &&
         std::abs((b.x - a.x) * dy - (b.y - a.y) * dx) <=
         kCollinearityToleranceM * std::hypot(dx, dy);
}

bool WaypointGuard::is_sharp_turn(
  const geometry_msgs::msg::PoseStamped & from,
  const std::vector<geometry_msgs::msg::PoseStamped> & path, std::size_t index)
{
  const auto & start = from.pose.position;
  const auto & goal = path[index].pose.position;
  const double incoming = std::atan2(goal.y - start.y, goal.x - start.x);
  const auto & q = from.pose.orientation;
  const double current = std::atan2(2 * (q.w * q.z + q.x * q.y),
      1 - 2 * (q.y * q.y + q.z * q.z));
  const auto changes_heading = [](double a, double b) {
      return std::abs(std::remainder(a - b, kTau)) > kSharpTurnThresholdRad;
    };
  if (std::hypot(goal.x - start.x, goal.y - start.y) > kMinimumHeadingSegmentM &&
    changes_heading(current, incoming))
  {
    return true;
  }
  if (index + 1 == path.size()) {
    return false;
  }
  const auto & next = path[index + 1].pose.position;
  return changes_heading(incoming, std::atan2(next.y - goal.y, next.x - goal.x));
}

int WaypointGuard::turn_clearance_cost(
  const PointCost & point_cost, const geometry_msgs::msg::Point & point) const
{
  int cost = point_cost(point);
  const double axial = config_.turn_clearance_margin_m;
  const double diagonal = config_.turn_diagonal_clearance_m;
  const std::array<std::pair<double, double>, 8> offsets{{
      {axial, 0.0}, {-axial, 0.0}, {0.0, axial}, {0.0, -axial},
      {diagonal, diagonal}, {-diagonal, diagonal},
      {diagonal, -diagonal}, {-diagonal, -diagonal}}};
  for (const auto & [dx, dy] : offsets) {
    auto sample = point;
    sample.x += dx;
    sample.y += dy;
    cost = std::max(cost, point_cost(sample));
  }
  return cost;
}
}  // namespace robot_cleaning_manager
