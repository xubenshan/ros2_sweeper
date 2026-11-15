// SPDX-License-Identifier: Apache-2.0
#include "robot_cleaning_manager/checkpoint_store.hpp"
#include "robot_cleaning_manager/cleaning_event_log.hpp"
#include "robot_cleaning_manager/completion_decision.hpp"
#include "robot_cleaning_manager/navigation_executor.hpp"
#include "robot_cleaning_manager/pause_ownership.hpp"
#include "robot_cleaning_manager/planning_request.hpp"
#include "robot_cleaning_manager/replan_policy.hpp"
#include "robot_cleaning_manager/recovery_executor.hpp"
#include "robot_cleaning_manager/task_state.hpp"
#include "robot_cleaning_manager/waypoint_guard.hpp"

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <csignal>
#include <cstdlib>
#include <functional>
#include <limits>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <unordered_map>

#include <nav_msgs/msg/occupancy_grid.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <nav_msgs/msg/path.hpp>
#include <robot_cleaning_interfaces/action/clean_task.hpp>
#include <robot_cleaning_interfaces/msg/cleaning_event.hpp>
#include <robot_cleaning_interfaces/msg/coverage_status.hpp>
#include <robot_cleaning_interfaces/msg/localization_health.hpp>
#include <robot_cleaning_interfaces/srv/begin_coverage.hpp>
#include <robot_cleaning_interfaces/srv/plan_coverage.hpp>
#include <robot_cleaning_interfaces/srv/list_cleaning_events.hpp>
#include <std_msgs/msg/float32.hpp>
#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/empty.hpp>
#include <std_msgs/msg/string.hpp>
#include <std_srvs/srv/trigger.hpp>
#include <tf2_ros/buffer.hpp>
#include <tf2_ros/transform_listener.hpp>

