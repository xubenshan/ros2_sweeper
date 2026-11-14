// SPDX-License-Identifier: Apache-2.0
#include "robot_coverage_planner/coverage_plan.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <random>
#include <stdexcept>
#include <tuple>

namespace robot_coverage_planner
{
namespace
{
constexpr double kTau = 6.28318530718;
constexpr double kEstimatedGapPenalty = 2.5;
constexpr double kMissingCellPenalty = 10.0;
constexpr double kRefinementCellValue = 2.4;
constexpr double kSweepTrackingAllowance = 0.025;
constexpr double kGapCompletionAllowance = 0.01;
constexpr int kMaximumOpenFloorCells = 30000;
constexpr int kMaximumGapGoals = 24;
constexpr double kFailedGoalExclusionRadiusM = 0.20;
constexpr double kMinimumGapGoalTravelM = 0.15;
}

std::vector<SweepCell> decompose(const GridMap & grid, const Mask & reachable)
{
  std::vector<SweepCell> result;
  std::vector<Span> previous;
  std::vector<std::size_t> previous_ids;
  for (int y = 0; y < grid.height; ++y) {
    std::vector<Span> current;
    for (int x = 0; x < grid.width; ++x) {
      if (!reachable[grid.index({x, y})]) {
        continue;
      }
      const int first = x;
      while (x + 1 < grid.width && reachable[grid.index({x + 1, y})]) {
        ++x;
      }
      current.push_back({y, first, x});
    }
    std::vector<std::vector<std::size_t>> parents(current.size());
    std::vector<int> child_count(previous.size(), 0);
    for (std::size_t i = 0; i < current.size(); ++i) {
      for (std::size_t j = 0; j < previous.size(); ++j) {
        if (current[i].first <= previous[j].last && previous[j].first <= current[i].last) {
          parents[i].push_back(j);
          ++child_count[j];
        }
      }
    }
    std::vector<std::size_t> ids;
    for (std::size_t i = 0; i < current.size(); ++i) {
      if (parents[i].size() == 1 && child_count[parents[i].front()] == 1) {
        ids.push_back(previous_ids[parents[i].front()]);
      } else {
        ids.push_back(result.size());
        result.emplace_back();
      }
      result[ids.back()].push_back(current[i]);
    }
    previous = std::move(current);
    previous_ids = std::move(ids);
  }
  return result;
}

CoveragePlan::CoveragePlan(
  const GridMap & grid, PlanOptions options, Cell start, const Mask & blocked_centers)
: grid_(grid), options_(options)
{
  if (!std::isfinite(options.cleaning_radius) || options.cleaning_radius <= 0 ||
    !std::isfinite(options.row_overlap) || options.row_overlap < 0 || options.row_overlap >= 1 ||
    !std::isfinite(options.waypoint_spacing) || options.waypoint_spacing <= 0 ||
    !std::isfinite(options.turn_cost) || options.turn_cost < 0 ||
    !std::isfinite(options.edge_margin) || options.edge_margin < 0)
  {
    throw std::invalid_argument("invalid coverage parameters");
  }
  auto free = grid_.drivable(options.robot_radius + options.safety_margin);
  if (!blocked_centers.empty()) {
    if (blocked_centers.size() != free.size()) {
      throw std::invalid_argument("blocked center grid does not match the map");
    }
    for (std::size_t i = 0; i < free.size(); ++i) {
      free[i] = free[i] && !blocked_centers[i];
    }
  }
  if (!grid_.valid(start) || !free[grid_.index(start)]) {
    throw std::invalid_argument("start does not fit in navigable space");
  }
  reachable_ = Wavefront(grid_, free, start).reachable();
}

Mask CoveragePlan::within(const std::vector<Region> & regions) const
{
  Mask result(grid_.size(), regions.empty());
  if (regions.empty()) {
    return result;
  }
  for (int i = 0; i < grid_.size(); ++i) {
    const auto position = grid_.center(grid_.cell(i));
    const double x = position.first;
    const double y = position.second;
    result[i] = std::any_of(regions.begin(), regions.end(), [x, y](const Region & region) {
        return x >= region.min_x && x <= region.max_x && y >= region.min_y && y <= region.max_y;
      });
  }
  return result;
}

Mask CoveragePlan::target_floor(const std::vector<Region> & regions) const
{
  auto allowed = within(regions);
  if (options_.edge_margin > 0.0) {
    Mask free(grid_.size(), 0);
    Mask obstacles(grid_.size(), 0);
    for (int i = 0; i < grid_.size(); ++i) {
      free[i] = grid_.occupancy[i] == 0;
      obstacles[i] = !free[i];
    }
    const auto start = std::find(reachable_.begin(), reachable_.end(), 1);
    const auto connected = Wavefront(grid_, free, grid_.cell(start - reachable_.begin())).reachable();
    const auto clearance = grid_.manhattan_distance(obstacles);
    const double body = std::max(1.0, std::round(options_.robot_radius / grid_.resolution));
    const double brush = std::max(1.0, std::round(options_.cleaning_radius / grid_.resolution));
    const double edge = std::round(options_.edge_margin / grid_.resolution);
    Mask centers(grid_.size(), 0);
    for (int i = 0; i < grid_.size(); ++i) {
      centers[i] = connected[i] && clearance[i] > body;
    }
    const auto distance = grid_.manhattan_distance(centers);
    for (int i = 0; i < grid_.size(); ++i) {
      allowed[i] = allowed[i] && connected[i] && clearance[i] > edge && distance[i] <= brush;
    }
    return allowed;
  }
  for (int i = 0; i < grid_.size(); ++i) {
    allowed[i] = allowed[i] && grid_.occupancy[i] == 0;
  }
  Mask target(grid_.size(), 0);
  for (int i = 0; i < grid_.size(); ++i) {
    if (reachable_[i]) {
      grid_.stamp(target, allowed, grid_.cell(i), options_.cleaning_radius);
    }
  }
  return target;
}

std::vector<std::vector<Cell>> CoveragePlan::lanes(
  const Mask & allowed, bool vertical, int phase, int spacing, double slope) const
{
  const int cross = vertical ? grid_.width : grid_.height;
  const int along = vertical ? grid_.height : grid_.width;
  const auto at = [vertical, slope](int line, int step) {
      const int offset = line + static_cast<int>(std::lround(slope * step));
      return vertical ? Cell{offset, step} : Cell{step, offset};
    };
  const auto is_allowed = [&](Cell cell) {
      return grid_.valid(cell) && allowed[grid_.index(cell)];
    };
  const double step_length = grid_.resolution * std::hypot(1.0, slope);
  const double step_cells = std::round(options_.waypoint_spacing / step_length);
  const int waypoint_step = static_cast<int>(std::clamp(step_cells, 1.0, double(along)));
  const int shift = static_cast<int>(std::lround(slope * (along - 1)));
  std::vector<std::vector<Cell>> strips;
  std::vector<std::vector<Cell>> short_strips;
  for (int line = phase - std::max(0, shift); line < cross - std::min(0, shift); line += spacing) {
    for (int step = 0; step < along; ++step) {
      if (!is_allowed(at(line, step))) {
        continue;
      }
      const int first = step;
      while (step + 1 < along && is_allowed(at(line, step + 1)) &&
        (slope == 0.0 || grid_.straight(reachable_, at(line, step), at(line, step + 1))))
      {
        ++step;
      }
      std::vector<Cell> strip{at(line, first)};
      int last = first;
      for (int position = first + 1; position <= step; ++position) {
        if (slope != 0.0 && !grid_.straight(reachable_, strip.back(), at(line, position))) {
          last = position - 1;
          strip.push_back(at(line, last));
        }
        if (position == step || position - last >= waypoint_step) {
          strip.push_back(at(line, position));
          last = position;
        }
      }
      // Target residual islands in the gap pass once the tracker knows what is missing.
      auto & destination = (step - first + 1) * step_length < 2 * options_.cleaning_radius ?
        short_strips : strips;
      destination.push_back(std::move(strip));
    }
  }
  return strips.empty() ? std::move(short_strips) : std::move(strips);
}

void CoveragePlan::append(
  std::vector<Cell> & path, Cell & from, Cell to, const Wavefront * distances) const
{
  if (from == to) {
    return;
  }
  if (grid_.straight(reachable_, from, to)) {
    path.push_back(to);
  } else {
    auto transit = distances ? distances->path_to(to) :
      Wavefront(grid_, reachable_, from).path_to(to);
    if (transit.empty()) {
      return;
    }
    std::size_t i = 0;
    while (i + 1 < transit.size()) {
      std::size_t end = i + 1;
      while (end + 1 < transit.size() && grid_.straight(reachable_, transit[i], transit[end + 1])) {
        ++end;
      }
      path.push_back(transit[end]);
      i = end;
    }
  }
  from = to;
}

std::vector<Cell> CoveragePlan::order_lanes(
  Cell start, double heading, std::vector<std::vector<Cell>> strips) const
{
  std::vector<Cell> path;
  while (!strips.empty()) {
    const Wavefront distances(grid_, reachable_, start);
    double best = std::numeric_limits<double>::infinity();
    std::size_t chosen = 0;
    bool reversed = false;
    for (std::size_t i = 0; i < strips.size(); ++i) {
      for (bool reverse : {false, true}) {
        const auto entry = reverse ? strips[i].back() : strips[i].front();
        const auto distance = distances.cost(entry);
        if (distance < 0) {
          continue;
        }
        const auto transit = distances.path_to(entry);
        const auto next = transit.size() > 1 ? transit[1] : start;
        const double bearing = next == start ? heading :
          std::atan2(next.y - start.y, next.x - start.x);
        const double score = distance * grid_.resolution +
          options_.turn_cost * std::abs(std::remainder(bearing - heading, kTau));
        if (score < best) {
          best = score;
          chosen = i;
          reversed = reverse;
        }
      }
    }
    if (!std::isfinite(best)) {
      break;
    }
    auto next = std::move(strips[chosen]);
    strips.erase(strips.begin() + chosen);
    if (reversed) {
      std::reverse(next.begin(), next.end());
    }
    for (const Cell target : next) {
      if (target != start) {
        heading = std::atan2(target.y - start.y, target.x - start.x);
      }
      append(path, start, target);
    }
  }
  return path;
}

double CoveragePlan::trace(
  Cell start, const std::vector<Cell> & path, const Mask & target, Mask & swept) const
{
  double length = 0.0;
  for (const Cell point : path) {
    const int dx = point.x - start.x;
    const int dy = point.y - start.y;
    const int steps = std::max(std::abs(dx), std::abs(dy));
    for (int i = 1; i <= steps; ++i) {
      const double fraction = static_cast<double>(i) / steps;
      const Cell sample{start.x + static_cast<int>(std::lround(fraction * dx)),
        start.y + static_cast<int>(std::lround(fraction * dy))};
      grid_.stamp(swept, target, sample, options_.cleaning_radius);
    }
    length += std::hypot(dx, dy) * grid_.resolution;
    start = point;
  }
  return length;
}

double CoveragePlan::route_cost(
  Cell start, const std::vector<Cell> & path, const Mask & target) const
{
  Mask swept(grid_.size(), 0);
  grid_.stamp(swept, target, start, options_.cleaning_radius);
  const auto length = trace(start, path, target, swept);
  const auto missed = std::count(target.begin(), target.end(), 1) -
    std::count(swept.begin(), swept.end(), 1);
  // Isolated missed cells need extra travel beyond their ideal straight-line sweep.
  const double estimated_gap_cost =
    kEstimatedGapPenalty * missed * grid_.resolution * grid_.resolution /
    (2 * options_.cleaning_radius);
  return length + estimated_gap_cost;
}

namespace
{
using LinkCosts = std::vector<std::vector<double>>;

std::vector<int> nearest_strip_order(const LinkCosts & links, int seed)
{
  const int origin = static_cast<int>(links.size()) - 1;
  const auto strip_count = static_cast<std::size_t>(origin / 2);
  std::mt19937 random(seed);
  std::uniform_real_distribution<double> perturbation(0.0, 0.75);
  std::vector<int> order;
  std::vector<bool> assigned(strip_count, false);
  int from = origin;
  while (order.size() < strip_count) {
    double nearest = std::numeric_limits<double>::infinity();
    int chosen = 0;
    for (int j = 0; j < origin; ++j) {
      if (assigned[j / 2]) {
        continue;
      }
      const double score = links[from][j] + (seed ? perturbation(random) : 0.0);
      if (score < nearest) {
        nearest = score;
        chosen = j;
      }
    }
    order.push_back(chosen);
    assigned[chosen / 2] = true;
    from = chosen ^ 1;
  }
  return order;
}

void improve_strip_order(const LinkCosts & links, std::vector<int> & order)
{
  const auto transit_cost = [&links](const std::vector<int> & entries) {
      int from = static_cast<int>(links.size()) - 1;
      double cost = 0.0;
      for (const int entry : entries) {
        cost += links[from][entry];
        from = entry ^ 1;
      }
      return cost;
    };
  for (int pass = 0; pass < 24; ++pass) {
    double lowest = transit_cost(order);
    auto improved = order;
    const auto consider = [&](std::vector<int> trial) {
        const double cost = transit_cost(trial);
        if (cost + 1e-7 < lowest) {
          lowest = cost;
          improved = std::move(trial);
        }
      };
    for (auto i = order.begin(); i != order.end(); ++i) {
      for (auto j = i; j != order.end(); ++j) {
        auto trial = order;
        const auto first = trial.begin() + (i - order.begin());
        const auto last = trial.begin() + (j - order.begin()) + 1;
        std::reverse(first, last);
        std::transform(first, last, first, [](int entry) {return entry ^ 1;});
        consider(std::move(trial));
      }
      for (std::size_t j = 0; j < order.size(); ++j) {
        if (j == static_cast<std::size_t>(i - order.begin())) {
          continue;
        }
        for (int reverse : {0, 1}) {
          auto trial = order;
          trial.erase(trial.begin() + (i - order.begin()));
          trial.insert(trial.begin() + j, *i ^ reverse);
          consider(std::move(trial));
        }
      }
    }
    if (improved == order) {
      break;
    }
    order = std::move(improved);
  }
}
}  // namespace

double CoveragePlan::score_open_floor_route(
  Cell start, const Mask & target, int desired, std::vector<Cell> & route) const
{
  const double missing_cost = kMissingCellPenalty * grid_.resolution * grid_.resolution /
    (2 * options_.cleaning_radius);
  Mask swept(grid_.size(), 0);
  grid_.stamp(swept, target, start, options_.cleaning_radius);
  auto cursor = start;
  double length = 0.0;
  int covered = 0;
  for (std::size_t i = 0; i < route.size(); ++i) {
    length += trace(cursor, {route[i]}, target, swept);
    cursor = route[i];
    covered = std::count(swept.begin(), swept.end(), 1);
    if (covered >= desired) {
      route.resize(i + 1);
      break;
    }
  }
  return length + missing_cost * std::max(0, desired - covered);
}

std::vector<Cell> CoveragePlan::connect_strips(
  Cell start, const std::vector<std::vector<Cell>> & strips, const Mask & target,
  int desired, double & best_score) const
{
  // Each strip can be entered from either end. Optimize the route over
  // oriented endpoints using the length of feasible grid connectors.
  std::vector<Cell> endpoints;
  for (const auto & strip : strips) {
    endpoints.push_back(strip.front());
    endpoints.push_back(strip.back());
  }
  const int origin = static_cast<int>(endpoints.size());
  endpoints.push_back(start);
  std::vector<std::vector<double>> links(origin + 1, std::vector<double>(origin, 0.0));
  for (int i = 0; i <= origin; ++i) {
    const Wavefront distances(grid_, reachable_, endpoints[i]);
    for (int j = 0; j < origin; ++j) {
      auto from = endpoints[i];
      std::vector<Cell> connector;
      append(connector, from, endpoints[j], &distances);
      from = endpoints[i];
      for (const auto point : connector) {
        links[i][j] += std::hypot(point.x - from.x, point.y - from.y) * grid_.resolution;
        from = point;
      }
    }
  }
  std::vector<Cell> best;
  for (int seed = 0; seed < 10; ++seed) {
    auto order = nearest_strip_order(links, seed);
    improve_strip_order(links, order);
    std::vector<Cell> route;
    auto cursor = start;
    for (const int entry : order) {
      auto strip = strips[entry / 2];
      if (entry % 2) {
        std::reverse(strip.begin(), strip.end());
      }
      for (const auto point : strip) {
        append(route, cursor, point);
      }
    }
    const double score = score_open_floor_route(start, target, desired, route);
    if (score < best_score) {
      best_score = score;
      best = std::move(route);
    }
  }
  return best;
}

std::vector<Cell> CoveragePlan::refine_sweep(
  Cell start, const Mask & target, int desired, std::vector<Cell> route) const
{
  if (route.size() < 2 || route.size() > 200) {
    return route;
  }
  route.insert(route.begin(), start);
  const auto distance = [this](Cell from, Cell to) {
      return std::hypot(to.x - from.x, to.y - from.y) * grid_.resolution;
    };
  const double value_per_cell = kRefinementCellValue * grid_.resolution * grid_.resolution /
    (2.0 * options_.cleaning_radius);
  double added = 0.0;
  for (int pass = 0; pass < 8; ++pass) {
    // Count visits per target cell to find the unique coverage contributed by
    // each pair of segments around a waypoint.
    std::vector<std::vector<int>> segment_cells(route.size());
    Mask start_disk(grid_.size(), 0);
    grid_.stamp(start_disk, target, start, options_.cleaning_radius);
    std::vector<int> visits(start_disk.begin(), start_disk.end());
    for (std::size_t i = 1; i < route.size(); ++i) {
      Mask swept(grid_.size(), 0);
      trace(route[i - 1], {route[i]}, target, swept);
      for (int cell = 0; cell < grid_.size(); ++cell) {
        if (swept[cell]) {
          segment_cells[i].push_back(cell);
          ++visits[cell];
        }
      }
    }
    const int covered = std::count_if(visits.begin(), visits.end(), [](int count) {return count > 0;});
    double best = 0.0;
    double best_extra = 0.0;
    std::size_t index = 0;
    Cell replacement{};
    const int span = static_cast<int>(std::clamp(std::round(0.20 / grid_.resolution), 1.0, 4.0));
    for (std::size_t i = 1; i + 1 < route.size(); ++i) {
      const auto from = route[i - 1];
      const auto point = route[i];
      const auto to = route[i + 1];
      const double original_length = distance(from, point) + distance(point, to);
      auto remaining_visits = visits;
      int lost = 0;
      for (std::size_t segment = i; segment <= i + 1; ++segment) {
        for (const int cell : segment_cells[segment]) {
          lost += --remaining_visits[cell] == 0;
        }
      }
      for (int dy = -span; dy <= span; ++dy) {
        for (int dx = -span; dx <= span; ++dx) {
          const Cell candidate{point.x + dx, point.y + dy};
          const double first = distance(from, candidate);
          const double second = distance(candidate, to);
          const double extra = first + second - original_length;
          if (candidate == point || first < 0.12 || second < 0.12 || extra > 0.30 ||
            added + extra > 1.70 || !grid_.straight(reachable_, from, candidate) ||
            !grid_.straight(reachable_, candidate, to))
          {
            continue;
          }
          Mask swept(grid_.size(), 0);
          trace(from, {candidate, to}, target, swept);
          int regained = 0;
          for (int cell = 0; cell < grid_.size(); ++cell) {
            regained += swept[cell] && remaining_visits[cell] == 0;
          }
          const auto gain = std::min(desired, covered - lost + regained) - std::min(desired, covered);
          const double score = value_per_cell * gain - extra;
          if (score > best + 1e-7) {
            best = score;
            index = i;
            replacement = candidate;
            best_extra = extra;
          }
        }
      }
    }
    if (index == 0) {
      break;
    }
    route[index] = replacement;
    added += best_extra;
  }
  route.erase(route.begin());
  return route;
}

std::vector<Cell> CoveragePlan::open_floor_route(
  Cell start, const Mask & allowed, const Mask & target, double target_coverage) const
{
  const auto area = std::count(target.begin(), target.end(), 1);
  if (area == 0 || grid_.size() > kMaximumOpenFloorCells) {
    return {};
  }
  // Leave a small allowance for tracking error. Rank incomplete candidates by
  // the additional travel the missing area would require.
  const int desired = static_cast<int>(std::ceil(
      std::min(1.0, target_coverage + kSweepTrackingAllowance) * area));
  const int nominal = static_cast<int>(std::clamp(std::round(
      2 * options_.cleaning_radius / grid_.resolution), 1.0, 32.0));
  double best_score = std::numeric_limits<double>::infinity();
  std::vector<Cell> best;
  for (int spacing : {nominal, nominal + 1, std::max(1, nominal - 1)}) {
    for (bool vertical : {false, true}) {
      for (double slope : {0.0, -1.0 / 6.0, 1.0 / 6.0}) {
        for (int phase = 0; phase < spacing; ++phase) {
          const auto strips = lanes(allowed, vertical, phase, spacing, slope);
          if (strips.empty() || strips.size() > 48) {
            continue;
          }
          auto route = connect_strips(start, strips, target, desired, best_score);
          if (!route.empty()) {
            best = std::move(route);
          }
        }
      }
    }
  }
  if (options_.refine_sweep) {
    return refine_sweep(start, target, desired, std::move(best));
  }
  return best;
}

std::vector<Cell> CoveragePlan::sweep(
  Cell start, const std::vector<Region> & regions, double target_coverage,
  const Mask & task_floor) const
{
  if (!std::isfinite(target_coverage) || target_coverage <= 0.0 || target_coverage > 1.0) {
    throw std::invalid_argument("invalid target coverage");
  }
  if (!task_floor.empty() && task_floor.size() != static_cast<std::size_t>(grid_.size())) {
    throw std::invalid_argument("target grid does not match the map");
  }
  std::vector<Cell> path;
  Mask assigned(grid_.size(), 0);
  std::vector<std::vector<Region>> zones;
  for (const auto & region : regions) {
    zones.push_back({region});
  }
  if (zones.empty()) {
    zones.emplace_back();
  }
  const double row_cells = std::round(
    2 * options_.cleaning_radius * (1 - options_.row_overlap) / grid_.resolution);
  const int spacing = static_cast<int>(
    std::clamp(row_cells, 1.0, static_cast<double>(std::max(grid_.width, grid_.height))));
  double heading = 0.0;
  for (const auto & zone : zones) {
    auto mask = within(zone);
    auto target = task_floor.empty() ? target_floor(zone) : mask;
    for (int i = 0; i < grid_.size(); ++i) {
      if (!task_floor.empty()) {
        target[i] = target[i] && task_floor[i];
      }
      mask[i] = mask[i] && reachable_[i] && !assigned[i];
      assigned[i] |= mask[i];
    }
    double best_cost = std::numeric_limits<double>::infinity();
    std::vector<Cell> best;
    if (options_.edge_margin > 0.0) {
      best = open_floor_route(start, mask, target, target_coverage);
    }
    if (best.empty()) {
      for (bool vertical : {false, true}) {
        const int phases = std::min(spacing, 4);
        for (int offset = 0; offset < phases; ++offset) {
          auto route = order_lanes(start, heading,
              lanes(mask, vertical, offset * spacing / phases, spacing));
          if (route.empty()) {
            continue;
          }
          const double cost = route_cost(start, route, target);
          if (cost < best_cost) {
            best_cost = cost;
            best = std::move(route);
          }
        }
      }
    }
    if (best.empty()) {
      // A zone narrower than the sampling interval may fall between both sets of lanes.
      const auto area = decompose(grid_, mask);
      Cell from = start;
      for (const auto & cell : area) {
        const auto & row = cell[cell.size() / 2];
        append(best, from, {row.first + (row.last - row.first) / 2, row.y});
      }
    }
    if (!best.empty()) {
      const Cell previous = best.size() > 1 ? best[best.size() - 2] :
        (path.empty() ? start : path.back());
      start = best.back();
      heading = std::atan2(start.y - previous.y, start.x - previous.x);
      path.insert(path.end(), best.begin(), best.end());
    }
  }
  return path;
}

std::vector<Cell> CoveragePlan::gaps(
  Cell start, const std::vector<Region> & regions, const Mask & covered,
  const std::vector<Cell> & excluded, const Mask & priority, const Mask & task_floor,
  double target_coverage, double distance_budget) const
{
  auto missing = task_floor.empty() ? target_floor(regions) : task_floor;
  if (missing.size() != static_cast<std::size_t>(grid_.size()) || covered.size() != missing.size() ||
    (!priority.empty() && priority.size() != missing.size()))
  {
    throw std::invalid_argument("coverage or priority grid does not match the map");
  }
  const auto target_area = std::count(missing.begin(), missing.end(), 1);
  for (int i = 0; i < grid_.size(); ++i) {
    missing[i] = missing[i] && !covered[i];
  }
  if (!std::isfinite(target_coverage) || target_coverage < 0.0 || target_coverage > 1.0 ||
    !std::isfinite(distance_budget) || distance_budget < 0.0)
  {
    throw std::invalid_argument("invalid gap coverage target or distance budget");
  }
  int deficit = 0;
  double distance = 0.0;
  if (target_coverage == 0.0) {
    return gap_route(start, std::move(missing), excluded, priority, 0, 0.0, 1.0, 0,
        deficit, distance);
  }
  const auto already_covered = target_area - std::count(missing.begin(), missing.end(), 1);
  const int desired = std::max(1, static_cast<int>(std::ceil(
      std::min(1.0, target_coverage + kGapCompletionAllowance) * target_area) - already_covered));
  std::vector<Cell> best;
  int best_deficit = std::numeric_limits<int>::max();
  double best_distance = std::numeric_limits<double>::infinity();
  const auto search = [&](double budget) {
      for (int seed = 0; seed < 4; ++seed) {
        for (double weight : {1.0, 1.4, 1.8, 2.2, 2.6}) {
          auto route = gap_route(start, missing, excluded, priority,
              desired, budget, weight, seed, deficit, distance);
          if (!route.empty() &&
            std::tie(deficit, distance) < std::tie(best_deficit, best_distance))
          {
            best_deficit = deficit;
            best_distance = distance;
            best = std::move(route);
          }
        }
      }
    };
  search(distance_budget);
  if (best_deficit > 0 && distance_budget > 0.0) {
    // A short partial route can consume a whole gap pass. Prefer the shortest
    // route that reaches the coverage target, even beyond the efficiency budget.
    search(0.0);
  }
  return best;
}

std::vector<Cell> CoveragePlan::gap_route(
  Cell start, Mask missing, const std::vector<Cell> & excluded, const Mask & priority,
  int desired, double distance_budget, double distance_weight, int seed,
  int & coverage_deficit, double & distance) const
{
  struct Candidate
  {
    Cell cell;
    double score;
  };
  const double brush = grid_.cells_for_radius(options_.cleaning_radius);
  const int radius = static_cast<int>(std::min(std::ceil(brush),
      static_cast<double>(std::max(grid_.width, grid_.height))));
  const double goal_cost = 2.0 * options_.cleaning_radius;
  const auto weight = [&priority, seed](int index) {
      return seed != 3 && !priority.empty() && priority[index] ? 4 : 1;
    };
  const auto travel_cost = [distance_weight](double length) {
      return distance_weight == 1.0 ? length : std::pow(length, distance_weight);
    };
  std::vector<Cell> result;
  double traveled = 0.0;
  int cleaned = 0;
  std::mt19937 generator(seed);
  std::uniform_real_distribution<double> preference(0.75, 1.25);
  for (int remaining = 0; remaining < kMaximumGapGoals &&
    (desired == 0 || cleaned < desired); ++remaining)
  {
    const Wavefront distances(grid_, reachable_, start);
    std::vector<Candidate> candidates;
    for (int i = 0; i < grid_.size(); ++i) {
      const Cell candidate = grid_.cell(i);
      const double straight_distance = std::hypot(candidate.x - start.x, candidate.y - start.y) *
        grid_.resolution;
      if (!reachable_[i] || candidate == start || distances.cost(candidate) < 0 ||
        (desired > 0 && straight_distance < kMinimumGapGoalTravelM) ||
        (distance_budget > 0.0 && traveled + straight_distance > distance_budget) ||
        std::any_of(excluded.begin(), excluded.end(), [&](Cell failure) {
          return std::hypot(candidate.x - failure.x, candidate.y - failure.y) *
                 grid_.resolution < kFailedGoalExclusionRadiusM;
        }))
      {
        continue;
      }
      int gain = 0;
      for (int dy = -radius; dy <= radius; ++dy) {
        for (int dx = -radius; dx <= radius; ++dx) {
          const Cell point{candidate.x + dx, candidate.y + dy};
          if (dx * dx + dy * dy <= brush * brush + 1e-9 && grid_.valid(point)) {
            const int index = grid_.index(point);
            if (missing[index]) {
              gain += weight(index);
            }
          }
        }
      }
      if (gain > 0) {
        candidates.push_back({candidate, gain /
          travel_cost(goal_cost + distances.cost(candidate) * grid_.resolution)});
      }
    }
    if (candidates.empty()) {
      break;
    }
    // Rank a bounded shortlist by new floor swept along the actual connector.
    const auto limit = candidates.begin() + std::min<std::size_t>(
        seed == 0 ? 16 : 32, candidates.size());
    std::partial_sort(candidates.begin(), limit, candidates.end(),
      [this](const Candidate & a, const Candidate & b) {
        if (a.score != b.score) {
          return a.score > b.score;
        }
        return grid_.index(a.cell) < grid_.index(b.cell);
      });
    double best = 0.0;
    double best_length = 0.0;
    std::vector<Cell> best_path;
    Mask best_swept;
    for (auto it = candidates.begin(); it != limit; ++it) {
      std::vector<Cell> connector;
      Cell from = start;
      append(connector, from, it->cell, &distances);
      if (connector.empty()) {
        continue;
      }
      Mask swept(grid_.size(), 0);
      const double length = trace(start, connector, missing, swept);
      if (distance_budget > 0.0 && traveled + length > distance_budget) {
        continue;
      }
      int gain = 0;
      for (int i = 0; i < grid_.size(); ++i) {
        if (swept[i]) {
          gain += weight(i);
        }
      }
      const double score = gain / travel_cost(length + goal_cost * connector.size()) *
        (seed == 0 ? 1.0 : preference(generator));
      if (score > best) {
        best = score;
        best_length = length;
        best_path = std::move(connector);
        best_swept = std::move(swept);
      }
    }
    if (best_path.empty()) {
      break;
    }
    start = best_path.back();
    traveled += best_length;
    result.insert(result.end(), best_path.begin(), best_path.end());
    for (int i = 0; i < grid_.size(); ++i) {
      cleaned += best_swept[i];
      missing[i] = missing[i] && !best_swept[i];
    }
  }
  coverage_deficit = std::max(0, desired - cleaned);
  distance = traveled;
  return result;
}
}  // namespace robot_coverage_planner
