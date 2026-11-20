// SPDX-License-Identifier: Apache-2.0
#include "robot_coverage_planner/coverage_search.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <queue>
#include <stdexcept>

namespace robot_coverage_planner
{
namespace
{
constexpr std::array<int, 8> DX{{1, 1, 0, -1, -1, -1, 0, 1}};
constexpr std::array<int, 8> DY{{0, 1, 1, 1, 0, -1, -1, -1}};
constexpr int HEADINGS = 9;
struct Entry {double estimate; double cost; int state;
  bool operator>(const Entry & rhs) const {return estimate > rhs.estimate;}};

std::vector<double> coverage_potential(const SearchGrid & g, const SearchOptions & o)
{
  const int count = g.width * g.height;
  const int radius = static_cast<int>(std::ceil(o.cleaning_radius / g.resolution));
  std::vector<double> potential(static_cast<std::size_t>(count), 0.0);
  for (int cell = 0; cell < count; ++cell) {
    const int x = cell % g.width, y = cell / g.width;
    int target_cells = 0, uncovered_cells = 0;
    for (int oy = -radius; oy <= radius; ++oy) for (int ox = -radius; ox <= radius; ++ox) {
      if (ox * ox + oy * oy > radius * radius) {continue;}
      const int nx = x + ox, ny = y + oy;
      if (nx < 0 || ny < 0 || nx >= g.width || ny >= g.height) {continue;}
      const auto value = g.coverage[ny * g.width + nx];
      if (value < 0) {continue;}
      ++target_cells;
      if (value == 0) {++uncovered_cells;}
    }
    if (target_cells > 0) {
      potential[cell] = static_cast<double>(uncovered_cells) / target_cells;
    }
  }
  return potential;
}

std::vector<int> search(const SearchGrid & g, int start, int goal,
  const SearchOptions & o, double discount, const std::vector<double> & potential)
{
  const int count = g.width * g.height;
  const int initial = start * HEADINGS + 8;
  std::vector<double> dist(static_cast<std::size_t>(count) * HEADINGS,
    std::numeric_limits<double>::infinity());
  std::vector<int> parent(dist.size(), -1);
  std::priority_queue<Entry, std::vector<Entry>, std::greater<Entry>> open;
  const int gx = goal % g.width, gy = goal / g.width;
  const auto h = [&](int x, int y) {return std::hypot(gx - x, gy - y) * g.resolution * 0.45;};
  dist[initial] = 0.0;
  open.push({h(start % g.width, start / g.width), 0.0, initial});
  int found = -1;
  while (!open.empty()) {
    const auto q = open.top(); open.pop();
    if (q.cost != dist[q.state]) {continue;}
    const int cell = q.state / HEADINGS, heading = q.state % HEADINGS;
    if (cell == goal) {found = q.state; break;}
    const int x = cell % g.width, y = cell / g.width;
    for (int d = 0; d < 8; ++d) {
      const int nx = x + DX[d], ny = y + DY[d];
      if (nx < 0 || ny < 0 || nx >= g.width || ny >= g.height) {continue;}
      const int next = ny * g.width + nx;
      if (g.cost[next] >= o.lethal_cost) {continue;}
      if (DX[d] && DY[d] && (g.cost[y * g.width + nx] >= o.lethal_cost ||
        g.cost[ny * g.width + x] >= o.lethal_cost)) {continue;}
      const double length = g.resolution * ((DX[d] && DY[d]) ? 1.41421356237 : 1.0);
      const double risk = o.obstacle_weight * g.cost[next] / 252.0;
      const double reward = discount * potential[next];
      const double turn = heading != 8 && heading != d ? o.turn_cost_m : 0.0;
      const double cost = q.cost + length * std::max(0.45, 1.0 + risk - reward) + turn;
      const int state = next * HEADINGS + d;
      if (cost >= dist[state]) {continue;}
      dist[state] = cost; parent[state] = q.state;
      open.push({cost + h(nx, ny), cost, state});
    }
  }
  if (found < 0) {return {};}
  std::vector<int> route;
  for (int s = found; s >= 0; s = parent[s]) {
    route.push_back(s / HEADINGS);
    if (s == initial) {break;}
  }
  if (route.empty() || route.back() != start) {return {};}
  std::reverse(route.begin(), route.end());
  return route;
}

SearchResult evaluate(const SearchGrid & g, std::vector<int> route, const SearchOptions & o)
{
  SearchResult r; r.cells = std::move(route);
  std::vector<std::uint8_t> swept(g.coverage.size(), 0);
  const int radius = static_cast<int>(std::ceil(o.cleaning_radius / g.resolution));
  double risk = 0.0; int covered_steps = 0;
  for (std::size_t i = 0; i < r.cells.size(); ++i) {
    const int cell = r.cells[i], x = cell % g.width, y = cell / g.width;
    risk += g.resolution * o.obstacle_weight * g.cost[cell] / 252.0;
    covered_steps += g.coverage[cell] == 100;
    if (i > 0) {
      const int p = r.cells[i - 1], dx = x - p % g.width, dy = y - p / g.width;
      r.length_m += std::hypot(dx, dy) * g.resolution;
      if (i > 1) {
        const int b = r.cells[i - 2], px = p % g.width - b % g.width;
        const int py = p / g.width - b / g.width;
        if (dx * py != dy * px || dx * px + dy * py <= 0) {r.score_m += o.turn_cost_m;}
      }
    }
    for (int oy = -radius; oy <= radius; ++oy) for (int ox = -radius; ox <= radius; ++ox) {
      if (ox * ox + oy * oy > radius * radius) {continue;}
      const int nx = x + ox, ny = y + oy;
      if (nx >= 0 && ny >= 0 && nx < g.width && ny < g.height) {
        const int i_cell = ny * g.width + nx;
        if (g.coverage[i_cell] == 0) {swept[i_cell] = 1;}
      }
    }
  }
  const auto new_cells = std::count(swept.begin(), swept.end(), std::uint8_t{1});
  r.estimated_new_area_m2 = new_cells * g.resolution * g.resolution;
  const double repeat = covered_steps * g.resolution * 0.20;
  const double bounded_reward = std::min(r.length_m * 0.35, r.estimated_new_area_m2 * 2.0);
  r.score_m = std::max(0.0, r.length_m + r.score_m + risk + repeat - bounded_reward);
  return r;
}
}  // namespace

SearchResult evaluate_route(
  const SearchGrid & g, const std::vector<int> & route, const SearchOptions & o)
{
  return evaluate(g, route, o);
}

std::vector<SearchResult> coverage_candidates(
  const SearchGrid & g, int start, int goal, const SearchOptions & o)
{
  const auto size = static_cast<std::size_t>(g.width) * g.height;
  if (g.width <= 0 || g.height <= 0 || !std::isfinite(g.resolution) || g.resolution <= 0.0 ||
    g.cost.size() != size || g.coverage.size() != size || start < 0 || goal < 0 ||
    start >= static_cast<int>(size) || goal >= static_cast<int>(size) ||
    !std::isfinite(o.cleaning_radius) || o.cleaning_radius < 0.0 ||
    !std::isfinite(o.obstacle_weight) || o.obstacle_weight < 0.0 ||
    !std::isfinite(o.coverage_weight) || o.coverage_weight < 0.0 ||
    !std::isfinite(o.turn_cost_m) || o.turn_cost_m < 0.0) {
    throw std::invalid_argument("invalid coverage search input");
  }
  if (g.cost[start] >= o.lethal_cost || g.cost[goal] >= o.lethal_cost) {return {};}
  const auto potential = coverage_potential(g, o);
  const std::array<double, 5> discounts{{0.0, o.coverage_weight * 0.35,
      o.coverage_weight, std::min(0.70, o.coverage_weight * 1.6),
      std::min(0.85, o.coverage_weight * 2.4)}};
  std::vector<SearchResult> results;
  for (double discount : discounts) {
    auto route = search(g, start, goal, o, discount, potential);
    if (route.empty() || std::any_of(results.begin(), results.end(), [&](const auto & r) {
        return r.cells == route;
      })) {continue;}
    results.push_back(evaluate(g, std::move(route), o));
  }
  std::vector<int> ranked;
  ranked.reserve(size);
  for (int cell = 0; cell < static_cast<int>(size); ++cell) {
    if (cell != start && cell != goal && g.cost[cell] < o.lethal_cost && potential[cell] >= 0.25) {
      ranked.push_back(cell);
    }
  }
  std::sort(ranked.begin(), ranked.end(), [&](int a, int b) {
      return potential[a] > potential[b];
    });
  std::vector<int> seeds;
  const int separation = std::max(2, static_cast<int>(std::ceil(
      2.0 * o.cleaning_radius / g.resolution)));
  for (const auto cell : ranked) {
    const int x = cell % g.width, y = cell / g.width;
    if (std::none_of(seeds.begin(), seeds.end(), [&](int other) {
        const int ox = other % g.width, oy = other / g.width;
        return std::hypot(x - ox, y - oy) < separation;
      })) {
      seeds.push_back(cell);
    }
    if (seeds.size() == 8) {break;}
  }
  for (const auto seed : seeds) {
    auto to_seed = search(g, start, seed, o, 0.0, potential);
    auto from_seed = search(g, seed, goal, o, 0.0, potential);
    if (to_seed.empty() || from_seed.empty()) {continue;}
    to_seed.insert(to_seed.end(), from_seed.begin() + 1, from_seed.end());
    if (std::any_of(results.begin(), results.end(), [&](const auto & r) {
        return r.cells == to_seed;
      })) {continue;}
    results.push_back(evaluate(g, std::move(to_seed), o));
  }
  std::sort(results.begin(), results.end(), [](const auto & a, const auto & b) {
      return a.score_m < b.score_m;
    });
  return results;
}
}  // namespace robot_coverage_planner
