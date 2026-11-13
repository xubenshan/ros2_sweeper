// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <chrono>
#include <functional>
#include <limits>
#include <memory>
#include <optional>
#include <string>

#include <geometry_msgs/msg/pose_stamped.hpp>
#include <nav2_msgs/action/navigate_to_pose.hpp>
#include <lifecycle_msgs/srv/get_state.hpp>
#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>

namespace robot_cleaning_manager
{
class NavigationProgress
{
public:
  bool observe(double remaining, const geometry_msgs::msg::PoseStamped & pose);

private:
  double best_remaining_{std::numeric_limits<double>::infinity()};
  std::optional<geometry_msgs::msg::PoseStamped> anchor_;
};

class NavigationExecutor
{
public:
  using Action = nav2_msgs::action::NavigateToPose;
  enum class Status {
    succeeded, rejected, failed, canceled, timed_out, no_progress, unavailable, cancel_unconfirmed
  };
  using Completion = std::function<void(Status)>;

  explicit NavigationExecutor(rclcpp::Node & node);
  bool ready() const;
  bool busy() const {return busy_;}
  void send(
    const geometry_msgs::msg::PoseStamped & pose, Completion completion,
    const std::string & behavior_tree = {});
  void cancel();
  void poll(std::chrono::seconds timeout, std::chrono::seconds progress_timeout);

private:
  using Handle = rclcpp_action::ClientGoalHandle<Action>;
  using Clock = std::chrono::steady_clock;
  void request_cancel();
  void finish(Status status);

  using GetState = lifecycle_msgs::srv::GetState;
  rclcpp_action::Client<Action>::SharedPtr client_;
  rclcpp::Client<GetState>::SharedPtr lifecycle_;
  Clock::time_point last_check_;
  Clock::time_point last_active_;
  Handle::SharedPtr goal_;
  Completion completion_;
  std::uint64_t sequence_{0};
  bool busy_{false};
  bool cancel_requested_{false};
  Status cancel_status_{Status::canceled};
  Clock::time_point sent_at_;
  Clock::time_point last_progress_;
  Clock::time_point cancel_at_;
  NavigationProgress progress_;
};
}  // namespace robot_cleaning_manager