namespace robot_cleaning_manager
{
using namespace std::chrono_literals;
using CleanTask = robot_cleaning_interfaces::action::CleanTask;
using TaskHandle = rclcpp_action::ServerGoalHandle<CleanTask>;
using Trigger = std_srvs::srv::Trigger;
using Pose = geometry_msgs::msg::PoseStamped;
using Plan = robot_cleaning_interfaces::srv::PlanCoverage;
using Begin = robot_cleaning_interfaces::srv::BeginCoverage;
using Coverage = robot_cleaning_interfaces::msg::CoverageStatus;
using CleaningEvent = robot_cleaning_interfaces::msg::CleaningEvent;
using LocalizationHealth = robot_cleaning_interfaces::msg::LocalizationHealth;
using ListCleaningEvents = robot_cleaning_interfaces::srv::ListCleaningEvents;
using Grid = nav_msgs::msg::OccupancyGrid;

namespace
{
constexpr double kMaximumOdomSampleM = 0.50;
constexpr double kCoveredSweepSkipRatio = 0.85;
constexpr double kMaximumCostmapAgeS = 2.0;
constexpr double kMaximumFutureClockSkewS = 0.10;
constexpr int kNav2InscribedCost = 99;

std::string map_identity(const nav_msgs::msg::OccupancyGrid & map)
{
  uint64_t hash = 14695981039346656037ULL;
  const auto mix = [&hash](uint8_t value) {
      hash = (hash ^ value) * 1099511628211ULL;
    };
  const auto & origin = map.info.origin;
  std::ostringstream geometry;
  geometry.precision(17);
  geometry << map.header.frame_id << ' ' << map.info.width << ' ' << map.info.height << ' '
           << map.info.resolution << ' ' << origin.position.x << ' ' << origin.position.y << ' '
           << origin.orientation.z << ' ' << origin.orientation.w;
  for (auto value : geometry.str()) {
    mix(static_cast<uint8_t>(value));
  }
  for (auto value : map.data) {
    mix(static_cast<uint8_t>(value));
  }
  return std::to_string(hash);
}
}  // namespace

class CleaningTaskManager : public rclcpp::Node
{
public:
  CleaningTaskManager()
  : Node("cleaning_task_manager"), nav_(*this),
    checkpoints_(declare_parameter<std::string>(
        "checkpoint_dir", std::string(std::getenv("HOME") ? std::getenv("HOME") : ".") +
        "/.ros/sweeper_checkpoints")),
    timeout_(declare_parameter<int>("navigation_timeout_s", 90)),
    progress_timeout_(declare_parameter<int>("progress_timeout_s", 35)),
    gap_progress_timeout_(declare_parameter<int>("gap_progress_timeout_s", progress_timeout_.count())),
    planning_timeout_(declare_parameter<int>("planning_timeout_s", 60)),
    startup_timeout_(declare_parameter<int>("startup_timeout_s", 60)),
    nav_unavailable_grace_(declare_parameter<int>("nav_unavailable_grace_s", 5)),
    retries_(declare_parameter<int>("navigation_retries", 1)),
    gap_retries_(declare_parameter<int>("gap_navigation_retries", retries_)),
    use_planner_(declare_parameter("use_coverage_planner", false)),
    defer_blocked_sweep_goals_(declare_parameter("defer_blocked_sweep_goals", false)),
    adjust_blocked_gap_goals_(declare_parameter("adjust_blocked_gap_goals", false)),
    early_gap_replan_(declare_parameter("early_gap_replan", true)),
    max_gap_passes_(declare_parameter<int>("max_gap_passes", 3)),
    gap_failure_replan_threshold_(declare_parameter<int>("gap_failure_replan_threshold", 0)),
    event_log_capacity_(declare_parameter<int>("event_log_capacity", 500)),
    event_log_(static_cast<std::size_t>(std::max(1, event_log_capacity_))),
    cleaning_radius_(declare_parameter("cleaning_radius", std::numeric_limits<double>::quiet_NaN())),
    map_frame_(declare_parameter<std::string>("map_frame", "")),
    base_frame_(declare_parameter<std::string>("base_frame", "")),
    coverage_completion_margin_(declare_parameter("coverage_completion_margin", 0.01)),
    target_path_efficiency_(declare_parameter("target_path_efficiency", 0.0)),
    minimum_gap_distance_budget_m_(
      declare_parameter("minimum_gap_distance_budget_m", 0.50)),
    gap_behavior_tree_(declare_parameter<std::string>("gap_behavior_tree", "")),
    planning_requests_(PlanningRequestOptions{
        cleaning_radius_, target_path_efficiency_, minimum_gap_distance_budget_m_}),
    waypoint_guard_(WaypointGuardConfig{
        declare_parameter("waypoint_adjustment_radius_m", 0.15),
        declare_parameter("maximum_adjustment_connector_m", 0.80),
        declare_parameter("turn_clearance_margin_m", 0.035),
        declare_parameter("turn_diagonal_clearance_m", 0.025),
        declare_parameter("short_connector_guard_m", 1.20)}),
    tf_(get_clock()), listener_(tf_, this, false)
  {
    if (timeout_.count() < 1 || progress_timeout_.count() < 1 || gap_progress_timeout_.count() < 1 ||
      planning_timeout_.count() < 1 || startup_timeout_.count() < 1 ||
      nav_unavailable_grace_.count() < 1 ||
      retries_ < 0 || gap_retries_ < 0 || gap_failure_replan_threshold_ < 0 ||
      !std::isfinite(cleaning_radius_) || cleaning_radius_ <= 0.0 ||
      map_frame_.empty() || base_frame_.empty() ||
      !std::isfinite(coverage_completion_margin_) || coverage_completion_margin_ < 0.0 ||
      coverage_completion_margin_ > 0.10 ||
      !std::isfinite(target_path_efficiency_) || target_path_efficiency_ < 0.0 ||
      event_log_capacity_ < 1 || event_log_capacity_ > 10000 ||
      target_path_efficiency_ > 1.0 || !std::isfinite(minimum_gap_distance_budget_m_) ||
      minimum_gap_distance_budget_m_ <= 0.0)
    {
      throw std::invalid_argument("invalid navigation limits or required robot geometry");
    }
    names_ = declare_parameter<std::vector<std::string>>("region_names", std::vector<std::string>{});
    for (const auto & name : names_) {
      auto route = declare_parameter<std::vector<double>>("routes." + name, std::vector<double>{});
      if (route.empty() || route.size() % 3 != 0 ||
        !std::all_of(route.begin(), route.end(), [](double n) {return std::isfinite(n);}))
      {
        throw std::invalid_argument("invalid route for region " + name);
      }
      for (std::size_t i = 0; i < route.size(); i += 3) {
        Pose pose;
        pose.header.frame_id = map_frame_;
        pose.pose.position.x = route[i];
        pose.pose.position.y = route[i + 1];
        pose.pose.orientation.z = std::sin(route[i + 2] / 2.0);
        pose.pose.orientation.w = std::cos(route[i + 2] / 2.0);
        routes_[name].push_back(pose);
      }
    }

    const auto latched = rclcpp::QoS(1).transient_local();
    heartbeat_ = create_publisher<std_msgs::msg::Empty>("cleaning/heartbeat", 10);
    active_pub_ = create_publisher<std_msgs::msg::Bool>("cleaning/active", latched);
    recovery_cmd_ = create_publisher<geometry_msgs::msg::Twist>("cmd_vel_recovery", 10);
    contact_sub_ = create_subscription<std_msgs::msg::String>(
      "motion/contact", latched, [this](std_msgs::msg::String::ConstSharedPtr msg) {
        contact_ = msg->data;
        if (task_ && state() == TaskState::running && contact_ != "clear" && !recovery_) {
          recovery_.emplace(contact_);
          recovery_start_.reset();
          record_event("COLLISION_RECOVERY", CleaningEvent::WARNING,
            "Collision detected on " + contact_);
          transition_to(TaskState::recovering, "collision detected");
          nav_.cancel();
          RCLCPP_WARN(get_logger(), "Collision on %s, recovering waypoint %zu",
            contact_.c_str(), current_.next);
        }
      });
    estop_sub_ = create_subscription<std_msgs::msg::Bool>(
      "motion/estop_state", latched, [this](std_msgs::msg::Bool::ConstSharedPtr msg) {
        estopped_ = msg->data;
        if (estopped_) {
          pause_ownership_.set(PauseOwner::emergency_stop);
          record_event("EMERGENCY_STOP", CleaningEvent::WARNING, "Emergency stop asserted");
        }
        if (estopped_ && task_ &&
          (state() == TaskState::running || state() == TaskState::recovering))
        {
          active_pub_->publish(std_msgs::msg::Bool{});
          transition_to(TaskState::paused, "emergency stop asserted");
          stop_recovery();
          nav_.cancel();
          persist();
        }
      });
    if (use_planner_) {
      plan_ = create_client<Plan>("cleaning/plan_coverage");
      begin_ = create_client<Begin>("cleaning/begin_coverage");
      coverage_sub_ = create_subscription<Coverage>(
        "cleaning/coverage_status", latched, [this](Coverage::ConstSharedPtr update) {
          if (task_ && localization_healthy_ && update->task_id == current_.task_id) {
            coverage_grid_ = update->covered;
            current_.covered = update->covered.data;
            current_.coverage = update->coverage;
            current_.distance = update->path_length_m;
          }
        });
      if (defer_blocked_sweep_goals_ || adjust_blocked_gap_goals_) {
        costmap_sub_ = create_subscription<Grid>("global_costmap/costmap", latched,
          [this](Grid::ConstSharedPtr costmap) {
            if (WaypointGuard::has_grid_geometry(*costmap)) {
              costmap_ = std::move(costmap);
            }
          });
        local_costmap_sub_ = create_subscription<Grid>("local_costmap/costmap", latched,
          [this](Grid::ConstSharedPtr costmap) {
            if (WaypointGuard::has_grid_geometry(*costmap)) {
              local_costmap_ = std::move(costmap);
            }
          });
      }
    }
    state_pub_ = create_publisher<std_msgs::msg::String>("cleaning/state", latched);
    progress_pub_ = create_publisher<std_msgs::msg::Float32>("cleaning/progress", latched);
    goal_pub_ = create_publisher<Pose>("cleaning/current_goal", latched);
    path_pub_ = create_publisher<nav_msgs::msg::Path>("cleaning/path", latched);
    event_pub_ = create_publisher<CleaningEvent>(
      "cleaning/events", rclcpp::QoS(50).reliable().transient_local());
    event_list_ = create_service<ListCleaningEvents>(
      "cleaning/list_events", [this](
        ListCleaningEvents::Request::SharedPtr request,
        ListCleaningEvents::Response::SharedPtr response) {
        constexpr std::size_t kDefaultLimit = 50;
        constexpr std::size_t kMaximumLimit = 200;
        const auto requested = request->limit == 0 ? kDefaultLimit :
          static_cast<std::size_t>(request->limit);
        response->events = event_log_.select(
          std::min(requested, kMaximumLimit), request->task_id_filter, request->code_filter);
        response->success = true;
        response->message = "events returned newest first";
      });
    localization_sub_ = create_subscription<LocalizationHealth>(
      "cleaning/localization_health", latched,
      [this](LocalizationHealth::ConstSharedPtr health) {on_localization_health(*health);});
    map_sub_ = create_subscription<nav_msgs::msg::OccupancyGrid>(
      "map", latched, [this](nav_msgs::msg::OccupancyGrid::ConstSharedPtr map) {
        if (map->info.width && map->info.height &&
          map->data.size() == static_cast<std::size_t>(map->info.width) * map->info.height)
        {
          map_id_ = map_identity(*map);
        }
      });
    odom_sub_ = create_subscription<nav_msgs::msg::Odometry>(
      "odom", rclcpp::SensorDataQoS(), [this](nav_msgs::msg::Odometry::ConstSharedPtr odom) {
        const auto & p = odom->pose.pose.position;
        if (!use_planner_ && previous_ && task_ && localization_healthy_ &&
          state() == TaskState::running) {
          const double step = std::hypot(p.x - previous_->x, p.y - previous_->y);
          if (step < kMaximumOdomSampleM) {
            current_.distance += step;
          }
        }
        previous_ = p;
      });
    pause_ = create_service<Trigger>("cleaning/pause", [this](
      Trigger::Request::SharedPtr, Trigger::Response::SharedPtr reply)
      {
        if (!task_ || (state() != TaskState::running && state() != TaskState::recovering)) {
          reply->message = "No running task to pause";
          return;
        }
        pause_ownership_.set(PauseOwner::manual);
        record_event("MANUAL_PAUSE", CleaningEvent::INFO, "Pause requested by operator");
        transition_to(TaskState::paused, "pause requested");
        stop_recovery();
        nav_.cancel();
        reply->success = persist();
        active_pub_->publish(std_msgs::msg::Bool{});
        reply->message = reply->success ? "Paused; navigation cancel requested" : checkpoint_error_;
      });
    resume_ = create_service<Trigger>("cleaning/resume", [this](
      Trigger::Request::SharedPtr, Trigger::Response::SharedPtr reply)
      {
        if (!task_ || state() != TaskState::paused || nav_.busy() || !nav_.ready() || estopped_ ||
          !localization_healthy_) {
          reply->message =
            "Wait for a paused task, healthy localization, and navigation cancel acknowledgment";
          return;
        }
        reply->success = true;
        std_msgs::msg::Bool active;
        active.data = true;
        active_pub_->publish(active);
        pause_ownership_.clear();
        record_event("MANUAL_RESUME", CleaningEvent::INFO, "Resume requested by operator");
        reply->message = "Resuming remaining route from the current pose";
        transition_to(TaskState::running, "resume requested");
      });
    server_ = rclcpp_action::create_server<CleanTask>(
      this, "cleaning/task",
      [this](const rclcpp_action::GoalUUID &, std::shared_ptr<const CleanTask::Goal> goal) {
        if (shutting_down_ || estopped_ || task_ || reserved_ ||
          !TaskCheckpointStore::valid_id(goal->task_id) ||
          !std::isfinite(goal->target_coverage) || goal->target_coverage < 0.0f ||
          goal->target_coverage > 1.0f ||
          (goal->mode != CleanTask::Goal::ALL && goal->mode != CleanTask::Goal::REGIONS) ||
          (goal->mode == CleanTask::Goal::REGIONS && goal->regions.empty()))
        {
          return rclcpp_action::GoalResponse::REJECT;
        }
        reserved_ = true;
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
      },
      [](const std::shared_ptr<TaskHandle>) {return rclcpp_action::CancelResponse::ACCEPT;},
      [this](std::shared_ptr<TaskHandle> handle) {
        reserved_ = false;
        ++generation_;
        task_ = std::move(handle);
        current_ = Checkpoint{};
        current_.task_id = task_->get_goal()->task_id;
        current_.regions = task_->get_goal()->mode == CleanTask::Goal::ALL ?
          (use_planner_ ? std::vector<std::string>{} : names_) : task_->get_goal()->regions;
        coverage_grid_ = nav_msgs::msg::OccupancyGrid{};
        excluded_.clear();
        deferred_gap_goals_.clear();
        coverage_target_ = task_->get_goal()->target_coverage > 0 ?
          task_->get_goal()->target_coverage : 0.90f;
        checkpoint_error_.clear();
        stop_reason_.clear();
        last_failure_.clear();
        attempts_ = 0;
        consecutive_failures_ = 0;
        early_replan_attempted_ = false;
        nav_missing_since_.reset();
        pause_ownership_.clear();
        planning_in_flight_ = false;
        started_ = std::chrono::steady_clock::now();
        transition_to(TaskState::waiting_map, "goal accepted");
        record_event("GOAL_ACCEPTED", CleaningEvent::INFO, "CleanTask goal accepted");
      });
    timer_ = create_wall_timer(100ms, std::bind(&CleaningTaskManager::tick, this));
    publish_state();
  }

