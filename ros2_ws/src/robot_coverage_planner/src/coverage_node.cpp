// SPDX-License-Identifier: Apache-2.0
#include "robot_coverage_planner/baseline_coverage_plan.hpp"
#include "robot_coverage_planner/coverage_plan.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <mutex>
#include <limits>
#include <stdexcept>
#include <unordered_map>

#include <nav_msgs/msg/occupancy_grid.hpp>
#include <nav_msgs/msg/path.hpp>
#include <rclcpp/create_timer.hpp>
#include <rclcpp/rclcpp.hpp>
#include <robot_cleaning_interfaces/msg/coverage_status.hpp>
#include <robot_cleaning_interfaces/msg/localization_health.hpp>
#include <robot_cleaning_interfaces/srv/begin_coverage.hpp>
#include <robot_cleaning_interfaces/srv/plan_coverage.hpp>
#include <std_msgs/msg/string.hpp>
#include <tf2_ros/buffer.hpp>
#include <tf2_ros/transform_listener.hpp>

namespace robot_coverage_planner
{
using namespace std::chrono_literals;
using Grid = nav_msgs::msg::OccupancyGrid;
using Begin = robot_cleaning_interfaces::srv::BeginCoverage;
using Plan = robot_cleaning_interfaces::srv::PlanCoverage;
using Status = robot_cleaning_interfaces::msg::CoverageStatus;

using LocalizationHealth = robot_cleaning_interfaces::msg::LocalizationHealth;
namespace
{
constexpr double kMaximumCostmapAgeS = 2.0;
constexpr double kMaximumFutureClockSkewS = 0.1;
constexpr double kStartPoseFallbackRadiusM = 0.25;
constexpr double kMaximumDistanceSampleM = 0.50;
constexpr auto kContinuousSamplePeriod = std::chrono::milliseconds(50);
constexpr auto kCellSamplePeriod = std::chrono::milliseconds(150);
}

class CoverageNode : public rclcpp::Node
{
public:
  CoverageNode()
  : Node("coverage_planner"), tf_(get_clock()), listener_(tf_, this, false)
  {
    options_.robot_radius = declare_parameter(
      "robot_radius", std::numeric_limits<double>::quiet_NaN());
    options_.safety_margin = declare_parameter("safety_margin", 0.005);
    options_.edge_margin = declare_parameter("edge_margin", 0.0);
    options_.refine_sweep = declare_parameter("refine_sweep", false);
    sweep_use_live_costmap_ = declare_parameter("sweep_use_live_costmap", true);
    gap_use_local_costmap_ = declare_parameter("gap_use_local_costmap", false);
    target_gap_coverage_ = declare_parameter("target_gap_coverage", false);
    continuous_coverage_tracking_ = declare_parameter("continuous_coverage_tracking", false);
    sweep_safety_margin_ = declare_parameter("sweep_safety_margin", options_.safety_margin);
    gap_safety_margin_ = declare_parameter("gap_safety_margin", options_.safety_margin);
    gap_edge_priority_margin_ = declare_parameter("gap_edge_priority_margin", 0.0);
    if (!std::isfinite(sweep_safety_margin_) || sweep_safety_margin_ < options_.safety_margin ||
      !std::isfinite(gap_safety_margin_) || gap_safety_margin_ < options_.safety_margin ||
      !std::isfinite(gap_edge_priority_margin_) || gap_edge_priority_margin_ < 0.0)
    {
      throw std::invalid_argument("invalid sweep or gap clearance");
    }
    options_.cleaning_radius = declare_parameter(
      "cleaning_radius", std::numeric_limits<double>::quiet_NaN());
    options_.row_overlap = declare_parameter("row_overlap", 0.10);
    options_.waypoint_spacing = declare_parameter("waypoint_spacing", 0.40);
    options_.turn_cost = declare_parameter("turn_cost", 0.20);
    planning_algorithm_ = declare_parameter<std::string>("planning_algorithm", "optimized");
    if (planning_algorithm_ != "optimized" && planning_algorithm_ != "baseline") {
      throw std::invalid_argument("planning_algorithm must be optimized or baseline");
    }
    base_frame_ = declare_parameter<std::string>("base_frame", "");
    odom_frame_ = declare_parameter<std::string>("odom_frame", "");
    if (!std::isfinite(options_.robot_radius) || options_.robot_radius <= 0.0 ||
      !std::isfinite(options_.cleaning_radius) || options_.cleaning_radius <= 0.0 ||
      base_frame_.empty() || odom_frame_.empty())
    {
      throw std::invalid_argument("robot geometry parameters must be provided by launch");
    }
    for (const auto & name :
      declare_parameter("region_names", std::vector<std::string>{}))
    {
      const auto bounds = declare_parameter("regions." + name, std::vector<double>{});
      if (bounds.size() != 4 || bounds[0] >= bounds[2] || bounds[1] >= bounds[3] ||
        !std::all_of(bounds.begin(), bounds.end(), [](double value) {return std::isfinite(value);}))
      {
        throw std::invalid_argument("invalid bounds for region " + name);
      }
      regions_[name] = {bounds[0], bounds[1], bounds[2], bounds[3]};
    }

    const auto latched = rclcpp::QoS(1).transient_local();
    map_sub_ = create_subscription<Grid>("map", latched, [this](Grid::ConstSharedPtr grid) {
        std::scoped_lock lock(map_mutex_);
        map_ = std::move(grid);
      });
    costmap_sub_ = create_subscription<Grid>(
      "global_costmap/costmap", latched, [this](Grid::ConstSharedPtr grid) {
        std::scoped_lock lock(map_mutex_);
        costmap_ = std::move(grid);
      });
    if (gap_use_local_costmap_) {
      local_costmap_sub_ = create_subscription<Grid>(
        "local_costmap/costmap", latched, [this](Grid::ConstSharedPtr grid) {
          std::scoped_lock lock(map_mutex_);
          local_costmap_ = std::move(grid);
        });
    }
    state_sub_ = create_subscription<std_msgs::msg::String>(
      "cleaning/state", latched, [this](std_msgs::msg::String::ConstSharedPtr state) {
        if (state->data != "RUNNING") {
          previous_.reset();
        }
        running_ = state->data == "RUNNING";
      });
    localization_sub_ = create_subscription<LocalizationHealth>(
      "cleaning/localization_health", latched,
      [this](LocalizationHealth::ConstSharedPtr health) {
        if (!health->healthy) {
          previous_.reset();
          previous_cell_.reset();
        }
        localization_healthy_ = health->healthy;
      });
    status_pub_ = create_publisher<Status>("cleaning/coverage_status", latched);
    grid_pub_ = create_publisher<Grid>("cleaning/covered_grid", latched);
    plan_pub_ = create_publisher<nav_msgs::msg::Path>("cleaning/planner_path", latched);
    plan_group_ = create_callback_group(rclcpp::CallbackGroupType::MutuallyExclusive);
    plan_ = create_service<Plan>("cleaning/plan_coverage", [this](
        const Plan::Request::SharedPtr request, Plan::Response::SharedPtr response)
      {
        plan_route(*request, *response);
      }, rclcpp::ServicesQoS(), plan_group_);
    begin_ = create_service<Begin>("cleaning/begin_coverage", [this](
        const Begin::Request::SharedPtr request, Begin::Response::SharedPtr response)
      {
        begin_tracking(*request, *response);
      });
    if (continuous_coverage_tracking_) {
      timer_ = rclcpp::create_timer(
        this, get_clock(), kContinuousSamplePeriod, std::bind(&CoverageNode::sample, this));
    } else {
      timer_ = create_wall_timer(kCellSamplePeriod, std::bind(&CoverageNode::sample, this));
    }
  }

private:
  Grid::ConstSharedPtr map() const
  {
    std::scoped_lock lock(map_mutex_);
    if (!map_) {
      throw std::runtime_error("No occupancy grid yet");
    }
    return map_;
  }

