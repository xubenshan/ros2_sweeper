// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from oomwoo_msgs:msg/BumpEvent.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "oomwoo_msgs/msg/detail/bump_event__rosidl_typesupport_introspection_c.h"
#include "oomwoo_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "oomwoo_msgs/msg/detail/bump_event__functions.h"
#include "oomwoo_msgs/msg/detail/bump_event__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `contact`
// Member `robot`
// Member `approach`
#include "geometry_msgs/msg/point.h"
// Member `contact`
// Member `robot`
// Member `approach`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void oomwoo_msgs__msg__BumpEvent__rosidl_typesupport_introspection_c__BumpEvent_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  oomwoo_msgs__msg__BumpEvent__init(message_memory);
}

void oomwoo_msgs__msg__BumpEvent__rosidl_typesupport_introspection_c__BumpEvent_fini_function(void * message_memory)
{
  oomwoo_msgs__msg__BumpEvent__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember oomwoo_msgs__msg__BumpEvent__rosidl_typesupport_introspection_c__BumpEvent_message_member_array[10] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(oomwoo_msgs__msg__BumpEvent, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "contact",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(oomwoo_msgs__msg__BumpEvent, contact),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "robot",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(oomwoo_msgs__msg__BumpEvent, robot),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "approach",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(oomwoo_msgs__msg__BumpEvent, approach),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "heading",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(oomwoo_msgs__msg__BumpEvent, heading),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "side",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(oomwoo_msgs__msg__BumpEvent, side),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "left_depress",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(oomwoo_msgs__msg__BumpEvent, left_depress),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "right_depress",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(oomwoo_msgs__msg__BumpEvent, right_depress),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "left_rate",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(oomwoo_msgs__msg__BumpEvent, left_rate),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "right_rate",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(oomwoo_msgs__msg__BumpEvent, right_rate),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers oomwoo_msgs__msg__BumpEvent__rosidl_typesupport_introspection_c__BumpEvent_message_members = {
  "oomwoo_msgs__msg",  // message namespace
  "BumpEvent",  // message name
  10,  // number of fields
  sizeof(oomwoo_msgs__msg__BumpEvent),
  false,  // has_any_key_member_
  oomwoo_msgs__msg__BumpEvent__rosidl_typesupport_introspection_c__BumpEvent_message_member_array,  // message members
  oomwoo_msgs__msg__BumpEvent__rosidl_typesupport_introspection_c__BumpEvent_init_function,  // function to initialize message memory (memory has to be allocated)
  oomwoo_msgs__msg__BumpEvent__rosidl_typesupport_introspection_c__BumpEvent_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t oomwoo_msgs__msg__BumpEvent__rosidl_typesupport_introspection_c__BumpEvent_message_type_support_handle = {
  0,
  &oomwoo_msgs__msg__BumpEvent__rosidl_typesupport_introspection_c__BumpEvent_message_members,
  get_message_typesupport_handle_function,
  &oomwoo_msgs__msg__BumpEvent__get_type_hash,
  &oomwoo_msgs__msg__BumpEvent__get_type_description,
  &oomwoo_msgs__msg__BumpEvent__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_oomwoo_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, oomwoo_msgs, msg, BumpEvent)() {
  oomwoo_msgs__msg__BumpEvent__rosidl_typesupport_introspection_c__BumpEvent_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  oomwoo_msgs__msg__BumpEvent__rosidl_typesupport_introspection_c__BumpEvent_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  oomwoo_msgs__msg__BumpEvent__rosidl_typesupport_introspection_c__BumpEvent_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  oomwoo_msgs__msg__BumpEvent__rosidl_typesupport_introspection_c__BumpEvent_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  if (!oomwoo_msgs__msg__BumpEvent__rosidl_typesupport_introspection_c__BumpEvent_message_type_support_handle.typesupport_identifier) {
    oomwoo_msgs__msg__BumpEvent__rosidl_typesupport_introspection_c__BumpEvent_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &oomwoo_msgs__msg__BumpEvent__rosidl_typesupport_introspection_c__BumpEvent_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