  void begin_shutdown()
  {
    shutting_down_ = true;
    stop_recovery();
    if (task_) {
      nav_.cancel();
      if (!current_.path.empty()) {
        persist();
      }
    }
  }

  bool shutting_down_task() const {return static_cast<bool>(task_);}

  void finish_shutdown()
  {
    if (task_) {
      if (task_->is_canceling()) {
        if (state() != TaskState::canceling) {
          transition_to(TaskState::canceling, "shutdown acknowledged cancel request");
        }
        finish(TaskState::canceled, "Task canceled");
      } else {
        finish(TaskState::failed, "Manager stopped; checkpoint preserved");
      }
    }
  }

private:
  TaskState state() const noexcept {return state_machine_.state();}

  void record_event(
    const std::string & code, std::uint8_t severity, const std::string & message,
    bool recoverable = true, std::string_view previous_state = {})
  {
    if (!event_pub_) {
      return;
    }
    CleaningEvent event;
    event.header.stamp = now();
    event.header.frame_id = map_frame_;
    event.task_id = current_.task_id;
    event.severity = severity;
    event.code = code;
    event.state = task_state_name(state());
    event.previous_state = previous_state;
    event.recoverable = recoverable;
    event.message = message;
    event.coverage = current_.coverage;
    event.completed_waypoints = current_.completed;
    event.failed_waypoints = current_.failed;
    event.total_waypoints = current_.total;
    event_pub_->publish(event_log_.append(std::move(event)));
  }

  void on_localization_health(const LocalizationHealth & health)
  {
    const bool first = !localization_seen_;
    const bool was_healthy = localization_healthy_;
    const auto previous_health_state = localization_state_;
    localization_seen_ = true;
    localization_state_ = health.state;
    localization_healthy_ = health.healthy;
    localization_reason_ = health.reason;

    if (first) {
      if (health.healthy) {
        record_event("LOCALIZATION_READY", CleaningEvent::INFO, health.reason);
      } else if (health.state == LocalizationHealth::LOST) {
        record_event("LOCALIZATION_LOST", CleaningEvent::WARNING, health.reason);
      }
    } else if (health.state != previous_health_state) {
      if (health.state == LocalizationHealth::LOST) {
        record_event("LOCALIZATION_LOST", CleaningEvent::WARNING, health.reason);
      } else if (health.healthy && !was_healthy) {
        record_event("LOCALIZATION_RECOVERED", CleaningEvent::INFO, health.reason);
      } else if (health.state == LocalizationHealth::DEGRADED) {
        record_event("LOCALIZATION_DEGRADED", CleaningEvent::WARNING, health.reason);
      }
    }

    if (health.state == LocalizationHealth::LOST) {
      previous_.reset();
    }

    if (!health.healthy && health.state == LocalizationHealth::LOST && task_ &&
      (state() == TaskState::planning || state() == TaskState::running ||
      state() == TaskState::recovering))
    {
      const auto interrupted_state = state();
      pause_ownership_.set(PauseOwner::localization);
      active_pub_->publish(std_msgs::msg::Bool{});
      transition_to(TaskState::paused, "localization lost");
      stop_recovery();
      if (interrupted_state == TaskState::running || interrupted_state == TaskState::recovering) {
        nav_.cancel();
      }
      persist();
      record_event(
        "LOCALIZATION_PAUSED_TASK", CleaningEvent::WARNING,
        interrupted_state == TaskState::planning ?
        "Task paused while planning; route will be saved but not executed: " + health.reason :
        "Task paused and navigation cancel requested: " + health.reason);
      return;
    }

    if (health.healthy && !was_healthy &&
      pause_ownership_.localization_owned() && task_ && state() == TaskState::paused)
    {
      pause_ownership_.localization_recovered();
    }
  }

