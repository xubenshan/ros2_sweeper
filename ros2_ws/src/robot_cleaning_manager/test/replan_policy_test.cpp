// SPDX-License-Identifier: Apache-2.0
#include "robot_cleaning_manager/replan_policy.hpp"

#include <gtest/gtest.h>

using robot_cleaning_manager::should_retry_gap_plan_without_failure_exclusions;

TEST(ReplanPolicy, RetriesGapPlanWithoutFailureExclusionsOnce)
{
  EXPECT_TRUE(should_retry_gap_plan_without_failure_exclusions(true, false, true));
  EXPECT_FALSE(should_retry_gap_plan_without_failure_exclusions(true, true, true));
}

TEST(ReplanPolicy, DoesNotRetryWithoutFailureExclusionsWhenNotApplicable)
{
  EXPECT_FALSE(should_retry_gap_plan_without_failure_exclusions(false, false, true));
  EXPECT_FALSE(should_retry_gap_plan_without_failure_exclusions(true, false, false));
}
