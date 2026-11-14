// SPDX-License-Identifier: Apache-2.0
#include "robot_cleaning_manager/waypoint_guard.hpp"

#include <cmath>

#include <gtest/gtest.h>

using robot_cleaning_manager::WaypointGuard;

namespace
{
nav_msgs::msg::OccupancyGrid grid()
{
  nav_msgs::msg::OccupancyGrid result;
  result.header.frame_id = "map";
  result.info.width = 20;
  result.info.height = 20;
  result.info.resolution = 0.05F;
  result.info.origin.orientation.w = 1.0;
  result.data.assign(400, 0);
  return result;
}

geometry_msgs::msg::PoseStamped pose(double x, double y)
{
  geometry_msgs::msg::PoseStamped result;
  result.header.frame_id = "map";
  result.pose.position.x = x;
  result.pose.position.y = y;
  result.pose.orientation.w = 1.0;
  return result;
}
}  // namespace

TEST(WaypointGuard, DetectsBlockedConnector)
{
  const auto cost = [](const geometry_msgs::msg::Point & point) {
      return point.x >= 0.45 && point.x <= 0.55 ? 100 : 0;
    };
  EXPECT_FALSE(WaypointGuard::clear_connector(0.05, cost, pose(0.0, 0.0), pose(1.0, 0.0)));
  EXPECT_TRUE(WaypointGuard::clear_connector(0.05, cost, pose(0.0, 0.0), pose(0.4, 0.0)));
}

TEST(WaypointGuard, FindsNearbyClearGoalWithoutChangingTheRequestedPose)
{
  const auto map = grid();
  const auto cost = [](const geometry_msgs::msg::Point & point) {
      return std::hypot(point.x - 0.50, point.y - 0.50) < 0.02 ? 100 : 0;
    };
  WaypointGuard guard;
  const auto requested = pose(0.50, 0.50);
  const auto adjusted = guard.nearby_clear_goal(
    map, 0.05, cost, cost, pose(0.25, 0.50), requested);
  ASSERT_TRUE(adjusted);
  EXPECT_NE(std::hypot(adjusted->pose.position.x - requested.pose.position.x,
    adjusted->pose.position.y - requested.pose.position.y), 0.0);
  EXPECT_LE(std::hypot(adjusted->pose.position.x - requested.pose.position.x,
    adjusted->pose.position.y - requested.pose.position.y), 0.15 + 1e-6);
}

TEST(WaypointGuard, IdentifiesRedundantCollinearWaypoint)
{
  const std::vector<geometry_msgs::msg::PoseStamped> path{
    pose(0.0, 0.0), pose(0.5, 0.0), pose(1.0, 0.0)};
  EXPECT_TRUE(WaypointGuard::is_between_on_line(path, 1));
  EXPECT_FALSE(WaypointGuard::is_between_on_line(path, 0));
}

TEST(WaypointGuard, ExpandsSharpTurnCostByConfiguredClearance)
{
  const auto cost = [](const geometry_msgs::msg::Point & point) {
      return point.x > 0.02 ? 100 : 0;
    };
  WaypointGuard guard;
  geometry_msgs::msg::Point origin;
  EXPECT_EQ(cost(origin), 0);
  EXPECT_EQ(guard.turn_clearance_cost(cost, origin), 100);
}
