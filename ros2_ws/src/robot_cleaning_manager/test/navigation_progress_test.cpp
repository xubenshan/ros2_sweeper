// SPDX-License-Identifier: Apache-2.0
#include "robot_cleaning_manager/navigation_executor.hpp"

#include <gtest/gtest.h>

using robot_cleaning_manager::NavigationProgress;

TEST(NavigationProgress, MovingDuringDetourKeepsGoalAlive)
{
  NavigationProgress progress;
  geometry_msgs::msg::PoseStamped pose;
  pose.header.frame_id = "map";
  EXPECT_TRUE(progress.observe(1.0, pose));
  pose.pose.position.x = -0.04;
  EXPECT_FALSE(progress.observe(1.2, pose));
  pose.pose.position.x = -0.15;
  EXPECT_TRUE(progress.observe(1.4, pose));
  EXPECT_FALSE(progress.observe(1.4, pose));
}

TEST(NavigationProgress, ChangingFramesDoesNotLookLikeMovement)
{
  NavigationProgress progress;
  geometry_msgs::msg::PoseStamped pose;
  pose.header.frame_id = "map";
  EXPECT_TRUE(progress.observe(1.0, pose));
  pose.header.frame_id = "odom";
  pose.pose.position.x = 10.0;
  EXPECT_FALSE(progress.observe(1.4, pose));
  EXPECT_FALSE(progress.observe(1.4, pose));
  EXPECT_TRUE(progress.observe(0.8, pose));
}
