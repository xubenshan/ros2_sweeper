// SPDX-License-Identifier: Apache-2.0
#include "robot_cleaning_manager/cleaning_event_log.hpp"

#include <gtest/gtest.h>

namespace
{
robot_cleaning_interfaces::msg::CleaningEvent event(
  const std::string & task, const std::string & code)
{
  robot_cleaning_interfaces::msg::CleaningEvent value;
  value.task_id = task;
  value.code = code;
  return value;
}
}  // namespace

TEST(CleaningEventLog, AssignsSequenceAndTrimsOldest)
{
  robot_cleaning_manager::CleaningEventLog log(2);
  EXPECT_EQ(log.append(event("a", "START")).sequence, 1U);
  EXPECT_EQ(log.append(event("a", "PLAN")).sequence, 2U);
  EXPECT_EQ(log.append(event("a", "DONE")).sequence, 3U);
  ASSERT_EQ(log.size(), 2U);
  const auto selected = log.select(10);
  ASSERT_EQ(selected.size(), 2U);
  EXPECT_EQ(selected[0].code, "DONE");
  EXPECT_EQ(selected[1].code, "PLAN");
}

TEST(CleaningEventLog, FiltersAndReturnsNewestFirst)
{
  robot_cleaning_manager::CleaningEventLog log(8);
  log.append(event("a", "START"));
  log.append(event("b", "START"));
  log.append(event("a", "PAUSE"));
  log.append(event("a", "START"));
  const auto selected = log.select(2, "a", "START");
  ASSERT_EQ(selected.size(), 2U);
  EXPECT_GT(selected[0].sequence, selected[1].sequence);
  EXPECT_EQ(selected[0].task_id, "a");
  EXPECT_EQ(selected[0].code, "START");
}

TEST(CleaningEventLog, StoresAnImmutableFieldSnapshot)
{
  robot_cleaning_manager::CleaningEventLog log(4);
  auto original = event("task-a", "NAVIGATION_FAILED");
  original.message = "timed out";
  original.coverage = 0.42F;
  original.completed_waypoints = 7;
  log.append(original);
  original.message = "mutated after append";
  original.coverage = 0.0F;

  const auto selected = log.select(1, "task-a", "NAVIGATION_FAILED");
  ASSERT_EQ(selected.size(), 1U);
  EXPECT_EQ(selected.front().message, "timed out");
  EXPECT_FLOAT_EQ(selected.front().coverage, 0.42F);
  EXPECT_EQ(selected.front().completed_waypoints, 7U);
}

TEST(CleaningEventLog, RejectsZeroCapacity)
{
  EXPECT_THROW(robot_cleaning_manager::CleaningEventLog(0), std::invalid_argument);
}
