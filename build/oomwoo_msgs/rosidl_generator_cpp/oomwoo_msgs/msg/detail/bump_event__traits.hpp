// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from oomwoo_msgs:msg/BumpEvent.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "oomwoo_msgs/msg/bump_event.hpp"


#ifndef OOMWOO_MSGS__MSG__DETAIL__BUMP_EVENT__TRAITS_HPP_
#define OOMWOO_MSGS__MSG__DETAIL__BUMP_EVENT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "oomwoo_msgs/msg/detail/bump_event__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'contact'
// Member 'robot'
// Member 'approach'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace oomwoo_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const BumpEvent & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: contact
  {
    out << "contact: ";
    to_flow_style_yaml(msg.contact, out);
    out << ", ";
  }

  // member: robot
  {
    out << "robot: ";
    to_flow_style_yaml(msg.robot, out);
    out << ", ";
  }

  // member: approach
  {
    out << "approach: ";
    to_flow_style_yaml(msg.approach, out);
    out << ", ";
  }

  // member: heading
  {
    out << "heading: ";
    rosidl_generator_traits::value_to_yaml(msg.heading, out);
    out << ", ";
  }

  // member: side
  {
    out << "side: ";
    rosidl_generator_traits::value_to_yaml(msg.side, out);
    out << ", ";
  }

  // member: left_depress
  {
    out << "left_depress: ";
    rosidl_generator_traits::value_to_yaml(msg.left_depress, out);
    out << ", ";
  }

  // member: right_depress
  {
    out << "right_depress: ";
    rosidl_generator_traits::value_to_yaml(msg.right_depress, out);
    out << ", ";
  }

  // member: left_rate
  {
    out << "left_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.left_rate, out);
    out << ", ";
  }

  // member: right_rate
  {
    out << "right_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.right_rate, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const BumpEvent & msg,
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

  // member: contact
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "contact:\n";
    to_block_style_yaml(msg.contact, out, indentation + 2);
  }

  // member: robot
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "robot:\n";
    to_block_style_yaml(msg.robot, out, indentation + 2);
  }

  // member: approach
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "approach:\n";
    to_block_style_yaml(msg.approach, out, indentation + 2);
  }

  // member: heading
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "heading: ";
    rosidl_generator_traits::value_to_yaml(msg.heading, out);
    out << "\n";
  }

  // member: side
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "side: ";
    rosidl_generator_traits::value_to_yaml(msg.side, out);
    out << "\n";
  }

  // member: left_depress
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left_depress: ";
    rosidl_generator_traits::value_to_yaml(msg.left_depress, out);
    out << "\n";
  }

  // member: right_depress
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right_depress: ";
    rosidl_generator_traits::value_to_yaml(msg.right_depress, out);
    out << "\n";
  }

  // member: left_rate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "left_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.left_rate, out);
    out << "\n";
  }

  // member: right_rate
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "right_rate: ";
    rosidl_generator_traits::value_to_yaml(msg.right_rate, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const BumpEvent & msg, bool use_flow_style = false)
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

}  // namespace oomwoo_msgs

namespace rosidl_generator_traits
{

[[deprecated("use oomwoo_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const oomwoo_msgs::msg::BumpEvent & msg,
  std::ostream & out, size_t indentation = 0)
{
  oomwoo_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use oomwoo_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const oomwoo_msgs::msg::BumpEvent & msg)
{
  return oomwoo_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<oomwoo_msgs::msg::BumpEvent>()
{
  return "oomwoo_msgs::msg::BumpEvent";
}

template<>
inline const char * name<oomwoo_msgs::msg::BumpEvent>()
{
  return "oomwoo_msgs/msg/BumpEvent";
}

template<>
struct has_fixed_size<oomwoo_msgs::msg::BumpEvent>
  : std::integral_constant<bool, has_fixed_size<geometry_msgs::msg::Point>::value && has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<oomwoo_msgs::msg::BumpEvent>
  : std::integral_constant<bool, has_bounded_size<geometry_msgs::msg::Point>::value && has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<oomwoo_msgs::msg::BumpEvent>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // OOMWOO_MSGS__MSG__DETAIL__BUMP_EVENT__TRAITS_HPP_
