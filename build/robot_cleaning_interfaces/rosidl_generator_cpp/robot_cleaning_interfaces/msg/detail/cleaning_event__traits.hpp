// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_cleaning_interfaces:msg/CleaningEvent.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/msg/cleaning_event.hpp"


#ifndef ROBOT_CLEANING_INTERFACES__MSG__DETAIL__CLEANING_EVENT__TRAITS_HPP_
#define ROBOT_CLEANING_INTERFACES__MSG__DETAIL__CLEANING_EVENT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robot_cleaning_interfaces/msg/detail/cleaning_event__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace robot_cleaning_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const CleaningEvent & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: sequence
  {
    out << "sequence: ";
    rosidl_generator_traits::value_to_yaml(msg.sequence, out);
    out << ", ";
  }

  // member: severity
  {
    out << "severity: ";
    rosidl_generator_traits::value_to_yaml(msg.severity, out);
    out << ", ";
  }

  // member: task_id
  {
    out << "task_id: ";
    rosidl_generator_traits::value_to_yaml(msg.task_id, out);
    out << ", ";
  }

  // member: code
  {
    out << "code: ";
    rosidl_generator_traits::value_to_yaml(msg.code, out);
    out << ", ";
  }

  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << ", ";
  }

  // member: previous_state
  {
    out << "previous_state: ";
    rosidl_generator_traits::value_to_yaml(msg.previous_state, out);
    out << ", ";
  }

  // member: recoverable
  {
    out << "recoverable: ";
    rosidl_generator_traits::value_to_yaml(msg.recoverable, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << ", ";
  }

  // member: coverage
  {
    out << "coverage: ";
    rosidl_generator_traits::value_to_yaml(msg.coverage, out);
    out << ", ";
  }

  // member: completed_waypoints
  {
    out << "completed_waypoints: ";
    rosidl_generator_traits::value_to_yaml(msg.completed_waypoints, out);
    out << ", ";
  }

  // member: failed_waypoints
  {
    out << "failed_waypoints: ";
    rosidl_generator_traits::value_to_yaml(msg.failed_waypoints, out);
    out << ", ";
  }

  // member: total_waypoints
  {
    out << "total_waypoints: ";
    rosidl_generator_traits::value_to_yaml(msg.total_waypoints, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CleaningEvent & msg,
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

  // member: sequence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "sequence: ";
    rosidl_generator_traits::value_to_yaml(msg.sequence, out);
    out << "\n";
  }

  // member: severity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "severity: ";
    rosidl_generator_traits::value_to_yaml(msg.severity, out);
    out << "\n";
  }

  // member: task_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_id: ";
    rosidl_generator_traits::value_to_yaml(msg.task_id, out);
    out << "\n";
  }

  // member: code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "code: ";
    rosidl_generator_traits::value_to_yaml(msg.code, out);
    out << "\n";
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

  // member: previous_state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "previous_state: ";
    rosidl_generator_traits::value_to_yaml(msg.previous_state, out);
    out << "\n";
  }

  // member: recoverable
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "recoverable: ";
    rosidl_generator_traits::value_to_yaml(msg.recoverable, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }

  // member: coverage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "coverage: ";
    rosidl_generator_traits::value_to_yaml(msg.coverage, out);
    out << "\n";
  }

  // member: completed_waypoints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "completed_waypoints: ";
    rosidl_generator_traits::value_to_yaml(msg.completed_waypoints, out);
    out << "\n";
  }

  // member: failed_waypoints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "failed_waypoints: ";
    rosidl_generator_traits::value_to_yaml(msg.failed_waypoints, out);
    out << "\n";
  }

  // member: total_waypoints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_waypoints: ";
    rosidl_generator_traits::value_to_yaml(msg.total_waypoints, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CleaningEvent & msg, bool use_flow_style = false)
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
  const robot_cleaning_interfaces::msg::CleaningEvent & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_cleaning_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_cleaning_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const robot_cleaning_interfaces::msg::CleaningEvent & msg)
{
  return robot_cleaning_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<robot_cleaning_interfaces::msg::CleaningEvent>()
{
  return "robot_cleaning_interfaces::msg::CleaningEvent";
}

template<>
inline const char * name<robot_cleaning_interfaces::msg::CleaningEvent>()
{
  return "robot_cleaning_interfaces/msg/CleaningEvent";
}

template<>
struct has_fixed_size<robot_cleaning_interfaces::msg::CleaningEvent>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_cleaning_interfaces::msg::CleaningEvent>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robot_cleaning_interfaces::msg::CleaningEvent>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_CLEANING_INTERFACES__MSG__DETAIL__CLEANING_EVENT__TRAITS_HPP_
