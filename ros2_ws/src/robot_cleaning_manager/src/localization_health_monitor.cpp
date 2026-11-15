// SPDX-License-Identifier: Apache-2.0
#include "robot_cleaning_manager/localization_health.hpp"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>

#include <geometry_msgs/msg/pose_with_covariance_stamped.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <rclcpp/rclcpp.hpp>
#include <robot_cleaning_interfaces/msg/localization_health.hpp>
#include <tf2/exceptions.hpp>
#include <tf2_ros/buffer.hpp>
#include <tf2_ros/transform_listener.hpp>

namespace robot_cleaning_manager
{
using namespace std::chrono_literals;
using Health = robot_cleaning_interfaces::msg::LocalizationHealth;
using PoseWithCovariance = geometry_msgs::msg::PoseWithCovarianceStamped;

class LocalizationHealthMonitor : public rclcpp::Node
{
public:
  LocalizationHealthMonitor()
  : Node("localization_health_monitor"),
    evaluator_(LocalizationHealthConfig{
        declare_parameter("lost_covariance_threshold", 0.50),
        declare_parameter("recovered_covariance_threshold", 0.25),
        std::chrono::milliseconds(static_cast<int>(
            1000.0 * declare_parameter("lost_hold_s", 1.0))),
        std::chrono::milliseconds(static_cast<int>(
            1000.0 * declare_parameter("recovered_hold_s", 2.0)))}),
    covariance_required_(declare_parameter("covariance_required", true)),
    pose_timeout_s_(declare_parameter("pose_timeout_s", 2.0)),
    moving_linear_threshold_(declare_parameter("moving_linear_threshold_mps", 0.02)),
    moving_angular_threshold_(declare_parameter("moving_angular_threshold_rps", 0.05)),
    map_frame_(declare_parameter<std::string>("map_frame", "")),
    base_frame_(declare_parameter<std::string>("base_frame", "")),
    tf_(get_clock()), listener_(tf_, this, false)
  {
    if (map_frame_.empty() || base_frame_.empty() || !std::isfinite(pose_timeout_s_) ||
      pose_timeout_s_ <= 0.0 || !std::isfinite(moving_linear_threshold_) ||
      moving_linear_threshold_ < 0.0 || !std::isfinite(moving_angular_threshold_) ||
      moving_angular_threshold_ < 0.0)
    {
      throw std::invalid_argument("invalid localization monitor parameters");
    }

    const auto health_qos = rclcpp::QoS(1).reliable().transient_local();
    health_pub_ = create_publisher<Health>("cleaning/localization_health", health_qos);
    pose_sub_ = create_subscription<PoseWithCovariance>(
      "amcl_pose", rclcpp::QoS(10).reliable(),
      [this](PoseWithCovariance::ConstSharedPtr msg) {
        const auto & covariance = msg->pose.covariance;
        const auto trace = normalized_xy_covariance(covariance[0], covariance[7]);
        covariance_valid_ = trace.has_value();
        covariance_xy_ = trace.value_or(covariance[0] + covariance[7]);
        pose_received_ = true;
        ++pose_generation_;
        const bool stamped = msg->header.stamp.sec != 0 || msg->header.stamp.nanosec != 0;
        last_pose_stamp_ = stamped ?
          rclcpp::Time(msg->header.stamp, get_clock()->get_clock_type()) : now();
      });
    odom_sub_ = create_subscription<nav_msgs::msg::Odometry>(
      "odom", rclcpp::SensorDataQoS(), [this](nav_msgs::msg::Odometry::ConstSharedPtr msg) {
        const auto & twist = msg->twist.twist;
        moving_ = std::hypot(twist.linear.x, twist.linear.y) > moving_linear_threshold_ ||
          std::abs(twist.angular.z) > moving_angular_threshold_;
      });
    timer_ = create_wall_timer(100ms, std::bind(&LocalizationHealthMonitor::evaluate, this));
  }

private:
  static double age_seconds(const rclcpp::Time & current, const rclcpp::Time & stamp)
  {
    return std::max(0.0, (current - stamp).seconds());
  }

