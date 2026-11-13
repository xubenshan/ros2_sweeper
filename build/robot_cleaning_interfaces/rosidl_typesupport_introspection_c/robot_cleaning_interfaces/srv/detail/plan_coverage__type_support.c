// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from robot_cleaning_interfaces:srv/PlanCoverage.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "robot_cleaning_interfaces/srv/detail/plan_coverage__rosidl_typesupport_introspection_c.h"
#include "robot_cleaning_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "robot_cleaning_interfaces/srv/detail/plan_coverage__functions.h"
#include "robot_cleaning_interfaces/srv/detail/plan_coverage__struct.h"


// Include directives for member types
// Member `regions`
#include "rosidl_runtime_c/string_functions.h"
// Member `start`
#include "geometry_msgs/msg/pose_stamped.h"
// Member `start`
#include "geometry_msgs/msg/detail/pose_stamped__rosidl_typesupport_introspection_c.h"
// Member `covered`
#include "nav_msgs/msg/occupancy_grid.h"
// Member `covered`
#include "nav_msgs/msg/detail/occupancy_grid__rosidl_typesupport_introspection_c.h"
// Member `excluded`
#include "geometry_msgs/msg/point.h"
// Member `excluded`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__PlanCoverage_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  robot_cleaning_interfaces__srv__PlanCoverage_Request__init(message_memory);
}

void robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__PlanCoverage_Request_fini_function(void * message_memory)
{
  robot_cleaning_interfaces__srv__PlanCoverage_Request__fini(message_memory);
}

