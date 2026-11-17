// SPDX-License-Identifier: Apache-2.0
#include <algorithm>
#include <atomic>
#include <cmath>
#include <functional>
#include <mutex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>

#include <nav2_core/planner_exceptions.hpp>
#include <nav2_costmap_2d/footprint_collision_checker.hpp>
#include <nav2_navfn_planner/navfn_planner.hpp>
#include <pluginlib/class_list_macros.hpp>
#include <rclcpp/create_publisher.hpp>
#include <std_msgs/msg/string.hpp>

namespace robot_coverage_planner
{
class CoverageDirectPlanner : public nav2_navfn_planner::NavfnPlanner
{
public:
  void configure(
    const rclcpp_lifecycle::LifecycleNode::WeakPtr & parent,
    std::string name, std::shared_ptr<tf2_ros::Buffer> tf,
    std::shared_ptr<nav2_costmap_2d::Costmap2DROS> costmap_ros) override
  {
    robot_footprint_ = costmap_ros->getRobotFootprint();
    NavfnPlanner::configure(parent, name, std::move(tf), std::move(costmap_ros));
    const auto node = parent.lock();
    if (!node) {
      throw std::runtime_error("CoverageDirectPlanner parent node expired");
    }
    maximum_direct_length_ = double_parameter(
      *node, name + ".maximum_direct_length", 1.20);
    maximum_direct_cost_ = integer_parameter(
      *node, name + ".maximum_direct_cost", 220);
    sampling_step_ = double_parameter(*node, name + ".sampling_step", 0.025);
    if (!std::isfinite(maximum_direct_length_) || maximum_direct_length_ <= 0.0 ||
      maximum_direct_cost_ < 0 || maximum_direct_cost_ >=
      static_cast<int>(nav2_costmap_2d::INSCRIBED_INFLATED_OBSTACLE) ||
      !std::isfinite(sampling_step_) || sampling_step_ <= 0.0)
    {
      throw std::invalid_argument("invalid CoverageDirectPlanner direct-path limits");
    }
    auto node_parameters = node->get_node_parameters_interface();
    auto node_topics = node->get_node_topics_interface();
    planner_events_ = rclcpp::create_publisher<std_msgs::msg::String>(
      node_parameters, node_topics, "/coverage_direct_planner/events", rclcpp::QoS(100));
    RCLCPP_INFO(
      logger_, "Coverage direct connectors enabled: maximum_length=%.2f m maximum_cost=%d",
      maximum_direct_length_, maximum_direct_cost_);
  }

  nav_msgs::msg::Path createPlan(
    const geometry_msgs::msg::PoseStamped & start,
    const geometry_msgs::msg::PoseStamped & goal,
    std::function<bool()> cancel_checker) override
  {
    const auto request_id = ++request_count_;
    const double dx = goal.pose.position.x - start.pose.position.x;
    const double dy = goal.pose.position.y - start.pose.position.y;
    const double length = std::hypot(dx, dy);
    bool attempted = false;
    std::string reject_reason;
    if (start.header.frame_id != global_frame_ || goal.header.frame_id != global_frame_) {
      reject_reason = "frame_mismatch";
    } else if (length <= 1e-6) {
      reject_reason = "zero_length";
    } else if (length > maximum_direct_length_) {
      reject_reason = "too_long";
      ++distance_rejections_;
    } else {
      attempted = true;
      ++direct_attempts_;
      auto direct = straight_plan(start, goal, length, cancel_checker, &reject_reason);
      if (!direct.poses.empty()) {
        ++direct_successes_;
        publish_event("direct_success", request_id, attempted, false, start, goal, length, "");
        return direct;
      }
      if (reject_reason == "costmap_blocked") {
        ++costmap_rejections_;
      } else if (reject_reason == "footprint_blocked") {
        ++footprint_rejections_;
      } else {
        ++other_rejections_;
      }
    }
    if (!attempted && reject_reason != "too_long") {
      ++other_rejections_;
    }
    ++navfn_fallbacks_;
    const auto decision = attempted ? "direct_rejected_navfn_fallback" : "navfn_fallback";
    try {
      auto fallback = NavfnPlanner::createPlan(start, goal, std::move(cancel_checker));
      publish_event(decision, request_id, attempted, true, start, goal, length, reject_reason);
      return fallback;
    } catch (const std::exception &) {
      // Keep the request-level record when Navfn cancels or throws. The
      // exception is rethrown so Nav2 keeps its normal failure semantics.
      publish_event(
        attempted ? "direct_rejected_navfn_exception" : "navfn_exception",
        request_id, attempted, true, start, goal, length, reject_reason);
      throw;
    } catch (...) {
      publish_event(
        attempted ? "direct_rejected_navfn_exception" : "navfn_exception",
        request_id, attempted, true, start, goal, length, reject_reason);
      throw;
    }
  }

private:
  void publish_event(
    const std::string & decision, uint64_t request_id, bool attempted, bool fallback,
    const geometry_msgs::msg::PoseStamped & start,
    const geometry_msgs::msg::PoseStamped & goal,
    double length, const std::string & reject_reason) const
  {
    if (!planner_events_) {
      return;
    }
    std::ostringstream event;
    event << "{\"stamp_ns\":" << clock_->now().nanoseconds()
          << ",\"request_id\":" << request_id
          << ",\"decision\":\"" << decision
          << "\",\"attempted_direct\":" << (attempted ? "true" : "false")
          << ",\"fallback\":" << (fallback ? "true" : "false")
          << ",\"start_x\":" << start.pose.position.x
          << ",\"start_y\":" << start.pose.position.y
          << ",\"goal_x\":" << goal.pose.position.x
          << ",\"goal_y\":" << goal.pose.position.y
          << ",\"length_m\":" << length
          << ",\"reject_reason\":\"" << reject_reason
          << "\",\"request_count\":" << request_count_.load()
          << ",\"direct_attempts\":" << direct_attempts_.load()
          << ",\"direct_successes\":" << direct_successes_.load()
          << ",\"distance_rejections\":" << distance_rejections_.load()
          << ",\"costmap_rejections\":" << costmap_rejections_.load()
          << ",\"footprint_rejections\":" << footprint_rejections_.load()
          << ",\"other_rejections\":" << other_rejections_.load()
          << ",\"navfn_fallbacks\":" << navfn_fallbacks_.load() << "}";
    // Keep per-request diagnostics available without flooding normal launch logs.
    RCLCPP_DEBUG(
      logger_, "CoverageDirect decision=%s attempted=%s fallback=%s length=%.3f reason=%s",
      decision.c_str(), attempted ? "true" : "false", fallback ? "true" : "false",
      length, reject_reason.c_str());
    std_msgs::msg::String message;
    message.data = event.str();
    planner_events_->publish(message);
  }