  void evaluate()
  {
    const auto current = now();
    bool transform_available = false;
    double transform_age_s = -1.0;
    std::optional<rclcpp::Time> transform_stamp;
    try {
      const auto transform = tf_.lookupTransform(map_frame_, base_frame_, tf2::TimePointZero);
      transform_available = true;
      const rclcpp::Time stamp(transform.header.stamp, get_clock()->get_clock_type());
      transform_stamp = stamp;
      transform_age_s = age_seconds(current, stamp);
    } catch (const tf2::TransformException &) {
      transform_available = false;
    }

    const double pose_age_s = last_pose_stamp_ ? age_seconds(current, *last_pose_stamp_) : -1.0;
    const double freshness_age_s = covariance_required_ ? pose_age_s : transform_age_s;
    const bool pose_fresh = localization_data_fresh(moving_, freshness_age_s, pose_timeout_s_);
    const bool new_pose_evidence = localization_recovery_evidence(
      pose_generation_ > lost_pose_generation_, pose_age_s, pose_timeout_s_);
    const bool returned_transform_evidence = !lost_transform_stamp_ &&
      localization_recovery_evidence(
        transform_stamp.has_value(), transform_age_s, pose_timeout_s_);
    const bool new_slam_transform = transform_stamp &&
      (!lost_transform_stamp_ || *transform_stamp > *lost_transform_stamp_);
    const bool recovery_evidence = covariance_required_ ?
      (new_pose_evidence || returned_transform_evidence) :
      localization_recovery_evidence(new_slam_transform, transform_age_s, pose_timeout_s_);
    const LocalizationObservation observation{
      covariance_required_, pose_received_, pose_fresh, transform_available,
      covariance_valid_, covariance_xy_, recovery_evidence};
    const auto decision = evaluator_.update(observation, std::chrono::steady_clock::now());

    if (decision.changed && decision.state == LocalizationState::lost) {
      lost_pose_generation_ = pose_generation_;
      lost_transform_stamp_ = transform_stamp;
    }

    Health message;
    message.header.stamp = current;
    message.header.frame_id = map_frame_;
    message.state = static_cast<std::uint8_t>(decision.state);
    message.healthy = decision.operational;
    message.covariance_xy = covariance_xy_;
    message.lost_covariance_threshold = lost_threshold();
    message.pose_age_s = freshness_age_s;
    message.reason = decision.reason;
    health_pub_->publish(message);

    if (decision.changed) {
      const auto name = localization_state_name(decision.state);
      if (decision.state == LocalizationState::lost) {
        RCLCPP_ERROR(get_logger(), "Localization %s: %s", name, decision.reason.c_str());
      } else {
        RCLCPP_INFO(get_logger(), "Localization %s: %s", name, decision.reason.c_str());
      }
    }
  }

  double lost_threshold() const
  {
    return get_parameter("lost_covariance_threshold").as_double();
  }

  LocalizationHealthEvaluator evaluator_;
  const bool covariance_required_;
  const double pose_timeout_s_;
  const double moving_linear_threshold_;
  const double moving_angular_threshold_;
  const std::string map_frame_;
  const std::string base_frame_;
  bool moving_{false};
  bool pose_received_{false};
  bool covariance_valid_{false};
  double covariance_xy_{0.0};
  std::optional<rclcpp::Time> last_pose_stamp_;
  std::uint64_t pose_generation_{0};
  std::uint64_t lost_pose_generation_{0};
  tf2_ros::Buffer tf_;
  std::optional<rclcpp::Time> lost_transform_stamp_;
  tf2_ros::TransformListener listener_;
  rclcpp::Publisher<Health>::SharedPtr health_pub_;
  rclcpp::Subscription<PoseWithCovariance>::SharedPtr pose_sub_;
  rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr odom_sub_;
  rclcpp::TimerBase::SharedPtr timer_;
};
}  // namespace robot_cleaning_manager

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<robot_cleaning_manager::LocalizationHealthMonitor>());
  rclcpp::shutdown();
  return 0;
}
