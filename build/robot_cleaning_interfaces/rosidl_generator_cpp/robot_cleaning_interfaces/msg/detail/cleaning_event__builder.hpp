// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_cleaning_interfaces:msg/CleaningEvent.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/msg/cleaning_event.hpp"


#ifndef ROBOT_CLEANING_INTERFACES__MSG__DETAIL__CLEANING_EVENT__BUILDER_HPP_
#define ROBOT_CLEANING_INTERFACES__MSG__DETAIL__CLEANING_EVENT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_cleaning_interfaces/msg/detail/cleaning_event__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_cleaning_interfaces
{

namespace msg
{

namespace builder
{

class Init_CleaningEvent_total_waypoints
{
public:
  explicit Init_CleaningEvent_total_waypoints(::robot_cleaning_interfaces::msg::CleaningEvent & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::msg::CleaningEvent total_waypoints(::robot_cleaning_interfaces::msg::CleaningEvent::_total_waypoints_type arg)
  {
    msg_.total_waypoints = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::CleaningEvent msg_;
};

class Init_CleaningEvent_failed_waypoints
{
public:
  explicit Init_CleaningEvent_failed_waypoints(::robot_cleaning_interfaces::msg::CleaningEvent & msg)
  : msg_(msg)
  {}
  Init_CleaningEvent_total_waypoints failed_waypoints(::robot_cleaning_interfaces::msg::CleaningEvent::_failed_waypoints_type arg)
  {
    msg_.failed_waypoints = std::move(arg);
    return Init_CleaningEvent_total_waypoints(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::CleaningEvent msg_;
};

class Init_CleaningEvent_completed_waypoints
{
public:
  explicit Init_CleaningEvent_completed_waypoints(::robot_cleaning_interfaces::msg::CleaningEvent & msg)
  : msg_(msg)
  {}
  Init_CleaningEvent_failed_waypoints completed_waypoints(::robot_cleaning_interfaces::msg::CleaningEvent::_completed_waypoints_type arg)
  {
    msg_.completed_waypoints = std::move(arg);
    return Init_CleaningEvent_failed_waypoints(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::CleaningEvent msg_;
};

class Init_CleaningEvent_coverage
{
public:
  explicit Init_CleaningEvent_coverage(::robot_cleaning_interfaces::msg::CleaningEvent & msg)
  : msg_(msg)
  {}
  Init_CleaningEvent_completed_waypoints coverage(::robot_cleaning_interfaces::msg::CleaningEvent::_coverage_type arg)
  {
    msg_.coverage = std::move(arg);
    return Init_CleaningEvent_completed_waypoints(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::CleaningEvent msg_;
};

class Init_CleaningEvent_message
{
public:
  explicit Init_CleaningEvent_message(::robot_cleaning_interfaces::msg::CleaningEvent & msg)
  : msg_(msg)
  {}
  Init_CleaningEvent_coverage message(::robot_cleaning_interfaces::msg::CleaningEvent::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_CleaningEvent_coverage(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::CleaningEvent msg_;
};

class Init_CleaningEvent_recoverable
{
public:
  explicit Init_CleaningEvent_recoverable(::robot_cleaning_interfaces::msg::CleaningEvent & msg)
  : msg_(msg)
  {}
  Init_CleaningEvent_message recoverable(::robot_cleaning_interfaces::msg::CleaningEvent::_recoverable_type arg)
  {
    msg_.recoverable = std::move(arg);
    return Init_CleaningEvent_message(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::CleaningEvent msg_;
};

class Init_CleaningEvent_previous_state
{
public:
  explicit Init_CleaningEvent_previous_state(::robot_cleaning_interfaces::msg::CleaningEvent & msg)
  : msg_(msg)
  {}
  Init_CleaningEvent_recoverable previous_state(::robot_cleaning_interfaces::msg::CleaningEvent::_previous_state_type arg)
  {
    msg_.previous_state = std::move(arg);
    return Init_CleaningEvent_recoverable(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::CleaningEvent msg_;
};

class Init_CleaningEvent_state
{
public:
  explicit Init_CleaningEvent_state(::robot_cleaning_interfaces::msg::CleaningEvent & msg)
  : msg_(msg)
  {}
  Init_CleaningEvent_previous_state state(::robot_cleaning_interfaces::msg::CleaningEvent::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_CleaningEvent_previous_state(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::CleaningEvent msg_;
};

class Init_CleaningEvent_code
{
public:
  explicit Init_CleaningEvent_code(::robot_cleaning_interfaces::msg::CleaningEvent & msg)
  : msg_(msg)
  {}
  Init_CleaningEvent_state code(::robot_cleaning_interfaces::msg::CleaningEvent::_code_type arg)
  {
    msg_.code = std::move(arg);
    return Init_CleaningEvent_state(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::CleaningEvent msg_;
};

class Init_CleaningEvent_task_id
{
public:
  explicit Init_CleaningEvent_task_id(::robot_cleaning_interfaces::msg::CleaningEvent & msg)
  : msg_(msg)
  {}
  Init_CleaningEvent_code task_id(::robot_cleaning_interfaces::msg::CleaningEvent::_task_id_type arg)
  {
    msg_.task_id = std::move(arg);
    return Init_CleaningEvent_code(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::CleaningEvent msg_;
};

class Init_CleaningEvent_severity
{
public:
  explicit Init_CleaningEvent_severity(::robot_cleaning_interfaces::msg::CleaningEvent & msg)
  : msg_(msg)
  {}
  Init_CleaningEvent_task_id severity(::robot_cleaning_interfaces::msg::CleaningEvent::_severity_type arg)
  {
    msg_.severity = std::move(arg);
    return Init_CleaningEvent_task_id(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::CleaningEvent msg_;
};

class Init_CleaningEvent_sequence
{
public:
  explicit Init_CleaningEvent_sequence(::robot_cleaning_interfaces::msg::CleaningEvent & msg)
  : msg_(msg)
  {}
  Init_CleaningEvent_severity sequence(::robot_cleaning_interfaces::msg::CleaningEvent::_sequence_type arg)
  {
    msg_.sequence = std::move(arg);
    return Init_CleaningEvent_severity(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::CleaningEvent msg_;
};

class Init_CleaningEvent_header
{
public:
  Init_CleaningEvent_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CleaningEvent_sequence header(::robot_cleaning_interfaces::msg::CleaningEvent::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_CleaningEvent_sequence(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::CleaningEvent msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::msg::CleaningEvent>()
{
  return robot_cleaning_interfaces::msg::builder::Init_CleaningEvent_header();
}

}  // namespace robot_cleaning_interfaces

#endif  // ROBOT_CLEANING_INTERFACES__MSG__DETAIL__CLEANING_EVENT__BUILDER_HPP_
