// SPDX-License-Identifier: Apache-2.0
#include "robot_motion_safety/policy.hpp"

#include <array>
#include <chrono>
#include <functional>
#include <stdexcept>

#include <rclcpp/rclcpp.hpp>
#include <ros_gz_interfaces/msg/contacts.hpp>
#include <std_msgs/msg/empty.hpp>
#include <std_msgs/msg/bool.hpp>
#include <std_msgs/msg/string.hpp>
#include <std_srvs/srv/set_bool.hpp>

namespace robot_motion_safety
{
using namespace std::chrono_literals;
using Clock = std::chrono::steady_clock;
using Twist = geometry_msgs::msg::Twist;
using Contacts = ros_gz_interfaces::msg::Contacts;
using SetBool = std_srvs::srv::SetBool;

class CmdVelArbiter : public rclcpp::Node
{
public:
  CmdVelArbiter()
  : Node("cmd_vel_arbiter"),
    linear_limit_(declare_parameter("linear_limit", 0.35)),
    angular_limit_(declare_parameter("angular_limit", 1.8)),
    stale_(declare_parameter("watchdog_ms", 300))
  {
    if (!std::isfinite(linear_limit_) || linear_limit_ <= 0 ||
      !std::isfinite(angular_limit_) || angular_limit_ <= 0 || stale_.count() <= 0)
    {
      throw std::invalid_argument("invalid safety limits");
    }
    const auto latched = rclcpp::QoS(1).transient_local();
    output_ = create_publisher<Twist>("cmd_vel", 10);
    contact_pub_ = create_publisher<std_msgs::msg::String>("motion/contact", latched);
    status_pub_ = create_publisher<std_msgs::msg::String>("motion/source", latched);
    estop_pub_ = create_publisher<std_msgs::msg::Bool>("motion/estop_state", latched);
    const std::array<std::string, 4> names = {
      "motion/nav", "cmd_vel_edge", "cmd_vel_recovery", "cmd_vel_teleop"};
    for (std::size_t i = 0; i < names.size(); ++i) {
      inputs_[i] = create_subscription<Twist>(names[i], 10, [this, i](Twist::ConstSharedPtr msg) {
          slots_[i] = {*msg, Clock::now()};
        });
    }
    state_sub_ = create_subscription<std_msgs::msg::String>(
      "cleaning/state", latched, [this](std_msgs::msg::String::ConstSharedPtr msg) {
        state_ = msg->data;
        if (state_ == "PAUSED" || state_ == "CANCELING") {
          manual_ = Source::none;
        }
      });
    heartbeat_sub_ = create_subscription<std_msgs::msg::Empty>(
      "cleaning/heartbeat", 10, [this](std_msgs::msg::Empty::ConstSharedPtr) {
        heartbeat_ = Clock::now();
      });
    control_sub_ = create_subscription<std_msgs::msg::String>(
      "motion/control", 10, [this](std_msgs::msg::String::ConstSharedPtr msg) {
        if (msg->data == "teleop") {
          manual_ = Source::teleop;
        } else if (msg->data == "edge") {
          manual_ = Source::edge;
        } else if (msg->data == "nav") {
          manual_ = Source::nav;
        } else if (msg->data == "auto") {
          manual_ = Source::none;
        } else {
          RCLCPP_WARN(get_logger(), "Unknown motion control: %s", msg->data.c_str());
        }
      });
    const std::array<std::string, 2> bumper_names = {"bumper_left/contact", "bumper_right/contact"};
    for (std::size_t i = 0; i < bumper_names.size(); ++i) {
      bumpers_[i] = create_subscription<Contacts>(
        bumper_names[i], rclcpp::SensorDataQoS(), [this, i](Contacts::ConstSharedPtr msg) {
          contacts_[i] = msg->contacts.empty() ? Clock::time_point{} : Clock::now();
        });
    }
    estop_service_ = create_service<SetBool>("motion/estop", [this](
        SetBool::Request::SharedPtr request, SetBool::Response::SharedPtr reply)
      {
        estop_ = request->data;
        std_msgs::msg::Bool status;
        status.data = estop_;
        estop_pub_->publish(status);
        manual_ = Source::none;
        clear_inputs();
        output_->publish(Twist{});
        reply->success = true;
        reply->message = estop_ ? "Emergency stop latched" : "Emergency stop released";
      });
    timer_ = create_wall_timer(25ms, std::bind(&CmdVelArbiter::tick, this));
  }

private:
  void clear_inputs()
  {
    for (auto & slot : slots_) {
      slot.stamp = Clock::time_point{};
    }
  }

  void tick()
  {
    const auto now = Clock::now();
    const bool left = now - contacts_[0] < 220ms;
    const bool right = now - contacts_[1] < 220ms;
    const std::string contact = left && right ? "both" : left ? "left" : right ? "right" : "clear";
    if (contact != contact_) {
      std_msgs::msg::String msg;
      msg.data = contact;
      contact_pub_->publish(msg);
      contact_ = contact;
    }
    const bool alive = now - heartbeat_ < 400ms;
    const auto source = authorized(state_, manual_, alive, estop_, left || right);
    if (source != source_) {
      source_ = source;
      clear_inputs();
      std_msgs::msg::String status;
      const std::array<const char *, 5> names = {"none", "nav", "edge", "recovery", "teleop"};
      status.data = names[static_cast<int>(source)];
      status_pub_->publish(status);
      output_->publish(Twist{});
      return;
    }
    Twist output;
    if (source != Source::none) {
      const auto & slot = slots_[static_cast<int>(source) - 1];
      if (now - slot.stamp < stale_) {
        output = guard(slot.command, linear_limit_, angular_limit_, left || right);
      }
    }
    output_->publish(output);
  }

  struct Slot
  {
    Twist command = Twist();
    Clock::time_point stamp{};
  };
  double linear_limit_;
  double angular_limit_;
  std::chrono::milliseconds stale_;
  std::array<Slot, 4> slots_{};
  std::array<Clock::time_point, 2> contacts_{};
  Clock::time_point heartbeat_{};
  Source source_{Source::none};
  Source manual_{Source::none};
  bool estop_{false};
  std::string state_;
  std::string contact_;
  rclcpp::Publisher<Twist>::SharedPtr output_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr contact_pub_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr status_pub_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr estop_pub_;
  std::array<rclcpp::Subscription<Twist>::SharedPtr, 4> inputs_;
  std::array<rclcpp::Subscription<Contacts>::SharedPtr, 2> bumpers_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr state_sub_;
  rclcpp::Subscription<std_msgs::msg::Empty>::SharedPtr heartbeat_sub_;
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr control_sub_;
  rclcpp::Service<SetBool>::SharedPtr estop_service_;
  rclcpp::TimerBase::SharedPtr timer_;
};
}  // namespace robot_motion_safety

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<robot_motion_safety::CmdVelArbiter>());
  rclcpp::shutdown();
  return 0;
}