  static GridMap adapt(const Grid & map)
  {
    const auto & q = map.info.origin.orientation;
    GridMap grid{static_cast<int>(map.info.width), static_cast<int>(map.info.height),
      map.info.resolution, map.info.origin.position.x, map.info.origin.position.y,
      std::atan2(2 * (q.w * q.z + q.x * q.y), 1 - 2 * (q.y * q.y + q.z * q.z)), map.data};
    grid.validate();
    return grid;
  }

  std::size_t add_live_obstacles(GridMap & grid, const std::string & frame, Mask & blocked_centers)
  {
    Grid::ConstSharedPtr latest;
    {
      std::scoped_lock lock(map_mutex_);
      latest = costmap_;
    }
    if (!latest || latest->header.frame_id != frame) {
      return 0;
    }
    const auto age = now() - rclcpp::Time(latest->header.stamp, get_clock()->get_clock_type());
    if (age < rclcpp::Duration::from_seconds(-kMaximumFutureClockSkewS) ||
      age > rclcpp::Duration::from_seconds(kMaximumCostmapAgeS))
    {
      return 0;
    }
    const auto live = adapt(*latest);
    std::size_t added = 0;
    for (int i = 0; i < live.size(); ++i) {
      const auto value = live.occupancy[i];
      if (value != 100 && (value != 99 || blocked_centers.empty())) {
        continue;
      }
      const auto [x, y] = live.center(live.cell(i));
      if (const auto cell = grid.from_world(x, y)) {
        const int index = grid.index(*cell);
        if (value == 100) {
          added += grid.occupancy[index] == 0;
          grid.occupancy[index] = 100;
        } else {
          // Inscribed costs already include the robot body. Exclude them as
          // centers without adding a second footprint inflation.
          blocked_centers[index] = 1;
        }
      }
    }
    return added;
  }

