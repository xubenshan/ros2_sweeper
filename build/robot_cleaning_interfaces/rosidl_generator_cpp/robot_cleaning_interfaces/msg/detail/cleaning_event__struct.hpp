// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_cleaning_interfaces:msg/CleaningEvent.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/msg/cleaning_event.hpp"


#ifndef ROBOT_CLEANING_INTERFACES__MSG__DETAIL__CLEANING_EVENT__STRUCT_HPP_
#define ROBOT_CLEANING_INTERFACES__MSG__DETAIL__CLEANING_EVENT__STRUCT_HPP_

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
# define DEPRECATED__robot_cleaning_interfaces__msg__CleaningEvent __attribute__((deprecated))
#else
# define DEPRECATED__robot_cleaning_interfaces__msg__CleaningEvent __declspec(deprecated)
#endif

namespace robot_cleaning_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct CleaningEvent_
{
  using Type = CleaningEvent_<ContainerAllocator>;

  explicit CleaningEvent_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sequence = 0ull;
      this->severity = 0;
      this->task_id = "";
      this->code = "";
      this->state = "";
      this->previous_state = "";
      this->recoverable = false;
      this->message = "";
      this->coverage = 0.0f;
      this->completed_waypoints = 0ul;
      this->failed_waypoints = 0ul;
      this->total_waypoints = 0ul;
    }
  }

  explicit CleaningEvent_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    task_id(_alloc),
    code(_alloc),
    state(_alloc),
    previous_state(_alloc),
    message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->sequence = 0ull;
      this->severity = 0;
      this->task_id = "";
      this->code = "";
      this->state = "";
      this->previous_state = "";
      this->recoverable = false;
      this->message = "";
      this->coverage = 0.0f;
      this->completed_waypoints = 0ul;
      this->failed_waypoints = 0ul;
      this->total_waypoints = 0ul;
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _sequence_type =
    uint64_t;
  _sequence_type sequence;
  using _severity_type =
    uint8_t;
  _severity_type severity;
  using _task_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _task_id_type task_id;
  using _code_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _code_type code;
  using _state_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _state_type state;
  using _previous_state_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _previous_state_type previous_state;
  using _recoverable_type =
    bool;
  _recoverable_type recoverable;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;
  using _coverage_type =
    float;
  _coverage_type coverage;
  using _completed_waypoints_type =
    uint32_t;
  _completed_waypoints_type completed_waypoints;
  using _failed_waypoints_type =
    uint32_t;
  _failed_waypoints_type failed_waypoints;
  using _total_waypoints_type =
    uint32_t;
  _total_waypoints_type total_waypoints;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__sequence(
    const uint64_t & _arg)
  {
    this->sequence = _arg;
    return *this;
  }
  Type & set__severity(
    const uint8_t & _arg)
  {
    this->severity = _arg;
    return *this;
  }
  Type & set__task_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->task_id = _arg;
    return *this;
  }
  Type & set__code(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->code = _arg;
    return *this;
  }
  Type & set__state(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->state = _arg;
    return *this;
  }
  Type & set__previous_state(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->previous_state = _arg;
    return *this;
  }
  Type & set__recoverable(
    const bool & _arg)
  {
    this->recoverable = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }
  Type & set__coverage(
    const float & _arg)
  {
    this->coverage = _arg;
    return *this;
  }
  Type & set__completed_waypoints(
    const uint32_t & _arg)
  {
    this->completed_waypoints = _arg;
    return *this;
  }
  Type & set__failed_waypoints(
    const uint32_t & _arg)
  {
    this->failed_waypoints = _arg;
    return *this;
  }
  Type & set__total_waypoints(
    const uint32_t & _arg)
  {
    this->total_waypoints = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t INFO =
    0u;
  static constexpr uint8_t WARNING =
    1u;
  // guard against 'ERROR' being predefined by MSVC by temporarily undefining it
#if defined(_WIN32)
#  if defined(ERROR)
#    pragma push_macro("ERROR")
#    undef ERROR
#  endif
#endif
  static constexpr uint8_t ERROR =
    2u;
#if defined(_WIN32)
#  pragma warning(suppress : 4602)
#  pragma pop_macro("ERROR")
#endif

  // pointer types
  using RawPtr =
    robot_cleaning_interfaces::msg::CleaningEvent_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_cleaning_interfaces::msg::CleaningEvent_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_cleaning_interfaces::msg::CleaningEvent_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_cleaning_interfaces::msg::CleaningEvent_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_cleaning_interfaces::msg::CleaningEvent_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_cleaning_interfaces::msg::CleaningEvent_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_cleaning_interfaces::msg::CleaningEvent_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_cleaning_interfaces::msg::CleaningEvent_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_cleaning_interfaces::msg::CleaningEvent_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_cleaning_interfaces::msg::CleaningEvent_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_cleaning_interfaces__msg__CleaningEvent
    std::shared_ptr<robot_cleaning_interfaces::msg::CleaningEvent_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_cleaning_interfaces__msg__CleaningEvent
    std::shared_ptr<robot_cleaning_interfaces::msg::CleaningEvent_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const CleaningEvent_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->sequence != other.sequence) {
      return false;
    }
    if (this->severity != other.severity) {
      return false;
    }
    if (this->task_id != other.task_id) {
      return false;
    }
    if (this->code != other.code) {
      return false;
    }
    if (this->state != other.state) {
      return false;
    }
    if (this->previous_state != other.previous_state) {
      return false;
    }
    if (this->recoverable != other.recoverable) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    if (this->coverage != other.coverage) {
      return false;
    }
    if (this->completed_waypoints != other.completed_waypoints) {
      return false;
    }
    if (this->failed_waypoints != other.failed_waypoints) {
      return false;
    }
    if (this->total_waypoints != other.total_waypoints) {
      return false;
    }
    return true;
  }
  bool operator!=(const CleaningEvent_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct CleaningEvent_

// alias to use template instance with default allocator
using CleaningEvent =
  robot_cleaning_interfaces::msg::CleaningEvent_<std::allocator<void>>;

// constant definitions
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t CleaningEvent_<ContainerAllocator>::INFO;
#endif  // __cplusplus < 201703L
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t CleaningEvent_<ContainerAllocator>::WARNING;
#endif  // __cplusplus < 201703L
// guard against 'ERROR' being predefined by MSVC by temporarily undefining it
#if defined(_WIN32)
#  if defined(ERROR)
#    pragma push_macro("ERROR")
#    undef ERROR
#  endif
#endif
#if __cplusplus < 201703L
// static constexpr member variable definitions are only needed in C++14 and below, deprecated in C++17
template<typename ContainerAllocator>
constexpr uint8_t CleaningEvent_<ContainerAllocator>::ERROR;
#endif  // __cplusplus < 201703L
#if defined(_WIN32)
#  pragma warning(suppress : 4602)
#  pragma pop_macro("ERROR")
#endif

}  // namespace msg

}  // namespace robot_cleaning_interfaces

#endif  // ROBOT_CLEANING_INTERFACES__MSG__DETAIL__CLEANING_EVENT__STRUCT_HPP_
