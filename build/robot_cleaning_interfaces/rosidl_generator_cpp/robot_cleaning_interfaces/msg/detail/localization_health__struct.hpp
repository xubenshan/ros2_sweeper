// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_cleaning_interfaces:msg/LocalizationHealth.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/msg/localization_health.hpp"


#ifndef ROBOT_CLEANING_INTERFACES__MSG__DETAIL__LOCALIZATION_HEALTH__STRUCT_HPP_
#define ROBOT_CLEANING_INTERFACES__MSG__DETAIL__LOCALIZATION_HEALTH__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__robot_cleaning_interfaces__msg__LocalizationHealth __attribute__((deprecated))
#else
# define DEPRECATED__robot_cleaning_interfaces__msg__LocalizationHealth __declspec(deprecated)
#endif

namespace robot_cleaning_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct LocalizationHealth_
{
  using Type = LocalizationHealth_<ContainerAllocator>;

  explicit LocalizationHealth_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->state = 0;
      this->healthy = false;
      this->covariance_xy = 0.0;
      this->lost_covariance_threshold = 0.0;
      this->pose_age_s = 0.0;
      this->reason = "";
    }
  }

  explicit LocalizationHealth_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    reason(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->state = 0;
      this->healthy = false;
      this->covariance_xy = 0.0;
      this->lost_covariance_threshold = 0.0;
      this->pose_age_s = 0.0;
      this->reason = "";
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _state_type =
    uint8_t;
  _state_type state;
  using _healthy_type =
    bool;
  _healthy_type healthy;
  using _covariance_xy_type =
    double;
  _covariance_xy_type covariance_xy;
  using _lost_covariance_threshold_type =
    double;
  _lost_covariance_threshold_type lost_covariance_threshold;
  using _pose_age_s_type =
    double;
  _pose_age_s_type pose_age_s;
  using _reason_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _reason_type reason;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__state(
    const uint8_t & _arg)
  {
    this->state = _arg;
    return *this;
  }
  Type & set__healthy(
    const bool & _arg)
  {
    this->healthy = _arg;
    return *this;
  }
  Type & set__covariance_xy(
    const double & _arg)
  {
    this->covariance_xy = _arg;
    return *this;
  }
  Type & set__lost_covariance_threshold(
    const double & _arg)
  {
    this->lost_covariance_threshold = _arg;
    return *this;
  }
  Type & set__pose_age_s(
    const double & _arg)
  {
    this->pose_age_s = _arg;
    return *this;
  }
  Type & set__reason(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->reason = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t UNKNOWN =
    0u;
  static constexpr uint8_t HEALTHY =
    1u;
  static constexpr uint8_t DEGRADED =
    2u;
  static constexpr uint8_t LOST =
    3u;

  // pointer types
  using RawPtr =
    robot_cleaning_interfaces::msg::LocalizationHealth_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_cleaning_interfaces::msg::LocalizationHealth_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_cleaning_interfaces::msg::LocalizationHealth_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_cleaning_interfaces::msg::LocalizationHealth_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_cleaning_interfaces::msg::LocalizationHealth_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_cleaning_interfaces::msg::LocalizationHealth_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_cleaning_interfaces::msg::LocalizationHealth_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_cleaning_interfaces::msg::LocalizationHealth_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_cleaning_interfaces::msg::LocalizationHealth_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_cleaning_interfaces::msg::LocalizationHealth_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_cleaning_interfaces__msg__LocalizationHealth
    std::shared_ptr<robot_cleaning_interfaces::msg::LocalizationHealth_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_cleaning_interfaces__msg__LocalizationHealth
    std::shared_ptr<robot_cleaning_interfaces::msg::LocalizationHealth_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const LocalizationHealth_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    if (this->healthy != other.healthy) {
      return false;
    }
    if (this->covariance_xy != other.covariance_xy) {
      return false;
    }
    if (this->lost_covariance_threshold != other.lost_covariance_threshold) {
      return false;
    }
    if (this->pose_age_s != other.pose_age_s) {
      return false;
    }
    if (this->reason != other.reason) {
      return false;
    }
    return true;
  }
  bool operator!=(const LocalizationHealth_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct LocalizationHealth_

// alias to use template instance with default allocator
using LocalizationHealth =
  robot_cleaning_interfaces::msg::LocalizationHealth_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LocalizationHealth_<ContainerAllocator>::UNKNOWN;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LocalizationHealth_<ContainerAllocator>::HEALTHY;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LocalizationHealth_<ContainerAllocator>::DEGRADED;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t LocalizationHealth_<ContainerAllocator>::LOST;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace robot_cleaning_interfaces

#endif  // ROBOT_CLEANING_INTERFACES__MSG__DETAIL__LOCALIZATION_HEALTH__STRUCT_HPP_
