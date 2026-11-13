// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from oomwoo_msgs:msg/BumpEvent.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "oomwoo_msgs/msg/bump_event.hpp"


#ifndef OOMWOO_MSGS__MSG__DETAIL__BUMP_EVENT__BUILDER_HPP_
#define OOMWOO_MSGS__MSG__DETAIL__BUMP_EVENT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "oomwoo_msgs/msg/detail/bump_event__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace oomwoo_msgs
{

namespace msg
{

namespace builder
{

class Init_BumpEvent_right_rate
{
public:
  explicit Init_BumpEvent_right_rate(::oomwoo_msgs::msg::BumpEvent & msg)
  : msg_(msg)
  {}
  ::oomwoo_msgs::msg::BumpEvent right_rate(::oomwoo_msgs::msg::BumpEvent::_right_rate_type arg)
  {
    msg_.right_rate = std::move(arg);
    return std::move(msg_);
  }

private:
  ::oomwoo_msgs::msg::BumpEvent msg_;
};

class Init_BumpEvent_left_rate
{
public:
  explicit Init_BumpEvent_left_rate(::oomwoo_msgs::msg::BumpEvent & msg)
  : msg_(msg)
  {}
  Init_BumpEvent_right_rate left_rate(::oomwoo_msgs::msg::BumpEvent::_left_rate_type arg)
  {
    msg_.left_rate = std::move(arg);
    return Init_BumpEvent_right_rate(msg_);
  }

private:
  ::oomwoo_msgs::msg::BumpEvent msg_;
};

class Init_BumpEvent_right_depress
{
public:
  explicit Init_BumpEvent_right_depress(::oomwoo_msgs::msg::BumpEvent & msg)
  : msg_(msg)
  {}
  Init_BumpEvent_left_rate right_depress(::oomwoo_msgs::msg::BumpEvent::_right_depress_type arg)
  {
    msg_.right_depress = std::move(arg);
    return Init_BumpEvent_left_rate(msg_);
  }

private:
  ::oomwoo_msgs::msg::BumpEvent msg_;
};

class Init_BumpEvent_left_depress
{
public:
  explicit Init_BumpEvent_left_depress(::oomwoo_msgs::msg::BumpEvent & msg)
  : msg_(msg)
  {}
  Init_BumpEvent_right_depress left_depress(::oomwoo_msgs::msg::BumpEvent::_left_depress_type arg)
  {
    msg_.left_depress = std::move(arg);
    return Init_BumpEvent_right_depress(msg_);
  }

private:
  ::oomwoo_msgs::msg::BumpEvent msg_;
};

class Init_BumpEvent_side
{
public:
  explicit Init_BumpEvent_side(::oomwoo_msgs::msg::BumpEvent & msg)
  : msg_(msg)
  {}
  Init_BumpEvent_left_depress side(::oomwoo_msgs::msg::BumpEvent::_side_type arg)
  {
    msg_.side = std::move(arg);
    return Init_BumpEvent_left_depress(msg_);
  }

private:
  ::oomwoo_msgs::msg::BumpEvent msg_;
};

class Init_BumpEvent_heading
{
public:
  explicit Init_BumpEvent_heading(::oomwoo_msgs::msg::BumpEvent & msg)
  : msg_(msg)
  {}
  Init_BumpEvent_side heading(::oomwoo_msgs::msg::BumpEvent::_heading_type arg)
  {
    msg_.heading = std::move(arg);
    return Init_BumpEvent_side(msg_);
  }

private:
  ::oomwoo_msgs::msg::BumpEvent msg_;
};

class Init_BumpEvent_approach
{
public:
  explicit Init_BumpEvent_approach(::oomwoo_msgs::msg::BumpEvent & msg)
  : msg_(msg)
  {}
  Init_BumpEvent_heading approach(::oomwoo_msgs::msg::BumpEvent::_approach_type arg)
  {
    msg_.approach = std::move(arg);
    return Init_BumpEvent_heading(msg_);
  }

private:
  ::oomwoo_msgs::msg::BumpEvent msg_;
};

class Init_BumpEvent_robot
{
public:
  explicit Init_BumpEvent_robot(::oomwoo_msgs::msg::BumpEvent & msg)
  : msg_(msg)
  {}
  Init_BumpEvent_approach robot(::oomwoo_msgs::msg::BumpEvent::_robot_type arg)
  {
    msg_.robot = std::move(arg);
    return Init_BumpEvent_approach(msg_);
  }

private:
  ::oomwoo_msgs::msg::BumpEvent msg_;
};

class Init_BumpEvent_contact
{
public:
  explicit Init_BumpEvent_contact(::oomwoo_msgs::msg::BumpEvent & msg)
  : msg_(msg)
  {}
  Init_BumpEvent_robot contact(::oomwoo_msgs::msg::BumpEvent::_contact_type arg)
  {
    msg_.contact = std::move(arg);
    return Init_BumpEvent_robot(msg_);
  }

private:
  ::oomwoo_msgs::msg::BumpEvent msg_;
};

class Init_BumpEvent_header
{
public:
  Init_BumpEvent_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_BumpEvent_contact header(::oomwoo_msgs::msg::BumpEvent::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_BumpEvent_contact(msg_);
  }

private:
  ::oomwoo_msgs::msg::BumpEvent msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::oomwoo_msgs::msg::BumpEvent>()
{
  return oomwoo_msgs::msg::builder::Init_BumpEvent_header();
}

}  // namespace oomwoo_msgs

#endif  // OOMWOO_MSGS__MSG__DETAIL__BUMP_EVENT__BUILDER_HPP_
