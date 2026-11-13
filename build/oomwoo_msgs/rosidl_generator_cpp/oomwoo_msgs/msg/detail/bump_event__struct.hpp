// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from oomwoo_msgs:msg/BumpEvent.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "oomwoo_msgs/msg/bump_event.hpp"


#ifndef OOMWOO_MSGS__MSG__DETAIL__BUMP_EVENT__STRUCT_HPP_
#define OOMWOO_MSGS__MSG__DETAIL__BUMP_EVENT__STRUCT_HPP_

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
// Member 'contact'
// Member 'robot'
// Member 'approach'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__oomwoo_msgs__msg__BumpEvent __attribute__((deprecated))
#else
# define DEPRECATED__oomwoo_msgs__msg__BumpEvent __declspec(deprecated)
#endif

namespace oomwoo_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct BumpEvent_
{
  using Type = BumpEvent_<ContainerAllocator>;

  explicit BumpEvent_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    contact(_init),
    robot(_init),
    approach(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->heading = 0.0;
      this->side = 0;
      this->left_depress = 0.0f;
      this->right_depress = 0.0f;
      this->left_rate = 0.0f;
      this->right_rate = 0.0f;
    }
  }

  explicit BumpEvent_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    contact(_alloc, _init),
    robot(_alloc, _init),
    approach(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->heading = 0.0;
      this->side = 0;
      this->left_depress = 0.0f;
      this->right_depress = 0.0f;
      this->left_rate = 0.0f;
      this->right_rate = 0.0f;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _contact_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _contact_type contact;
  using _robot_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _robot_type robot;
  using _approach_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _approach_type approach;
  using _heading_type =
    double;
  _heading_type heading;
  using _side_type =
    uint8_t;
  _side_type side;
  using _left_depress_type =
    float;
  _left_depress_type left_depress;
  using _right_depress_type =
    float;
  _right_depress_type right_depress;
  using _left_rate_type =
    float;
  _left_rate_type left_rate;
  using _right_rate_type =
    float;
  _right_rate_type right_rate;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__contact(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->contact = _arg;
    return *this;
  }
  Type & set__robot(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->robot = _arg;
    return *this;
  }
  Type & set__approach(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->approach = _arg;
    return *this;
  }
  Type & set__heading(
    const double & _arg)
  {
    this->heading = _arg;
    return *this;
  }
  Type & set__side(
    const uint8_t & _arg)
  {
    this->side = _arg;
    return *this;
  }
  Type & set__left_depress(
    const float & _arg)
  {
    this->left_depress = _arg;
    return *this;
  }
  Type & set__right_depress(
    const float & _arg)
  {
    this->right_depress = _arg;
    return *this;
  }
  Type & set__left_rate(
    const float & _arg)
  {
    this->left_rate = _arg;
    return *this;
  }
  Type & set__right_rate(
    const float & _arg)
  {
    this->right_rate = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t SIDE_BOTH =
    0u;
  static constexpr uint8_t SIDE_LEFT =
    1u;
  static constexpr uint8_t SIDE_RIGHT =
    2u;

  // pointer types
  using RawPtr =
    oomwoo_msgs::msg::BumpEvent_<ContainerAllocator> *;
  using ConstRawPtr =
    const oomwoo_msgs::msg::BumpEvent_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<oomwoo_msgs::msg::BumpEvent_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<oomwoo_msgs::msg::BumpEvent_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      oomwoo_msgs::msg::BumpEvent_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<oomwoo_msgs::msg::BumpEvent_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      oomwoo_msgs::msg::BumpEvent_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<oomwoo_msgs::msg::BumpEvent_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<oomwoo_msgs::msg::BumpEvent_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<oomwoo_msgs::msg::BumpEvent_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__oomwoo_msgs__msg__BumpEvent
    std::shared_ptr<oomwoo_msgs::msg::BumpEvent_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__oomwoo_msgs__msg__BumpEvent
    std::shared_ptr<oomwoo_msgs::msg::BumpEvent_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const BumpEvent_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->contact != other.contact) {
      return false;
    }
    if (this->robot != other.robot) {
      return false;
    }
    if (this->approach != other.approach) {
      return false;
    }
    if (this->heading != other.heading) {
      return false;
    }
    if (this->side != other.side) {
      return false;
    }
    if (this->left_depress != other.left_depress) {
      return false;
    }
    if (this->right_depress != other.right_depress) {
      return false;
    }
    if (this->left_rate != other.left_rate) {
      return false;
    }
    if (this->right_rate != other.right_rate) {
      return false;
    }
    return true;
  }
  bool operator!=(const BumpEvent_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct BumpEvent_

// alias to use template instance with default allocator
using BumpEvent =
  oomwoo_msgs::msg::BumpEvent_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t BumpEvent_<ContainerAllocator>::SIDE_BOTH;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t BumpEvent_<ContainerAllocator>::SIDE_LEFT;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t BumpEvent_<ContainerAllocator>::SIDE_RIGHT;
#endif  // __cplusplus < 201703L

}  // namespace msg

}  // namespace oomwoo_msgs

#endif  // OOMWOO_MSGS__MSG__DETAIL__BUMP_EVENT__STRUCT_HPP_
