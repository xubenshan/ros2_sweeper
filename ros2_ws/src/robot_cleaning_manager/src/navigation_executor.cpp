// SPDX-License-Identifier: Apache-2.0
#include "robot_cleaning_manager/navigation_executor.hpp"

#include <cmath>
#include <utility>

namespace robot_cleaning_manager
{
namespace
{
constexpr double kMeaningfulRemainingDistanceM = 0.08;
constexpr double kMeaningfulPoseMovementM = 0.12;
constexpr auto kLifecyclePollPeriod = std::chrono::milliseconds(500);
constexpr auto kLifecycleResponseLifetime = std::chrono::seconds(3);
constexpr auto kLifecycleActiveFreshness = std::chrono::seconds(2);
constexpr auto kUnavailableCancelTimeout = std::chrono::seconds(3);
constexpr auto kCancelAcknowledgmentTimeout = std::chrono::seconds(8);
}

bool NavigationProgress::observe(double remaining, const geometry_msgs::msg::PoseStamped & pose)
{
  const bool closer = std::isfinite(remaining) && remaining >= 0.0 &&
    remaining + kMeaningfulRemainingDistanceM < best_remaining_;
  if (closer) {
    best_remaining_ = remaining;
  }
  const auto & point = pose.pose.position;
  if (pose.header.frame_id.empty() || !std::isfinite(point.x) || !std::isfinite(point.y)) {
    return closer;
  }
  if (!anchor_ || anchor_->header.frame_id != pose.header.frame_id) {
    anchor_ = pose;
    return closer;
  }
  const auto & previous = anchor_->pose.position;
  const bool moved = std::hypot(point.x - previous.x, point.y - previous.y) >=
    kMeaningfulPoseMovementM;
  if (moved || closer) {
    anchor_ = pose;
  }
  // A recovery or detour can move the robot while the replanned path grows.
  return closer || moved;
}

NavigationExecutor::NavigationExecutor(rclcpp::Node & node)
: client_(rclcpp_action::create_client<Action>(&node, "navigate_to_pose")),
  lifecycle_(node.create_client<GetState>("bt_navigator/get_state"))
{
}

bool NavigationExecutor::ready() const
{
  return client_->action_server_is_ready() &&
    Clock::now() - last_active_ < kLifecycleActiveFreshness;
}

void NavigationExecutor::send(
  const geometry_msgs::msg::PoseStamped & pose, Completion completion,
  const std::string & behavior_tree)
{
  if (busy_ || !ready()) {
    completion(Status::unavailable);
    return;
  }
  const auto sequence = ++sequence_;
  busy_ = true;
  cancel_requested_ = false;
  cancel_status_ = Status::canceled;
  completion_ = std::move(completion);
  sent_at_ = last_progress_ = Clock::now();
  progress_ = NavigationProgress{};
  Action::Goal request;
  request.pose = pose;
  request.behavior_tree = behavior_tree;
  rclcpp_action::Client<Action>::SendGoalOptions options;
  options.goal_response_callback = [this, sequence](Handle::SharedPtr handle) {
      if (sequence != sequence_ || !busy_) {
        if (handle) {
          try {
            client_->async_cancel_goal(handle);
          } catch (const rclcpp_action::exceptions::UnknownGoalHandleError &) {}
        }
        return;
      }
      if (!handle) {
        finish(cancel_requested_ ? cancel_status_ : Status::rejected);
        return;
      }
      goal_ = std::move(handle);
      if (cancel_requested_) {
        request_cancel();
      }
    };
  options.feedback_callback = [this, sequence](
    Handle::SharedPtr, const std::shared_ptr<const Action::Feedback> feedback)
    {
      if (sequence == sequence_ && busy_ && !cancel_requested_ &&
        progress_.observe(feedback->distance_remaining, feedback->current_pose))
      {
        last_progress_ = Clock::now();
      }
    };
  options.result_callback = [this, sequence](const Handle::WrappedResult & result) {
      if (sequence != sequence_ || !busy_) {
        return;
      }
      if (cancel_requested_) {
        finish(cancel_status_);
      } else if (result.code == rclcpp_action::ResultCode::SUCCEEDED &&
        result.result && result.result->error_code == Action::Result::NONE)
      {
        finish(Status::succeeded);
      } else {
        finish(Status::failed);
      }
    };
  client_->async_send_goal(request, options);
}

void NavigationExecutor::request_cancel()
{
  if (goal_) {
    try {
      client_->async_cancel_goal(goal_);
    } catch (const rclcpp_action::exceptions::UnknownGoalHandleError &) {
      // The result can already be queued on the executor.
    }
  }
}

void NavigationExecutor::cancel()
{
  if (!busy_ || cancel_requested_) {
    return;
  }
  cancel_requested_ = true;
  cancel_at_ = Clock::now();
  request_cancel();
}

void NavigationExecutor::poll(
  std::chrono::seconds timeout, std::chrono::seconds progress_timeout)
{
  const auto now = Clock::now();
  if (now - last_check_ >= kLifecyclePollPeriod) {
    last_check_ = now;
    lifecycle_->prune_requests_older_than(std::chrono::system_clock::now() -
      kLifecycleResponseLifetime);
    if (lifecycle_->service_is_ready()) {
      lifecycle_->async_send_request(std::make_shared<GetState::Request>(),
        [this](rclcpp::Client<GetState>::SharedFuture result) {
          last_active_ = result.get()->current_state.id ==
            lifecycle_msgs::msg::State::PRIMARY_STATE_ACTIVE ? Clock::now() : Clock::time_point{};
        });
    }
  }
  if (!busy_) {
    return;
  }
  if (cancel_requested_) {
    // A server that has disappeared cannot acknowledge cancel. Ignore any
    // result from that generation if it reappears after this timeout.
    if (!ready() && now - cancel_at_ > kUnavailableCancelTimeout) {
      finish(Status::unavailable);
    } else if (now - cancel_at_ > kCancelAcknowledgmentTimeout) {
      finish(Status::cancel_unconfirmed);
    }
    return;
  }
  if (now - sent_at_ >= timeout) {
    cancel_status_ = Status::timed_out;
    cancel();
  } else if (goal_ && now - last_progress_ >= progress_timeout) {
    cancel_status_ = Status::no_progress;
    cancel();
  }
}

void NavigationExecutor::finish(Status status)
{
  ++sequence_;
  busy_ = false;
  goal_.reset();
  auto completion = std::move(completion_);
  completion(status);
}
}  // namespace robot_cleaning_manager
