// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_cleaning_interfaces:msg/CoverageStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/msg/coverage_status.hpp"


#ifndef ROBOT_CLEANING_INTERFACES__MSG__DETAIL__COVERAGE_STATUS__BUILDER_HPP_
#define ROBOT_CLEANING_INTERFACES__MSG__DETAIL__COVERAGE_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_cleaning_interfaces/msg/detail/coverage_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_cleaning_interfaces
{

namespace msg
{

namespace builder
{

class Init_CoverageStatus_covered
{
public:
  explicit Init_CoverageStatus_covered(::robot_cleaning_interfaces::msg::CoverageStatus & msg)
  : msg_(msg)
  {}
  ::robot_cleaning_interfaces::msg::CoverageStatus covered(::robot_cleaning_interfaces::msg::CoverageStatus::_covered_type arg)
  {
    msg_.covered = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::CoverageStatus msg_;
};

class Init_CoverageStatus_path_length_m
{
public:
  explicit Init_CoverageStatus_path_length_m(::robot_cleaning_interfaces::msg::CoverageStatus & msg)
  : msg_(msg)
  {}
  Init_CoverageStatus_covered path_length_m(::robot_cleaning_interfaces::msg::CoverageStatus::_path_length_m_type arg)
  {
    msg_.path_length_m = std::move(arg);
    return Init_CoverageStatus_covered(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::CoverageStatus msg_;
};

class Init_CoverageStatus_coverage
{
public:
  explicit Init_CoverageStatus_coverage(::robot_cleaning_interfaces::msg::CoverageStatus & msg)
  : msg_(msg)
  {}
  Init_CoverageStatus_path_length_m coverage(::robot_cleaning_interfaces::msg::CoverageStatus::_coverage_type arg)
  {
    msg_.coverage = std::move(arg);
    return Init_CoverageStatus_path_length_m(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::CoverageStatus msg_;
};

class Init_CoverageStatus_task_id
{
public:
  Init_CoverageStatus_task_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_CoverageStatus_coverage task_id(::robot_cleaning_interfaces::msg::CoverageStatus::_task_id_type arg)
  {
    msg_.task_id = std::move(arg);
    return Init_CoverageStatus_coverage(msg_);
  }

private:
  ::robot_cleaning_interfaces::msg::CoverageStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_cleaning_interfaces::msg::CoverageStatus>()
{
  return robot_cleaning_interfaces::msg::builder::Init_CoverageStatus_task_id();
}

}  // namespace robot_cleaning_interfaces

#endif  // ROBOT_CLEANING_INTERFACES__MSG__DETAIL__COVERAGE_STATUS__BUILDER_HPP_
