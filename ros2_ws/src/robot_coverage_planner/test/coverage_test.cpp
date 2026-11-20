// SPDX-License-Identifier: Apache-2.0
#include "robot_coverage_planner/baseline_coverage_plan.hpp"
#include "robot_coverage_planner/coverage_plan.hpp"
#include "robot_coverage_planner/coverage_search.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <stdexcept>

#include <gtest/gtest.h>

using namespace robot_coverage_planner;

namespace
{
GridMap empty_grid()
{
  return GridMap{14, 12, 0.1, -0.2, 0.4, 0.0, std::vector<int8_t>(168, 0)};
}
}

TEST(GridMap, RotatedOriginAndBounds)
{
  auto grid = empty_grid();
  grid.origin_yaw = 1.5707963267948966;
  const Cell cell{5, 7};
  const auto [x, y] = grid.center(cell);
  EXPECT_EQ(grid.from_world(x, y), cell);
  EXPECT_FALSE(grid.from_world(100, y));
  EXPECT_FALSE(grid.from_world(grid.origin_x + 0.001, grid.origin_y - 0.001));
}

TEST(GridMap, InflationAndCornerClearance)
{
  auto grid = empty_grid();
  grid.occupancy[grid.index({3, 3})] = -1;
  auto inflated = grid.drivable(0.12);
  EXPECT_FALSE(inflated[grid.index({3, 3})]);
  EXPECT_FALSE(inflated[grid.index({4, 3})]);
  EXPECT_TRUE(inflated[grid.index({5, 3})]);
  EXPECT_FALSE(inflated[grid.index({0, 4})]);
  EXPECT_FALSE(grid.straight(grid.drivable(0), {2, 3}, {3, 4}));
}

TEST(GridMap, IncludesBrushBoundaryWithFloat32MapResolution)
{
  auto grid = empty_grid();
  grid.resolution = static_cast<float>(0.05);
  const Mask floor(grid.size(), 1);
  Mask swept(grid.size(), 0);
  grid.stamp(swept, floor, {7, 6}, 0.20);
  EXPECT_TRUE(swept[grid.index({7, 10})]);
  EXPECT_FALSE(swept[grid.index({8, 10})]);
  grid.occupancy[grid.index({5, 6})] = 100;
  const auto allowed = grid.drivable(0.20);
  EXPECT_FALSE(allowed[grid.index({9, 6})]);
  EXPECT_TRUE(allowed[grid.index({9, 7})]);
}

TEST(GridMap, CoverageAtPoseResolvesMovementInsideOneCell)
{
  GridMap grid{12, 8, 0.05, 1.0, -1.0, 0, std::vector<int8_t>(96, 0)};
  const Mask target(grid.size(), 1);
  Mask covered(grid.size(), 0);
  const Cell start{4, 3};
  const Cell right{8, 3};
  const auto [x, y] = grid.center(start);
  ASSERT_EQ(grid.from_world(x - 0.02, y), grid.from_world(x + 0.02, y));
  EXPECT_TRUE(grid.stamp_at_pose(covered, target, x - 0.02, y, 0.20));
  EXPECT_FALSE(covered[grid.index(right)]);
  EXPECT_TRUE(grid.stamp_at_pose(covered, target, x + 0.02, y, 0.20));
  EXPECT_TRUE(covered[grid.index(right)]);
  EXPECT_FALSE(grid.stamp_at_pose(covered, target, x + 0.02, y, 0.20));
}

