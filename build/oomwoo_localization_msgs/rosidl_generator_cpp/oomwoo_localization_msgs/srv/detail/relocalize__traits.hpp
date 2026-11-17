// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from oomwoo_localization_msgs:srv/Relocalize.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "oomwoo_localization_msgs/srv/relocalize.hpp"


#ifndef OOMWOO_LOCALIZATION_MSGS__SRV__DETAIL__RELOCALIZE__TRAITS_HPP_
#define OOMWOO_LOCALIZATION_MSGS__SRV__DETAIL__RELOCALIZE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "oomwoo_localization_msgs/srv/detail/relocalize__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace oomwoo_localization_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const Relocalize_Request & msg,
  std::ostream & out)
{
  (void)msg;
  out << "null";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Relocalize_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  (void)msg;
  (void)indentation;
  out << "null\n";
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Relocalize_Request & msg, bool use_flow_style = false)
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

}  // namespace oomwoo_localization_msgs

namespace rosidl_generator_traits
{

[[deprecated("use oomwoo_localization_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const oomwoo_localization_msgs::srv::Relocalize_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  oomwoo_localization_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use oomwoo_localization_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const oomwoo_localization_msgs::srv::Relocalize_Request & msg)
{
  return oomwoo_localization_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<oomwoo_localization_msgs::srv::Relocalize_Request>()
{
  return "oomwoo_localization_msgs::srv::Relocalize_Request";
}

template<>
inline const char * name<oomwoo_localization_msgs::srv::Relocalize_Request>()
{
  return "oomwoo_localization_msgs/srv/Relocalize_Request";
}

template<>
struct has_fixed_size<oomwoo_localization_msgs::srv::Relocalize_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<oomwoo_localization_msgs::srv::Relocalize_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<oomwoo_localization_msgs::srv::Relocalize_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose_with_covariance_stamped__traits.hpp"

namespace oomwoo_localization_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const Relocalize_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: pose
  {
    out << "pose: ";
    to_flow_style_yaml(msg.pose, out);
    out << ", ";
  }

  // member: score
  {
    out << "score: ";
    rosidl_generator_traits::value_to_yaml(msg.score, out);
    out << ", ";
  }

  // member: score_normalized
  {
    out << "score_normalized: ";
    rosidl_generator_traits::value_to_yaml(msg.score_normalized, out);
    out << ", ";
  }

  // member: confidence
  {
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << ", ";
  }

  // member: runtime_s
  {
    out << "runtime_s: ";
    rosidl_generator_traits::value_to_yaml(msg.runtime_s, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Relocalize_Response & msg,
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

  // member: pose
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose:\n";
    to_block_style_yaml(msg.pose, out, indentation + 2);
  }

  // member: score
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "score: ";
    rosidl_generator_traits::value_to_yaml(msg.score, out);
    out << "\n";
  }

  // member: score_normalized
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "score_normalized: ";
    rosidl_generator_traits::value_to_yaml(msg.score_normalized, out);
    out << "\n";
  }

  // member: confidence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << "\n";
  }

  // member: runtime_s
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "runtime_s: ";
    rosidl_generator_traits::value_to_yaml(msg.runtime_s, out);
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
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Relocalize_Response & msg, bool use_flow_style = false)
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

}  // namespace oomwoo_localization_msgs

namespace rosidl_generator_traits
{

[[deprecated("use oomwoo_localization_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const oomwoo_localization_msgs::srv::Relocalize_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  oomwoo_localization_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use oomwoo_localization_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const oomwoo_localization_msgs::srv::Relocalize_Response & msg)
{
  return oomwoo_localization_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<oomwoo_localization_msgs::srv::Relocalize_Response>()
{
  return "oomwoo_localization_msgs::srv::Relocalize_Response";
}

template<>
inline const char * name<oomwoo_localization_msgs::srv::Relocalize_Response>()
{
  return "oomwoo_localization_msgs/srv/Relocalize_Response";
}

template<>
struct has_fixed_size<oomwoo_localization_msgs::srv::Relocalize_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<oomwoo_localization_msgs::srv::Relocalize_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<oomwoo_localization_msgs::srv::Relocalize_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace oomwoo_localization_msgs
{

namespace srv
{

inline void to_flow_style_yaml(
  const Relocalize_Event & msg,
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
  const Relocalize_Event & msg,
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

inline std::string to_yaml(const Relocalize_Event & msg, bool use_flow_style = false)
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

}  // namespace oomwoo_localization_msgs

namespace rosidl_generator_traits
{

[[deprecated("use oomwoo_localization_msgs::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const oomwoo_localization_msgs::srv::Relocalize_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  oomwoo_localization_msgs::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use oomwoo_localization_msgs::srv::to_yaml() instead")]]
inline std::string to_yaml(const oomwoo_localization_msgs::srv::Relocalize_Event & msg)
{
  return oomwoo_localization_msgs::srv::to_yaml(msg);
}

template<>
inline const char * data_type<oomwoo_localization_msgs::srv::Relocalize_Event>()
{
  return "oomwoo_localization_msgs::srv::Relocalize_Event";
}

template<>
inline const char * name<oomwoo_localization_msgs::srv::Relocalize_Event>()
{
  return "oomwoo_localization_msgs/srv/Relocalize_Event";
}

template<>
struct has_fixed_size<oomwoo_localization_msgs::srv::Relocalize_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<oomwoo_localization_msgs::srv::Relocalize_Event>
  : std::integral_constant<bool, has_bounded_size<oomwoo_localization_msgs::srv::Relocalize_Request>::value && has_bounded_size<oomwoo_localization_msgs::srv::Relocalize_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<oomwoo_localization_msgs::srv::Relocalize_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<oomwoo_localization_msgs::srv::Relocalize>()
{
  return "oomwoo_localization_msgs::srv::Relocalize";
}

template<>
inline const char * name<oomwoo_localization_msgs::srv::Relocalize>()
{
  return "oomwoo_localization_msgs/srv/Relocalize";
}

template<>
struct has_fixed_size<oomwoo_localization_msgs::srv::Relocalize>
  : std::integral_constant<
    bool,
    has_fixed_size<oomwoo_localization_msgs::srv::Relocalize_Request>::value &&
    has_fixed_size<oomwoo_localization_msgs::srv::Relocalize_Response>::value
  >
{
};

template<>
struct has_bounded_size<oomwoo_localization_msgs::srv::Relocalize>
  : std::integral_constant<
    bool,
    has_bounded_size<oomwoo_localization_msgs::srv::Relocalize_Request>::value &&
    has_bounded_size<oomwoo_localization_msgs::srv::Relocalize_Response>::value
  >
{
};

template<>
struct is_service<oomwoo_localization_msgs::srv::Relocalize>
  : std::true_type
{
};

template<>
struct is_service_request<oomwoo_localization_msgs::srv::Relocalize_Request>
  : std::true_type
{
};

template<>
struct is_service_response<oomwoo_localization_msgs::srv::Relocalize_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // OOMWOO_LOCALIZATION_MSGS__SRV__DETAIL__RELOCALIZE__TRAITS_HPP_
