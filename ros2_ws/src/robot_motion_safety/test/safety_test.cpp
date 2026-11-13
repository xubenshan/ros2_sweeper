// SPDX-License-Identifier: Apache-2.0
#include "robot_motion_safety/policy.hpp"

#include <limits>
#include <gtest/gtest.h>

using namespace robot_motion_safety;

TEST(SafetyPolicy, AuthorityAndEmergencyStop)
{
  EXPECT_EQ(authorized("RUNNING", Source::none, true, false, false), Source::nav);
  EXPECT_EQ(authorized("RUNNING", Source::none, false, false, false), Source::none);
  EXPECT_EQ(authorized("RUNNING", Source::teleop, true, false, false), Source::teleop);
  EXPECT_EQ(authorized("RECOVERING", Source::teleop, true, false, true), Source::recovery);
  EXPECT_EQ(authorized("RECOVERING", Source::none, true, true, true), Source::none);
  EXPECT_EQ(authorized("RUNNING", Source::nav, true, false, true), Source::none);
}

TEST(SafetyPolicy, BoundsAndContact)
{
  geometry_msgs::msg::Twist command;
  command.linear.x = 0.8;
  command.angular.z = -4;
  EXPECT_DOUBLE_EQ(guard(command, 0.35, 1.8, false).linear.x, 0.35);
  EXPECT_DOUBLE_EQ(guard(command, 0.35, 1.8, false).angular.z, -1.8);
  EXPECT_DOUBLE_EQ(guard(command, 0.35, 1.8, true).linear.x, 0);
  command.linear.x = -0.1;
  EXPECT_DOUBLE_EQ(guard(command, 0.35, 1.8, true).linear.x, -0.1);
  command.linear.x = std::numeric_limits<double>::quiet_NaN();
  EXPECT_DOUBLE_EQ(guard(command, 0.35, 1.8, false).angular.z, 0);
}
