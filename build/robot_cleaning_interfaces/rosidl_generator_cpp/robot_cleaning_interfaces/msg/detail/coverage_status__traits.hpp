// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_cleaning_interfaces:msg/CoverageStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/msg/coverage_status.hpp"


#ifndef ROBOT_CLEANING_INTERFACES__MSG__DETAIL__COVERAGE_STATUS__TRAITS_HPP_
#define ROBOT_CLEANING_INTERFACES__MSG__DETAIL__COVERAGE_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robot_cleaning_interfaces/msg/detail/coverage_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'covered'
#include "nav_msgs/msg/detail/occupancy_grid__traits.hpp"

namespace robot_cleaning_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const CoverageStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: task_id
  {
    out << "task_id: ";
    rosidl_generator_traits::value_to_yaml(msg.task_id, out);
    out << ", ";
  }

  // member: coverage
  {
    out << "coverage: ";
    rosidl_generator_traits::value_to_yaml(msg.coverage, out);
    out << ", ";
  }

  // member: path_length_m
  {
    out << "path_length_m: ";
    rosidl_generator_traits::value_to_yaml(msg.path_length_m, out);
    out << ", ";
  }

  // member: covered
  {
    out << "covered: ";
    to_flow_style_yaml(msg.covered, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const CoverageStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: task_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_id: ";
    rosidl_generator_traits::value_to_yaml(msg.task_id, out);
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

  // member: path_length_m
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "path_length_m: ";
    rosidl_generator_traits::value_to_yaml(msg.path_length_m, out);
    out << "\n";
  }

  // member: covered
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "covered:\n";
    to_block_style_yaml(msg.covered, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const CoverageStatus & msg, bool use_flow_style = false)
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
  const robot_cleaning_interfaces::msg::CoverageStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_cleaning_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_cleaning_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const robot_cleaning_interfaces::msg::CoverageStatus & msg)
{
  return robot_cleaning_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<robot_cleaning_interfaces::msg::CoverageStatus>()
{
  return "robot_cleaning_interfaces::msg::CoverageStatus";
}

template<>
inline const char * name<robot_cleaning_interfaces::msg::CoverageStatus>()
{
  return "robot_cleaning_interfaces/msg/CoverageStatus";
}

template<>
struct has_fixed_size<robot_cleaning_interfaces::msg::CoverageStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_cleaning_interfaces::msg::CoverageStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robot_cleaning_interfaces::msg::CoverageStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_CLEANING_INTERFACES__MSG__DETAIL__COVERAGE_STATUS__TRAITS_HPP_
