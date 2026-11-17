// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_cleaning_interfaces:msg/CleaningEvent.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/msg/cleaning_event.h"


#ifndef ROBOT_CLEANING_INTERFACES__MSG__DETAIL__CLEANING_EVENT__STRUCT_H_
#define ROBOT_CLEANING_INTERFACES__MSG__DETAIL__CLEANING_EVENT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'INFO'.
enum
{
  robot_cleaning_interfaces__msg__CleaningEvent__INFO = 0
};

/// Constant 'WARNING'.
enum
{
  robot_cleaning_interfaces__msg__CleaningEvent__WARNING = 1
};

/// Constant 'ERROR'.
enum
{
  robot_cleaning_interfaces__msg__CleaningEvent__ERROR = 2
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'task_id'
// Member 'code'
// Member 'state'
// Member 'previous_state'
// Member 'message'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/CleaningEvent in the package robot_cleaning_interfaces.
typedef struct robot_cleaning_interfaces__msg__CleaningEvent
{
  std_msgs__msg__Header header;
  uint64_t sequence;
  uint8_t severity;
  rosidl_runtime_c__String task_id;
  rosidl_runtime_c__String code;
  rosidl_runtime_c__String state;
  rosidl_runtime_c__String previous_state;
  bool recoverable;
  rosidl_runtime_c__String message;
  float coverage;
  uint32_t completed_waypoints;
  uint32_t failed_waypoints;
  uint32_t total_waypoints;
} robot_cleaning_interfaces__msg__CleaningEvent;

// Struct for a sequence of robot_cleaning_interfaces__msg__CleaningEvent.
typedef struct robot_cleaning_interfaces__msg__CleaningEvent__Sequence
{
  robot_cleaning_interfaces__msg__CleaningEvent * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_cleaning_interfaces__msg__CleaningEvent__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_CLEANING_INTERFACES__MSG__DETAIL__CLEANING_EVENT__STRUCT_H_
