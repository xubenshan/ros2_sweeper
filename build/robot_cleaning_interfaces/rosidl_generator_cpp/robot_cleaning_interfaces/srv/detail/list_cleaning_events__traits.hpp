// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_cleaning_interfaces:srv/ListCleaningEvents.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/srv/list_cleaning_events.hpp"


#ifndef ROBOT_CLEANING_INTERFACES__SRV__DETAIL__LIST_CLEANING_EVENTS__TRAITS_HPP_
#define ROBOT_CLEANING_INTERFACES__SRV__DETAIL__LIST_CLEANING_EVENTS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robot_cleaning_interfaces/srv/detail/list_cleaning_events__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace robot_cleaning_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const ListCleaningEvents_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: limit
  {
    out << "limit: ";
    rosidl_generator_traits::value_to_yaml(msg.limit, out);
    out << ", ";
  }

  // member: task_id_filter
  {
    out << "task_id_filter: ";
    rosidl_generator_traits::value_to_yaml(msg.task_id_filter, out);
    out << ", ";
  }

  // member: code_filter
  {
    out << "code_filter: ";
    rosidl_generator_traits::value_to_yaml(msg.code_filter, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ListCleaningEvents_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: limit
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "limit: ";
    rosidl_generator_traits::value_to_yaml(msg.limit, out);
    out << "\n";
  }

  // member: task_id_filter
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "task_id_filter: ";
    rosidl_generator_traits::value_to_yaml(msg.task_id_filter, out);
    out << "\n";
  }

  // member: code_filter
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "code_filter: ";
    rosidl_generator_traits::value_to_yaml(msg.code_filter, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ListCleaningEvents_Request & msg, bool use_flow_style = false)
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
  const robot_cleaning_interfaces::srv::ListCleaningEvents_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_cleaning_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_cleaning_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const robot_cleaning_interfaces::srv::ListCleaningEvents_Request & msg)
{
  return robot_cleaning_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<robot_cleaning_interfaces::srv::ListCleaningEvents_Request>()
{
  return "robot_cleaning_interfaces::srv::ListCleaningEvents_Request";
}

template<>
inline const char * name<robot_cleaning_interfaces::srv::ListCleaningEvents_Request>()
{
  return "robot_cleaning_interfaces/srv/ListCleaningEvents_Request";
}

template<>
struct has_fixed_size<robot_cleaning_interfaces::srv::ListCleaningEvents_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_cleaning_interfaces::srv::ListCleaningEvents_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robot_cleaning_interfaces::srv::ListCleaningEvents_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'events'
#include "robot_cleaning_interfaces/msg/detail/cleaning_event__traits.hpp"

namespace robot_cleaning_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const ListCleaningEvents_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << ", ";
  }

  // member: events
  {
    if (msg.events.size() == 0) {
      out << "events: []";
    } else {
      out << "events: [";
      size_t pending_items = msg.events.size();
      for (auto item : msg.events) {
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
  const ListCleaningEvents_Response & msg,
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

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }

  // member: events
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.events.size() == 0) {
      out << "events: []\n";
    } else {
      out << "events:\n";
      for (auto item : msg.events) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ListCleaningEvents_Response & msg, bool use_flow_style = false)
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
  const robot_cleaning_interfaces::srv::ListCleaningEvents_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_cleaning_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_cleaning_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const robot_cleaning_interfaces::srv::ListCleaningEvents_Response & msg)
{
  return robot_cleaning_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<robot_cleaning_interfaces::srv::ListCleaningEvents_Response>()
{
  return "robot_cleaning_interfaces::srv::ListCleaningEvents_Response";
}

template<>
inline const char * name<robot_cleaning_interfaces::srv::ListCleaningEvents_Response>()
{
  return "robot_cleaning_interfaces/srv/ListCleaningEvents_Response";
}

template<>
struct has_fixed_size<robot_cleaning_interfaces::srv::ListCleaningEvents_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_cleaning_interfaces::srv::ListCleaningEvents_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robot_cleaning_interfaces::srv::ListCleaningEvents_Response>
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
  const ListCleaningEvents_Event & msg,
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
  const ListCleaningEvents_Event & msg,
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

inline std::string to_yaml(const ListCleaningEvents_Event & msg, bool use_flow_style = false)
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
  const robot_cleaning_interfaces::srv::ListCleaningEvents_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_cleaning_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_cleaning_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const robot_cleaning_interfaces::srv::ListCleaningEvents_Event & msg)
{
  return robot_cleaning_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<robot_cleaning_interfaces::srv::ListCleaningEvents_Event>()
{
  return "robot_cleaning_interfaces::srv::ListCleaningEvents_Event";
}

template<>
inline const char * name<robot_cleaning_interfaces::srv::ListCleaningEvents_Event>()
{
  return "robot_cleaning_interfaces/srv/ListCleaningEvents_Event";
}

template<>
struct has_fixed_size<robot_cleaning_interfaces::srv::ListCleaningEvents_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_cleaning_interfaces::srv::ListCleaningEvents_Event>
  : std::integral_constant<bool, has_bounded_size<robot_cleaning_interfaces::srv::ListCleaningEvents_Request>::value && has_bounded_size<robot_cleaning_interfaces::srv::ListCleaningEvents_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<robot_cleaning_interfaces::srv::ListCleaningEvents_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<robot_cleaning_interfaces::srv::ListCleaningEvents>()
{
  return "robot_cleaning_interfaces::srv::ListCleaningEvents";
}

template<>
inline const char * name<robot_cleaning_interfaces::srv::ListCleaningEvents>()
{
  return "robot_cleaning_interfaces/srv/ListCleaningEvents";
}

template<>
struct has_fixed_size<robot_cleaning_interfaces::srv::ListCleaningEvents>
  : std::integral_constant<
    bool,
    has_fixed_size<robot_cleaning_interfaces::srv::ListCleaningEvents_Request>::value &&
    has_fixed_size<robot_cleaning_interfaces::srv::ListCleaningEvents_Response>::value
  >
{
};

template<>
struct has_bounded_size<robot_cleaning_interfaces::srv::ListCleaningEvents>
  : std::integral_constant<
    bool,
    has_bounded_size<robot_cleaning_interfaces::srv::ListCleaningEvents_Request>::value &&
    has_bounded_size<robot_cleaning_interfaces::srv::ListCleaningEvents_Response>::value
  >
{
};

template<>
struct is_service<robot_cleaning_interfaces::srv::ListCleaningEvents>
  : std::true_type
{
};

template<>
struct is_service_request<robot_cleaning_interfaces::srv::ListCleaningEvents_Request>
  : std::true_type
{
};

template<>
struct is_service_response<robot_cleaning_interfaces::srv::ListCleaningEvents_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_CLEANING_INTERFACES__SRV__DETAIL__LIST_CLEANING_EVENTS__TRAITS_HPP_