TEST(CoveragePlan, OpenFloorLeavesTheEdgeBandForEdgeCleaning)
{
  GridMap grid{25, 25, 0.05, 0, 0, 0, std::vector<int8_t>(625, 0)};
  for (int i = 0; i < grid.width; ++i) {
    grid.occupancy[grid.index({i, 0})] = 100;
    grid.occupancy[grid.index({i, 24})] = 100;
    grid.occupancy[grid.index({0, i})] = 100;
    grid.occupancy[grid.index({24, i})] = 100;
  }
  PlanOptions options;
  const Cell start{12, 12};
  const CoveragePlan full_floor(grid, options, start);
  options.edge_margin = 0.15;
  const CoveragePlan open_floor(grid, options, start);
  const auto target = open_floor.target_floor({});
  EXPECT_EQ(std::count(target.begin(), target.end(), 1), 17 * 17);
  EXPECT_TRUE(full_floor.target_floor({})[grid.index({3, 12})]);
  EXPECT_FALSE(target[grid.index({3, 12})]);
  EXPECT_TRUE(target[grid.index({4, 12})]);
  EXPECT_EQ(full_floor.reachable(), open_floor.reachable());
  const auto route = open_floor.sweep(start, {});
  ASSERT_FALSE(route.empty());
  options.refine_sweep = true;
  const CoveragePlan refined(grid, options, start);
  const auto adjusted = refined.sweep(start, {});
  EXPECT_EQ(route.size(), adjusted.size());
  for (const auto & candidate : {route, adjusted}) {
    auto from = start;
    for (const auto to : candidate) {
      EXPECT_TRUE(grid.straight(open_floor.reachable(), from, to));
      from = to;
    }
  }
}

TEST(CoveragePlan, LiveInscribedCellsBlockSweepWithoutChangingTheTaskFloor)
{
  const auto grid = empty_grid();
  PlanOptions options;
  options.robot_radius = 0.0;
  options.safety_margin = 0.0;
  options.edge_margin = 0.10;
  const Cell start{2, 3};
  const CoveragePlan original(grid, options, start);
  const auto task_floor = original.target_floor({});
  Mask blocked_centers(grid.size(), 0);
  for (int y = 0; y < grid.height; ++y) {
    blocked_centers[grid.index({6, y})] = 1;
  }
  const CoveragePlan live(grid, options, start, blocked_centers);
  const auto route = live.sweep(start, {}, 0.90, task_floor);
  ASSERT_FALSE(route.empty());
  EXPECT_TRUE(task_floor[grid.index({10, 4})]);
  EXPECT_FALSE(live.reachable()[grid.index({10, 4})]);
  auto from = start;
  for (const auto to : route) {
    EXPECT_LT(to.x, 6);
    EXPECT_TRUE(grid.straight(live.reachable(), from, to));
    from = to;
  }
}

TEST(CoveragePlan, GapRouteStopsAfterEnoughNewFloor)
{
  GridMap grid{36, 28, 0.05, 0, 0, 0, std::vector<int8_t>(1008, 0)};
  PlanOptions options;
  options.robot_radius = options.safety_margin = 0.0;
  const Cell start{17, 14};
  const CoveragePlan plan(grid, options, start);
  const Mask floor(grid.size(), 1);
  Mask covered(grid.size(), 0);
  for (int i = 0; i < grid.size(); ++i) {
    covered[i] = grid.cell(i).x < 18;
  }
  const auto all_gaps = plan.gaps(start, {}, covered, {}, {}, floor);
  const auto target_gaps = plan.gaps(start, {}, covered, {}, {}, floor, 0.54);
  const auto budgeted = plan.gaps(start, {}, covered, {}, {}, floor, 0.54, 0.35);
  ASSERT_FALSE(target_gaps.empty());
  ASSERT_FALSE(budgeted.empty());
  EXPECT_LT(target_gaps.size(), all_gaps.size());
  auto from = start;
  for (const auto to : target_gaps) {
    EXPECT_TRUE(grid.straight(plan.reachable(), from, to));
    from = to;
  }
  from = start;
  double traveled = 0.0;
  for (const auto to : budgeted) {
    traveled += std::hypot(to.x - from.x, to.y - from.y) * grid.resolution;
    from = to;
  }
  EXPECT_LE(traveled, 0.35 + 1e-9);

  const auto beyond_budget = plan.gaps(start, {}, covered, {}, {}, floor, 0.80, 0.35);
  from = start;
  traveled = 0.0;
  for (const auto to : beyond_budget) {
    EXPECT_TRUE(grid.straight(plan.reachable(), from, to));
    traveled += std::hypot(to.x - from.x, to.y - from.y) * grid.resolution;
    from = to;
  }
  EXPECT_GT(traveled, 0.35);
}

