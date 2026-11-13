// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_cleaning_interfaces:srv/BeginCoverage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/srv/begin_coverage.hpp"


#ifndef ROBOT_CLEANING_INTERFACES__SRV__DETAIL__BEGIN_COVERAGE__TRAITS_HPP_
#define ROBOT_CLEANING_INTERFACES__SRV__DETAIL__BEGIN_COVERAGE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robot_cleaning_interfaces/srv/detail/begin_coverage__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'start'
#include "geometry_msgs/msg/detail/pose_stamped__traits.hpp"

namespace robot_cleaning_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const BeginCoverage_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: task_id
  {
    out << "task_id: ";
    rosidl_generator_traits::value_to_yaml(msg.task_id, out);
    out << ", ";
  }

  // member: regions
  {
    if (msg.regions.size() == 0) {
      out << "regions: []";
    } else {
      out << "regions: [";
      size_t pending_items = msg.regions.size();
      for (auto item : msg.regions) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: start
  {
    out << "start: ";
    to_flow_style_yaml(msg.start, out);
    out << ", ";
  }

  // member: restored_grid
  {
    if (msg.restored_grid.size() == 0) {
      out << "restored_grid: []";
    } else {
      out << "restored_grid: [";
      size_t pending_items = msg.restored_grid.size();
      for (auto item : msg.restored_grid) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: restored_distance_m
  {
    out << "restored_distance_m: ";
    rosidl_generator_traits::value_to_yaml(msg.restored_distance_m, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const BeginCoverage_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: task_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_id: ";
    rosidl_generator_traits::value_to_yaml(msg.task_id, out);
    out << "\n";
  }

  // member: regions
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.regions.size() == 0) {
      out << "regions: []\n";
    } else {
      out << "regions:\n";
      for (auto item : msg.regions) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: start
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "start:\n";
    to_block_style_yaml(msg.start, out, indentation + 2);
  }

  // member: restored_grid
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.restored_grid.size() == 0) {
      out << "restored_grid: []\n";
    } else {
      out << "restored_grid:\n";
      for (auto item : msg.restored_grid) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: restored_distance_m
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "restored_distance_m: ";
    rosidl_generator_traits::value_to_yaml(msg.restored_distance_m, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const BeginCoverage_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace robot_cleaning_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use robot_cleaning_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const robot_cleaning_interfaces::srv::BeginCoverage_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_cleaning_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_cleaning_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const robot_cleaning_interfaces::srv::BeginCoverage_Request & msg)
{
  return robot_cleaning_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<robot_cleaning_interfaces::srv::BeginCoverage_Request>()
{
  return "robot_cleaning_interfaces::srv::BeginCoverage_Request";
}

template<>
inline const char * name<robot_cleaning_interfaces::srv::BeginCoverage_Request>()
{
  return "robot_cleaning_interfaces/srv/BeginCoverage_Request";
}

template<>
struct has_fixed_size<robot_cleaning_interfaces::srv::BeginCoverage_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_cleaning_interfaces::srv::BeginCoverage_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robot_cleaning_interfaces::srv::BeginCoverage_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace robot_cleaning_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const BeginCoverage_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: reason
  {
    out << "reason: ";
    rosidl_generator_traits::value_to_yaml(msg.reason, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const BeginCoverage_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: reason
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "reason: ";
    rosidl_generator_traits::value_to_yaml(msg.reason, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const BeginCoverage_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace robot_cleaning_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use robot_cleaning_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const robot_cleaning_interfaces::srv::BeginCoverage_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_cleaning_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_cleaning_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const robot_cleaning_interfaces::srv::BeginCoverage_Response & msg)
{
  return robot_cleaning_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<robot_cleaning_interfaces::srv::BeginCoverage_Response>()
{
  return "robot_cleaning_interfaces::srv::BeginCoverage_Response";
}

template<>
inline const char * name<robot_cleaning_interfaces::srv::BeginCoverage_Response>()
{
  return "robot_cleaning_interfaces/srv/BeginCoverage_Response";
}

template<>
struct has_fixed_size<robot_cleaning_interfaces::srv::BeginCoverage_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_cleaning_interfaces::srv::BeginCoverage_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robot_cleaning_interfaces::srv::BeginCoverage_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace robot_cleaning_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const BeginCoverage_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const BeginCoverage_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const BeginCoverage_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace robot_cleaning_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use robot_cleaning_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const robot_cleaning_interfaces::srv::BeginCoverage_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_cleaning_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_cleaning_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const robot_cleaning_interfaces::srv::BeginCoverage_Event & msg)
{
  return robot_cleaning_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<robot_cleaning_interfaces::srv::BeginCoverage_Event>()
{
  return "robot_cleaning_interfaces::srv::BeginCoverage_Event";
}

template<>
inline const char * name<robot_cleaning_interfaces::srv::BeginCoverage_Event>()
{
  return "robot_cleaning_interfaces/srv/BeginCoverage_Event";
}

template<>
struct has_fixed_size<robot_cleaning_interfaces::srv::BeginCoverage_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_cleaning_interfaces::srv::BeginCoverage_Event>
  : std::integral_constant<bool, has_bounded_size<robot_cleaning_interfaces::srv::BeginCoverage_Request>::value && has_bounded_size<robot_cleaning_interfaces::srv::BeginCoverage_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<robot_cleaning_interfaces::srv::BeginCoverage_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<robot_cleaning_interfaces::srv::BeginCoverage>()
{
  return "robot_cleaning_interfaces::srv::BeginCoverage";
}

template<>
inline const char * name<robot_cleaning_interfaces::srv::BeginCoverage>()
{
  return "robot_cleaning_interfaces/srv/BeginCoverage";
}

template<>
struct has_fixed_size<robot_cleaning_interfaces::srv::BeginCoverage>
  : std::integral_constant<
    bool,
    has_fixed_size<robot_cleaning_interfaces::srv::BeginCoverage_Request>::value &&
    has_fixed_size<robot_cleaning_interfaces::srv::BeginCoverage_Response>::value
  >
{
};

template<>
struct has_bounded_size<robot_cleaning_interfaces::srv::BeginCoverage>
  : std::integral_constant<
    bool,
    has_bounded_size<robot_cleaning_interfaces::srv::BeginCoverage_Request>::value &&
    has_bounded_size<robot_cleaning_interfaces::srv::BeginCoverage_Response>::value
  >
{
};

template<>
struct is_service<robot_cleaning_interfaces::srv::BeginCoverage>
  : std::true_type
{
};

template<>
struct is_service_request<robot_cleaning_interfaces::srv::BeginCoverage_Request>
  : std::true_type
{
};

template<>
struct is_service_response<robot_cleaning_interfaces::srv::BeginCoverage_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_CLEANING_INTERFACES__SRV__DETAIL__BEGIN_COVERAGE__TRAITS_HPP_
