// SPDX-License-Identifier: Apache-2.0
#pragma once
#include <cstdint>
#include <vector>
namespace robot_coverage_planner
{
struct SearchGrid
{
  int width{0};
  int height{0};
  double resolution{0.0};
  std::vector<std::uint8_t> cost;
  // OccupancyGrid: 100 covered, 0 target/uncovered, negative non-target.
  std::vector<std::int8_t> coverage;
};
struct SearchOptions
{
  double cleaning_radius{0.20};
  double obstacle_weight{2.0};
  double coverage_weight{0.35};
  double turn_cost_m{0.08};
  std::uint8_t lethal_cost{253};
};
struct SearchResult
{
  std::vector<int> cells;
  double length_m{0.0};
  double estimated_new_area_m2{0.0};
  double score_m{0.0};
};
std::vector<SearchResult> coverage_candidates(
  const SearchGrid & grid, int start, int goal, const SearchOptions & options);
SearchResult evaluate_route(
  const SearchGrid & grid, const std::vector<int> & route, const SearchOptions & options);
}  // namespace robot_coverage_planner
