// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_cleaning_interfaces:srv/ListCleaningEvents.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/srv/list_cleaning_events.h"


#ifndef ROBOT_CLEANING_INTERFACES__SRV__DETAIL__LIST_CLEANING_EVENTS__STRUCT_H_
#define ROBOT_CLEANING_INTERFACES__SRV__DETAIL__LIST_CLEANING_EVENTS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'task_id_filter'
// Member 'code_filter'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/ListCleaningEvents in the package robot_cleaning_interfaces.
typedef struct robot_cleaning_interfaces__srv__ListCleaningEvents_Request
{
  uint32_t limit;
  rosidl_runtime_c__String task_id_filter;
  rosidl_runtime_c__String code_filter;
} robot_cleaning_interfaces__srv__ListCleaningEvents_Request;

// Struct for a sequence of robot_cleaning_interfaces__srv__ListCleaningEvents_Request.
typedef struct robot_cleaning_interfaces__srv__ListCleaningEvents_Request__Sequence
{
  robot_cleaning_interfaces__srv__ListCleaningEvents_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_cleaning_interfaces__srv__ListCleaningEvents_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"
// Member 'events'
#include "robot_cleaning_interfaces/msg/detail/cleaning_event__struct.h"

/// Struct defined in srv/ListCleaningEvents in the package robot_cleaning_interfaces.
typedef struct robot_cleaning_interfaces__srv__ListCleaningEvents_Response
{
  bool success;
  rosidl_runtime_c__String message;
  robot_cleaning_interfaces__msg__CleaningEvent__Sequence events;
} robot_cleaning_interfaces__srv__ListCleaningEvents_Response;

// Struct for a sequence of robot_cleaning_interfaces__srv__ListCleaningEvents_Response.
typedef struct robot_cleaning_interfaces__srv__ListCleaningEvents_Response__Sequence
{
  robot_cleaning_interfaces__srv__ListCleaningEvents_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_cleaning_interfaces__srv__ListCleaningEvents_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  robot_cleaning_interfaces__srv__ListCleaningEvents_Event__request__MAX_SIZE = 1
};
// response
enum
{
  robot_cleaning_interfaces__srv__ListCleaningEvents_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/ListCleaningEvents in the package robot_cleaning_interfaces.
typedef struct robot_cleaning_interfaces__srv__ListCleaningEvents_Event
{
  service_msgs__msg__ServiceEventInfo info;
  robot_cleaning_interfaces__srv__ListCleaningEvents_Request__Sequence request;
  robot_cleaning_interfaces__srv__ListCleaningEvents_Response__Sequence response;
} robot_cleaning_interfaces__srv__ListCleaningEvents_Event;

// Struct for a sequence of robot_cleaning_interfaces__srv__ListCleaningEvents_Event.
typedef struct robot_cleaning_interfaces__srv__ListCleaningEvents_Event__Sequence
{
  robot_cleaning_interfaces__srv__ListCleaningEvents_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_cleaning_interfaces__srv__ListCleaningEvents_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_CLEANING_INTERFACES__SRV__DETAIL__LIST_CLEANING_EVENTS__STRUCT_H_