  void publish_state()
  {
    std_msgs::msg::String msg;
    msg.data = task_state_name(state());
    state_pub_->publish(msg);
    RCLCPP_INFO(get_logger(), "task=%s state=%s completed=%zu next=%zu/%zu",
      current_.task_id.c_str(), msg.data.c_str(), current_.completed, current_.next,
      current_.path.size());
  }

  bool transition_to(TaskState next, std::string_view trigger)
  {
    const auto previous = state();
    if (!state_machine_.transition(next)) {
      RCLCPP_ERROR(get_logger(), "Illegal task transition %s -> %s (%.*s)",
        task_state_name(previous).data(), task_state_name(next).data(),
        static_cast<int>(trigger.size()), trigger.data());
      record_event(
        "ILLEGAL_STATE_TRANSITION", CleaningEvent::ERROR,
        std::string(task_state_name(previous)) + " -> " + std::string(task_state_name(next)) +
        ": " + std::string(trigger), false, task_state_name(previous));
      return false;
    }
    RCLCPP_DEBUG(get_logger(), "Task transition %s -> %s (%.*s)",
      task_state_name(previous).data(), task_state_name(next).data(),
      static_cast<int>(trigger.size()), trigger.data());
    publish_state();
    record_event(
      "STATE_TRANSITION", CleaningEvent::INFO, std::string(trigger), true,
      task_state_name(previous));
    return true;
  }

  bool persist()
  {
    try {
      checkpoints_.save(current_);
      return true;
    } catch (const std::exception & e) {
      checkpoint_error_ = std::string("Checkpoint failed: ") + e.what();
      RCLCPP_ERROR(get_logger(), "%s", checkpoint_error_.c_str());
      record_event("CHECKPOINT_ERROR", CleaningEvent::ERROR, checkpoint_error_, false);
      return false;
    }
  }

  std::optional<Pose> position()
  {
    try {
      const auto transform = tf_.lookupTransform(map_frame_, base_frame_, tf2::TimePointZero);
      Pose pose;
      pose.header = transform.header;
      pose.pose.position.x = transform.transform.translation.x;
      pose.pose.position.y = transform.transform.translation.y;
      pose.pose.orientation = transform.transform.rotation;
      return pose;
    } catch (const tf2::TransformException &) {
      return std::nullopt;
    }
  }

  void prepare()
  {
    transition_to(TaskState::planning, "dependencies ready");
    plan_deadline_ = std::chrono::steady_clock::now() + planning_timeout_;
    try {
      if (task_->get_goal()->resume_checkpoint) {
        auto stored = checkpoints_.load(current_.task_id);
        if (!stored || stored->map_id != map_id_ || stored->regions != current_.regions) {
          finish(TaskState::failed, "Checkpoint missing or map/regions changed");
          return;
        }
        current_ = std::move(*stored);
      } else {
        current_.map_id = map_id_;
      }
      if (use_planner_) {
        auto request = std::make_shared<Begin::Request>();
        request->task_id = current_.task_id;
        request->regions = current_.regions;
        request->start = *position();
        request->restored_grid = current_.covered;
        request->restored_distance_m = current_.distance;
        const auto generation = generation_;
        planning_in_flight_ = true;
        begin_->async_send_request(request, [this, generation](rclcpp::Client<Begin>::SharedFuture future) {
            if (!planning(generation)) {
              return;
            }
            planning_in_flight_ = false;
            const auto response = future.get();
            if (!response->success) {
              finish(TaskState::failed, response->reason);
            } else if (current_.path.empty()) {
              request_plan(false);
            } else {
              start_route();
            }
          });
        return;
      }
      if (!task_->get_goal()->resume_checkpoint) {
        for (const auto & region : current_.regions) {
          const auto route = routes_.find(region);
          if (route == routes_.end()) {
            finish(TaskState::failed, "Unknown region: " + region);
            return;
          }
          current_.path.insert(current_.path.end(), route->second.begin(), route->second.end());
        }
        current_.total = current_.path.size();
      }
    } catch (const std::exception & e) {
      finish(TaskState::failed, e.what());
      return;
    }
    start_route();
  }

  bool planning(std::uint64_t generation) const
  {
    const bool accepts_result = state() == TaskState::planning ||
      (state() == TaskState::paused && pause_ownership_.localization_owned() && planning_in_flight_);
    return task_ && generation_ == generation && accepts_result && !task_->is_canceling();
  }