TEST(CoveragePlan, SplitMergeAndCollisionFreeTransitions)
{
  auto grid = empty_grid();
  for (int y = 4; y <= 6; ++y) {
    grid.occupancy[grid.index({6, y})] = 100;
  }
  PlanOptions options;
  options.robot_radius = 0;
  options.safety_margin = 0;
  const Cell start{1, 1};
  const CoveragePlan plan(grid, options, start);
  EXPECT_EQ(decompose(grid, plan.reachable()).size(), 4u);
  const auto waypoints = plan.sweep(start, {});
  ASSERT_GT(waypoints.size(), 5u);
  Cell last = start;
  for (auto point : waypoints) {
    EXPECT_TRUE(grid.straight(plan.reachable(), last, point));
    last = point;
  }
}

TEST(CoveragePlan, AvoidsOverlappingShortSweepsAroundFurniture)
{
  GridMap grid{76, 67, 0.05, 0, 0, 0, std::vector<int8_t>(76 * 67, 0)};
  const std::array<std::array<int, 4>, 6> obstacles{{
    {8, 17, 17, 28}, {20, 18, 29, 36}, {34, 10, 44, 22},
    {39, 30, 53, 40}, {56, 10, 65, 24}, {63, 27, 70, 42}
  }};
  for (const auto & bounds : obstacles) {
    const auto [left, bottom, right, top] = bounds;
    for (int y = bottom; y < top; ++y) {
      for (int x = left; x < right; ++x) {
        grid.occupancy[grid.index({x, y})] = 100;
      }
    }
  }
  const PlanOptions options;
  const Cell start{56, 60};
  const CoveragePlan plan(grid, options, start);
  const auto target = plan.target_floor({});
  const auto route = plan.sweep(start, {});
  Mask covered(grid.size(), 0);
  grid.stamp(covered, target, start, options.cleaning_radius);
  auto last = start;
  double length = 0.0;
  for (const auto next : route) {
    EXPECT_TRUE(grid.straight(plan.reachable(), last, next));
    const int dx = next.x - last.x;
    const int dy = next.y - last.y;
    const int steps = std::max(std::abs(dx), std::abs(dy));
    for (int i = 1; i <= steps; ++i) {
      const double fraction = static_cast<double>(i) / steps;
      const Cell sample{last.x + static_cast<int>(std::lround(fraction * dx)),
        last.y + static_cast<int>(std::lround(fraction * dy))};
      grid.stamp(covered, target, sample, options.cleaning_radius);
    }
    length += std::hypot(dx, dy) * grid.resolution;
    last = next;
  }
  EXPECT_LT(length, 31.0);
  EXPECT_GE(std::count(covered.begin(), covered.end(), 1),
    0.84 * std::count(target.begin(), target.end(), 1));
}

TEST(CoveragePlan, NarrowGapSelectsReachableBrushPosition)
{
  const auto grid = empty_grid();
  PlanOptions options;
  options.robot_radius = 0.10;
  options.safety_margin = 0.0;
  const CoveragePlan plan(grid, options, {2, 2});
  Mask covered(grid.size(), 1);
  covered[grid.index({6, 7})] = 0;
  const auto fill = plan.gaps({2, 2}, {}, covered, {{6, 7}});
  ASSERT_FALSE(fill.empty());
  EXPECT_NE(fill.back(), (Cell{6, 7}));
  Mask stamped(grid.size(), 0);
  grid.stamp(stamped, plan.target_floor({}), fill.back(), options.cleaning_radius);
  EXPECT_TRUE(stamped[grid.index({6, 7})]);
}

TEST(CoveragePlan, GapFillCreditsCellsSweptBetweenGoals)
{
  const auto grid = empty_grid();
  PlanOptions options;
  options.cleaning_radius = 0.06;
  const Cell start{2, 4};
  const CoveragePlan plan(grid, options, start);
  Mask covered(grid.size(), 1);
  for (int x = 3; x <= 8; ++x) {
    covered[grid.index({x, start.y})] = 0;
  }
  const auto route = plan.gaps(start, {}, covered, {});
  ASSERT_EQ(route.size(), 1u);
  EXPECT_EQ(route.front(), (Cell{8, 4}));
}

