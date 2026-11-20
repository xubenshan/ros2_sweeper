// SPDX-License-Identifier: Apache-2.0
#include <algorithm>
#include <atomic>
#include <chrono>
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
#include "robot_coverage_planner/coverage_search.hpp"
#include <pluginlib/class_list_macros.hpp>
#include <rclcpp/create_publisher.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
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
    strategy_ = string_parameter(*node, name + ".strategy", "direct");
    coverage_cleaning_radius_ = double_parameter(*node,
      name + ".coverage_cleaning_radius", 0.20);
    max_detour_ratio_ = double_parameter(*node, name + ".max_detour_ratio", 1.25);
    max_detour_distance_ = double_parameter(*node, name + ".max_detour_distance", 0.75);
    coverage_weight_ = double_parameter(*node, name + ".coverage_weight", 0.35);
    min_new_area_m2_ = double_parameter(*node, name + ".min_coverage_gain_m2", 0.0025);
    min_area_gain_per_extra_meter_ = double_parameter(
      *node, name + ".min_coverage_gain_per_extra_meter", 0.05);
    min_score_gain_m_ = double_parameter(*node, name + ".min_score_gain_m", 0.03);
    if (strategy_ != "direct" && strategy_ != "coverage_aware") {
      throw std::invalid_argument("strategy must be direct or coverage_aware");
    }
    if (!std::isfinite(coverage_cleaning_radius_) || coverage_cleaning_radius_ <= 0.0 ||
      !std::isfinite(max_detour_ratio_) || max_detour_ratio_ < 1.0 ||
      !std::isfinite(max_detour_distance_) || max_detour_distance_ < 0.0 ||
      !std::isfinite(coverage_weight_) || coverage_weight_ < 0.0 ||
      !std::isfinite(min_new_area_m2_) || min_new_area_m2_ < 0.0 ||
      !std::isfinite(min_area_gain_per_extra_meter_) || min_area_gain_per_extra_meter_ < 0.0 ||
      !std::isfinite(min_score_gain_m_) || min_score_gain_m_ < 0.0) {
      throw std::invalid_argument("invalid coverage-aware planner limits");
    }
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
    if (strategy_ == "coverage_aware") {
      coverage_sub_ = node->create_subscription<nav_msgs::msg::OccupancyGrid>(
        "/cleaning/covered_grid", rclcpp::QoS(1).transient_local(),
        [this](nav_msgs::msg::OccupancyGrid::ConstSharedPtr msg) {
          std::scoped_lock lock(coverage_mutex_);
          coverage_ = std::move(msg);
          coverage_received_ = clock_->now();
        });
    }
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
    const auto started = std::chrono::steady_clock::now();
    if (strategy_ == "coverage_aware") {
      return coverage_plan(start, goal, std::move(cancel_checker), request_id, started);
    }
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
  static std::string string_parameter(
    rclcpp_lifecycle::LifecycleNode & node, const std::string & name,
    const std::string & default_value)
  {
    if (!node.has_parameter(name)) {node.declare_parameter(name, default_value);}
    return node.get_parameter(name).as_string();
  }

  nav_msgs::msg::Path coverage_plan(
    const geometry_msgs::msg::PoseStamped & start,
    const geometry_msgs::msg::PoseStamped & goal, std::function<bool()> cancel_checker,
    uint64_t request_id, std::chrono::steady_clock::time_point started)
  {
    ++coverage_requests_;
    nav_msgs::msg::Path reference;
    try {
      reference = NavfnPlanner::createPlan(start, goal, cancel_checker);
    } catch (...) {
      ++navfn_fallbacks_;
      publish_coverage_event("navfn_exception", request_id, 0, 0.0, 0.0, started);
      throw;
    }
    const double reference_length = path_length(reference);
    nav_msgs::msg::OccupancyGrid::ConstSharedPtr coverage_snapshot;
    rclcpp::Time received(0, 0, clock_->get_clock_type());
    {
      std::scoped_lock lock(coverage_mutex_);
      coverage_snapshot = coverage_;
      received = coverage_received_;
    }
    std::string reason;
    if (!coverage_snapshot || !coverage_valid(*coverage_snapshot, received, start, goal, reason)) {
      ++navfn_fallbacks_;
      publish_coverage_event("coverage_fallback_" + reason, request_id, 0,
        reference_length, 0.0, started);
      return reference;
    }
    ++coverage_searches_;
    if (cancel_checker()) {throw nav2_core::PlannerCancelled("Coverage search canceled");}

    using Costmap = nav2_costmap_2d::Costmap2D;
    unsigned int width;
    unsigned int height;
    unsigned int sx;
    unsigned int sy;
    unsigned int gx;
    unsigned int gy;
    double origin_x;
    double origin_y;
    SearchGrid grid;
    std::vector<int> reference_cells;
    reference_cells.reserve(reference.poses.size());
    {
      std::scoped_lock<Costmap::mutex_t> lock(*costmap_->getMutex());
      width = costmap_->getSizeInCellsX();
      height = costmap_->getSizeInCellsY();
      origin_x = costmap_->getOriginX();
      origin_y = costmap_->getOriginY();
      grid.width = static_cast<int>(width);
      grid.height = static_cast<int>(height);
      grid.resolution = costmap_->getResolution();
      grid.cost.resize(static_cast<std::size_t>(width) * height);
      for (unsigned int y = 0; y < height; ++y) for (unsigned int x = 0; x < width; ++x) {
        grid.cost[y * width + x] = costmap_->getCost(x, y);
      }
      grid.coverage = coverage_snapshot->data;
      if (!costmap_->worldToMap(start.pose.position.x, start.pose.position.y, sx, sy) ||
        !costmap_->worldToMap(goal.pose.position.x, goal.pose.position.y, gx, gy)) {
        ++navfn_fallbacks_;
        publish_coverage_event("coverage_fallback_endpoint_outside", request_id, 0,
          reference_length, 0.0, started);
        return reference;
      }
      for (const auto & pose : reference.poses) {
        unsigned int mx, my;
        if (!costmap_->worldToMap(pose.pose.position.x, pose.pose.position.y, mx, my)) {
          continue;
        }
        const int cell = static_cast<int>(my * width + mx);
        if (reference_cells.empty() || reference_cells.back() != cell) {
          reference_cells.push_back(cell);
        }
      }
    }

    SearchOptions options;
    options.cleaning_radius = coverage_cleaning_radius_;
    options.coverage_weight = coverage_weight_;
    auto candidates = coverage_candidates(grid, sy * width + sx, gy * width + gx, options);
    candidates_generated_ += candidates.size();
    const auto reference_result = evaluate_route(grid, reference_cells, options);
    const double reference_new_area = reference_result.estimated_new_area_m2;
    const double reference_score = reference_result.score_m;
    const double max_length = std::min(reference_length * max_detour_ratio_,
      reference_length + max_detour_distance_);
    nav2_costmap_2d::FootprintCollisionChecker<Costmap *> checker(costmap_);
    std::size_t rejected_detour = 0;
    std::size_t rejected_area = 0;
    std::size_t rejected_score = 0;
    std::size_t rejected_safety = 0;
    const SearchResult * best_candidate = nullptr;
    for (const auto & candidate : candidates) {
      if (!best_candidate || candidate.score_m < best_candidate->score_m) {
        best_candidate = &candidate;
      }
    }
    for (const auto & candidate : candidates) {
      if (cancel_checker()) {throw nav2_core::PlannerCancelled("Coverage candidate canceled");}
      if (candidate.length_m > max_length) {++rejected_detour; continue;}
      const double area_gain = candidate.estimated_new_area_m2 - reference_new_area;
      const double extra_distance = std::max(0.0, candidate.length_m - reference_length);
      // A shorter or equal-length safe candidate may be selected on its total
      // score. Only a true detour must justify its extra travel with coverage.
      const bool coverage_regression = area_gain < -1e-9;
      const bool insufficient_area = coverage_regression ||
        (extra_distance > 1e-6 && area_gain < min_new_area_m2_);
      const bool insufficient_efficiency = extra_distance > 1e-6 &&
        area_gain / extra_distance < min_area_gain_per_extra_meter_;
      if (insufficient_area || insufficient_efficiency) {
        ++rejected_area; continue;
      }
      if (candidate.score_m + min_score_gain_m_ >= reference_score) {
        ++rejected_score; continue;
      }
      bool same_geometry;
      bool safe = false;
      {
        std::scoped_lock<Costmap::mutex_t> lock(*costmap_->getMutex());
        same_geometry = costmap_->getSizeInCellsX() == width &&
          costmap_->getSizeInCellsY() == height &&
          std::abs(costmap_->getResolution() - grid.resolution) <= 1e-9 &&
          std::abs(costmap_->getOriginX() - origin_x) <= 1e-9 &&
          std::abs(costmap_->getOriginY() - origin_y) <= 1e-9;
        if (same_geometry) {
          safe = candidate_is_safe(candidate, checker, cancel_checker);
        }
      }
      if (!same_geometry || !safe) {
        ++rejected_safety; continue;
      }
      nav_msgs::msg::Path path;
      path.header.frame_id = global_frame_;
      path.header.stamp = clock_->now();
      for (std::size_t i = 0; i < candidate.cells.size(); ++i) {
        const int cell = candidate.cells[i];
        const double wx = origin_x + (cell % grid.width + 0.5) * grid.resolution;
        const double wy = origin_y + (cell / grid.width + 0.5) * grid.resolution;
        const auto next = candidate.cells[std::min(i + 1, candidate.cells.size() - 1)];
        const auto prev = candidate.cells[i == 0 ? i : i - 1];
        const double yaw = std::atan2(next / grid.width - prev / grid.width,
          next % grid.width - prev % grid.width);
        geometry_msgs::msg::PoseStamped pose;
        pose.header = path.header;
        pose.pose.position.x = wx;
        pose.pose.position.y = wy;
        pose.pose.orientation.z = std::sin(yaw / 2.0);
        pose.pose.orientation.w = std::cos(yaw / 2.0);
        path.poses.push_back(pose);
      }
      path.poses.front().pose = start.pose;
      path.poses.back().pose = goal.pose;
      ++coverage_selected_;
      publish_coverage_event("coverage_selected", request_id, candidates.size(),
        reference_length, candidate.estimated_new_area_m2, started,
        candidate.length_m, candidate.length_m - reference_length, reference_new_area,
        candidate.length_m, candidate.estimated_new_area_m2, candidate.score_m,
        rejected_detour, rejected_area, rejected_score, rejected_safety);
      return path;
    }
    ++navfn_fallbacks_;
    std::string fallback = "coverage_fallback_no_safe_candidate";
    if (candidates.empty()) {
      fallback += "_none_generated";
    } else if (rejected_safety == candidates.size()) {
      fallback += "_footprint";
    } else if (rejected_detour == candidates.size()) {
      fallback += "_detour";
    } else if (rejected_area == candidates.size()) {
      fallback += "_area";
    } else if (rejected_score == candidates.size()) {
      fallback += "_score";
    } else {
      fallback += "_mixed_constraints";
    }
    publish_coverage_event(fallback, request_id, candidates.size(),
      reference_length, 0.0, started, 0.0, 0.0, reference_new_area,
      best_candidate ? best_candidate->length_m : 0.0,
      best_candidate ? best_candidate->estimated_new_area_m2 : 0.0,
      best_candidate ? best_candidate->score_m : 0.0,
      rejected_detour, rejected_area, rejected_score, rejected_safety);
    return reference;
  }

  static double path_length(const nav_msgs::msg::Path & path)
  {
    double total = 0.0;
    for (std::size_t i = 1; i < path.poses.size(); ++i) {
      const auto & a = path.poses[i - 1].pose.position;
      const auto & b = path.poses[i].pose.position;
      total += std::hypot(b.x - a.x, b.y - a.y);
    }
    return total;
  }

  bool coverage_valid(const nav_msgs::msg::OccupancyGrid & g, rclcpp::Time received,
    const geometry_msgs::msg::PoseStamped & start, const geometry_msgs::msg::PoseStamped & goal,
    std::string & reason) const
  {
    if (start.header.frame_id != global_frame_ || goal.header.frame_id != global_frame_ ||
      g.header.frame_id != global_frame_) {reason = "frame"; return false;}
    const auto age = clock_->now() - received;
    if (age < rclcpp::Duration::from_seconds(0.0) || age > rclcpp::Duration::from_seconds(2.0)) {
      reason = "stale"; return false;
    }
    const auto & q = g.info.origin.orientation;
    const double norm = std::sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
    if (!std::isfinite(norm) || norm < 1e-9) {reason = "geometry"; return false;}
    const double x = q.x / norm, y = q.y / norm, z = q.z / norm, w = q.w / norm;
    const double roll = std::atan2(2.0 * (w * x + y * z), 1.0 - 2.0 * (x * x + y * y));
    const double pitch_sin = 2.0 * (w * y - z * x);
    const double pitch = std::asin(std::clamp(pitch_sin, -1.0, 1.0));
    const double origin_yaw = std::atan2(2.0 * (w * z + x * y),
      1.0 - 2.0 * (y * y + z * z));
    const double costmap_origin_yaw = 0.0;
    const double yaw_error = std::atan2(
      std::sin(origin_yaw - costmap_origin_yaw), std::cos(origin_yaw - costmap_origin_yaw));
    const auto message_age = clock_->now() - rclcpp::Time(g.header.stamp, clock_->get_clock_type());
    if (message_age < rclcpp::Duration::from_seconds(-0.1) ||
      message_age > rclcpp::Duration::from_seconds(2.0)) {reason = "message_stale"; return false;}
    if (std::abs(roll) > 1e-6 || std::abs(pitch) > 1e-6 || std::abs(yaw_error) > 1e-6 ||
      g.info.width != costmap_->getSizeInCellsX() ||
      g.info.height != costmap_->getSizeInCellsY() ||
      std::abs(g.info.resolution - costmap_->getResolution()) > 1e-6 ||
      std::abs(g.info.origin.position.x - costmap_->getOriginX()) > 1e-4 ||
      std::abs(g.info.origin.position.y - costmap_->getOriginY()) > 1e-4 ||
      g.data.size() != static_cast<std::size_t>(g.info.width) * g.info.height) {
      reason = "geometry"; return false;
    }
    if (!std::isfinite(start.pose.position.x) || !std::isfinite(start.pose.position.y) ||
      !std::isfinite(goal.pose.position.x) || !std::isfinite(goal.pose.position.y)) {
      reason = "pose"; return false;
    }
    return true;
  }

  template<typename Checker>
  bool candidate_is_safe(const SearchResult & candidate, Checker & checker,
    const std::function<bool()> & canceled) const
  {
    const double step = std::min(0.025, costmap_->getResolution() / 2.0);
    for (std::size_t i = 0; i < candidate.cells.size(); ++i) {
      if (canceled()) {throw nav2_core::PlannerCancelled("Footprint validation canceled");}
      const int a = candidate.cells[i];
      const int b = candidate.cells[std::min(i + 1, candidate.cells.size() - 1)];
      double ax, ay, bx, by;
      costmap_->mapToWorld(a % costmap_->getSizeInCellsX(), a / costmap_->getSizeInCellsX(), ax, ay);
      costmap_->mapToWorld(b % costmap_->getSizeInCellsX(), b / costmap_->getSizeInCellsX(), bx, by);
      const double distance = std::hypot(bx - ax, by - ay);
      const int samples = std::max(1, static_cast<int>(std::ceil(distance / step)));
      const double yaw = std::atan2(by - ay, bx - ax);
      for (int j = 0; j <= samples; ++j) {
        const double f = static_cast<double>(j) / samples;
        unsigned int mx, my;
        const double x = ax + f * (bx - ax), y = ay + f * (by - ay);
        if (!costmap_->worldToMap(x, y, mx, my) ||
          costmap_->getCost(mx, my) >= nav2_costmap_2d::INSCRIBED_INFLATED_OBSTACLE ||
          checker.footprintCostAtPose(x, y, yaw, robot_footprint_) >=
          nav2_costmap_2d::INSCRIBED_INFLATED_OBSTACLE) {return false;}
      }
    }
    return true;
  }

  void publish_coverage_event(const std::string & decision, uint64_t request_id,
    std::size_t candidate_count, double reference_length, double new_area,
    std::chrono::steady_clock::time_point started,
    double selected_length = 0.0, double extra_distance = 0.0,
    double reference_new_area = 0.0, double best_candidate_length = 0.0,
    double best_candidate_new_area = 0.0, double best_candidate_score = 0.0,
    std::size_t rejected_detour = 0, std::size_t rejected_area = 0,
    std::size_t rejected_score = 0, std::size_t rejected_safety = 0) const
  {
    if (!planner_events_) {return;}
    const auto elapsed = std::chrono::duration<double>(
      std::chrono::steady_clock::now() - started).count();
    std::ostringstream out;
    out << "{\"stamp_ns\":" << clock_->now().nanoseconds()
        << ",\"request_id\":" << request_id << ",\"decision\":\"" << decision
        << "\",\"strategy\":\"coverage_aware\",\"candidate_count\":" << candidate_count
        << ",\"coverage_search_participated\":" <<
      ((decision == "coverage_selected" ||
      decision.rfind("coverage_fallback_no_safe_candidate", 0) == 0) ?
      "true" : "false")
        << ",\"reference_length_m\":" << reference_length
        << ",\"selected_length_m\":" << selected_length
        << ",\"extra_distance_m\":" << extra_distance
        << ",\"new_area_m2\":" << new_area
        << ",\"reference_new_area_m2\":" << reference_new_area
        << ",\"best_candidate_length_m\":" << best_candidate_length
        << ",\"best_candidate_new_area_m2\":" << best_candidate_new_area
        << ",\"best_candidate_score_m\":" << best_candidate_score
        << ",\"rejected_detour\":" << rejected_detour
        << ",\"rejected_area\":" << rejected_area
        << ",\"rejected_score\":" << rejected_score
        << ",\"rejected_safety\":" << rejected_safety
        << ",\"planning_ms\":" << elapsed * 1000.0
        << ",\"coverage_requests\":" << coverage_requests_.load()
        << ",\"coverage_searches\":" << coverage_searches_.load()
        << ",\"coverage_selected\":" << coverage_selected_.load()
        << ",\"candidates_generated\":" << candidates_generated_.load()
        << ",\"navfn_fallbacks\":" << navfn_fallbacks_.load() << "}";
    std_msgs::msg::String message; message.data = out.str(); planner_events_->publish(message);
  }

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

  std::string strategy_{"direct"};
  double coverage_cleaning_radius_{0.20};
  double max_detour_ratio_{1.25};
  double max_detour_distance_{0.75};
  double coverage_weight_{0.35};
  double min_new_area_m2_{0.0025};
  double min_area_gain_per_extra_meter_{0.05};
  double min_score_gain_m_{0.03};
  mutable std::mutex coverage_mutex_;
  nav_msgs::msg::OccupancyGrid::ConstSharedPtr coverage_;
  rclcpp::Time coverage_received_{0, 0, RCL_ROS_TIME};
  rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr coverage_sub_;
  std::atomic<uint64_t> coverage_requests_{0};
  std::atomic<uint64_t> coverage_searches_{0};
  std::atomic<uint64_t> candidates_generated_{0};
  std::atomic<uint64_t> coverage_selected_{0};

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