  std::size_t add_local_blocked_centers(
    const GridMap & grid, const std::string & frame, Mask & blocked_centers)
  {
    Grid::ConstSharedPtr latest;
    {
      std::scoped_lock lock(map_mutex_);
      latest = local_costmap_;
    }
    if (!latest || blocked_centers.empty()) {
      return 0;
    }
    const auto age = now() - rclcpp::Time(latest->header.stamp, get_clock()->get_clock_type());
    if (age < rclcpp::Duration::from_seconds(-kMaximumFutureClockSkewS) ||
      age > rclcpp::Duration::from_seconds(kMaximumCostmapAgeS))
    {
      return 0;
    }
    geometry_msgs::msg::Transform map_to_local;
    map_to_local.rotation.w = 1.0;
    if (latest->header.frame_id != frame) {
      try {
        map_to_local = tf_.lookupTransform(
          latest->header.frame_id, frame, tf2::TimePointZero).transform;
      } catch (const tf2::TransformException &) {
        return 0;
      }
    }
    const auto local = adapt(*latest);
    const auto & q = map_to_local.rotation;
    const double yaw = std::atan2(2 * (q.w * q.z + q.x * q.y),
        1 - 2 * (q.y * q.y + q.z * q.z));
    const double c = std::cos(yaw);
    const double d = std::sin(yaw);
    std::size_t added = 0;
    for (int i = 0; i < grid.size(); ++i) {
      if (blocked_centers[i] || grid.occupancy[i] != 0) {
        continue;
      }
      const auto [x, y] = grid.center(grid.cell(i));
      const auto cell = local.from_world(
        map_to_local.translation.x + c * x - d * y,
        map_to_local.translation.y + d * x + c * y);
      // Nav2 has already inflated these costs by the robot footprint.
      if (cell && local.occupancy[local.index(*cell)] >= 99) {
        blocked_centers[i] = 1;
        ++added;
      }
    }
    return added;
  }

  std::vector<Region> bounds(const std::vector<std::string> & requested) const
  {
    std::vector<Region> result;
    for (const auto & name : requested) {
      const auto region = regions_.find(name);
      if (region == regions_.end()) {
        throw std::invalid_argument("Unknown region: " + name);
      }
      result.push_back(region->second);
    }
    return result;
  }

  Cell start_cell(
    const GridMap & grid, const geometry_msgs::msg::PoseStamped & start,
    const PlanOptions & options, const Mask & blocked_centers = {}) const
  {
    const auto position = grid.from_world(start.pose.position.x, start.pose.position.y);
    if (!position) {
      throw std::invalid_argument("Robot pose is outside the map");
    }
    const auto free = grid.drivable(options.robot_radius + options.safety_margin);
    const auto drivable = [&](int index) {
        return free[index] && (blocked_centers.empty() || !blocked_centers[index]);
      };
    if (drivable(grid.index(*position))) {
      return *position;
    }
    double best = kStartPoseFallbackRadiusM;
    std::optional<Cell> fallback;
    for (int i = 0; i < grid.size(); ++i) {
      if (!drivable(i)) {
        continue;
      }
      const auto cell = grid.cell(i);
      const auto distance = std::hypot(cell.x - position->x, cell.y - position->y) *
        grid.resolution;
      if (distance < best) {
        best = distance;
        fallback = cell;
      }
    }
    if (!fallback) {
        throw std::invalid_argument("No drivable start within configured fallback radius");
    }
    return *fallback;
  }

