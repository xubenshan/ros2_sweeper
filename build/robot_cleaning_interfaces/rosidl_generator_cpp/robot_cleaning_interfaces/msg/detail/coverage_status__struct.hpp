// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_cleaning_interfaces:msg/CoverageStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/msg/coverage_status.hpp"


#ifndef ROBOT_CLEANING_INTERFACES__MSG__DETAIL__COVERAGE_STATUS__STRUCT_HPP_
#define ROBOT_CLEANING_INTERFACES__MSG__DETAIL__COVERAGE_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'covered'
#include "nav_msgs/msg/detail/occupancy_grid__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__robot_cleaning_interfaces__msg__CoverageStatus __attribute__((deprecated))
#else
# define DEPRECATED__robot_cleaning_interfaces__msg__CoverageStatus __declspec(deprecated)
#endif

namespace robot_cleaning_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CoverageStatus_
{
  using Type = CoverageStatus_<ContainerAllocator>;

  explicit CoverageStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : covered(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->task_id = "";
      this->coverage = 0.0f;
      this->path_length_m = 0.0;
    }
  }

  explicit CoverageStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : task_id(_alloc),
    covered(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->task_id = "";
      this->coverage = 0.0f;
      this->path_length_m = 0.0;
    }
  }

  // field types and members
  using _task_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _task_id_type task_id;
  using _coverage_type =
    float;
  _coverage_type coverage;
  using _path_length_m_type =
    double;
  _path_length_m_type path_length_m;
  using _covered_type =
    nav_msgs::msg::OccupancyGrid_<ContainerAllocator>;
  _covered_type covered;

  // setters for named parameter idiom
  Type & set__task_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->task_id = _arg;
    return *this;
  }
  Type & set__coverage(
    const float & _arg)
  {
    this->coverage = _arg;
    return *this;
  }
  Type & set__path_length_m(
    const double & _arg)
  {
    this->path_length_m = _arg;
    return *this;
  }
  Type & set__covered(
    const nav_msgs::msg::OccupancyGrid_<ContainerAllocator> & _arg)
  {
    this->covered = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_cleaning_interfaces::msg::CoverageStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_cleaning_interfaces::msg::CoverageStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_cleaning_interfaces::msg::CoverageStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_cleaning_interfaces::msg::CoverageStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_cleaning_interfaces::msg::CoverageStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_cleaning_interfaces::msg::CoverageStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_cleaning_interfaces::msg::CoverageStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_cleaning_interfaces::msg::CoverageStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_cleaning_interfaces::msg::CoverageStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_cleaning_interfaces::msg::CoverageStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_cleaning_interfaces__msg__CoverageStatus
    std::shared_ptr<robot_cleaning_interfaces::msg::CoverageStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_cleaning_interfaces__msg__CoverageStatus
    std::shared_ptr<robot_cleaning_interfaces::msg::CoverageStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CoverageStatus_ & other) const
  {
    if (this->task_id != other.task_id) {
      return false;
    }
    if (this->coverage != other.coverage) {
      return false;
    }
    if (this->path_length_m != other.path_length_m) {
      return false;
    }
    if (this->covered != other.covered) {
      return false;
    }
    return true;
  }
  bool operator!=(const CoverageStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CoverageStatus_

// alias to use template instance with default allocator
using CoverageStatus =
  robot_cleaning_interfaces::msg::CoverageStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robot_cleaning_interfaces

#endif  // ROBOT_CLEANING_INTERFACES__MSG__DETAIL__COVERAGE_STATUS__STRUCT_HPP_
