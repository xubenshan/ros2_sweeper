// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_cleaning_interfaces:srv/PlanCoverage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/srv/plan_coverage.hpp"


#ifndef ROBOT_CLEANING_INTERFACES__SRV__DETAIL__PLAN_COVERAGE__TRAITS_HPP_
#define ROBOT_CLEANING_INTERFACES__SRV__DETAIL__PLAN_COVERAGE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robot_cleaning_interfaces/srv/detail/plan_coverage__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'start'
#include "geometry_msgs/msg/detail/pose_stamped__traits.hpp"
// Member 'covered'
#include "nav_msgs/msg/detail/occupancy_grid__traits.hpp"
// Member 'excluded'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace robot_cleaning_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const PlanCoverage_Request & msg,
  std::ostream & out)
{
  out << "{";
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

  // member: gap_fill
  {
    out << "gap_fill: ";
    rosidl_generator_traits::value_to_yaml(msg.gap_fill, out);
    out << ", ";
  }

  // member: target_coverage
  {
    out << "target_coverage: ";
    rosidl_generator_traits::value_to_yaml(msg.target_coverage, out);
    out << ", ";
  }

  // member: distance_budget_m
  {
    out << "distance_budget_m: ";
    rosidl_generator_traits::value_to_yaml(msg.distance_budget_m, out);
    out << ", ";
  }

  // member: covered
  {
    out << "covered: ";
    to_flow_style_yaml(msg.covered, out);
    out << ", ";
  }

  // member: excluded
  {
    if (msg.excluded.size() == 0) {
      out << "excluded: []";
    } else {
      out << "excluded: [";
      size_t pending_items = msg.excluded.size();
      for (auto item : msg.excluded) {
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
  const PlanCoverage_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
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

  // member: gap_fill
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "gap_fill: ";
    rosidl_generator_traits::value_to_yaml(msg.gap_fill, out);
    out << "\n";
  }

  // member: target_coverage
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target_coverage: ";
    rosidl_generator_traits::value_to_yaml(msg.target_coverage, out);
    out << "\n";
  }

  // member: distance_budget_m
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "distance_budget_m: ";
    rosidl_generator_traits::value_to_yaml(msg.distance_budget_m, out);
    out << "\n";
  }

  // member: covered
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "covered:\n";
    to_block_style_yaml(msg.covered, out, indentation + 2);
  }

  // member: excluded
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.excluded.size() == 0) {
      out << "excluded: []\n";
    } else {
      out << "excluded:\n";
      for (auto item : msg.excluded) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PlanCoverage_Request & msg, bool use_flow_style = false)
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
  const robot_cleaning_interfaces::srv::PlanCoverage_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_cleaning_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_cleaning_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const robot_cleaning_interfaces::srv::PlanCoverage_Request & msg)
{
  return robot_cleaning_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<robot_cleaning_interfaces::srv::PlanCoverage_Request>()
{
  return "robot_cleaning_interfaces::srv::PlanCoverage_Request";
}

template<>
inline const char * name<robot_cleaning_interfaces::srv::PlanCoverage_Request>()
{
  return "robot_cleaning_interfaces/srv/PlanCoverage_Request";
}

template<>
struct has_fixed_size<robot_cleaning_interfaces::srv::PlanCoverage_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_cleaning_interfaces::srv::PlanCoverage_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robot_cleaning_interfaces::srv::PlanCoverage_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'path'
#include "nav_msgs/msg/detail/path__traits.hpp"

namespace robot_cleaning_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const PlanCoverage_Response & msg,
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
    out << ", ";
  }

  // member: path
  {
    out << "path: ";
    to_flow_style_yaml(msg.path, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const PlanCoverage_Response & msg,
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

  // member: path
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "path:\n";
    to_block_style_yaml(msg.path, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const PlanCoverage_Response & msg, bool use_flow_style = false)
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
  const robot_cleaning_interfaces::srv::PlanCoverage_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_cleaning_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_cleaning_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const robot_cleaning_interfaces::srv::PlanCoverage_Response & msg)
{
  return robot_cleaning_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<robot_cleaning_interfaces::srv::PlanCoverage_Response>()
{
  return "robot_cleaning_interfaces::srv::PlanCoverage_Response";
}

template<>
inline const char * name<robot_cleaning_interfaces::srv::PlanCoverage_Response>()
{
  return "robot_cleaning_interfaces/srv/PlanCoverage_Response";
}

template<>
struct has_fixed_size<robot_cleaning_interfaces::srv::PlanCoverage_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_cleaning_interfaces::srv::PlanCoverage_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robot_cleaning_interfaces::srv::PlanCoverage_Response>
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
  const PlanCoverage_Event & msg,
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
  const PlanCoverage_Event & msg,
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

inline std::string to_yaml(const PlanCoverage_Event & msg, bool use_flow_style = false)
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
  const robot_cleaning_interfaces::srv::PlanCoverage_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_cleaning_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_cleaning_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const robot_cleaning_interfaces::srv::PlanCoverage_Event & msg)
{
  return robot_cleaning_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<robot_cleaning_interfaces::srv::PlanCoverage_Event>()
{
  return "robot_cleaning_interfaces::srv::PlanCoverage_Event";
}

template<>
inline const char * name<robot_cleaning_interfaces::srv::PlanCoverage_Event>()
{
  return "robot_cleaning_interfaces/srv/PlanCoverage_Event";
}

template<>
struct has_fixed_size<robot_cleaning_interfaces::srv::PlanCoverage_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_cleaning_interfaces::srv::PlanCoverage_Event>
  : std::integral_constant<bool, has_bounded_size<robot_cleaning_interfaces::srv::PlanCoverage_Request>::value && has_bounded_size<robot_cleaning_interfaces::srv::PlanCoverage_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<robot_cleaning_interfaces::srv::PlanCoverage_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<robot_cleaning_interfaces::srv::PlanCoverage>()
{
  return "robot_cleaning_interfaces::srv::PlanCoverage";
}

template<>
inline const char * name<robot_cleaning_interfaces::srv::PlanCoverage>()
{
  return "robot_cleaning_interfaces/srv/PlanCoverage";
}

template<>
struct has_fixed_size<robot_cleaning_interfaces::srv::PlanCoverage>
  : std::integral_constant<
    bool,
    has_fixed_size<robot_cleaning_interfaces::srv::PlanCoverage_Request>::value &&
    has_fixed_size<robot_cleaning_interfaces::srv::PlanCoverage_Response>::value
  >
{
};

template<>
struct has_bounded_size<robot_cleaning_interfaces::srv::PlanCoverage>
  : std::integral_constant<
    bool,
    has_bounded_size<robot_cleaning_interfaces::srv::PlanCoverage_Request>::value &&
    has_bounded_size<robot_cleaning_interfaces::srv::PlanCoverage_Response>::value
  >
{
};

template<>
struct is_service<robot_cleaning_interfaces::srv::PlanCoverage>
  : std::true_type
{
};

template<>
struct is_service_request<robot_cleaning_interfaces::srv::PlanCoverage_Request>
  : std::true_type
{
};

template<>
struct is_service_response<robot_cleaning_interfaces::srv::PlanCoverage_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_CLEANING_INTERFACES__SRV__DETAIL__PLAN_COVERAGE__TRAITS_HPP_
