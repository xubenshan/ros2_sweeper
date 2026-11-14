// SPDX-License-Identifier: Apache-2.0
#include "robot_coverage_planner/baseline_coverage_plan.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <stdexcept>

namespace robot_coverage_planner
{
namespace
{
constexpr double kSweepTrackingAllowance = 0.025;
constexpr double kGapCompletionAllowance = 0.01;
constexpr double kFailureExclusionRadiusM = 0.20;
constexpr int kMaximumGapGoals = 24;
}

BaselineCoveragePlan::BaselineCoveragePlan(
  const GridMap & grid, PlanOptions options, Cell start, const Mask & blocked_centers)
: grid_(grid), options_(options), geometry_(grid, options, start, blocked_centers)
{
}

Mask BaselineCoveragePlan::target_floor(const std::vector<Region> & regions) const
{
  return geometry_.target_floor(regions);
}

Mask BaselineCoveragePlan::center_mask(const std::vector<Region> & regions) const
{
  Mask result = geometry_.reachable();
  if (regions.empty()) {
    return result;
  }
  for (int i = 0; i < grid_.size(); ++i) {
    const auto [x, y] = grid_.center(grid_.cell(i));
    result[i] = result[i] && std::any_of(
      regions.begin(), regions.end(), [x, y](const Region & region) {
        return x >= region.min_x && x <= region.max_x &&
               y >= region.min_y && y <= region.max_y;
      });
  }
  return result;
}

void BaselineCoveragePlan::append_connector(
  std::vector<Cell> & path, Cell & from, Cell to) const
{
  if (from == to) {
    return;
  }
  if (grid_.straight(reachable(), from, to)) {
    path.push_back(to);
    from = to;
    return;
  }
  const auto transit = Wavefront(grid_, reachable(), from).path_to(to);
  if (transit.empty()) {
    return;
  }
  std::size_t begin = 0;
  while (begin + 1 < transit.size()) {
    std::size_t end = begin + 1;
    while (end + 1 < transit.size() &&
      grid_.straight(reachable(), transit[begin], transit[end + 1]))
    {
      ++end;
    }
    path.push_back(transit[end]);
    begin = end;
  }
  from = to;
}

double BaselineCoveragePlan::trace(
  Cell start, const std::vector<Cell> & path, const Mask & target, Mask & swept) const
{
  double length = 0.0;
  for (const auto point : path) {
    const int dx = point.x - start.x;
    const int dy = point.y - start.y;
    const int steps = std::max(std::abs(dx), std::abs(dy));
    for (int i = 1; i <= steps; ++i) {
      const double part = static_cast<double>(i) / steps;
      const Cell sample{start.x + static_cast<int>(std::lround(part * dx)),
        start.y + static_cast<int>(std::lround(part * dy))};
      grid_.stamp(swept, target, sample, options_.cleaning_radius);
    }
    length += std::hypot(dx, dy) * grid_.resolution;
    start = point;
  }
  return length;
}

std::vector<Cell> BaselineCoveragePlan::sweep(
  Cell start, const std::vector<Region> & regions, double target_coverage,
  const Mask & task_floor) const
{
  if (!std::isfinite(target_coverage) || target_coverage <= 0.0 || target_coverage > 1.0) {
    throw std::invalid_argument("invalid target coverage");
  }
  if (!task_floor.empty() && task_floor.size() != static_cast<std::size_t>(grid_.size())) {
    throw std::invalid_argument("target grid does not match the map");
  }
  const auto centers = center_mask(regions);
  auto target = task_floor.empty() ? target_floor(regions) : task_floor;
  if (!regions.empty() && !task_floor.empty()) {
    const auto zone_floor = target_floor(regions);
    for (int i = 0; i < grid_.size(); ++i) {
      target[i] = target[i] && zone_floor[i];
    }
  }
  const int target_cells = std::count(target.begin(), target.end(), 1);
  if (target_cells == 0) {
    return {};
  }
  const int desired = static_cast<int>(std::ceil(
      std::min(1.0, target_coverage + kSweepTrackingAllowance) * target_cells));
  const int lane_spacing = static_cast<int>(std::clamp(std::round(
      2.0 * options_.cleaning_radius * (1.0 - options_.row_overlap) / grid_.resolution),
      1.0, static_cast<double>(std::max(grid_.width, grid_.height))));
  const int waypoint_step = static_cast<int>(std::max(
      1.0, std::round(options_.waypoint_spacing / grid_.resolution)));

  int min_x = grid_.width;
  int max_x = -1;
  int min_y = grid_.height;
  int max_y = -1;
  for (int i = 0; i < grid_.size(); ++i) {
    if (centers[i]) {
      const auto cell = grid_.cell(i);
      min_x = std::min(min_x, cell.x);
      max_x = std::max(max_x, cell.x);
      min_y = std::min(min_y, cell.y);
      max_y = std::max(max_y, cell.y);
    }
  }
  if (max_x < min_x || max_y < min_y) {
    return {};
  }
  // Sweep along the longer map extent. This is a geometry rule, not route
  // optimization, and therefore remains deterministic across maps.
  const bool vertical = (max_y - min_y) > (max_x - min_x);
  const int cross_first = vertical ? min_x : min_y;
  const int cross_last = vertical ? max_x : max_y;
  const int along_first = vertical ? min_y : min_x;
  const int along_last = vertical ? max_y : max_x;
  const auto at = [vertical](int cross, int along) {
      return vertical ? Cell{cross, along} : Cell{along, cross};
    };

  std::vector<std::vector<Cell>> lines;
  bool reverse_line = false;
  for (int cross = cross_first; cross <= cross_last; cross += lane_spacing) {
    std::vector<std::vector<Cell>> spans;
    for (int along = along_first; along <= along_last; ++along) {
      const auto cell = at(cross, along);
      if (!centers[grid_.index(cell)]) {
        continue;
      }
      const int first = along;
      while (along + 1 <= along_last && centers[grid_.index(at(cross, along + 1))]) {
        ++along;
      }
      std::vector<Cell> span{at(cross, first)};
      for (int sample = first + waypoint_step; sample < along; sample += waypoint_step) {
        span.push_back(at(cross, sample));
      }
      if (span.back() != at(cross, along)) {
        span.push_back(at(cross, along));
      }
      spans.push_back(std::move(span));
    }
    if (reverse_line) {
      std::reverse(spans.begin(), spans.end());
      for (auto & span : spans) {
        std::reverse(span.begin(), span.end());
      }
    }
    lines.insert(lines.end(), spans.begin(), spans.end());
    reverse_line = !reverse_line;
  }

  std::vector<Cell> route;
  Mask swept(grid_.size(), 0);
  grid_.stamp(swept, target, start, options_.cleaning_radius);
  auto cursor = start;
  for (const auto & span : lines) {
    for (const auto point : span) {
      std::vector<Cell> connector;
      auto next = cursor;
      append_connector(connector, next, point);
      if (connector.empty() && point != cursor) {
        continue;
      }
      trace(cursor, connector, target, swept);
      route.insert(route.end(), connector.begin(), connector.end());
      cursor = point;
      if (std::count(swept.begin(), swept.end(), 1) >= desired) {
        return route;
      }
    }
  }
  return route;
}

std::vector<Cell> BaselineCoveragePlan::gap_route(
  Cell start, Mask missing, const std::vector<Cell> & excluded,
  int desired, double distance_budget, int & deficit) const
{
  Mask initially_cleaned(grid_.size(), 0);
  grid_.stamp(initially_cleaned, missing, start, options_.cleaning_radius);
  int cleaned = std::count(initially_cleaned.begin(), initially_cleaned.end(), 1);
  for (int i = 0; i < grid_.size(); ++i) {
    missing[i] = missing[i] && !initially_cleaned[i];
  }
  std::vector<Cell> route;
  double traveled = 0.0;
  for (int goal = 0; goal < kMaximumGapGoals && (desired == 0 || cleaned < desired); ++goal) {
    const Wavefront distances(grid_, reachable(), start);
    double nearest = std::numeric_limits<double>::infinity();
    int best_gain = 0;
    Cell selected{};
    for (int i = 0; i < grid_.size(); ++i) {
      if (!reachable()[i] || grid_.cell(i) == start) {
        continue;
      }
      const auto candidate = grid_.cell(i);
      const double distance = distances.cost(candidate) * grid_.resolution;
      if (distance < 0.0 ||
        (distance_budget > 0.0 && traveled + distance > distance_budget) ||
        std::any_of(excluded.begin(), excluded.end(), [&](Cell failure) {
          return std::hypot(candidate.x - failure.x, candidate.y - failure.y) *
                 grid_.resolution < kFailureExclusionRadiusM;
        }))
      {
        continue;
      }
      Mask disk(grid_.size(), 0);
      grid_.stamp(disk, missing, candidate, options_.cleaning_radius);
      const int gain = std::count(disk.begin(), disk.end(), 1);
      if (gain > 0 && (distance < nearest || (distance == nearest && gain > best_gain))) {
        nearest = distance;
        best_gain = gain;
        selected = candidate;
      }
    }
    if (best_gain == 0) {
      break;
    }
    std::vector<Cell> connector;
    auto end = start;
    append_connector(connector, end, selected);
    if (connector.empty()) {
      break;
    }
    Mask swept(grid_.size(), 0);
    const double length = trace(start, connector, missing, swept);
    if (distance_budget > 0.0 && traveled + length > distance_budget) {
      break;
    }
    traveled += length;
    start = selected;
    route.insert(route.end(), connector.begin(), connector.end());
    for (int i = 0; i < grid_.size(); ++i) {
      cleaned += swept[i];
      missing[i] = missing[i] && !swept[i];
    }
  }
  deficit = std::max(0, desired - cleaned);
  return route;
}

std::vector<Cell> BaselineCoveragePlan::gaps(
  Cell start, const std::vector<Region> & regions, const Mask & covered,
  const std::vector<Cell> & excluded, const Mask &, const Mask & task_floor,
  double target_coverage, double distance_budget) const
{
  auto missing = task_floor.empty() ? target_floor(regions) : task_floor;
  if (missing.size() != static_cast<std::size_t>(grid_.size()) || covered.size() != missing.size()) {
    throw std::invalid_argument("coverage grid does not match the map");
  }
  if (!std::isfinite(target_coverage) || target_coverage < 0.0 || target_coverage > 1.0 ||
    !std::isfinite(distance_budget) || distance_budget < 0.0)
  {
    throw std::invalid_argument("invalid gap coverage target or distance budget");
  }
  const int target_area = std::count(missing.begin(), missing.end(), 1);
  for (int i = 0; i < grid_.size(); ++i) {
    missing[i] = missing[i] && !covered[i];
  }
  const int already_covered = target_area - std::count(missing.begin(), missing.end(), 1);
  const int desired = target_coverage == 0.0 ? 0 : std::max(1,
    static_cast<int>(std::ceil(std::min(1.0, target_coverage + kGapCompletionAllowance) *
    target_area)) - already_covered);
  int deficit = 0;
  const double active_budget = target_coverage == 0.0 ? 0.0 : distance_budget;
  auto route = gap_route(start, missing, excluded, desired, active_budget, deficit);
  if (deficit > 0 && distance_budget > 0.0) {
    route = gap_route(start, std::move(missing), excluded, desired, 0.0, deficit);
  }
  return route;
}
}  // namespace robot_coverage_planner