  void plan_route(const Plan::Request & request, Plan::Response & response)
  {
    try {
      const auto source = map();
      auto grid = adapt(*source);
      if (request.start.header.frame_id != source->header.frame_id) {
        throw std::invalid_argument("Start pose is not in the map frame");
      }
      const auto zones = bounds(request.regions);
      Mask priority;
      Mask task_floor;
      Mask blocked_centers;
      const auto & covered = request.covered;
      if (!covered.data.empty()) {
        if (covered.header.frame_id != source->header.frame_id ||
          covered.info.width != source->info.width || covered.info.height != source->info.height ||
          covered.info.resolution != source->info.resolution ||
          covered.info.origin != source->info.origin || covered.data.size() != grid.occupancy.size())
        {
          throw std::invalid_argument("Coverage grid is not aligned with the static map");
        }
        for (auto value : covered.data) {
          task_floor.push_back(value >= 0);
        }
      }
      if (options_.edge_margin > 0.0) {
        blocked_centers.assign(grid.size(), 0);
        if (task_floor.empty()) {
          task_floor = CoveragePlan(grid, options_, start_cell(grid, request.start, options_)).
            target_floor(zones);
        }
      }
      if (request.gap_fill && gap_edge_priority_margin_ > 0.0) {
        priority = grid.drivable(gap_edge_priority_margin_ + 1e-8);
      }
      if (request.gap_fill || (options_.edge_margin > 0.0 && sweep_use_live_costmap_)) {
        const auto added = add_live_obstacles(grid, source->header.frame_id, blocked_centers);
        if (options_.edge_margin > 0.0) {
          RCLCPP_INFO(get_logger(), "Planning with %zu additional live obstacle cells", added);
        }
      }
      auto options = options_;
      options.safety_margin = request.gap_fill ? gap_safety_margin_ : sweep_safety_margin_;
      Cell start{};
      std::vector<Cell> points;
      if (request.gap_fill) {
        Mask cleaned;
        for (auto value : request.covered.data) {
          cleaned.push_back(value == 100);
        }
        std::vector<Cell> excluded;
        for (const auto & point : request.excluded) {
          if (auto cell = grid.from_world(point.x, point.y)) {
            excluded.push_back(*cell);
          }
        }
        const auto global_blocked = blocked_centers;
        const auto local_added = add_local_blocked_centers(
          grid, source->header.frame_id, blocked_centers);
        if (local_added > 0) {
          RCLCPP_INFO(get_logger(), "Gap search blocked %zu centers from the local costmap", local_added);
        }
        const auto gap_plan = [&]() {
            start = start_cell(grid, request.start, options, blocked_centers);
            if (planning_algorithm_ == "baseline") {
              const BaselineCoveragePlan planner(grid, options, start, blocked_centers);
              return planner.gaps(start, zones, cleaned, excluded, priority, task_floor,
                  target_gap_coverage_ ? request.target_coverage : 0.0,
                  request.distance_budget_m);
            }
            const CoveragePlan planner(grid, options, start, blocked_centers);
            return planner.gaps(start, zones, cleaned, excluded, priority, task_floor,
                target_gap_coverage_ ? request.target_coverage : 0.0,
                request.distance_budget_m);
          };
        if (local_added > 0) {
          try {
            points = gap_plan();
          } catch (const std::invalid_argument &) {
            // A rolling costmap can temporarily cover all start candidates.
          }
          if (points.empty()) {
            blocked_centers = global_blocked;
            RCLCPP_INFO(get_logger(), "Retrying gap search with the global costmap");
          }
        }
        if (points.empty()) {
          if (options.edge_margin > 0.0 && options.safety_margin > options_.safety_margin) {
            try {
              points = gap_plan();
            } catch (const std::invalid_argument &) {
              // Extra clearance can isolate a start that still fits the body.
            }
            if (points.empty()) {
              RCLCPP_INFO(get_logger(), "Retrying gap plan with the normal body clearance");
              options.safety_margin = options_.safety_margin;
              points = gap_plan();
            }
          } else {
            points = gap_plan();
          }
        }
      } else {
        start = start_cell(grid, request.start, options, blocked_centers);
        const double target = request.target_coverage == 0.0 ? 0.90 : request.target_coverage;
        if (planning_algorithm_ == "baseline") {
          const BaselineCoveragePlan planner(grid, options, start, blocked_centers);
          points = planner.sweep(start, zones, target, task_floor);
        } else {
          const CoveragePlan planner(grid, options, start, blocked_centers);
          points = planner.sweep(start, zones, target, task_floor);
        }
      }

      response.path.header.frame_id = source->header.frame_id;
      response.path.header.stamp = now();
      double planned_length = 0.0;
      for (std::size_t i = 0; i < points.size(); ++i) {
        const auto [x, y] = grid.center(points[i]);
        const auto previous = i > 0 ? points[i - 1] : start;
        const auto [px, py] = grid.center(previous);
        const auto yaw = std::atan2(y - py, x - px);
        planned_length += std::hypot(x - px, y - py);
        geometry_msgs::msg::PoseStamped pose;
        pose.header = response.path.header;
        pose.pose.position.x = x;
        pose.pose.position.y = y;
        pose.pose.orientation.z = std::sin(yaw / 2);
        pose.pose.orientation.w = std::cos(yaw / 2);
        response.path.poses.push_back(pose);
      }
      response.success = request.gap_fill || !points.empty();
      response.reason = points.empty() ? "No reachable target after geometry and failure exclusions" :
        (planning_algorithm_ == "baseline" ?
        (request.gap_fill ? "Baseline nearest-missing-floor gap route" :
        "Baseline deterministic boustrophedon route") :
        (request.gap_fill ? "Selected connectors by swept uncovered area and travel cost" :
        "Selected sweep lanes by travel and predicted missed floor"));
      RCLCPP_INFO(get_logger(), "algorithm=%s gap_fill=%d waypoints=%zu planned_m=%.2f: %s",
        planning_algorithm_.c_str(), request.gap_fill, points.size(), planned_length,
        response.reason.c_str());
      plan_pub_->publish(response.path);
    } catch (const std::exception & e) {
      response.reason = e.what();
    }
  }

