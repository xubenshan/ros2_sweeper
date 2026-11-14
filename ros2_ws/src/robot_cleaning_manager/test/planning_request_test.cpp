// SPDX-License-Identifier: Apache-2.0
#include "robot_cleaning_manager/planning_request.hpp"

#include <gtest/gtest.h>

using robot_cleaning_manager::PlanningRequestBuilder;
using robot_cleaning_manager::PlanningRequestContext;
using robot_cleaning_manager::PlanningRequestOptions;

namespace
{
nav_msgs::msg::OccupancyGrid grid()
{
  nav_msgs::msg::OccupancyGrid result;
  result.info.width = 10;
  result.info.height = 10;
  result.info.resolution = 0.05F;
  result.data.assign(100, 0);
  return result;
}
}  // namespace

TEST(PlanningRequest, PreservesSweepInputsWithoutGapBudget)
{
  PlanningRequestBuilder builder({0.20, 0.80, 0.50});
  PlanningRequestContext context;
  context.regions = {"room"};
  context.covered = grid();
  context.failure_exclusions.resize(1);
  const auto request = builder.build(context);
  EXPECT_FALSE(request.gap_fill);
  EXPECT_EQ(request.regions, context.regions);
  EXPECT_EQ(request.excluded.size(), 1U);
  EXPECT_DOUBLE_EQ(request.distance_budget_m, 0.0);
}

TEST(PlanningRequest, ComputesGapBudgetFromTargetAreaAndDistance)
{
  PlanningRequestBuilder builder({0.20, 0.80, 0.50});
  PlanningRequestContext context;
  context.gap_fill = true;
  context.covered = grid();
  context.distance_traveled_m = 0.10;
  const auto request = builder.build(context);
  // 100 * 0.05^2 / 0.40 = 0.625 m ideal; / 0.8 - 0.1 = 0.68125 m.
  EXPECT_NEAR(request.distance_budget_m, 0.68125, 1e-6);
}

TEST(PlanningRequest, AppliesMinimumBudgetAndDeferredWholePassExclusions)
{
  PlanningRequestBuilder builder({0.20, 0.80, 0.50});
  PlanningRequestContext context;
  context.gap_fill = true;
  context.covered = grid();
  context.distance_traveled_m = 5.0;
  context.current_path_size = 2;
  context.deferred_gap_goals.resize(2);
  const auto request = builder.build(context);
  EXPECT_DOUBLE_EQ(request.distance_budget_m, 0.50);
  EXPECT_EQ(request.excluded.size(), 2U);
}

TEST(PlanningRequest, CanRetryWithoutNavigationFailureExclusions)
{
  PlanningRequestBuilder builder({0.20, 0.0, 0.50});
  PlanningRequestContext context;
  context.gap_fill = true;
  context.failure_exclusions.resize(3);
  context.ignore_failure_exclusions = true;
  const auto request = builder.build(context);
  EXPECT_TRUE(request.excluded.empty());
}
