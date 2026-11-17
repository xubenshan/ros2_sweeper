// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_cleaning_interfaces:srv/ListCleaningEvents.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/srv/list_cleaning_events.hpp"


#ifndef ROBOT_CLEANING_INTERFACES__SRV__DETAIL__LIST_CLEANING_EVENTS__BUILDER_HPP_
#define ROBOT_CLEANING_INTERFACES__SRV__DETAIL__LIST_CLEANING_EVENTS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_cleaning_interfaces/srv/detail/list_cleaning_events__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_cleaning_interfaces
{

namespace srv
{

namespace builder
{

class Init_ListCleaningEvents_Request_code_filter
{
public:
  explicit Init_ListCleaningEvents_Request_code_filter(::robot_cleaning_interfaces::srv::ListCleaningEvents_Request & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::srv::ListCleaningEvents_Request code_filter(::robot_cleaning_interfaces::srv::ListCleaningEvents_Request::_code_filter_type arg)
  {
    msg_.code_filter = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::ListCleaningEvents_Request msg_;
};

class Init_ListCleaningEvents_Request_task_id_filter
{
public:
  explicit Init_ListCleaningEvents_Request_task_id_filter(::robot_cleaning_interfaces::srv::ListCleaningEvents_Request & msg)
  : msg_(msg)
  {}
  Init_ListCleaningEvents_Request_code_filter task_id_filter(::robot_cleaning_interfaces::srv::ListCleaningEvents_Request::_task_id_filter_type arg)
  {
    msg_.task_id_filter = std::move(arg);
    return Init_ListCleaningEvents_Request_code_filter(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::ListCleaningEvents_Request msg_;
};

class Init_ListCleaningEvents_Request_limit
{
public:
  Init_ListCleaningEvents_Request_limit()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ListCleaningEvents_Request_task_id_filter limit(::robot_cleaning_interfaces::srv::ListCleaningEvents_Request::_limit_type arg)
  {
    msg_.limit = std::move(arg);
    return Init_ListCleaningEvents_Request_task_id_filter(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::ListCleaningEvents_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::srv::ListCleaningEvents_Request>()
{
  return robot_cleaning_interfaces::srv::builder::Init_ListCleaningEvents_Request_limit();
}

}  // namespace robot_cleaning_interfaces


namespace robot_cleaning_interfaces
{

namespace srv
{

namespace builder
{

class Init_ListCleaningEvents_Response_events
{
public:
  explicit Init_ListCleaningEvents_Response_events(::robot_cleaning_interfaces::srv::ListCleaningEvents_Response & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::srv::ListCleaningEvents_Response events(::robot_cleaning_interfaces::srv::ListCleaningEvents_Response::_events_type arg)
  {
    msg_.events = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::ListCleaningEvents_Response msg_;
};

class Init_ListCleaningEvents_Response_message
{
public:
  explicit Init_ListCleaningEvents_Response_message(::robot_cleaning_interfaces::srv::ListCleaningEvents_Response & msg)
  : msg_(msg)
  {}
  Init_ListCleaningEvents_Response_events message(::robot_cleaning_interfaces::srv::ListCleaningEvents_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_ListCleaningEvents_Response_events(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::ListCleaningEvents_Response msg_;
};

class Init_ListCleaningEvents_Response_success
{
public:
  Init_ListCleaningEvents_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ListCleaningEvents_Response_message success(::robot_cleaning_interfaces::srv::ListCleaningEvents_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ListCleaningEvents_Response_message(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::ListCleaningEvents_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::srv::ListCleaningEvents_Response>()
{
  return robot_cleaning_interfaces::srv::builder::Init_ListCleaningEvents_Response_success();
}

}  // namespace robot_cleaning_interfaces


namespace robot_cleaning_interfaces
{

namespace srv
{

namespace builder
{

class Init_ListCleaningEvents_Event_response
{
public:
  explicit Init_ListCleaningEvents_Event_response(::robot_cleaning_interfaces::srv::ListCleaningEvents_Event & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::srv::ListCleaningEvents_Event response(::robot_cleaning_interfaces::srv::ListCleaningEvents_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::ListCleaningEvents_Event msg_;
};

class Init_ListCleaningEvents_Event_request
{
public:
  explicit Init_ListCleaningEvents_Event_request(::robot_cleaning_interfaces::srv::ListCleaningEvents_Event & msg)
  : msg_(msg)
  {}
  Init_ListCleaningEvents_Event_response request(::robot_cleaning_interfaces::srv::ListCleaningEvents_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_ListCleaningEvents_Event_response(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::ListCleaningEvents_Event msg_;
};

class Init_ListCleaningEvents_Event_info
{
public:
  Init_ListCleaningEvents_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ListCleaningEvents_Event_request info(::robot_cleaning_interfaces::srv::ListCleaningEvents_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_ListCleaningEvents_Event_request(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::ListCleaningEvents_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::srv::ListCleaningEvents_Event>()
{
  return robot_cleaning_interfaces::srv::builder::Init_ListCleaningEvents_Event_info();
}

}  // namespace robot_cleaning_interfaces

#endif  // ROBOT_CLEANING_INTERFACES__SRV__DETAIL__LIST_CLEANING_EVENTS__BUILDER_HPP_