TEST(CoveragePlan, GapFillPrefersPriorityFloorAndStillPlansEdgeCells)
{
  const auto grid = empty_grid();
  PlanOptions options;
  options.cleaning_radius = 0.06;
  const Cell start{3, 4};
  const Cell near{4, 4};
  const Cell interior{3, 7};
  const CoveragePlan plan(grid, options, start);
  Mask covered(grid.size(), 1);
  covered[grid.index(near)] = 0;
  covered[grid.index(interior)] = 0;
  Mask priority(grid.size(), 0);
  priority[grid.index(interior)] = 1;
  const auto original = plan.gaps(start, {}, covered, {});
  const auto ranked = plan.gaps(start, {}, covered, {}, priority);
  ASSERT_EQ(original.size(), 2u);
  ASSERT_EQ(ranked.size(), 2u);
  EXPECT_EQ(original.front(), near);
  EXPECT_EQ(ranked.front(), interior);
  EXPECT_EQ(ranked.back(), near);
}

TEST(CoveragePlan, RequestedRegionsKeepOrder)
{
  const auto grid = empty_grid();
  const CoveragePlan plan(grid, {}, {3, 3});
  const auto result = plan.sweep({3, 3}, {{0.5, 1.1, 1.0, 1.45}, {-0.05, 0.6, 0.3, 1.0}});
  ASSERT_FALSE(result.empty());
  const auto [x, y] = grid.center(result.front());
  EXPECT_GE(x, 0.5);
  EXPECT_GE(y, 1.1);
}

TEST(GridMap, RejectsInvalidGeometry)
{
  auto grid = empty_grid();
  grid.resolution = 0;
  EXPECT_THROW(grid.validate(), std::invalid_argument);
  grid.resolution = 0.1;
  grid.occupancy.pop_back();
  EXPECT_THROW(grid.validate(), std::invalid_argument);
}

TEST(CoveragePlan, FullyCoveredHasNoSupplementalGoals)
{
  const auto grid = empty_grid();
  const CoveragePlan plan(grid, {}, {3, 3});
  EXPECT_TRUE(plan.gaps({3, 3}, {}, plan.target_floor({}), {}).empty());
}

TEST(BaselineCoveragePlan, ProducesDeterministicCollisionFreeBoustrophedonRoute)
{
  auto grid = empty_grid();
  for (int y = 3; y <= 8; ++y) {
    grid.occupancy[grid.index({7, y})] = 100;
  }
  PlanOptions options;
  options.robot_radius = 0.0;
  options.safety_margin = 0.0;
  const Cell start{2, 2};
  const BaselineCoveragePlan plan(grid, options, start);
  const auto first = plan.sweep(start, {}, 0.90);
  const auto second = plan.sweep(start, {}, 0.90);
  ASSERT_FALSE(first.empty());
  EXPECT_EQ(first, second);
  auto from = start;
  for (const auto to : first) {
    EXPECT_TRUE(grid.straight(plan.reachable(), from, to));
    from = to;
  }
}

TEST(BaselineCoveragePlan, BasicGapFillMovesToNearestMissingFloor)
{
  const auto grid = empty_grid();
  PlanOptions options;
  options.robot_radius = 0.0;
  options.safety_margin = 0.0;
  options.cleaning_radius = 0.06;
  const Cell start{2, 4};
  const BaselineCoveragePlan plan(grid, options, start);
  auto covered = plan.target_floor({});
  covered[grid.index({4, 4})] = 0;
  covered[grid.index({10, 8})] = 0;
  const auto route = plan.gaps(start, {}, covered, {});
  ASSERT_FALSE(route.empty());
  EXPECT_LT(std::hypot(route.front().x - 4, route.front().y - 4),
    std::hypot(route.front().x - 10, route.front().y - 8));
}

