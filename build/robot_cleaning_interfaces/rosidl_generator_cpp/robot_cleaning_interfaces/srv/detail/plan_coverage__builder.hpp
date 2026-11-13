// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_cleaning_interfaces:srv/PlanCoverage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/srv/plan_coverage.hpp"


#ifndef ROBOT_CLEANING_INTERFACES__SRV__DETAIL__PLAN_COVERAGE__BUILDER_HPP_
#define ROBOT_CLEANING_INTERFACES__SRV__DETAIL__PLAN_COVERAGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_cleaning_interfaces/srv/detail/plan_coverage__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_cleaning_interfaces
{

namespace srv
{

namespace builder
{

class Init_PlanCoverage_Request_excluded
{
public:
  explicit Init_PlanCoverage_Request_excluded(::robot_cleaning_interfaces::srv::PlanCoverage_Request & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::srv::PlanCoverage_Request excluded(::robot_cleaning_interfaces::srv::PlanCoverage_Request::_excluded_type arg)
  {
    msg_.excluded = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::PlanCoverage_Request msg_;
};

class Init_PlanCoverage_Request_covered
{
public:
  explicit Init_PlanCoverage_Request_covered(::robot_cleaning_interfaces::srv::PlanCoverage_Request & msg)
  : msg_(msg)
  {}
  Init_PlanCoverage_Request_excluded covered(::robot_cleaning_interfaces::srv::PlanCoverage_Request::_covered_type arg)
  {
    msg_.covered = std::move(arg);
    return Init_PlanCoverage_Request_excluded(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::PlanCoverage_Request msg_;
};

class Init_PlanCoverage_Request_distance_budget_m
{
public:
  explicit Init_PlanCoverage_Request_distance_budget_m(::robot_cleaning_interfaces::srv::PlanCoverage_Request & msg)
  : msg_(msg)
  {}
  Init_PlanCoverage_Request_covered distance_budget_m(::robot_cleaning_interfaces::srv::PlanCoverage_Request::_distance_budget_m_type arg)
  {
    msg_.distance_budget_m = std::move(arg);
    return Init_PlanCoverage_Request_covered(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::PlanCoverage_Request msg_;
};

class Init_PlanCoverage_Request_target_coverage
{
public:
  explicit Init_PlanCoverage_Request_target_coverage(::robot_cleaning_interfaces::srv::PlanCoverage_Request & msg)
  : msg_(msg)
  {}
  Init_PlanCoverage_Request_distance_budget_m target_coverage(::robot_cleaning_interfaces::srv::PlanCoverage_Request::_target_coverage_type arg)
  {
    msg_.target_coverage = std::move(arg);
    return Init_PlanCoverage_Request_distance_budget_m(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::PlanCoverage_Request msg_;
};

class Init_PlanCoverage_Request_gap_fill
{
public:
  explicit Init_PlanCoverage_Request_gap_fill(::robot_cleaning_interfaces::srv::PlanCoverage_Request & msg)
  : msg_(msg)
  {}
  Init_PlanCoverage_Request_target_coverage gap_fill(::robot_cleaning_interfaces::srv::PlanCoverage_Request::_gap_fill_type arg)
  {
    msg_.gap_fill = std::move(arg);
    return Init_PlanCoverage_Request_target_coverage(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::PlanCoverage_Request msg_;
};

class Init_PlanCoverage_Request_start
{
public:
  explicit Init_PlanCoverage_Request_start(::robot_cleaning_interfaces::srv::PlanCoverage_Request & msg)
  : msg_(msg)
  {}
  Init_PlanCoverage_Request_gap_fill start(::robot_cleaning_interfaces::srv::PlanCoverage_Request::_start_type arg)
  {
    msg_.start = std::move(arg);
    return Init_PlanCoverage_Request_gap_fill(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::PlanCoverage_Request msg_;
};

class Init_PlanCoverage_Request_regions
{
public:
  Init_PlanCoverage_Request_regions()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlanCoverage_Request_start regions(::robot_cleaning_interfaces::srv::PlanCoverage_Request::_regions_type arg)
  {
    msg_.regions = std::move(arg);
    return Init_PlanCoverage_Request_start(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::PlanCoverage_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::srv::PlanCoverage_Request>()
{
  return robot_cleaning_interfaces::srv::builder::Init_PlanCoverage_Request_regions();
}

}  // namespace robot_cleaning_interfaces


namespace robot_cleaning_interfaces
{

namespace srv
{

namespace builder
{

class Init_PlanCoverage_Response_path
{
public:
  explicit Init_PlanCoverage_Response_path(::robot_cleaning_interfaces::srv::PlanCoverage_Response & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::srv::PlanCoverage_Response path(::robot_cleaning_interfaces::srv::PlanCoverage_Response::_path_type arg)
  {
    msg_.path = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::PlanCoverage_Response msg_;
};

class Init_PlanCoverage_Response_reason
{
public:
  explicit Init_PlanCoverage_Response_reason(::robot_cleaning_interfaces::srv::PlanCoverage_Response & msg)
  : msg_(msg)
  {}
  Init_PlanCoverage_Response_path reason(::robot_cleaning_interfaces::srv::PlanCoverage_Response::_reason_type arg)
  {
    msg_.reason = std::move(arg);
    return Init_PlanCoverage_Response_path(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::PlanCoverage_Response msg_;
};

class Init_PlanCoverage_Response_success
{
public:
  Init_PlanCoverage_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlanCoverage_Response_reason success(::robot_cleaning_interfaces::srv::PlanCoverage_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_PlanCoverage_Response_reason(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::PlanCoverage_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::srv::PlanCoverage_Response>()
{
  return robot_cleaning_interfaces::srv::builder::Init_PlanCoverage_Response_success();
}

}  // namespace robot_cleaning_interfaces


namespace robot_cleaning_interfaces
{

namespace srv
{

namespace builder
{

class Init_PlanCoverage_Event_response
{
public:
  explicit Init_PlanCoverage_Event_response(::robot_cleaning_interfaces::srv::PlanCoverage_Event & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::srv::PlanCoverage_Event response(::robot_cleaning_interfaces::srv::PlanCoverage_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::PlanCoverage_Event msg_;
};

class Init_PlanCoverage_Event_request
{
public:
  explicit Init_PlanCoverage_Event_request(::robot_cleaning_interfaces::srv::PlanCoverage_Event & msg)
  : msg_(msg)
  {}
  Init_PlanCoverage_Event_response request(::robot_cleaning_interfaces::srv::PlanCoverage_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_PlanCoverage_Event_response(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::PlanCoverage_Event msg_;
};

class Init_PlanCoverage_Event_info
{
public:
  Init_PlanCoverage_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlanCoverage_Event_request info(::robot_cleaning_interfaces::srv::PlanCoverage_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_PlanCoverage_Event_request(msg_);
  }

private:
  ::robot_cleaning_interfaces::srv::PlanCoverage_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::srv::PlanCoverage_Event>()
{
  return robot_cleaning_interfaces::srv::builder::Init_PlanCoverage_Event_info();
}

}  // namespace robot_cleaning_interfaces

#endif  // ROBOT_CLEANING_INTERFACES__SRV__DETAIL__PLAN_COVERAGE__BUILDER_HPP_
