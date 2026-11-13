// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <chrono>
#include <string>
#include <geometry_msgs/msg/twist.hpp>

namespace robot_cleaning_manager
{
class RecoveryExecutor
{
public:
  explicit RecoveryExecutor(const std::string & contact)
  : turn_(contact == "right" ? 0.65 : -0.65)
  {
  }

  geometry_msgs::msg::Twist command(std::chrono::steady_clock::duration elapsed) const
  {
    geometry_msgs::msg::Twist command;
    if (elapsed < std::chrono::milliseconds(1300)) {
      command.linear.x = -0.12;
    } else {
      command.angular.z = turn_;
    }
    return command;
  }

  static bool done(std::chrono::steady_clock::duration elapsed)
  {
    return elapsed >= std::chrono::milliseconds(2400);
  }

private:
  double turn_;
};
}  // namespace robot_cleaning_manager