  void begin_tracking(const Begin::Request & request, Begin::Response & response)
  {
    try {
      const auto source = map();
      auto grid = adapt(*source);
      if (request.start.header.frame_id != source->header.frame_id) {
        throw std::invalid_argument("Start pose is not in the map frame");
      }
      auto target = CoveragePlan(grid, options_, start_cell(grid, request.start, options_)).
        target_floor(bounds(request.regions));
      const auto total = std::count(target.begin(), target.end(), 1);
      if (total == 0 || (!request.restored_grid.empty() &&
        request.restored_grid.size() != target.size()))
      {
        throw std::invalid_argument("No reachable floor or restored grid size mismatch");
      }
      grid_ = std::move(grid);
      tracking_map_ = source;
      task_id_ = request.task_id;
      target_ = std::move(target);
      total_ = total;
      RCLCPP_INFO(get_logger(), "Tracking %zu target cells with edge_margin=%.2f m",
        total_, options_.edge_margin);
      cleaned_.assign(target_.size(), 0);
      for (std::size_t i = 0; i < request.restored_grid.size(); ++i) {
        cleaned_[i] = target_[i] && request.restored_grid[i] == 100;
      }
      distance_ = request.restored_distance_m;
      previous_.reset();
      previous_cell_.reset();
      response.success = true;
      publish();
    } catch (const std::exception & e) {
      response.reason = e.what();
    }
  }

