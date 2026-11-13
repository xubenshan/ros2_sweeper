// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_cleaning_interfaces:action/CleanTask.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/action/clean_task.h"


#ifndef ROBOT_CLEANING_INTERFACES__ACTION__DETAIL__CLEAN_TASK__STRUCT_H_
#define ROBOT_CLEANING_INTERFACES__ACTION__DETAIL__CLEAN_TASK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'ALL'.
enum
{
  robot_cleaning_interfaces__action__CleanTask_Goal__ALL = 0
};

/// Constant 'REGIONS'.
enum
{
  robot_cleaning_interfaces__action__CleanTask_Goal__REGIONS = 1
};

// Include directives for member types
// Member 'task_id'
// Member 'regions'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/CleanTask in the package robot_cleaning_interfaces.
typedef struct robot_cleaning_interfaces__action__CleanTask_Goal
{
  rosidl_runtime_c__String task_id;
  uint8_t mode;
  rosidl_runtime_c__String__Sequence regions;
  float target_coverage;
  bool resume_checkpoint;
} robot_cleaning_interfaces__action__CleanTask_Goal;

// Struct for a sequence of robot_cleaning_interfaces__action__CleanTask_Goal.
typedef struct robot_cleaning_interfaces__action__CleanTask_Goal__Sequence
{
  robot_cleaning_interfaces__action__CleanTask_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_cleaning_interfaces__action__CleanTask_Goal__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'reason'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/CleanTask in the package robot_cleaning_interfaces.
typedef struct robot_cleaning_interfaces__action__CleanTask_Result
{
  bool success;
  rosidl_runtime_c__String reason;
  float coverage;
  double path_length_m;
  uint32_t completed_waypoints;
  uint32_t failed_waypoints;
} robot_cleaning_interfaces__action__CleanTask_Result;

// Struct for a sequence of robot_cleaning_interfaces__action__CleanTask_Result.
typedef struct robot_cleaning_interfaces__action__CleanTask_Result__Sequence
{
  robot_cleaning_interfaces__action__CleanTask_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_cleaning_interfaces__action__CleanTask_Result__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'state'
// already included above
// #include "rosidl_runtime_c/string.h"
// Member 'current_goal'
#include "geometry_msgs/msg/detail/pose_stamped__struct.h"

/// Struct defined in action/CleanTask in the package robot_cleaning_interfaces.
typedef struct robot_cleaning_interfaces__action__CleanTask_Feedback
{
  rosidl_runtime_c__String state;
  float coverage;
  uint32_t completed_waypoints;
  uint32_t total_waypoints;
  geometry_msgs__msg__PoseStamped current_goal;
} robot_cleaning_interfaces__action__CleanTask_Feedback;

// Struct for a sequence of robot_cleaning_interfaces__action__CleanTask_Feedback.
typedef struct robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence
{
  robot_cleaning_interfaces__action__CleanTask_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "robot_cleaning_interfaces/action/detail/clean_task__struct.h"

/// Struct defined in action/CleanTask in the package robot_cleaning_interfaces.
typedef struct robot_cleaning_interfaces__action__CleanTask_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  robot_cleaning_interfaces__action__CleanTask_Goal goal;
} robot_cleaning_interfaces__action__CleanTask_SendGoal_Request;

// Struct for a sequence of robot_cleaning_interfaces__action__CleanTask_SendGoal_Request.
typedef struct robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence
{
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/CleanTask in the package robot_cleaning_interfaces.
typedef struct robot_cleaning_interfaces__action__CleanTask_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} robot_cleaning_interfaces__action__CleanTask_SendGoal_Response;

// Struct for a sequence of robot_cleaning_interfaces__action__CleanTask_SendGoal_Response.
typedef struct robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence
{
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__request__MAX_SIZE = 1
};
// response
enum
{
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/CleanTask in the package robot_cleaning_interfaces.
typedef struct robot_cleaning_interfaces__action__CleanTask_SendGoal_Event
{
  service_msgs__msg__ServiceEventInfo info;
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence request;
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence response;
} robot_cleaning_interfaces__action__CleanTask_SendGoal_Event;

// Struct for a sequence of robot_cleaning_interfaces__action__CleanTask_SendGoal_Event.
typedef struct robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence
{
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/CleanTask in the package robot_cleaning_interfaces.
typedef struct robot_cleaning_interfaces__action__CleanTask_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} robot_cleaning_interfaces__action__CleanTask_GetResult_Request;

// Struct for a sequence of robot_cleaning_interfaces__action__CleanTask_GetResult_Request.
typedef struct robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence
{
  robot_cleaning_interfaces__action__CleanTask_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__struct.h"

/// Struct defined in action/CleanTask in the package robot_cleaning_interfaces.
typedef struct robot_cleaning_interfaces__action__CleanTask_GetResult_Response
{
  int8_t status;
  robot_cleaning_interfaces__action__CleanTask_Result result;
} robot_cleaning_interfaces__action__CleanTask_GetResult_Response;

// Struct for a sequence of robot_cleaning_interfaces__action__CleanTask_GetResult_Response.
typedef struct robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence
{
  robot_cleaning_interfaces__action__CleanTask_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
// already included above
// #include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  robot_cleaning_interfaces__action__CleanTask_GetResult_Event__request__MAX_SIZE = 1
};
// response
enum
{
  robot_cleaning_interfaces__action__CleanTask_GetResult_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/CleanTask in the package robot_cleaning_interfaces.
typedef struct robot_cleaning_interfaces__action__CleanTask_GetResult_Event
{
  service_msgs__msg__ServiceEventInfo info;
  robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence request;
  robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence response;
} robot_cleaning_interfaces__action__CleanTask_GetResult_Event;

// Struct for a sequence of robot_cleaning_interfaces__action__CleanTask_GetResult_Event.
typedef struct robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence
{
  robot_cleaning_interfaces__action__CleanTask_GetResult_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__struct.h"

/// Struct defined in action/CleanTask in the package robot_cleaning_interfaces.
typedef struct robot_cleaning_interfaces__action__CleanTask_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  robot_cleaning_interfaces__action__CleanTask_Feedback feedback;
} robot_cleaning_interfaces__action__CleanTask_FeedbackMessage;

// Struct for a sequence of robot_cleaning_interfaces__action__CleanTask_FeedbackMessage.
typedef struct robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence
{
  robot_cleaning_interfaces__action__CleanTask_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_CLEANING_INTERFACES__ACTION__DETAIL__CLEAN_TASK__STRUCT_H_
