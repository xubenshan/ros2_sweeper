// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_cleaning_interfaces:srv/BeginCoverage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/srv/begin_coverage.hpp"


#ifndef ROBOT_CLEANING_INTERFACES__SRV__DETAIL__BEGIN_COVERAGE__STRUCT_HPP_
#define ROBOT_CLEANING_INTERFACES__SRV__DETAIL__BEGIN_COVERAGE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'start'
#include "geometry_msgs/msg/detail/pose_stamped__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__robot_cleaning_interfaces__srv__BeginCoverage_Request __attribute__((deprecated))
#else
# define DEPRECATED__robot_cleaning_interfaces__srv__BeginCoverage_Request __declspec(deprecated)
#endif

namespace robot_cleaning_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct BeginCoverage_Request_
{
  using Type = BeginCoverage_Request_<ContainerAllocator>;

  explicit BeginCoverage_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : start(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->task_id = "";
      this->restored_distance_m = 0.0;
    }
  }

  explicit BeginCoverage_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : task_id(_alloc),
    start(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->task_id = "";
      this->restored_distance_m = 0.0;
    }
  }

  // field types and members
  using _task_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _task_id_type task_id;
  using _regions_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _regions_type regions;
  using _start_type =
    geometry_msgs::msg::PoseStamped_<ContainerAllocator>;
  _start_type start;
  using _restored_grid_type =
    std::vector<int8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int8_t>>;
  _restored_grid_type restored_grid;
  using _restored_distance_m_type =
    double;
  _restored_distance_m_type restored_distance_m;

  // setters for named parameter idiom
  Type & set__task_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->task_id = _arg;
    return *this;
  }
  Type & set__regions(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->regions = _arg;
    return *this;
  }
  Type & set__start(
    const geometry_msgs::msg::PoseStamped_<ContainerAllocator> & _arg)
  {
    this->start = _arg;
    return *this;
  }
  Type & set__restored_grid(
    const std::vector<int8_t, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<int8_t>> & _arg)
  {
    this->restored_grid = _arg;
    return *this;
  }
  Type & set__restored_distance_m(
    const double & _arg)
  {
    this->restored_distance_m = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_cleaning_interfaces::srv::BeginCoverage_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_cleaning_interfaces::srv::BeginCoverage_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_cleaning_interfaces::srv::BeginCoverage_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_cleaning_interfaces::srv::BeginCoverage_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_cleaning_interfaces__srv__BeginCoverage_Request
    std::shared_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_cleaning_interfaces__srv__BeginCoverage_Request
    std::shared_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const BeginCoverage_Request_ & other) const
  {
    if (this->task_id != other.task_id) {
      return false;
    }
    if (this->regions != other.regions) {
      return false;
    }
    if (this->start != other.start) {
      return false;
    }
    if (this->restored_grid != other.restored_grid) {
      return false;
    }
    if (this->restored_distance_m != other.restored_distance_m) {
      return false;
    }
    return true;
  }
  bool operator!=(const BeginCoverage_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct BeginCoverage_Request_

// alias to use template instance with default allocator
using BeginCoverage_Request =
  robot_cleaning_interfaces::srv::BeginCoverage_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace robot_cleaning_interfaces


#ifndef _WIN32
# define DEPRECATED__robot_cleaning_interfaces__srv__BeginCoverage_Response __attribute__((deprecated))
#else
# define DEPRECATED__robot_cleaning_interfaces__srv__BeginCoverage_Response __declspec(deprecated)
#endif

namespace robot_cleaning_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct BeginCoverage_Response_
{
  using Type = BeginCoverage_Response_<ContainerAllocator>;

  explicit BeginCoverage_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->reason = "";
    }
  }

  explicit BeginCoverage_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : reason(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->reason = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _reason_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _reason_type reason;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__reason(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->reason = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_cleaning_interfaces::srv::BeginCoverage_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_cleaning_interfaces::srv::BeginCoverage_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_cleaning_interfaces::srv::BeginCoverage_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_cleaning_interfaces::srv::BeginCoverage_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_cleaning_interfaces__srv__BeginCoverage_Response
    std::shared_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_cleaning_interfaces__srv__BeginCoverage_Response
    std::shared_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const BeginCoverage_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->reason != other.reason) {
      return false;
    }
    return true;
  }
  bool operator!=(const BeginCoverage_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct BeginCoverage_Response_

// alias to use template instance with default allocator
using BeginCoverage_Response =
  robot_cleaning_interfaces::srv::BeginCoverage_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace robot_cleaning_interfaces


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__robot_cleaning_interfaces__srv__BeginCoverage_Event __attribute__((deprecated))
#else
# define DEPRECATED__robot_cleaning_interfaces__srv__BeginCoverage_Event __declspec(deprecated)
#endif

namespace robot_cleaning_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct BeginCoverage_Event_
{
  using Type = BeginCoverage_Event_<ContainerAllocator>;

  explicit BeginCoverage_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit BeginCoverage_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<robot_cleaning_interfaces::srv::BeginCoverage_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<robot_cleaning_interfaces::srv::BeginCoverage_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<robot_cleaning_interfaces::srv::BeginCoverage_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<robot_cleaning_interfaces::srv::BeginCoverage_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<robot_cleaning_interfaces::srv::BeginCoverage_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<robot_cleaning_interfaces::srv::BeginCoverage_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<robot_cleaning_interfaces::srv::BeginCoverage_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<robot_cleaning_interfaces::srv::BeginCoverage_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_cleaning_interfaces::srv::BeginCoverage_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_cleaning_interfaces::srv::BeginCoverage_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_cleaning_interfaces::srv::BeginCoverage_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_cleaning_interfaces::srv::BeginCoverage_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_cleaning_interfaces__srv__BeginCoverage_Event
    std::shared_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_cleaning_interfaces__srv__BeginCoverage_Event
    std::shared_ptr<robot_cleaning_interfaces::srv::BeginCoverage_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const BeginCoverage_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const BeginCoverage_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct BeginCoverage_Event_

// alias to use template instance with default allocator
using BeginCoverage_Event =
  robot_cleaning_interfaces::srv::BeginCoverage_Event_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace robot_cleaning_interfaces

namespace robot_cleaning_interfaces
{

namespace srv
{

struct BeginCoverage
{
  using Request = robot_cleaning_interfaces::srv::BeginCoverage_Request;
  using Response = robot_cleaning_interfaces::srv::BeginCoverage_Response;
  using Event = robot_cleaning_interfaces::srv::BeginCoverage_Event;
};

}  // namespace srv

}  // namespace robot_cleaning_interfaces

#endif  // ROBOT_CLEANING_INTERFACES__SRV__DETAIL__BEGIN_COVERAGE__STRUCT_HPP_