  void request_plan(bool gap, bool ignore_failure_exclusions = false)
  {
    const auto pose = position();
    record_event(gap ? "GAP_PLAN_REQUESTED" : "SWEEP_PLAN_REQUESTED", CleaningEvent::INFO,
      gap ? "Coverage gap-fill plan requested" : "Initial coverage plan requested");
    if (!pose || !plan_->service_is_ready()) {
      finish(TaskState::failed, "Planner or map-frame pose unavailable");
      return;
    }
    if (state() != TaskState::paused) {
      transition_to(TaskState::planning, gap ? "gap plan requested" : "sweep plan requested");
    }
    plan_deadline_ = std::chrono::steady_clock::now() + planning_timeout_;
    planning_in_flight_ = true;
    PlanningRequestContext context;
    context.regions = current_.regions;
    context.start = *pose;
    context.gap_fill = gap;
    context.target_coverage = coverage_target_;
    context.distance_traveled_m = current_.distance;
    context.covered = coverage_grid_;
    context.failure_exclusions = excluded_;
    context.deferred_gap_goals = deferred_gap_goals_;
    context.current_path_size = current_.path.size();
    context.ignore_failure_exclusions = ignore_failure_exclusions;
    auto request = std::make_shared<Plan::Request>(planning_requests_.build(context));
    if (request->distance_budget_m > 0.0) {
      RCLCPP_INFO(get_logger(), "Remaining gap distance budget %.2f m", request->distance_budget_m);
    }
    if (gap && !deferred_gap_goals_.empty() && deferred_gap_goals_.size() == current_.path.size()) {
      // An entire pass was rejected before motion. Ask for an alternative
      // once, without recording the live obstacle as a permanent failure.
      RCLCPP_WARN(get_logger(), "Replanning around %zu deferred gap goals after no motion",
        deferred_gap_goals_.size());
    }
    deferred_gap_goals_.clear();
    const auto generation = generation_;
    plan_->async_send_request(request,
      [this, generation, gap, ignore_failure_exclusions](
        rclcpp::Client<Plan>::SharedFuture future) {
        if (!planning(generation)) {
          return;
        }
        planning_in_flight_ = false;
        const auto response = future.get();
        if (!response->success || response->path.poses.empty()) {
          if (should_retry_gap_plan_without_failure_exclusions(
              gap, ignore_failure_exclusions, !excluded_.empty()))
          {
            RCLCPP_WARN(get_logger(),
              "Gap replan found no route with %zu failure exclusions; retrying without them",
              excluded_.size());
            request_plan(gap, true);
            return;
          }
          auto reason = response->reason.empty() ? std::string("Planner returned no route") :
            response->reason;
          if (gap && ignore_failure_exclusions) {
            reason = "No coverage route after retry without failed-waypoint exclusions: " + reason;
          }
          record_event("PLANNING_FAILED", CleaningEvent::ERROR, reason, false);
          finish(TaskState::failed, reason);
          return;
        }
        current_.path = response->path.poses;
        current_.next = 0;
        current_.total += current_.path.size();
        if (gap) {
          ++current_.pass;
          consecutive_failures_ = 0;
        }
        record_event(gap ? "GAP_PLAN_READY" : "SWEEP_PLAN_READY", CleaningEvent::INFO,
          "Planner returned " + std::to_string(current_.path.size()) + " waypoints");
        start_route();
      });
  }

  void start_route()
  {
    if (current_.path.empty()) {
      finish(TaskState::failed, "No path for requested regions");
      return;
    }
    nav_msgs::msg::Path path;
    path.header.frame_id = map_frame_;
    path.header.stamp = now();
    path.poses = current_.path;
    path_pub_->publish(path);
    if (!persist()) {
      finish(TaskState::failed, checkpoint_error_);
      return;
    }
    if (!localization_healthy_) {
      pause_ownership_.set(PauseOwner::localization);
      active_pub_->publish(std_msgs::msg::Bool{});
      if (state() != TaskState::paused) {
        transition_to(TaskState::paused, "route ready while localization unhealthy");
      }
      record_event(
        "LOCALIZATION_HELD_ROUTE", CleaningEvent::WARNING,
        "Route saved but not started: " + localization_reason_);
      return;
    }
    const bool resuming_after_localization =
      state() == TaskState::paused && pause_ownership_.localization_owned();
    pause_ownership_.clear();
    std_msgs::msg::Bool active;
    active.data = true;
    active_pub_->publish(active);
    if (resuming_after_localization) {
      record_event("LOCALIZATION_AUTO_RESUME", CleaningEvent::INFO,
        "Localization stable; starting the saved route");
    }
    transition_to(TaskState::running, "route ready");
  }

  void feedback()
  {
    auto update = std::make_shared<CleanTask::Feedback>();
    update->state = task_state_name(state());
    update->coverage = current_.coverage;
    update->completed_waypoints = current_.completed;
    update->total_waypoints = current_.total;
    if (current_.next < current_.path.size()) {
      update->current_goal = current_.path[current_.next];
    }
    task_->publish_feedback(update);
    std_msgs::msg::Float32 progress;
    progress.data = update->coverage;
    progress_pub_->publish(progress);
  }

  void skip_covered_waypoints()
  {
    if (!use_planner_ || !WaypointGuard::has_grid_geometry(coverage_grid_)) {
      return;
    }
    // Gap planning scores the whole connector. Its endpoint can be covered
    // while the route to it still cleans missing floor.
    if (defer_blocked_sweep_goals_ && current_.pass > 0) {
      return;
    }
    const auto & info = coverage_grid_.info;
    const double radius = cleaning_radius_ / info.resolution;
    const int cells = static_cast<int>(std::ceil(radius));
    const auto before = current_.next;
    while (current_.next < current_.path.size()) {
      // A covered turn can still be needed to keep the next connection short
      // and drivable. In the optimized sweep skip only redundant line points.
      if (defer_blocked_sweep_goals_ && current_.pass == 0 &&
        !WaypointGuard::is_between_on_line(current_.path, current_.next))
      {
        break;
      }
      const auto & point = current_.path[current_.next].pose.position;
      const auto & origin = coverage_grid_.info.origin;
      const auto & q = origin.orientation;
      const double yaw = std::atan2(2 * (q.w * q.z + q.x * q.y),
          1 - 2 * (q.y * q.y + q.z * q.z));
      const double map_x = point.x - origin.position.x;
      const double map_y = point.y - origin.position.y;
      const int x = static_cast<int>(std::floor(
          (std::cos(yaw) * map_x + std::sin(yaw) * map_y) / info.resolution));
      const int y = static_cast<int>(std::floor(
          (-std::sin(yaw) * map_x + std::cos(yaw) * map_y) / info.resolution));
      int possible = 0;
      int covered = 0;
      for (int dy = -cells; dy <= cells; ++dy) {
        for (int dx = -cells; dx <= cells; ++dx) {
          const int nx = x + dx;
          const int ny = y + dy;
          if (dx * dx + dy * dy <= radius * radius && nx >= 0 && ny >= 0 &&
            nx < static_cast<int>(info.width) && ny < static_cast<int>(info.height))
          {
            const auto value = coverage_grid_.data[ny * info.width + nx];
            possible += value >= 0;
            covered += value == 100;
          }
        }
      }
      if (possible == 0 || covered < possible *
        (current_.pass == 0 ? kCoveredSweepSkipRatio : 1.0))
      {
        break;
      }
      ++current_.next;
      attempts_ = 0;
    }
    if (current_.next != before) {
      RCLCPP_DEBUG(get_logger(), "Skipped %zu covered waypoints", current_.next - before);
      persist();
    }
  }