  static double double_parameter(
    rclcpp_lifecycle::LifecycleNode & node, const std::string & name, double default_value)
  {
    if (!node.has_parameter(name)) {
      node.declare_parameter(name, default_value);
    }
    return node.get_parameter(name).as_double();
  }

  static int integer_parameter(
    rclcpp_lifecycle::LifecycleNode & node, const std::string & name, int default_value)
  {
    if (!node.has_parameter(name)) {
      node.declare_parameter(name, default_value);
    }
    return static_cast<int>(node.get_parameter(name).as_int());
  }

  nav_msgs::msg::Path straight_plan(
    const geometry_msgs::msg::PoseStamped & start,
    const geometry_msgs::msg::PoseStamped & goal, double length,
    const std::function<bool()> & cancel_checker,
    std::string * reject_reason) const
  {
    using Costmap = nav2_costmap_2d::Costmap2D;
    std::scoped_lock<Costmap::mutex_t> lock(*costmap_->getMutex());
    const double step = std::min(sampling_step_, costmap_->getResolution() / 2.0);
    if (!std::isfinite(step) || step < 0.001) {
      if (reject_reason) {
        *reject_reason = "invalid_sampling_step";
      }
      return nav_msgs::msg::Path{};
    }
    const auto steps = static_cast<int>(std::ceil(length / step));
    nav2_costmap_2d::FootprintCollisionChecker<Costmap *> collision_checker(costmap_);
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
        costmap_->getCost(mx, my) > maximum_direct_cost_)
      {
        if (reject_reason) {
          *reject_reason = "costmap_blocked";
        }
        return nav_msgs::msg::Path{};
      }
      const double footprint_cost = collision_checker.footprintCostAtPose(
        pose.pose.position.x, pose.pose.position.y, yaw, robot_footprint_);
      if (footprint_cost < 0.0 || footprint_cost > maximum_direct_cost_) {
        if (reject_reason) {
          *reject_reason = "footprint_blocked";
        }
        return nav_msgs::msg::Path{};
      }
      path.poses.push_back(pose);
    }
    path.poses.back().pose = goal.pose;
    return path;
  }

  double maximum_direct_length_{1.20};
  int maximum_direct_cost_{220};
  double sampling_step_{0.025};
  nav2_costmap_2d::Footprint robot_footprint_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr planner_events_;
  std::atomic<uint64_t> request_count_{0};
  std::atomic<uint64_t> direct_attempts_{0};
  std::atomic<uint64_t> direct_successes_{0};
  std::atomic<uint64_t> distance_rejections_{0};
  std::atomic<uint64_t> costmap_rejections_{0};
  std::atomic<uint64_t> footprint_rejections_{0};
  std::atomic<uint64_t> other_rejections_{0};
  std::atomic<uint64_t> navfn_fallbacks_{0};
};
}  // namespace robot_coverage_planner

PLUGINLIB_EXPORT_CLASS(robot_coverage_planner::CoverageDirectPlanner, nav2_core::GlobalPlanner)