  void sample()
  {
    if (!grid_ || !running_ || !localization_healthy_) {
      return;
    }
    try {
      const auto transform = tf_.lookupTransform(
        tracking_map_->header.frame_id, base_frame_, tf2::TimePointZero);
      const auto & point = transform.transform.translation;
      const auto cell = grid_->from_world(point.x, point.y);
      if (!cell) {
        previous_.reset();
        previous_cell_.reset();
        return;
      }
      auto distance_point = point;
      bool uses_odom = false;
      try {
        distance_point = tf_.lookupTransform(odom_frame_, base_frame_, tf2::TimePointZero).
          transform.translation;
        uses_odom = true;
      } catch (const tf2::TransformException &) {
        // A map-only graph can still track distance without an odom transform.
      }
      if (previous_ && previous_uses_odom_ == uses_odom) {
        const auto [x, y] = *previous_;
        const double step = std::hypot(distance_point.x - x, distance_point.y - y);
        if (step < kMaximumDistanceSampleM) {
          distance_ += step;
        }
      }
      previous_.emplace(distance_point.x, distance_point.y);
      previous_uses_odom_ = uses_odom;
      const bool moved_cell = !previous_cell_ || *previous_cell_ != *cell;
      bool new_floor = false;
      if (continuous_coverage_tracking_) {
        new_floor = grid_->stamp_at_pose(cleaned_, target_, point.x, point.y, options_.cleaning_radius);
      } else if (moved_cell) {
        grid_->stamp(cleaned_, target_, *cell, options_.cleaning_radius);
      }
      if (new_floor || moved_cell) {
        previous_cell_ = cell;
        publish();
      }
    } catch (const tf2::TransformException &) {
      previous_.reset();
      previous_cell_.reset();
    }
  }

  void publish()
  {
    Status msg;
    msg.task_id = task_id_;
    msg.covered.header = tracking_map_->header;
    msg.covered.header.stamp = now();
    msg.covered.info = tracking_map_->info;
    msg.covered.data.reserve(cleaned_.size());
    for (std::size_t i = 0; i < cleaned_.size(); ++i) {
      msg.covered.data.push_back(cleaned_[i] ? 100 : (target_[i] ? 0 : -1));
    }
    msg.coverage = static_cast<float>(std::count(cleaned_.begin(), cleaned_.end(), 1)) / total_;
    msg.path_length_m = distance_;
    grid_pub_->publish(msg.covered);
    status_pub_->publish(msg);
  }

  PlanOptions options_;
  bool sweep_use_live_costmap_;
  bool gap_use_local_costmap_;
  bool target_gap_coverage_;
  bool continuous_coverage_tracking_;
  double sweep_safety_margin_;
  double gap_safety_margin_;
  double gap_edge_priority_margin_;
  std::string planning_algorithm_;
  std::unordered_map<std::string, Region> regions_;
  std::string base_frame_;
  std::string odom_frame_;
  mutable std::mutex map_mutex_;
  Grid::ConstSharedPtr map_;
  Grid::ConstSharedPtr costmap_;
  Grid::ConstSharedPtr local_costmap_;
  Grid::ConstSharedPtr tracking_map_;
  std::optional<GridMap> grid_;
  std::optional<std::pair<double, double>> previous_;
  bool previous_uses_odom_{false};
  std::optional<Cell> previous_cell_;
  Mask target_;
  Mask cleaned_;
  std::string task_id_;
  std::size_t total_{0};
  double distance_{0};
  bool running_{false};
  bool localization_healthy_{false};
  tf2_ros::Buffer tf_;
  tf2_ros::TransformListener listener_;
  rclcpp::CallbackGroup::SharedPtr plan_group_;
  rclcpp::Subscription<Grid>::SharedPtr map_sub_;
  rclcpp::Subscription<Grid>::SharedPtr costmap_sub_;
  rclcpp::Subscription<Grid>::SharedPtr local_costmap_sub_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr state_sub_;
  rclcpp::Subscription<LocalizationHealth>::SharedPtr localization_sub_;
  rclcpp::Publisher<Status>::SharedPtr status_pub_;
  rclcpp::Publisher<Grid>::SharedPtr grid_pub_;
  rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr plan_pub_;
  rclcpp::Service<Begin>::SharedPtr begin_;
  rclcpp::Service<Plan>::SharedPtr plan_;
  rclcpp::TimerBase::SharedPtr timer_;
};
}  // namespace robot_coverage_planner

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::executors::MultiThreadedExecutor executor(rclcpp::ExecutorOptions(), 2);
  auto planner = std::make_shared<robot_coverage_planner::CoverageNode>();
  executor.add_node(planner);
  executor.spin();
  rclcpp::shutdown();
  return 0;
}
