// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_cleaning_interfaces:srv/BeginCoverage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/srv/begin_coverage.hpp"


#ifndef ROBOT_CLEANING_INTERFACES__SRV__DETAIL__BEGIN_COVERAGE__BUILDER_HPP_
#define ROBOT_CLEANING_INTERFACES__SRV__DETAIL__BEGIN_COVERAGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_cleaning_interfaces/srv/detail/begin_coverage__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_cleaning_interfaces
{

namespace srv
{

namespace builder
{

class Init_BeginCoverage_Request_restored_distance_m
{
public:
  explicit Init_BeginCoverage_Request_restored_distance_m(::robot_cleaning_interfaces::srv::BeginCoverage_Request & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::srv::BeginCoverage_Request restored_distance_m(::robot_cleaning_interfaces::srv::BeginCoverage_Request::_restored_distance_m_type arg)
  {
    msg_.restored_distance_m = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::BeginCoverage_Request msg_;
};

class Init_BeginCoverage_Request_restored_grid
{
public:
  explicit Init_BeginCoverage_Request_restored_grid(::robot_cleaning_interfaces::srv::BeginCoverage_Request & msg)
  : msg_(msg)
  {}
  Init_BeginCoverage_Request_restored_distance_m restored_grid(::robot_cleaning_interfaces::srv::BeginCoverage_Request::_restored_grid_type arg)
  {
    msg_.restored_grid = std::move(arg);
    return Init_BeginCoverage_Request_restored_distance_m(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::BeginCoverage_Request msg_;
};

class Init_BeginCoverage_Request_start
{
public:
  explicit Init_BeginCoverage_Request_start(::robot_cleaning_interfaces::srv::BeginCoverage_Request & msg)
  : msg_(msg)
  {}
  Init_BeginCoverage_Request_restored_grid start(::robot_cleaning_interfaces::srv::BeginCoverage_Request::_start_type arg)
  {
    msg_.start = std::move(arg);
    return Init_BeginCoverage_Request_restored_grid(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::BeginCoverage_Request msg_;
};

class Init_BeginCoverage_Request_regions
{
public:
  explicit Init_BeginCoverage_Request_regions(::robot_cleaning_interfaces::srv::BeginCoverage_Request & msg)
  : msg_(msg)
  {}
  Init_BeginCoverage_Request_start regions(::robot_cleaning_interfaces::srv::BeginCoverage_Request::_regions_type arg)
  {
    msg_.regions = std::move(arg);
    return Init_BeginCoverage_Request_start(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::BeginCoverage_Request msg_;
};

class Init_BeginCoverage_Request_task_id
{
public:
  Init_BeginCoverage_Request_task_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_BeginCoverage_Request_regions task_id(::robot_cleaning_interfaces::srv::BeginCoverage_Request::_task_id_type arg)
  {
    msg_.task_id = std::move(arg);
    return Init_BeginCoverage_Request_regions(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::BeginCoverage_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::srv::BeginCoverage_Request>()
{
  return robot_cleaning_interfaces::srv::builder::Init_BeginCoverage_Request_task_id();
}

}  // namespace robot_cleaning_interfaces


namespace robot_cleaning_interfaces
{

namespace srv
{

namespace builder
{

class Init_BeginCoverage_Response_reason
{
public:
  explicit Init_BeginCoverage_Response_reason(::robot_cleaning_interfaces::srv::BeginCoverage_Response & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::srv::BeginCoverage_Response reason(::robot_cleaning_interfaces::srv::BeginCoverage_Response::_reason_type arg)
  {
    msg_.reason = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::BeginCoverage_Response msg_;
};

class Init_BeginCoverage_Response_success
{
public:
  Init_BeginCoverage_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_BeginCoverage_Response_reason success(::robot_cleaning_interfaces::srv::BeginCoverage_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_BeginCoverage_Response_reason(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::BeginCoverage_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::srv::BeginCoverage_Response>()
{
  return robot_cleaning_interfaces::srv::builder::Init_BeginCoverage_Response_success();
}

}  // namespace robot_cleaning_interfaces


namespace robot_cleaning_interfaces
{

namespace srv
{

namespace builder
{

class Init_BeginCoverage_Event_response
{
public:
  explicit Init_BeginCoverage_Event_response(::robot_cleaning_interfaces::srv::BeginCoverage_Event & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::srv::BeginCoverage_Event response(::robot_cleaning_interfaces::srv::BeginCoverage_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::BeginCoverage_Event msg_;
};

class Init_BeginCoverage_Event_request
{
public:
  explicit Init_BeginCoverage_Event_request(::robot_cleaning_interfaces::srv::BeginCoverage_Event & msg)
  : msg_(msg)
  {}
  Init_BeginCoverage_Event_response request(::robot_cleaning_interfaces::srv::BeginCoverage_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_BeginCoverage_Event_response(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::BeginCoverage_Event msg_;
};

class Init_BeginCoverage_Event_info
{
public:
  Init_BeginCoverage_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_BeginCoverage_Event_request info(::robot_cleaning_interfaces::srv::BeginCoverage_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_BeginCoverage_Event_request(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::BeginCoverage_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::srv::BeginCoverage_Event>()
{
  return robot_cleaning_interfaces::srv::builder::Init_BeginCoverage_Event_info();
}

}  // namespace robot_cleaning_interfaces

#endif  // ROBOT_CLEANING_INTERFACES__SRV__DETAIL__BEGIN_COVERAGE__BUILDER_HPP_
