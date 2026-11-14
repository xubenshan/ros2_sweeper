// SPDX-License-Identifier: Apache-2.0
#include "robot_cleaning_manager/planning_request.hpp"

#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace robot_cleaning_manager
{
namespace
{
bool has_grid_geometry(const nav_msgs::msg::OccupancyGrid & grid)
{
  const auto & info = grid.info;
  return std::isfinite(info.resolution) && info.resolution > 0 && info.width && info.height &&
         grid.data.size() == static_cast<std::size_t>(info.width) * info.height;
}
}  // namespace

PlanningRequestBuilder::PlanningRequestBuilder(PlanningRequestOptions options)
: options_(options)
{
  if (!std::isfinite(options_.cleaning_radius_m) || options_.cleaning_radius_m <= 0.0 ||
    !std::isfinite(options_.target_path_efficiency) || options_.target_path_efficiency < 0.0 ||
    options_.target_path_efficiency > 1.0 ||
    !std::isfinite(options_.minimum_gap_distance_budget_m) ||
    options_.minimum_gap_distance_budget_m < 0.0)
  {
    throw std::invalid_argument("invalid planning request options");
  }
}

robot_cleaning_interfaces::srv::PlanCoverage::Request PlanningRequestBuilder::build(
  const PlanningRequestContext & context) const
{
  robot_cleaning_interfaces::srv::PlanCoverage::Request request;
  request.regions = context.regions;
  request.start = context.start;
  request.gap_fill = context.gap_fill;
  request.target_coverage = context.target_coverage;
  request.covered = context.covered;
  if (!context.ignore_failure_exclusions) {
    request.excluded = context.failure_exclusions;
  }
  if (context.gap_fill && !context.deferred_gap_goals.empty() &&
    context.deferred_gap_goals.size() == context.current_path_size)
  {
    request.excluded.insert(
      request.excluded.end(), context.deferred_gap_goals.begin(),
      context.deferred_gap_goals.end());
  }
  if (context.gap_fill && options_.target_path_efficiency > 0.0 &&
    has_grid_geometry(context.covered))
  {
    const auto target_cells = std::count_if(
      context.covered.data.begin(), context.covered.data.end(),
      [](int value) {return value >= 0;});
    const double resolution = context.covered.info.resolution;
    const double ideal_path_m = target_cells * resolution * resolution /
      (2.0 * options_.cleaning_radius_m);
    request.distance_budget_m = std::max(
      options_.minimum_gap_distance_budget_m,
      ideal_path_m / options_.target_path_efficiency - context.distance_traveled_m);
  }
  return request;
}
}  // namespace robot_cleaning_manager