  std::optional<Pose> adjust_blocked_waypoints()
  {
    const bool gap = current_.pass > 0;
    if (!costmap_ || (gap ? !adjust_blocked_gap_goals_ : !defer_blocked_sweep_goals_)) {
      return std::nullopt;
    }
    const auto age = now() - rclcpp::Time(costmap_->header.stamp, get_clock()->get_clock_type());
    const auto max_clock_skew = rclcpp::Duration::from_seconds(-kMaximumFutureClockSkewS);
    const auto max_costmap_age = rclcpp::Duration::from_seconds(kMaximumCostmapAgeS);
    if (age < max_clock_skew || age > max_costmap_age) {
      return std::nullopt;
    }
    std::optional<geometry_msgs::msg::Transform> map_to_local;
    if (local_costmap_) {
      const auto local_age = now() - rclcpp::Time(
        local_costmap_->header.stamp, get_clock()->get_clock_type());
      if (local_age >= max_clock_skew && local_age <= max_costmap_age) {
        try {
          map_to_local = tf_.lookupTransform(local_costmap_->header.frame_id,
              costmap_->header.frame_id, tf2::TimePointZero).transform;
        } catch (const tf2::TransformException &) {
          // Retain the global costmap check while the local transform is absent.
        }
      }
    }
    const PointCost raw_point_cost = [&](const geometry_msgs::msg::Point & point) {
        const int global = WaypointGuard::cost_at(*costmap_, point);
        if (!map_to_local) {
          return global;
        }
        const auto & q = map_to_local->rotation;
        const double yaw = std::atan2(2 * (q.w * q.z + q.x * q.y),
            1 - 2 * (q.y * q.y + q.z * q.z));
        auto local = point;
        local.x = map_to_local->translation.x + std::cos(yaw) * point.x - std::sin(yaw) * point.y;
        local.y = map_to_local->translation.y + std::sin(yaw) * point.x + std::cos(yaw) * point.y;
        return std::max(global, WaypointGuard::cost_at(*local_costmap_, local));
      };
    const PointCost turn_point_cost = [&](const geometry_msgs::msg::Point & point) {
        return waypoint_guard_.turn_clearance_cost(raw_point_cost, point);
      };
    const double resolution = map_to_local ?
      std::min(costmap_->info.resolution, local_costmap_->info.resolution) : costmap_->info.resolution;
    const auto before = current_.next;
    std::optional<Pose> adjusted;
    const auto from = position();
    while (current_.next < current_.path.size()) {
      const auto & goal = current_.path[current_.next];
      if (goal.header.frame_id != costmap_->header.frame_id) {
        break;
      }
      const bool short_connector = from && map_to_local &&
        from->header.frame_id == goal.header.frame_id &&
        std::hypot(goal.pose.position.x - from->pose.position.x,
        goal.pose.position.y - from->pose.position.y) <=
        waypoint_guard_.config().short_connector_guard_m;
      const auto & goal_cost = gap && from &&
        WaypointGuard::is_sharp_turn(*from, current_.path, current_.next) ?
        turn_point_cost : raw_point_cost;
      if (goal_cost(goal.pose.position) < kNav2InscribedCost && (!short_connector ||
        WaypointGuard::clear_connector(resolution, raw_point_cost, *from, goal, true)))
      {
        break;
      }
      if (from) {
        adjusted = waypoint_guard_.nearby_clear_goal(
          *costmap_, resolution, goal_cost, raw_point_cost, *from, goal);
        if (adjusted) {
          RCLCPP_INFO(get_logger(), "Adjusted %s waypoint %zu around live obstacle",
            gap ? "gap" : "sweep", current_.next);
          break;
        }
      }
      // Nav2 publishes inscribed and lethal obstacle costs as 99 and 100.
      // Leave these targets available to later passes if the obstacle moves.
      if (gap) {
        deferred_gap_goals_.push_back(goal.pose.position);
      }
      ++current_.next;
      ++current_.failed;
      attempts_ = 0;
    }
    if (current_.next != before) {
      RCLCPP_INFO(get_logger(), "Deferred %zu %s waypoints blocked by live costmap",
        current_.next - before, gap ? "gap" : "sweep");
      persist();
    }
    return adjusted;
  }

  void tick()
  {
    nav_.poll(timeout_, current_.pass > 0 ? gap_progress_timeout_ : progress_timeout_);
    if (!shutting_down_) {
      heartbeat_->publish(std_msgs::msg::Empty{});
    }
    if (!task_) {
      return;
    }
    if (shutting_down_) {
      if (!nav_.busy()) {
        finish_shutdown();
      }
      return;
    }
    if (task_->is_canceling()) {
      if (state() != TaskState::canceling) {
        pause_ownership_.set(PauseOwner::cancel);
        planning_in_flight_ = false;
        active_pub_->publish(std_msgs::msg::Bool{});
        record_event("CANCEL_REQUESTED", CleaningEvent::INFO, "CleanTask cancel requested");
        transition_to(TaskState::canceling, "Action cancel requested");
        stop_recovery();
      }
      if (nav_.busy()) {
        nav_.cancel();
      } else {
        finish(TaskState::canceled, stop_reason_.empty() ? "Task canceled" : stop_reason_);
      }
      return;
    }
    if (!checkpoint_error_.empty() ||
      (!current_.map_id.empty() && current_.map_id != map_id_))
    {
      if (nav_.busy()) {
        nav_.cancel();
      } else {
        finish(TaskState::failed,
          checkpoint_error_.empty() ? "Map changed during task" : checkpoint_error_);
      }
      return;
    }
    feedback();
    if (state() == TaskState::waiting_map) {
      if (localization_healthy_ && !map_id_.empty() && nav_.ready() &&
        (!use_planner_ || (begin_->service_is_ready() && plan_->service_is_ready() && position())))
      {
        prepare();
      } else {
        RCLCPP_INFO_THROTTLE(get_logger(), *get_clock(), 5000,
          "Waiting: localization=%d map=%d nav=%d planner=%d tracker=%d tf=%d",
          localization_healthy_,
          !map_id_.empty(), nav_.ready(), use_planner_ && plan_->service_is_ready(),
          use_planner_ && begin_->service_is_ready(), static_cast<bool>(position()));
        if (std::chrono::steady_clock::now() - started_ > startup_timeout_) {
          finish(TaskState::failed, "Localization, map, Nav2, planner, tracker, or map-frame pose unavailable");
        }
      }
      return;
    }
    if (state() == TaskState::planning) {
      if (std::chrono::steady_clock::now() > plan_deadline_) {
        planning_in_flight_ = false;
        finish(TaskState::failed, "Coverage planning timed out");
      }
      return;
    }
    if (state() == TaskState::stopping) {
      if (!nav_.busy()) {
        finish(TaskState::failed, stop_reason_);
      }
      return;
    }
    if (state() == TaskState::paused) {
      if (planning_in_flight_) {
        if (std::chrono::steady_clock::now() > plan_deadline_) {
          planning_in_flight_ = false;
          finish(TaskState::failed, "Coverage planning timed out while localization was unavailable");
        }
        return;
      }
      if (pause_ownership_.should_auto_resume(
          true, localization_healthy_, planning_in_flight_, !nav_.busy(), nav_.ready(), estopped_))
      {
        pause_ownership_.clear();
        std_msgs::msg::Bool active;
        active.data = true;
        active_pub_->publish(active);
        record_event("LOCALIZATION_AUTO_RESUME", CleaningEvent::INFO,
          "Localization stable; resuming remaining route");
        transition_to(TaskState::running, "localization recovered");
      }
      return;
    }
    if (!nav_.ready()) {
      const auto now = std::chrono::steady_clock::now();
      if (!nav_missing_since_) {
        nav_missing_since_ = now;
      }
      if (now - *nav_missing_since_ > nav_unavailable_grace_) {
        stop_reason_ = "Nav2 stopped during the cleaning task";
        transition_to(TaskState::stopping, "Nav2 unavailable beyond grace period");
        stop_recovery();
        nav_.cancel();
        persist();
      }
      return;
    }
    nav_missing_since_.reset();
    if (nav_.busy()) {
      return;
    }
    if (state() == TaskState::recovering) {
      if (recovery_) {
        run_recovery();
        return;
      }
      if (std::chrono::steady_clock::now() < retry_after_) {
        return;
      }
      transition_to(TaskState::running, "recovery delay completed");
    }
    if (use_planner_) {
      const auto decision = decide_completion(
        current_.coverage, coverage_target_, coverage_completion_margin_, false);
      if (decision.finish) {
        finish(decision.success ? TaskState::succeeded : TaskState::failed, decision.reason);
        return;
      }
    }
    if (use_planner_ && current_.pass > 0 && gap_failure_replan_threshold_ > 0 &&
      consecutive_failures_ >= gap_failure_replan_threshold_ && current_.next < current_.path.size())
    {
      if (current_.pass < static_cast<std::size_t>(std::max(0, max_gap_passes_))) {
        RCLCPP_WARN(get_logger(), "Replanning gaps after consecutive unreachable goals");
        request_plan(true);
      } else {
        finish_gap_budget_exhausted("Gap-fill route stalled after the final replanning attempt");
      }
      return;
    }
    if (use_planner_ && early_gap_replan_ && current_.regions.empty() &&
      current_.pass == 0 && max_gap_passes_ > 0 &&
      !early_replan_attempted_ && consecutive_failures_ >= 2 && current_.next < current_.path.size())
    {
      early_replan_attempted_ = true;
      RCLCPP_WARN(get_logger(), "Replanning unfinished floor after consecutive unreachable goals");
      request_plan(true);
      return;
    }
    skip_covered_waypoints();
    auto adjusted = adjust_blocked_waypoints();
    if (!checkpoint_error_.empty()) {
      finish(TaskState::failed, checkpoint_error_);
      return;
    }
    if (current_.next >= current_.path.size()) {
      if (use_planner_) {
        if (current_.pass < static_cast<std::size_t>(std::max(0, max_gap_passes_))) {
          request_plan(true);
        } else {
          finish_gap_budget_exhausted();
        }
        return;
      }
      finish(current_.failed ? TaskState::failed : TaskState::succeeded,
        current_.failed ? "Route finished with unreachable goals: " + last_failure_ :
        "Route completed");
      return;
    }
    auto pose = adjusted.value_or(current_.path[current_.next]);
    pose.header.stamp = now();
    goal_pub_->publish(pose);
    const auto generation = generation_;
    nav_.send(pose, [this, generation](NavigationExecutor::Status status) {
        if (!task_ || generation != generation_ || shutting_down_) {
          return;
        }
        if (status == NavigationExecutor::Status::cancel_unconfirmed) {
          stop_reason_ = "Nav2 did not acknowledge cancel; motion authority revoked";
          stop_recovery();
          transition_to(TaskState::stopping, "navigation cancel was not acknowledged");
          persist();
          return;
        }
        if (task_->is_canceling() || state() == TaskState::paused ||
          state() == TaskState::stopping ||
          recovery_ || !checkpoint_error_.empty())
        {
          return;
        }
        on_navigation_result(status);
      }, current_.pass > 0 ? gap_behavior_tree_ : std::string{});
  }

