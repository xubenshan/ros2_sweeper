// SPDX-License-Identifier: Apache-2.0
#include <algorithm>
#include <cmath>
#include <functional>
#include <mutex>
#include <utility>

#include <nav2_core/planner_exceptions.hpp>
#include <nav2_navfn_planner/navfn_planner.hpp>
#include <pluginlib/class_list_macros.hpp>

namespace robot_coverage_planner
{
class CoverageDirectPlanner : public nav2_navfn_planner::NavfnPlanner
{
public:
  nav_msgs::msg::Path createPlan(
    const geometry_msgs::msg::PoseStamped & start,
    const geometry_msgs::msg::PoseStamped & goal,
    std::function<bool()> cancel_checker) override
  {
    const double dx = goal.pose.position.x - start.pose.position.x;
    const double dy = goal.pose.position.y - start.pose.position.y;
    const double length = std::hypot(dx, dy);
    if (start.header.frame_id == global_frame_ && goal.header.frame_id == global_frame_ &&
      length > 1e-6 && length <= 1.20)
    {
      auto direct = straight_plan(start, goal, length, cancel_checker);
      if (!direct.poses.empty()) {
        return direct;
      }
    }
    return NavfnPlanner::createPlan(start, goal, std::move(cancel_checker));
  }

private:
  nav_msgs::msg::Path straight_plan(
    const geometry_msgs::msg::PoseStamped & start,
    const geometry_msgs::msg::PoseStamped & goal, double length,
    const std::function<bool()> & cancel_checker) const
  {
    using Costmap = nav2_costmap_2d::Costmap2D;
    std::scoped_lock<Costmap::mutex_t> lock(*costmap_->getMutex());
    const double step = std::min(0.025, costmap_->getResolution() / 2.0);
    if (!std::isfinite(step) || step < 0.001) {
      return nav_msgs::msg::Path{};
    }
    const auto steps = static_cast<int>(std::ceil(length / step));
    nav_msgs::msg::Path path;
    path.header.frame_id = global_frame_;
    path.header.stamp = clock_->now();
    auto pose = start;
    pose.header = path.header;
    const auto & a = start.pose.position;
    const auto & b = goal.pose.position;
    const double yaw = std::atan2(b.y - a.y, b.x - a.x);
    pose.pose.orientation.x = pose.pose.orientation.y = 0.0;
    pose.pose.orientation.z = std::sin(yaw / 2.0);
    pose.pose.orientation.w = std::cos(yaw / 2.0);
    path.poses.reserve(steps + 1);
    for (int i = 0; i <= steps; ++i) {
      if (cancel_checker()) {
        throw nav2_core::PlannerCancelled("Coverage connector canceled");
      }
      const double fraction = static_cast<double>(i) / steps;
      pose.pose.position.x = a.x + fraction * (b.x - a.x);
      pose.pose.position.y = a.y + fraction * (b.y - a.y);
      unsigned int mx, my;
      // Give the normal planner control close to the inscribed boundary. The
      // controller still checks the local footprint while following a line.
      if (!costmap_->worldToMap(pose.pose.position.x, pose.pose.position.y, mx, my) ||
        costmap_->getCost(mx, my) > 220)
      {
        return nav_msgs::msg::Path{};
      }
      path.poses.push_back(pose);
    }
    path.poses.back().pose = goal.pose;
    return path;
  }
};
}  // namespace robot_coverage_planner

PLUGINLIB_EXPORT_CLASS(robot_coverage_planner::CoverageDirectPlanner, nav2_core::GlobalPlanner)
