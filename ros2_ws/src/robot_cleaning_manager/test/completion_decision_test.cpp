// SPDX-License-Identifier: Apache-2.0
#include "robot_cleaning_manager/completion_decision.hpp"

#include <gtest/gtest.h>

using robot_cleaning_manager::decide_completion;

TEST(CompletionDecision, MarginCompletesImmediately)
{
  const auto decision = decide_completion(0.91, 0.90, 0.01, false);
  EXPECT_TRUE(decision.finish);
  EXPECT_TRUE(decision.success);
  EXPECT_EQ(decision.reason, "Coverage target reached with completion margin");
}

TEST(CompletionDecision, TargetMetWhenBudgetEndsIsSuccessWithoutMargin)
{
  const auto decision = decide_completion(0.9056, 0.90, 0.01, true);
  EXPECT_TRUE(decision.finish);
  EXPECT_TRUE(decision.success);
  EXPECT_NE(decision.reason.find("margin not reached"), std::string::npos);
}

TEST(CompletionDecision, TargetMetBeforeBudgetEndsContinuesForMargin)
{
  const auto decision = decide_completion(0.9056, 0.90, 0.01, false);
  EXPECT_FALSE(decision.finish);
  EXPECT_FALSE(decision.success);
}

TEST(CompletionDecision, BudgetExhaustedBelowTargetFails)
{
  const auto decision = decide_completion(0.8999, 0.90, 0.01, true);
  EXPECT_TRUE(decision.finish);
  EXPECT_FALSE(decision.success);
  EXPECT_NE(decision.reason.find("gap-fill limit exhausted"), std::string::npos);
}