  void run_recovery()
  {
    if (!recovery_start_) {
      recovery_start_ = std::chrono::steady_clock::now();
    }
    const auto elapsed = std::chrono::steady_clock::now() - *recovery_start_;
    if (!RecoveryExecutor::done(elapsed)) {
      recovery_cmd_->publish(recovery_->command(elapsed));
      return;
    }
    stop_recovery();
    RCLCPP_INFO(get_logger(), "Recovery complete, contact=%s", contact_.c_str());
    on_navigation_result(NavigationExecutor::Status::failed);
    if (state() == TaskState::recovering && attempts_ == 0) {
      transition_to(TaskState::running, "collision recovery completed");
    }
  }

  void finish_gap_budget_exhausted(const std::string & context = {})
  {
    const auto decision = decide_completion(
      current_.coverage, coverage_target_, coverage_completion_margin_, true);
    std::string reason = decision.reason;
    if (current_.failed > 0) {
      reason += "; skipped goals after navigation failures=" + std::to_string(current_.failed);
      if (!last_failure_.empty()) {
        reason += ", last failure: " + last_failure_;
      }
    }
    if (!context.empty()) {
      reason = context + "; " + reason;
    }
    finish(decision.success ? TaskState::succeeded : TaskState::failed, reason);
  }

  void stop_recovery()
  {
    if (recovery_) {
      recovery_cmd_->publish(geometry_msgs::msg::Twist{});
      recovery_.reset();
      recovery_start_.reset();
    }
  }

  void on_navigation_result(NavigationExecutor::Status status)
  {
    using Status = NavigationExecutor::Status;
    if (status == Status::succeeded) {
      ++current_.completed;
      ++current_.next;
      attempts_ = 0;
      consecutive_failures_ = 0;
      persist();
      return;
    }
    switch (status) {
      case Status::rejected: last_failure_ = "goal rejected"; break;
      case Status::timed_out: last_failure_ = "goal timed out"; break;
      case Status::no_progress: last_failure_ = "no progress"; break;
      case Status::unavailable: last_failure_ = "Nav2 unavailable"; break;
      case Status::canceled: last_failure_ = "goal canceled"; break;
      default: last_failure_ = "navigation failed"; break;
    }
    record_event("NAVIGATION_FAILED", CleaningEvent::WARNING, last_failure_);
    RCLCPP_WARN(get_logger(), "waypoint %zu: %s", current_.next, last_failure_.c_str());
    const auto allowed_retries = current_.pass > 0 ? gap_retries_ : retries_;
    if (attempts_++ >= allowed_retries) {
      record_event("NAVIGATION_GOAL_ABANDONED", CleaningEvent::WARNING,
        "Waypoint excluded after retries: " + last_failure_);
      ++current_.failed;
      ++consecutive_failures_;
      excluded_.push_back(current_.path[current_.next].pose.position);
      ++current_.next;
      attempts_ = 0;
      persist();
    } else {
      record_event("NAVIGATION_RETRY", CleaningEvent::WARNING, last_failure_);
      retry_after_ = std::chrono::steady_clock::now() + 1s;
      transition_to(TaskState::recovering, "navigation retry scheduled");
    }
  }

