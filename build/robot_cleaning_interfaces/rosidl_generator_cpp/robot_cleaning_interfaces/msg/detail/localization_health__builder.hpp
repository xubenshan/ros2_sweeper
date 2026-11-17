// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_cleaning_interfaces:msg/LocalizationHealth.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/msg/localization_health.hpp"


#ifndef ROBOT_CLEANING_INTERFACES__MSG__DETAIL__LOCALIZATION_HEALTH__BUILDER_HPP_
#define ROBOT_CLEANING_INTERFACES__MSG__DETAIL__LOCALIZATION_HEALTH__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_cleaning_interfaces/msg/detail/localization_health__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_cleaning_interfaces
{

namespace msg
{

namespace builder
{

class Init_LocalizationHealth_reason
{
public:
  explicit Init_LocalizationHealth_reason(::robot_cleaning_interfaces::msg::LocalizationHealth & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::msg::LocalizationHealth reason(::robot_cleaning_interfaces::msg::LocalizationHealth::_reason_type arg)
  {
    msg_.reason = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::LocalizationHealth msg_;
};

class Init_LocalizationHealth_pose_age_s
{
public:
  explicit Init_LocalizationHealth_pose_age_s(::robot_cleaning_interfaces::msg::LocalizationHealth & msg)
  : msg_(msg)
  {}
  Init_LocalizationHealth_reason pose_age_s(::robot_cleaning_interfaces::msg::LocalizationHealth::_pose_age_s_type arg)
  {
    msg_.pose_age_s = std::move(arg);
    return Init_LocalizationHealth_reason(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::LocalizationHealth msg_;
};

class Init_LocalizationHealth_lost_covariance_threshold
{
public:
  explicit Init_LocalizationHealth_lost_covariance_threshold(::robot_cleaning_interfaces::msg::LocalizationHealth & msg)
  : msg_(msg)
  {}
  Init_LocalizationHealth_pose_age_s lost_covariance_threshold(::robot_cleaning_interfaces::msg::LocalizationHealth::_lost_covariance_threshold_type arg)
  {
    msg_.lost_covariance_threshold = std::move(arg);
    return Init_LocalizationHealth_pose_age_s(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::LocalizationHealth msg_;
};

class Init_LocalizationHealth_covariance_xy
{
public:
  explicit Init_LocalizationHealth_covariance_xy(::robot_cleaning_interfaces::msg::LocalizationHealth & msg)
  : msg_(msg)
  {}
  Init_LocalizationHealth_lost_covariance_threshold covariance_xy(::robot_cleaning_interfaces::msg::LocalizationHealth::_covariance_xy_type arg)
  {
    msg_.covariance_xy = std::move(arg);
    return Init_LocalizationHealth_lost_covariance_threshold(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::LocalizationHealth msg_;
};

class Init_LocalizationHealth_healthy
{
public:
  explicit Init_LocalizationHealth_healthy(::robot_cleaning_interfaces::msg::LocalizationHealth & msg)
  : msg_(msg)
  {}
  Init_LocalizationHealth_covariance_xy healthy(::robot_cleaning_interfaces::msg::LocalizationHealth::_healthy_type arg)
  {
    msg_.healthy = std::move(arg);
    return Init_LocalizationHealth_covariance_xy(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::LocalizationHealth msg_;
};

class Init_LocalizationHealth_state
{
public:
  explicit Init_LocalizationHealth_state(::robot_cleaning_interfaces::msg::LocalizationHealth & msg)
  : msg_(msg)
  {}
  Init_LocalizationHealth_healthy state(::robot_cleaning_interfaces::msg::LocalizationHealth::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_LocalizationHealth_healthy(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::LocalizationHealth msg_;
};

class Init_LocalizationHealth_header
{
public:
  Init_LocalizationHealth_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LocalizationHealth_state header(::robot_cleaning_interfaces::msg::LocalizationHealth::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_LocalizationHealth_state(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::LocalizationHealth msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::msg::LocalizationHealth>()
{
  return robot_cleaning_interfaces::msg::builder::Init_LocalizationHealth_header();
}

}  // namespace robot_cleaning_interfaces

#endif  // ROBOT_CLEANING_INTERFACES__MSG__DETAIL__LOCALIZATION_HEALTH__BUILDER_HPP_