size_t robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__size_function__PlanCoverage_Request__regions(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__get_const_function__PlanCoverage_Request__regions(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__get_function__PlanCoverage_Request__regions(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__fetch_function__PlanCoverage_Request__regions(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__get_const_function__PlanCoverage_Request__regions(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__assign_function__PlanCoverage_Request__regions(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__get_function__PlanCoverage_Request__regions(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__resize_function__PlanCoverage_Request__regions(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__size_function__PlanCoverage_Request__excluded(
  const void * untyped_member)
{
  const geometry_msgs__msg__Point__Sequence * member =
    (const geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return member->size;
}

const void * robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__get_const_function__PlanCoverage_Request__excluded(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__Point__Sequence * member =
    (const geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return &member->data[index];
}

void * robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__get_function__PlanCoverage_Request__excluded(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__Point__Sequence * member =
    (geometry_msgs__msg__Point__Sequence *)(untyped_member);
  return &member->data[index];
}

void robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__fetch_function__PlanCoverage_Request__excluded(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const geometry_msgs__msg__Point * item =
    ((const geometry_msgs__msg__Point *)
    robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__get_const_function__PlanCoverage_Request__excluded(untyped_member, index));
  geometry_msgs__msg__Point * value =
    (geometry_msgs__msg__Point *)(untyped_value);
  *value = *item;
}

void robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__assign_function__PlanCoverage_Request__excluded(
  void * untyped_member, size_t index, const void * untyped_value)
{
  geometry_msgs__msg__Point * item =
    ((geometry_msgs__msg__Point *)
    robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__get_function__PlanCoverage_Request__excluded(untyped_member, index));
  const geometry_msgs__msg__Point * value =
    (const geometry_msgs__msg__Point *)(untyped_value);
  *item = *value;
}

bool robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__resize_function__PlanCoverage_Request__excluded(
  void * untyped_member, size_t size)
{
  geometry_msgs__msg__Point__Sequence * member =
    (geometry_msgs__msg__Point__Sequence *)(untyped_member);
  geometry_msgs__msg__Point__Sequence__fini(member);
  return geometry_msgs__msg__Point__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__PlanCoverage_Request_message_member_array[7] = {
  {
    "regions",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_cleaning_interfaces__srv__PlanCoverage_Request, regions),  // bytes offset in struct
    NULL,  // default value
    robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__size_function__PlanCoverage_Request__regions,  // size() function pointer
    robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__get_const_function__PlanCoverage_Request__regions,  // get_const(index) function pointer
    robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__get_function__PlanCoverage_Request__regions,  // get(index) function pointer
    robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__fetch_function__PlanCoverage_Request__regions,  // fetch(index, &value) function pointer
    robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__assign_function__PlanCoverage_Request__regions,  // assign(index, value) function pointer
    robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__resize_function__PlanCoverage_Request__regions  // resize(index) function pointer
  },
  {
    "start",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_cleaning_interfaces__srv__PlanCoverage_Request, start),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "gap_fill",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_cleaning_interfaces__srv__PlanCoverage_Request, gap_fill),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "target_coverage",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_cleaning_interfaces__srv__PlanCoverage_Request, target_coverage),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "distance_budget_m",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_cleaning_interfaces__srv__PlanCoverage_Request, distance_budget_m),  // bytes offset in struct
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
    offsetof(robot_cleaning_interfaces__srv__PlanCoverage_Request, covered),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "excluded",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_cleaning_interfaces__srv__PlanCoverage_Request, excluded),  // bytes offset in struct
    NULL,  // default value
    robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__size_function__PlanCoverage_Request__excluded,  // size() function pointer
    robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__get_const_function__PlanCoverage_Request__excluded,  // get_const(index) function pointer
    robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__get_function__PlanCoverage_Request__excluded,  // get(index) function pointer
    robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__fetch_function__PlanCoverage_Request__excluded,  // fetch(index, &value) function pointer
    robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__assign_function__PlanCoverage_Request__excluded,  // assign(index, value) function pointer
    robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__resize_function__PlanCoverage_Request__excluded  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__PlanCoverage_Request_message_members = {
  "robot_cleaning_interfaces__srv",  // message namespace
  "PlanCoverage_Request",  // message name
  7,  // number of fields
  sizeof(robot_cleaning_interfaces__srv__PlanCoverage_Request),
  false,  // has_any_key_member_
  robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__PlanCoverage_Request_message_member_array,  // message members
  robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__PlanCoverage_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__PlanCoverage_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__PlanCoverage_Request_message_type_support_handle = {
  0,
  &robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__PlanCoverage_Request_message_members,
  get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__srv__PlanCoverage_Request__get_type_hash,
  &robot_cleaning_interfaces__srv__PlanCoverage_Request__get_type_description,
  &robot_cleaning_interfaces__srv__PlanCoverage_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_robot_cleaning_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_cleaning_interfaces, srv, PlanCoverage_Request)() {
  robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__PlanCoverage_Request_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, PoseStamped)();
  robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__PlanCoverage_Request_message_member_array[5].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, nav_msgs, msg, OccupancyGrid)();
  robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__PlanCoverage_Request_message_member_array[6].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  if (!robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__PlanCoverage_Request_message_type_support_handle.typesupport_identifier) {
    robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__PlanCoverage_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__PlanCoverage_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "robot_cleaning_interfaces/srv/detail/plan_coverage__rosidl_typesupport_introspection_c.h"
// already included above
// #include "robot_cleaning_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "robot_cleaning_interfaces/srv/detail/plan_coverage__functions.h"
// already included above
// #include "robot_cleaning_interfaces/srv/detail/plan_coverage__struct.h"


// Include directives for member types
// Member `reason`
// already included above
// #include "rosidl_runtime_c/string_functions.h"
// Member `path`
#include "nav_msgs/msg/path.h"
// Member `path`
#include "nav_msgs/msg/detail/path__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void robot_cleaning_interfaces__srv__PlanCoverage_Response__rosidl_typesupport_introspection_c__PlanCoverage_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  robot_cleaning_interfaces__srv__PlanCoverage_Response__init(message_memory);
}

void robot_cleaning_interfaces__srv__PlanCoverage_Response__rosidl_typesupport_introspection_c__PlanCoverage_Response_fini_function(void * message_memory)
{
  robot_cleaning_interfaces__srv__PlanCoverage_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember robot_cleaning_interfaces__srv__PlanCoverage_Response__rosidl_typesupport_introspection_c__PlanCoverage_Response_message_member_array[3] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_cleaning_interfaces__srv__PlanCoverage_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "reason",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_cleaning_interfaces__srv__PlanCoverage_Response, reason),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "path",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_cleaning_interfaces__srv__PlanCoverage_Response, path),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers robot_cleaning_interfaces__srv__PlanCoverage_Response__rosidl_typesupport_introspection_c__PlanCoverage_Response_message_members = {
  "robot_cleaning_interfaces__srv",  // message namespace
  "PlanCoverage_Response",  // message name
  3,  // number of fields
  sizeof(robot_cleaning_interfaces__srv__PlanCoverage_Response),
  false,  // has_any_key_member_
  robot_cleaning_interfaces__srv__PlanCoverage_Response__rosidl_typesupport_introspection_c__PlanCoverage_Response_message_member_array,  // message members
  robot_cleaning_interfaces__srv__PlanCoverage_Response__rosidl_typesupport_introspection_c__PlanCoverage_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  robot_cleaning_interfaces__srv__PlanCoverage_Response__rosidl_typesupport_introspection_c__PlanCoverage_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t robot_cleaning_interfaces__srv__PlanCoverage_Response__rosidl_typesupport_introspection_c__PlanCoverage_Response_message_type_support_handle = {
  0,
  &robot_cleaning_interfaces__srv__PlanCoverage_Response__rosidl_typesupport_introspection_c__PlanCoverage_Response_message_members,
  get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__srv__PlanCoverage_Response__get_type_hash,
  &robot_cleaning_interfaces__srv__PlanCoverage_Response__get_type_description,
  &robot_cleaning_interfaces__srv__PlanCoverage_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_robot_cleaning_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_cleaning_interfaces, srv, PlanCoverage_Response)() {
  robot_cleaning_interfaces__srv__PlanCoverage_Response__rosidl_typesupport_introspection_c__PlanCoverage_Response_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, nav_msgs, msg, Path)();
  if (!robot_cleaning_interfaces__srv__PlanCoverage_Response__rosidl_typesupport_introspection_c__PlanCoverage_Response_message_type_support_handle.typesupport_identifier) {
    robot_cleaning_interfaces__srv__PlanCoverage_Response__rosidl_typesupport_introspection_c__PlanCoverage_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &robot_cleaning_interfaces__srv__PlanCoverage_Response__rosidl_typesupport_introspection_c__PlanCoverage_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "robot_cleaning_interfaces/srv/detail/plan_coverage__rosidl_typesupport_introspection_c.h"
// already included above
// #include "robot_cleaning_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "robot_cleaning_interfaces/srv/detail/plan_coverage__functions.h"
// already included above
// #include "robot_cleaning_interfaces/srv/detail/plan_coverage__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "robot_cleaning_interfaces/srv/plan_coverage.h"
// Member `request`
// Member `response`
// already included above
// #include "robot_cleaning_interfaces/srv/detail/plan_coverage__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__PlanCoverage_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  robot_cleaning_interfaces__srv__PlanCoverage_Event__init(message_memory);
}

void robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__PlanCoverage_Event_fini_function(void * message_memory)
{
  robot_cleaning_interfaces__srv__PlanCoverage_Event__fini(message_memory);
}

size_t robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__size_function__PlanCoverage_Event__request(
  const void * untyped_member)
{
  const robot_cleaning_interfaces__srv__PlanCoverage_Request__Sequence * member =
    (const robot_cleaning_interfaces__srv__PlanCoverage_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__get_const_function__PlanCoverage_Event__request(
  const void * untyped_member, size_t index)
{
  const robot_cleaning_interfaces__srv__PlanCoverage_Request__Sequence * member =
    (const robot_cleaning_interfaces__srv__PlanCoverage_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__get_function__PlanCoverage_Event__request(
  void * untyped_member, size_t index)
{
  robot_cleaning_interfaces__srv__PlanCoverage_Request__Sequence * member =
    (robot_cleaning_interfaces__srv__PlanCoverage_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__fetch_function__PlanCoverage_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const robot_cleaning_interfaces__srv__PlanCoverage_Request * item =
    ((const robot_cleaning_interfaces__srv__PlanCoverage_Request *)
    robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__get_const_function__PlanCoverage_Event__request(untyped_member, index));
  robot_cleaning_interfaces__srv__PlanCoverage_Request * value =
    (robot_cleaning_interfaces__srv__PlanCoverage_Request *)(untyped_value);
  *value = *item;
}

void robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__assign_function__PlanCoverage_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  robot_cleaning_interfaces__srv__PlanCoverage_Request * item =
    ((robot_cleaning_interfaces__srv__PlanCoverage_Request *)
    robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__get_function__PlanCoverage_Event__request(untyped_member, index));
  const robot_cleaning_interfaces__srv__PlanCoverage_Request * value =
    (const robot_cleaning_interfaces__srv__PlanCoverage_Request *)(untyped_value);
  *item = *value;
}

bool robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__resize_function__PlanCoverage_Event__request(
  void * untyped_member, size_t size)
{
  robot_cleaning_interfaces__srv__PlanCoverage_Request__Sequence * member =
    (robot_cleaning_interfaces__srv__PlanCoverage_Request__Sequence *)(untyped_member);
  robot_cleaning_interfaces__srv__PlanCoverage_Request__Sequence__fini(member);
  return robot_cleaning_interfaces__srv__PlanCoverage_Request__Sequence__init(member, size);
}

size_t robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__size_function__PlanCoverage_Event__response(
  const void * untyped_member)
{
  const robot_cleaning_interfaces__srv__PlanCoverage_Response__Sequence * member =
    (const robot_cleaning_interfaces__srv__PlanCoverage_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__get_const_function__PlanCoverage_Event__response(
  const void * untyped_member, size_t index)
{
  const robot_cleaning_interfaces__srv__PlanCoverage_Response__Sequence * member =
    (const robot_cleaning_interfaces__srv__PlanCoverage_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__get_function__PlanCoverage_Event__response(
  void * untyped_member, size_t index)
{
  robot_cleaning_interfaces__srv__PlanCoverage_Response__Sequence * member =
    (robot_cleaning_interfaces__srv__PlanCoverage_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__fetch_function__PlanCoverage_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const robot_cleaning_interfaces__srv__PlanCoverage_Response * item =
    ((const robot_cleaning_interfaces__srv__PlanCoverage_Response *)
    robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__get_const_function__PlanCoverage_Event__response(untyped_member, index));
  robot_cleaning_interfaces__srv__PlanCoverage_Response * value =
    (robot_cleaning_interfaces__srv__PlanCoverage_Response *)(untyped_value);
  *value = *item;
}

void robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__assign_function__PlanCoverage_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  robot_cleaning_interfaces__srv__PlanCoverage_Response * item =
    ((robot_cleaning_interfaces__srv__PlanCoverage_Response *)
    robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__get_function__PlanCoverage_Event__response(untyped_member, index));
  const robot_cleaning_interfaces__srv__PlanCoverage_Response * value =
    (const robot_cleaning_interfaces__srv__PlanCoverage_Response *)(untyped_value);
  *item = *value;
}

bool robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__resize_function__PlanCoverage_Event__response(
  void * untyped_member, size_t size)
{
  robot_cleaning_interfaces__srv__PlanCoverage_Response__Sequence * member =
    (robot_cleaning_interfaces__srv__PlanCoverage_Response__Sequence *)(untyped_member);
  robot_cleaning_interfaces__srv__PlanCoverage_Response__Sequence__fini(member);
  return robot_cleaning_interfaces__srv__PlanCoverage_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__PlanCoverage_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(robot_cleaning_interfaces__srv__PlanCoverage_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(robot_cleaning_interfaces__srv__PlanCoverage_Event, request),  // bytes offset in struct
    NULL,  // default value
    robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__size_function__PlanCoverage_Event__request,  // size() function pointer
    robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__get_const_function__PlanCoverage_Event__request,  // get_const(index) function pointer
    robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__get_function__PlanCoverage_Event__request,  // get(index) function pointer
    robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__fetch_function__PlanCoverage_Event__request,  // fetch(index, &value) function pointer
    robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__assign_function__PlanCoverage_Event__request,  // assign(index, value) function pointer
    robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__resize_function__PlanCoverage_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(robot_cleaning_interfaces__srv__PlanCoverage_Event, response),  // bytes offset in struct
    NULL,  // default value
    robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__size_function__PlanCoverage_Event__response,  // size() function pointer
    robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__get_const_function__PlanCoverage_Event__response,  // get_const(index) function pointer
    robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__get_function__PlanCoverage_Event__response,  // get(index) function pointer
    robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__fetch_function__PlanCoverage_Event__response,  // fetch(index, &value) function pointer
    robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__assign_function__PlanCoverage_Event__response,  // assign(index, value) function pointer
    robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__resize_function__PlanCoverage_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__PlanCoverage_Event_message_members = {
  "robot_cleaning_interfaces__srv",  // message namespace
  "PlanCoverage_Event",  // message name
  3,  // number of fields
  sizeof(robot_cleaning_interfaces__srv__PlanCoverage_Event),
  false,  // has_any_key_member_
  robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__PlanCoverage_Event_message_member_array,  // message members
  robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__PlanCoverage_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__PlanCoverage_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__PlanCoverage_Event_message_type_support_handle = {
  0,
  &robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__PlanCoverage_Event_message_members,
  get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__srv__PlanCoverage_Event__get_type_hash,
  &robot_cleaning_interfaces__srv__PlanCoverage_Event__get_type_description,
  &robot_cleaning_interfaces__srv__PlanCoverage_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_robot_cleaning_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_cleaning_interfaces, srv, PlanCoverage_Event)() {
  robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__PlanCoverage_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__PlanCoverage_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_cleaning_interfaces, srv, PlanCoverage_Request)();
  robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__PlanCoverage_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_cleaning_interfaces, srv, PlanCoverage_Response)();
  if (!robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__PlanCoverage_Event_message_type_support_handle.typesupport_identifier) {
    robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__PlanCoverage_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__PlanCoverage_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "robot_cleaning_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "robot_cleaning_interfaces/srv/detail/plan_coverage__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers robot_cleaning_interfaces__srv__detail__plan_coverage__rosidl_typesupport_introspection_c__PlanCoverage_service_members = {
  "robot_cleaning_interfaces__srv",  // service namespace
  "PlanCoverage",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // robot_cleaning_interfaces__srv__detail__plan_coverage__rosidl_typesupport_introspection_c__PlanCoverage_Request_message_type_support_handle,
  NULL,  // response message
  // robot_cleaning_interfaces__srv__detail__plan_coverage__rosidl_typesupport_introspection_c__PlanCoverage_Response_message_type_support_handle
  NULL  // event_message
  // robot_cleaning_interfaces__srv__detail__plan_coverage__rosidl_typesupport_introspection_c__PlanCoverage_Response_message_type_support_handle
};


static rosidl_service_type_support_t robot_cleaning_interfaces__srv__detail__plan_coverage__rosidl_typesupport_introspection_c__PlanCoverage_service_type_support_handle = {
  0,
  &robot_cleaning_interfaces__srv__detail__plan_coverage__rosidl_typesupport_introspection_c__PlanCoverage_service_members,
  get_service_typesupport_handle_function,
  &robot_cleaning_interfaces__srv__PlanCoverage_Request__rosidl_typesupport_introspection_c__PlanCoverage_Request_message_type_support_handle,
  &robot_cleaning_interfaces__srv__PlanCoverage_Response__rosidl_typesupport_introspection_c__PlanCoverage_Response_message_type_support_handle,
  &robot_cleaning_interfaces__srv__PlanCoverage_Event__rosidl_typesupport_introspection_c__PlanCoverage_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    robot_cleaning_interfaces,
    srv,
    PlanCoverage
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    robot_cleaning_interfaces,
    srv,
    PlanCoverage
  ),
  &robot_cleaning_interfaces__srv__PlanCoverage__get_type_hash,
  &robot_cleaning_interfaces__srv__PlanCoverage__get_type_description,
  &robot_cleaning_interfaces__srv__PlanCoverage__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_cleaning_interfaces, srv, PlanCoverage_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_cleaning_interfaces, srv, PlanCoverage_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_cleaning_interfaces, srv, PlanCoverage_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_robot_cleaning_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_cleaning_interfaces, srv, PlanCoverage)(void) {
  if (!robot_cleaning_interfaces__srv__detail__plan_coverage__rosidl_typesupport_introspection_c__PlanCoverage_service_type_support_handle.typesupport_identifier) {
    robot_cleaning_interfaces__srv__detail__plan_coverage__rosidl_typesupport_introspection_c__PlanCoverage_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)robot_cleaning_interfaces__srv__detail__plan_coverage__rosidl_typesupport_introspection_c__PlanCoverage_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_cleaning_interfaces, srv, PlanCoverage_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_cleaning_interfaces, srv, PlanCoverage_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_cleaning_interfaces, srv, PlanCoverage_Event)()->data;
  }

  return &robot_cleaning_interfaces__srv__detail__plan_coverage__rosidl_typesupport_introspection_c__PlanCoverage_service_type_support_handle;
}
