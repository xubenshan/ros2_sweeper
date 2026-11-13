// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from robot_cleaning_interfaces:msg/CoverageStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "robot_cleaning_interfaces/msg/detail/coverage_status__rosidl_typesupport_introspection_c.h"
#include "robot_cleaning_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "robot_cleaning_interfaces/msg/detail/coverage_status__functions.h"
#include "robot_cleaning_interfaces/msg/detail/coverage_status__struct.h"


// Include directives for member types
// Member `task_id`
#include "rosidl_runtime_c/string_functions.h"
// Member `covered`
#include "nav_msgs/msg/occupancy_grid.h"
// Member `covered`
#include "nav_msgs/msg/detail/occupancy_grid__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void robot_cleaning_interfaces__msg__CoverageStatus__rosidl_typesupport_introspection_c__CoverageStatus_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  robot_cleaning_interfaces__msg__CoverageStatus__init(message_memory);
}

void robot_cleaning_interfaces__msg__CoverageStatus__rosidl_typesupport_introspection_c__CoverageStatus_fini_function(void * message_memory)
{
  robot_cleaning_interfaces__msg__CoverageStatus__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember robot_cleaning_interfaces__msg__CoverageStatus__rosidl_typesupport_introspection_c__CoverageStatus_message_member_array[4] = {
  {
    "task_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_cleaning_interfaces__msg__CoverageStatus, task_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "coverage",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_cleaning_interfaces__msg__CoverageStatus, coverage),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "path_length_m",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_cleaning_interfaces__msg__CoverageStatus, path_length_m),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "covered",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_cleaning_interfaces__msg__CoverageStatus, covered),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers robot_cleaning_interfaces__msg__CoverageStatus__rosidl_typesupport_introspection_c__CoverageStatus_message_members = {
  "robot_cleaning_interfaces__msg",  // message namespace
  "CoverageStatus",  // message name
  4,  // number of fields
  sizeof(robot_cleaning_interfaces__msg__CoverageStatus),
  false,  // has_any_key_member_
  robot_cleaning_interfaces__msg__CoverageStatus__rosidl_typesupport_introspection_c__CoverageStatus_message_member_array,  // message members
  robot_cleaning_interfaces__msg__CoverageStatus__rosidl_typesupport_introspection_c__CoverageStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  robot_cleaning_interfaces__msg__CoverageStatus__rosidl_typesupport_introspection_c__CoverageStatus_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t robot_cleaning_interfaces__msg__CoverageStatus__rosidl_typesupport_introspection_c__CoverageStatus_message_type_support_handle = {
  0,
  &robot_cleaning_interfaces__msg__CoverageStatus__rosidl_typesupport_introspection_c__CoverageStatus_message_members,
  get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__msg__CoverageStatus__get_type_hash,
  &robot_cleaning_interfaces__msg__CoverageStatus__get_type_description,
  &robot_cleaning_interfaces__msg__CoverageStatus__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_robot_cleaning_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_cleaning_interfaces, msg, CoverageStatus)() {
  robot_cleaning_interfaces__msg__CoverageStatus__rosidl_typesupport_introspection_c__CoverageStatus_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, nav_msgs, msg, OccupancyGrid)();
  if (!robot_cleaning_interfaces__msg__CoverageStatus__rosidl_typesupport_introspection_c__CoverageStatus_message_type_support_handle.typesupport_identifier) {
    robot_cleaning_interfaces__msg__CoverageStatus__rosidl_typesupport_introspection_c__CoverageStatus_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &robot_cleaning_interfaces__msg__CoverageStatus__rosidl_typesupport_introspection_c__CoverageStatus_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
