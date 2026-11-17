// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from oomwoo_localization_msgs:srv/Relocalize.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "oomwoo_localization_msgs/srv/relocalize.h"


#ifndef OOMWOO_LOCALIZATION_MSGS__SRV__DETAIL__RELOCALIZE__STRUCT_H_
#define OOMWOO_LOCALIZATION_MSGS__SRV__DETAIL__RELOCALIZE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/Relocalize in the package oomwoo_localization_msgs.
typedef struct oomwoo_localization_msgs__srv__Relocalize_Request
{
  uint8_t structure_needs_at_least_one_member;
} oomwoo_localization_msgs__srv__Relocalize_Request;

// Struct for a sequence of oomwoo_localization_msgs__srv__Relocalize_Request.
typedef struct oomwoo_localization_msgs__srv__Relocalize_Request__Sequence
{
  oomwoo_localization_msgs__srv__Relocalize_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} oomwoo_localization_msgs__srv__Relocalize_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'pose'
#include "geometry_msgs/msg/detail/pose_with_covariance_stamped__struct.h"
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/Relocalize in the package oomwoo_localization_msgs.
typedef struct oomwoo_localization_msgs__srv__Relocalize_Response
{
  /// confident, accepted fix
  bool success;
  /// best base-frame pose in map
  geometry_msgs__msg__PoseWithCovarianceStamped pose;
  /// summed match score
  float score;
  /// score / n_beams, in [0, 1]
  float score_normalized;
  /// (top1 - top2) / top1, in [0, 1]
  float confidence;
  /// search wall-clock time
  float runtime_s;
  /// human-readable summary
  rosidl_runtime_c__String message;
} oomwoo_localization_msgs__srv__Relocalize_Response;

// Struct for a sequence of oomwoo_localization_msgs__srv__Relocalize_Response.
typedef struct oomwoo_localization_msgs__srv__Relocalize_Response__Sequence
{
  oomwoo_localization_msgs__srv__Relocalize_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} oomwoo_localization_msgs__srv__Relocalize_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  oomwoo_localization_msgs__srv__Relocalize_Event__request__MAX_SIZE = 1
};
// response
enum
{
  oomwoo_localization_msgs__srv__Relocalize_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/Relocalize in the package oomwoo_localization_msgs.
typedef struct oomwoo_localization_msgs__srv__Relocalize_Event
{
  service_msgs__msg__ServiceEventInfo info;
  oomwoo_localization_msgs__srv__Relocalize_Request__Sequence request;
  oomwoo_localization_msgs__srv__Relocalize_Response__Sequence response;
} oomwoo_localization_msgs__srv__Relocalize_Event;

// Struct for a sequence of oomwoo_localization_msgs__srv__Relocalize_Event.
typedef struct oomwoo_localization_msgs__srv__Relocalize_Event__Sequence
{
  oomwoo_localization_msgs__srv__Relocalize_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} oomwoo_localization_msgs__srv__Relocalize_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // OOMWOO_LOCALIZATION_MSGS__SRV__DETAIL__RELOCALIZE__STRUCT_H_
