// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_cleaning_interfaces:msg/LocalizationHealth.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/msg/localization_health.hpp"


#ifndef ROBOT_CLEANING_INTERFACES__MSG__DETAIL__LOCALIZATION_HEALTH__TRAITS_HPP_
#define ROBOT_CLEANING_INTERFACES__MSG__DETAIL__LOCALIZATION_HEALTH__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robot_cleaning_interfaces/msg/detail/localization_health__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace robot_cleaning_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const LocalizationHealth & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << ", ";
  }

  // member: healthy
  {
    out << "healthy: ";
    rosidl_generator_traits::value_to_yaml(msg.healthy, out);
    out << ", ";
  }

  // member: covariance_xy
  {
    out << "covariance_xy: ";
    rosidl_generator_traits::value_to_yaml(msg.covariance_xy, out);
    out << ", ";
  }

  // member: lost_covariance_threshold
  {
    out << "lost_covariance_threshold: ";
    rosidl_generator_traits::value_to_yaml(msg.lost_covariance_threshold, out);
    out << ", ";
  }

  // member: pose_age_s
  {
    out << "pose_age_s: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_age_s, out);
    out << ", ";
  }

  // member: reason
  {
    out << "reason: ";
    rosidl_generator_traits::value_to_yaml(msg.reason, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LocalizationHealth & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << "\n";
  }

  // member: healthy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "healthy: ";
    rosidl_generator_traits::value_to_yaml(msg.healthy, out);
    out << "\n";
  }

  // member: covariance_xy
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "covariance_xy: ";
    rosidl_generator_traits::value_to_yaml(msg.covariance_xy, out);
    out << "\n";
  }

  // member: lost_covariance_threshold
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "lost_covariance_threshold: ";
    rosidl_generator_traits::value_to_yaml(msg.lost_covariance_threshold, out);
    out << "\n";
  }

  // member: pose_age_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose_age_s: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_age_s, out);
    out << "\n";
  }

  // member: reason
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reason: ";
    rosidl_generator_traits::value_to_yaml(msg.reason, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LocalizationHealth & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace robot_cleaning_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use robot_cleaning_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const robot_cleaning_interfaces::msg::LocalizationHealth & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_cleaning_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_cleaning_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const robot_cleaning_interfaces::msg::LocalizationHealth & msg)
{
  return robot_cleaning_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<robot_cleaning_interfaces::msg::LocalizationHealth>()
{
  return "robot_cleaning_interfaces::msg::LocalizationHealth";
}

template<>
inline const char * name<robot_cleaning_interfaces::msg::LocalizationHealth>()
{
  return "robot_cleaning_interfaces/msg/LocalizationHealth";
}

template<>
struct has_fixed_size<robot_cleaning_interfaces::msg::LocalizationHealth>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_cleaning_interfaces::msg::LocalizationHealth>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robot_cleaning_interfaces::msg::LocalizationHealth>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_CLEANING_INTERFACES__MSG__DETAIL__LOCALIZATION_HEALTH__TRAITS_HPP_