  void finish(TaskState terminal_state, const std::string & reason)
  {
    stop_recovery();
    if (!is_terminal(terminal_state)) {
      RCLCPP_ERROR(get_logger(), "finish called with non-terminal state %s",
        task_state_name(terminal_state).data());
      terminal_state = TaskState::failed;
    }
    if (!transition_to(terminal_state, reason)) {
      return;
    }
    active_pub_->publish(std_msgs::msg::Bool{});
    pause_ownership_.clear();
    planning_in_flight_ = false;
    const char * terminal_code = terminal_state == TaskState::succeeded ? "TASK_SUCCEEDED" :
      (terminal_state == TaskState::canceled ? "TASK_CANCELED" : "TASK_FAILED");
    const auto severity = terminal_state == TaskState::failed ? CleaningEvent::ERROR :
      CleaningEvent::INFO;
    record_event(terminal_code, severity, reason, terminal_state != TaskState::failed);
    auto result = std::make_shared<CleanTask::Result>();
    result->success = terminal_state == TaskState::succeeded;
    result->reason = reason;
    result->completed_waypoints = current_.completed;
    result->failed_waypoints = current_.failed;
    result->path_length_m = current_.distance;
    result->coverage = current_.coverage;
    if (terminal_state == TaskState::canceled || terminal_state == TaskState::succeeded) {
      try {
        checkpoints_.remove(current_.task_id);
      } catch (const std::exception & e) {
        RCLCPP_WARN(get_logger(), "Cannot remove finished checkpoint: %s", e.what());
      }
    }
    if (terminal_state == TaskState::succeeded) {
      task_->succeed(result);
    } else if (terminal_state == TaskState::canceled) {
      task_->canceled(result);
    } else {
      task_->abort(result);
    }
    task_.reset();
  }

  NavigationExecutor nav_;
  TaskCheckpointStore checkpoints_;
  const std::chrono::seconds timeout_;
  const std::chrono::seconds progress_timeout_;
  const std::chrono::seconds gap_progress_timeout_;
  const std::chrono::seconds planning_timeout_;
  const std::chrono::seconds startup_timeout_;
  const std::chrono::seconds nav_unavailable_grace_;
  const int retries_;
  const int gap_retries_;
  const bool use_planner_;
  const bool defer_blocked_sweep_goals_;
  const bool adjust_blocked_gap_goals_;
  const bool early_gap_replan_;
  const int max_gap_passes_;
  const int gap_failure_replan_threshold_;
  const int event_log_capacity_;
  CleaningEventLog event_log_;
  const double cleaning_radius_;
  const std::string map_frame_;
  const std::string base_frame_;
  const double coverage_completion_margin_;
  const double target_path_efficiency_;
  const double minimum_gap_distance_budget_m_;
  const std::string gap_behavior_tree_;
  const PlanningRequestBuilder planning_requests_;
  const WaypointGuard waypoint_guard_;
  tf2_ros::Buffer tf_;
  tf2_ros::TransformListener listener_;
  float coverage_target_{0.90f};
  nav_msgs::msg::OccupancyGrid coverage_grid_;
  Grid::ConstSharedPtr costmap_;
  Grid::ConstSharedPtr local_costmap_;
  rclcpp::Subscription<Grid>::SharedPtr costmap_sub_;
  rclcpp::Subscription<Grid>::SharedPtr local_costmap_sub_;
  std::vector<geometry_msgs::msg::Point> excluded_;
  std::vector<geometry_msgs::msg::Point> deferred_gap_goals_;
  rclcpp::Client<Plan>::SharedPtr plan_;
  rclcpp::Client<Begin>::SharedPtr begin_;
  rclcpp::Subscription<Coverage>::SharedPtr coverage_sub_;
  std::chrono::steady_clock::time_point plan_deadline_;
  std::vector<std::string> names_;
  std::unordered_map<std::string, std::vector<Pose>> routes_;
  rclcpp_action::Server<CleanTask>::SharedPtr server_;
  std::shared_ptr<TaskHandle> task_;
  Checkpoint current_;
  TaskStateMachine state_machine_;
  std::string map_id_;
  std::string last_failure_;
  std::string checkpoint_error_;
  std::string stop_reason_;
  bool reserved_{false};
  bool shutting_down_{false};
  bool estopped_{false};
  bool localization_seen_{false};
  bool localization_healthy_{false};
  PauseOwnership pause_ownership_;
  bool planning_in_flight_{false};
  std::uint8_t localization_state_{LocalizationHealth::UNKNOWN};
  std::string localization_reason_{"waiting for localization health"};
  std::string contact_{"clear"};
  std::optional<RecoveryExecutor> recovery_;
  std::optional<std::chrono::steady_clock::time_point> recovery_start_;
  rclcpp::Publisher<std_msgs::msg::Empty>::SharedPtr heartbeat_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr active_pub_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr recovery_cmd_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr contact_sub_;
  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr estop_sub_;
  std::uint64_t generation_{0};
  int attempts_{0};
  int consecutive_failures_{0};
  bool early_replan_attempted_{false};
  std::chrono::steady_clock::time_point started_;
  std::chrono::steady_clock::time_point retry_after_;
  std::optional<std::chrono::steady_clock::time_point> nav_missing_since_;
  std::optional<geometry_msgs::msg::Point> previous_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr state_pub_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr progress_pub_;
  rclcpp::Publisher<Pose>::SharedPtr goal_pub_;
  rclcpp::Publisher<nav_msgs::msg::Path>::SharedPtr path_pub_;
  rclcpp::Publisher<CleaningEvent>::SharedPtr event_pub_;
  rclcpp::Service<ListCleaningEvents>::SharedPtr event_list_;
  rclcpp::Subscription<LocalizationHealth>::SharedPtr localization_sub_;
  rclcpp::Subscription<nav_msgs::msg::OccupancyGrid>::SharedPtr map_sub_;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;
  rclcpp::Service<Trigger>::SharedPtr pause_;
  rclcpp::Service<Trigger>::SharedPtr resume_;
  rclcpp::TimerBase::SharedPtr timer_;
};
}  // namespace robot_cleaning_manager

namespace
{
volatile std::sig_atomic_t stop_requested = 0;

void handle_signal(int)
{
  stop_requested = 1;
}
}

int main(int argc, char ** argv)
{
  using namespace std::chrono_literals;
  rclcpp::init(argc, argv, rclcpp::InitOptions(), rclcpp::SignalHandlerOptions::None);
  std::signal(SIGINT, handle_signal);
  std::signal(SIGTERM, handle_signal);
  auto manager = std::make_shared<robot_cleaning_manager::CleaningTaskManager>();
  rclcpp::executors::SingleThreadedExecutor executor;
  executor.add_node(manager);
  while (rclcpp::ok() && !stop_requested) {
    executor.spin_once(100ms);
  }
  manager->begin_shutdown();
  const auto deadline = std::chrono::steady_clock::now() + 4s;
  while (manager->shutting_down_task() && std::chrono::steady_clock::now() < deadline) {
    executor.spin_once(100ms);
  }
  manager->finish_shutdown();
  executor.remove_node(manager);
  manager.reset();
  rclcpp::shutdown();
  return 0;
}