TEST(BaselineCoveragePlan, UsesSameTaskFloorAsOptimizedPlanner)
{
  const auto grid = empty_grid();
  PlanOptions options;
  options.robot_radius = 0.0;
  options.safety_margin = 0.0;
  const Cell start{3, 3};
  const CoveragePlan optimized(grid, options, start);
  const BaselineCoveragePlan baseline(grid, options, start);
  EXPECT_EQ(baseline.target_floor({}), optimized.target_floor({}));
}

TEST(CoverageSearch, FindsAFreeRouteAroundAnObstacle)
{
  SearchGrid grid{20, 12, 0.10, std::vector<std::uint8_t>(240, 0),
    std::vector<std::int8_t>(240, 0)};
  for (int y = 1; y < 11; ++y) {
    grid.cost[y * grid.width + 9] = 253;
  }
  SearchOptions options;
  const auto candidates = coverage_candidates(grid, 2 * grid.width + 6, 2 * grid.width + 13, options);
  ASSERT_FALSE(candidates.empty());
  EXPECT_EQ(candidates.front().cells.front(), 2 * grid.width + 6);
  EXPECT_EQ(candidates.front().cells.back(), 2 * grid.width + 13);
  EXPECT_GT(candidates.front().length_m, 0.7);
  EXPECT_TRUE(std::all_of(candidates.front().cells.begin(), candidates.front().cells.end(),
    [&](int cell) {return grid.cost[cell] < options.lethal_cost;}));
}

TEST(CoverageSearch, EstimatesUniqueSweptAreaUsingCleaningRadius)
{
  SearchGrid grid{20, 12, 0.10, std::vector<std::uint8_t>(240, 0),
    std::vector<std::int8_t>(240, 100)};
  for (int x = 2; x <= 7; ++x) {
    grid.coverage[6 * grid.width + x] = 0;
  }
  SearchOptions options;
  options.cleaning_radius = 0.20;
  const auto candidates = coverage_candidates(grid, 6 * grid.width + 2,
    6 * grid.width + 7, options);
  ASSERT_FALSE(candidates.empty());
  EXPECT_GT(candidates.front().estimated_new_area_m2, 0.0);
  EXPECT_LT(candidates.front().estimated_new_area_m2, 1.0);
}

TEST(CoverageSearch, GeneratesBoundedCoverageDetourThroughUncoveredPatch)
{
  SearchGrid grid{40, 20, 0.10, std::vector<std::uint8_t>(800, 0),
    std::vector<std::int8_t>(800, 100)};
  for (int y = 3; y <= 6; ++y) {
    for (int x = 18; x <= 21; ++x) {
      grid.coverage[y * grid.width + x] = 0;
    }
  }
  SearchOptions options;
  options.cleaning_radius = 0.20;
  options.coverage_weight = 0.60;
  const int start = 10 * grid.width + 4;
  const int goal = 10 * grid.width + 35;
  std::vector<int> direct;
  for (int x = 4; x <= 35; ++x) {
    direct.push_back(10 * grid.width + x);
  }
  const auto reference = evaluate_route(grid, direct, options);
  const auto candidates = coverage_candidates(grid, start, goal, options);
  ASSERT_FALSE(candidates.empty());
  EXPECT_TRUE(std::any_of(candidates.begin(), candidates.end(), [&](const auto & candidate) {
    return candidate.length_m > reference.length_m &&
           candidate.estimated_new_area_m2 > reference.estimated_new_area_m2;
  }));
}

TEST(CoverageSearch, RejectsUnreachableAndInvalidInputs)
{
  SearchGrid grid{8, 8, 0.10, std::vector<std::uint8_t>(64, 0),
    std::vector<std::int8_t>(64, 0)};
  for (int y = 0; y < grid.height; ++y) {
    grid.cost[y * grid.width + 3] = 253;
  }
  SearchOptions options;
  EXPECT_TRUE(coverage_candidates(grid, 1, 6, options).empty());
  options.coverage_weight = -1.0;
  EXPECT_THROW(coverage_candidates(grid, 1, 2, options), std::invalid_argument);
}
