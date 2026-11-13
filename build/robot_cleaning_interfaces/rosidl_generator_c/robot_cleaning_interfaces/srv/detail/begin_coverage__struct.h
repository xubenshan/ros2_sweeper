// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_cleaning_interfaces:srv/BeginCoverage.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/srv/begin_coverage.h"


#ifndef ROBOT_CLEANING_INTERFACES__SRV__DETAIL__BEGIN_COVERAGE__STRUCT_H_
#define ROBOT_CLEANING_INTERFACES__SRV__DETAIL__BEGIN_COVERAGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'task_id'
// Member 'regions'
#include "rosidl_runtime_c/string.h"
// Member 'start'
#include "geometry_msgs/msg/detail/pose_stamped__struct.h"
// Member 'restored_grid'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in srv/BeginCoverage in the package robot_cleaning_interfaces.
typedef struct robot_cleaning_interfaces__srv__BeginCoverage_Request
{
  rosidl_runtime_c__String task_id;
  rosidl_runtime_c__String__Sequence regions;
  geometry_msgs__msg__PoseStamped start;
  rosidl_runtime_c__int8__Sequence restored_grid;
  double restored_distance_m;
} robot_cleaning_interfaces__srv__BeginCoverage_Request;

// Struct for a sequence of robot_cleaning_interfaces__srv__BeginCoverage_Request.
typedef struct robot_cleaning_interfaces__srv__BeginCoverage_Request__Sequence
{
  robot_cleaning_interfaces__srv__BeginCoverage_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_cleaning_interfaces__srv__BeginCoverage_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'reason'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/BeginCoverage in the package robot_cleaning_interfaces.
typedef struct robot_cleaning_interfaces__srv__BeginCoverage_Response
{
  bool success;
  rosidl_runtime_c__String reason;
} robot_cleaning_interfaces__srv__BeginCoverage_Response;

// Struct for a sequence of robot_cleaning_interfaces__srv__BeginCoverage_Response.
typedef struct robot_cleaning_interfaces__srv__BeginCoverage_Response__Sequence
{
  robot_cleaning_interfaces__srv__BeginCoverage_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_cleaning_interfaces__srv__BeginCoverage_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  robot_cleaning_interfaces__srv__BeginCoverage_Event__request__MAX_SIZE = 1
};
// response
enum
{
  robot_cleaning_interfaces__srv__BeginCoverage_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/BeginCoverage in the package robot_cleaning_interfaces.
typedef struct robot_cleaning_interfaces__srv__BeginCoverage_Event
{
  service_msgs__msg__ServiceEventInfo info;
  robot_cleaning_interfaces__srv__BeginCoverage_Request__Sequence request;
  robot_cleaning_interfaces__srv__BeginCoverage_Response__Sequence response;
} robot_cleaning_interfaces__srv__BeginCoverage_Event;

// Struct for a sequence of robot_cleaning_interfaces__srv__BeginCoverage_Event.
typedef struct robot_cleaning_interfaces__srv__BeginCoverage_Event__Sequence
{
  robot_cleaning_interfaces__srv__BeginCoverage_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_cleaning_interfaces__srv__BeginCoverage_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_CLEANING_INTERFACES__SRV__DETAIL__BEGIN_COVERAGE__STRUCT_H_
