// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <algorithm>
#include <cmath>
#include <string>
#include <geometry_msgs/msg/twist.hpp>

namespace robot_motion_safety
{
enum class Source {none, nav, edge, recovery, teleop};

inline Source authorized(
  const std::string & state, Source requested, bool heartbeat, bool estop, bool contact)
{
  if (estop) {
    return Source::none;
  }
  if (heartbeat && state == "RECOVERING") {
    return Source::recovery;
  }
  if (contact) {
    return Source::none;
  }
  if (requested == Source::teleop || requested == Source::edge) {
    return requested;
  }
  if (requested == Source::nav || (heartbeat && state == "RUNNING")) {
    return Source::nav;
  }
  return Source::none;
}

inline geometry_msgs::msg::Twist guard(
  const geometry_msgs::msg::Twist & requested, double linear_limit, double angular_limit,
  bool contact)
{
  geometry_msgs::msg::Twist output;
  if (std::isfinite(requested.linear.x) && std::isfinite(requested.angular.z)) {
    output.linear.x = std::clamp(requested.linear.x, -linear_limit, contact ? 0.0 : linear_limit);
    output.angular.z = contact ? 0.0 :
      std::clamp(requested.angular.z, -angular_limit, angular_limit);
  }
  return output;
}
}  // namespace robot_motion_safety
