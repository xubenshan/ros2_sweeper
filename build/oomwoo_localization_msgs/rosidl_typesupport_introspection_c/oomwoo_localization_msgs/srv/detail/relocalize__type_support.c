// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from oomwoo_localization_msgs:srv/Relocalize.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "oomwoo_localization_msgs/srv/detail/relocalize__rosidl_typesupport_introspection_c.h"
#include "oomwoo_localization_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "oomwoo_localization_msgs/srv/detail/relocalize__functions.h"
#include "oomwoo_localization_msgs/srv/detail/relocalize__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void oomwoo_localization_msgs__srv__Relocalize_Request__rosidl_typesupport_introspection_c__Relocalize_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  oomwoo_localization_msgs__srv__Relocalize_Request__init(message_memory);
}

void oomwoo_localization_msgs__srv__Relocalize_Request__rosidl_typesupport_introspection_c__Relocalize_Request_fini_function(void * message_memory)
{
  oomwoo_localization_msgs__srv__Relocalize_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember oomwoo_localization_msgs__srv__Relocalize_Request__rosidl_typesupport_introspection_c__Relocalize_Request_message_member_array[1] = {
  {
    "structure_needs_at_least_one_member",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(oomwoo_localization_msgs__srv__Relocalize_Request, structure_needs_at_least_one_member),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers oomwoo_localization_msgs__srv__Relocalize_Request__rosidl_typesupport_introspection_c__Relocalize_Request_message_members = {
  "oomwoo_localization_msgs__srv",  // message namespace
  "Relocalize_Request",  // message name
  1,  // number of fields
  sizeof(oomwoo_localization_msgs__srv__Relocalize_Request),
  false,  // has_any_key_member_
  oomwoo_localization_msgs__srv__Relocalize_Request__rosidl_typesupport_introspection_c__Relocalize_Request_message_member_array,  // message members
  oomwoo_localization_msgs__srv__Relocalize_Request__rosidl_typesupport_introspection_c__Relocalize_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  oomwoo_localization_msgs__srv__Relocalize_Request__rosidl_typesupport_introspection_c__Relocalize_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t oomwoo_localization_msgs__srv__Relocalize_Request__rosidl_typesupport_introspection_c__Relocalize_Request_message_type_support_handle = {
  0,
  &oomwoo_localization_msgs__srv__Relocalize_Request__rosidl_typesupport_introspection_c__Relocalize_Request_message_members,
  get_message_typesupport_handle_function,
  &oomwoo_localization_msgs__srv__Relocalize_Request__get_type_hash,
  &oomwoo_localization_msgs__srv__Relocalize_Request__get_type_description,
  &oomwoo_localization_msgs__srv__Relocalize_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_oomwoo_localization_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, oomwoo_localization_msgs, srv, Relocalize_Request)() {
  if (!oomwoo_localization_msgs__srv__Relocalize_Request__rosidl_typesupport_introspection_c__Relocalize_Request_message_type_support_handle.typesupport_identifier) {
    oomwoo_localization_msgs__srv__Relocalize_Request__rosidl_typesupport_introspection_c__Relocalize_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &oomwoo_localization_msgs__srv__Relocalize_Request__rosidl_typesupport_introspection_c__Relocalize_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "oomwoo_localization_msgs/srv/detail/relocalize__rosidl_typesupport_introspection_c.h"
// already included above
// #include "oomwoo_localization_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "oomwoo_localization_msgs/srv/detail/relocalize__functions.h"
// already included above
// #include "oomwoo_localization_msgs/srv/detail/relocalize__struct.h"


// Include directives for member types
// Member `pose`
#include "geometry_msgs/msg/pose_with_covariance_stamped.h"
// Member `pose`
#include "geometry_msgs/msg/detail/pose_with_covariance_stamped__rosidl_typesupport_introspection_c.h"
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void oomwoo_localization_msgs__srv__Relocalize_Response__rosidl_typesupport_introspection_c__Relocalize_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  oomwoo_localization_msgs__srv__Relocalize_Response__init(message_memory);
}

void oomwoo_localization_msgs__srv__Relocalize_Response__rosidl_typesupport_introspection_c__Relocalize_Response_fini_function(void * message_memory)
{
  oomwoo_localization_msgs__srv__Relocalize_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember oomwoo_localization_msgs__srv__Relocalize_Response__rosidl_typesupport_introspection_c__Relocalize_Response_message_member_array[7] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(oomwoo_localization_msgs__srv__Relocalize_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pose",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(oomwoo_localization_msgs__srv__Relocalize_Response, pose),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "score",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(oomwoo_localization_msgs__srv__Relocalize_Response, score),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "score_normalized",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(oomwoo_localization_msgs__srv__Relocalize_Response, score_normalized),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "confidence",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(oomwoo_localization_msgs__srv__Relocalize_Response, confidence),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "runtime_s",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(oomwoo_localization_msgs__srv__Relocalize_Response, runtime_s),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(oomwoo_localization_msgs__srv__Relocalize_Response, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers oomwoo_localization_msgs__srv__Relocalize_Response__rosidl_typesupport_introspection_c__Relocalize_Response_message_members = {
  "oomwoo_localization_msgs__srv",  // message namespace
  "Relocalize_Response",  // message name
  7,  // number of fields
  sizeof(oomwoo_localization_msgs__srv__Relocalize_Response),
  false,  // has_any_key_member_
  oomwoo_localization_msgs__srv__Relocalize_Response__rosidl_typesupport_introspection_c__Relocalize_Response_message_member_array,  // message members
  oomwoo_localization_msgs__srv__Relocalize_Response__rosidl_typesupport_introspection_c__Relocalize_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  oomwoo_localization_msgs__srv__Relocalize_Response__rosidl_typesupport_introspection_c__Relocalize_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t oomwoo_localization_msgs__srv__Relocalize_Response__rosidl_typesupport_introspection_c__Relocalize_Response_message_type_support_handle = {
  0,
  &oomwoo_localization_msgs__srv__Relocalize_Response__rosidl_typesupport_introspection_c__Relocalize_Response_message_members,
  get_message_typesupport_handle_function,
  &oomwoo_localization_msgs__srv__Relocalize_Response__get_type_hash,
  &oomwoo_localization_msgs__srv__Relocalize_Response__get_type_description,
  &oomwoo_localization_msgs__srv__Relocalize_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_oomwoo_localization_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, oomwoo_localization_msgs, srv, Relocalize_Response)() {
  oomwoo_localization_msgs__srv__Relocalize_Response__rosidl_typesupport_introspection_c__Relocalize_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, PoseWithCovarianceStamped)();
  if (!oomwoo_localization_msgs__srv__Relocalize_Response__rosidl_typesupport_introspection_c__Relocalize_Response_message_type_support_handle.typesupport_identifier) {
    oomwoo_localization_msgs__srv__Relocalize_Response__rosidl_typesupport_introspection_c__Relocalize_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &oomwoo_localization_msgs__srv__Relocalize_Response__rosidl_typesupport_introspection_c__Relocalize_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "oomwoo_localization_msgs/srv/detail/relocalize__rosidl_typesupport_introspection_c.h"
// already included above
// #include "oomwoo_localization_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "oomwoo_localization_msgs/srv/detail/relocalize__functions.h"
// already included above
// #include "oomwoo_localization_msgs/srv/detail/relocalize__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "oomwoo_localization_msgs/srv/relocalize.h"
// Member `request`
// Member `response`
// already included above
// #include "oomwoo_localization_msgs/srv/detail/relocalize__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__Relocalize_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  oomwoo_localization_msgs__srv__Relocalize_Event__init(message_memory);
}

void oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__Relocalize_Event_fini_function(void * message_memory)
{
  oomwoo_localization_msgs__srv__Relocalize_Event__fini(message_memory);
}

size_t oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__size_function__Relocalize_Event__request(
  const void * untyped_member)
{
  const oomwoo_localization_msgs__srv__Relocalize_Request__Sequence * member =
    (const oomwoo_localization_msgs__srv__Relocalize_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__get_const_function__Relocalize_Event__request(
  const void * untyped_member, size_t index)
{
  const oomwoo_localization_msgs__srv__Relocalize_Request__Sequence * member =
    (const oomwoo_localization_msgs__srv__Relocalize_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__get_function__Relocalize_Event__request(
  void * untyped_member, size_t index)
{
  oomwoo_localization_msgs__srv__Relocalize_Request__Sequence * member =
    (oomwoo_localization_msgs__srv__Relocalize_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__fetch_function__Relocalize_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const oomwoo_localization_msgs__srv__Relocalize_Request * item =
    ((const oomwoo_localization_msgs__srv__Relocalize_Request *)
    oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__get_const_function__Relocalize_Event__request(untyped_member, index));
  oomwoo_localization_msgs__srv__Relocalize_Request * value =
    (oomwoo_localization_msgs__srv__Relocalize_Request *)(untyped_value);
  *value = *item;
}

void oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__assign_function__Relocalize_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  oomwoo_localization_msgs__srv__Relocalize_Request * item =
    ((oomwoo_localization_msgs__srv__Relocalize_Request *)
    oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__get_function__Relocalize_Event__request(untyped_member, index));
  const oomwoo_localization_msgs__srv__Relocalize_Request * value =
    (const oomwoo_localization_msgs__srv__Relocalize_Request *)(untyped_value);
  *item = *value;
}

bool oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__resize_function__Relocalize_Event__request(
  void * untyped_member, size_t size)
{
  oomwoo_localization_msgs__srv__Relocalize_Request__Sequence * member =
    (oomwoo_localization_msgs__srv__Relocalize_Request__Sequence *)(untyped_member);
  oomwoo_localization_msgs__srv__Relocalize_Request__Sequence__fini(member);
  return oomwoo_localization_msgs__srv__Relocalize_Request__Sequence__init(member, size);
}

size_t oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__size_function__Relocalize_Event__response(
  const void * untyped_member)
{
  const oomwoo_localization_msgs__srv__Relocalize_Response__Sequence * member =
    (const oomwoo_localization_msgs__srv__Relocalize_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__get_const_function__Relocalize_Event__response(
  const void * untyped_member, size_t index)
{
  const oomwoo_localization_msgs__srv__Relocalize_Response__Sequence * member =
    (const oomwoo_localization_msgs__srv__Relocalize_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__get_function__Relocalize_Event__response(
  void * untyped_member, size_t index)
{
  oomwoo_localization_msgs__srv__Relocalize_Response__Sequence * member =
    (oomwoo_localization_msgs__srv__Relocalize_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__fetch_function__Relocalize_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const oomwoo_localization_msgs__srv__Relocalize_Response * item =
    ((const oomwoo_localization_msgs__srv__Relocalize_Response *)
    oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__get_const_function__Relocalize_Event__response(untyped_member, index));
  oomwoo_localization_msgs__srv__Relocalize_Response * value =
    (oomwoo_localization_msgs__srv__Relocalize_Response *)(untyped_value);
  *value = *item;
}

void oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__assign_function__Relocalize_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  oomwoo_localization_msgs__srv__Relocalize_Response * item =
    ((oomwoo_localization_msgs__srv__Relocalize_Response *)
    oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__get_function__Relocalize_Event__response(untyped_member, index));
  const oomwoo_localization_msgs__srv__Relocalize_Response * value =
    (const oomwoo_localization_msgs__srv__Relocalize_Response *)(untyped_value);
  *item = *value;
}

bool oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__resize_function__Relocalize_Event__response(
  void * untyped_member, size_t size)
{
  oomwoo_localization_msgs__srv__Relocalize_Response__Sequence * member =
    (oomwoo_localization_msgs__srv__Relocalize_Response__Sequence *)(untyped_member);
  oomwoo_localization_msgs__srv__Relocalize_Response__Sequence__fini(member);
  return oomwoo_localization_msgs__srv__Relocalize_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__Relocalize_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(oomwoo_localization_msgs__srv__Relocalize_Event, info),  // bytes offset in struct
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
    offsetof(oomwoo_localization_msgs__srv__Relocalize_Event, request),  // bytes offset in struct
    NULL,  // default value
    oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__size_function__Relocalize_Event__request,  // size() function pointer
    oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__get_const_function__Relocalize_Event__request,  // get_const(index) function pointer
    oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__get_function__Relocalize_Event__request,  // get(index) function pointer
    oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__fetch_function__Relocalize_Event__request,  // fetch(index, &value) function pointer
    oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__assign_function__Relocalize_Event__request,  // assign(index, value) function pointer
    oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__resize_function__Relocalize_Event__request  // resize(index) function pointer
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
    offsetof(oomwoo_localization_msgs__srv__Relocalize_Event, response),  // bytes offset in struct
    NULL,  // default value
    oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__size_function__Relocalize_Event__response,  // size() function pointer
    oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__get_const_function__Relocalize_Event__response,  // get_const(index) function pointer
    oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__get_function__Relocalize_Event__response,  // get(index) function pointer
    oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__fetch_function__Relocalize_Event__response,  // fetch(index, &value) function pointer
    oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__assign_function__Relocalize_Event__response,  // assign(index, value) function pointer
    oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__resize_function__Relocalize_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__Relocalize_Event_message_members = {
  "oomwoo_localization_msgs__srv",  // message namespace
  "Relocalize_Event",  // message name
  3,  // number of fields
  sizeof(oomwoo_localization_msgs__srv__Relocalize_Event),
  false,  // has_any_key_member_
  oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__Relocalize_Event_message_member_array,  // message members
  oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__Relocalize_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__Relocalize_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__Relocalize_Event_message_type_support_handle = {
  0,
  &oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__Relocalize_Event_message_members,
  get_message_typesupport_handle_function,
  &oomwoo_localization_msgs__srv__Relocalize_Event__get_type_hash,
  &oomwoo_localization_msgs__srv__Relocalize_Event__get_type_description,
  &oomwoo_localization_msgs__srv__Relocalize_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_oomwoo_localization_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, oomwoo_localization_msgs, srv, Relocalize_Event)() {
  oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__Relocalize_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__Relocalize_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, oomwoo_localization_msgs, srv, Relocalize_Request)();
  oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__Relocalize_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, oomwoo_localization_msgs, srv, Relocalize_Response)();
  if (!oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__Relocalize_Event_message_type_support_handle.typesupport_identifier) {
    oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__Relocalize_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__Relocalize_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "oomwoo_localization_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "oomwoo_localization_msgs/srv/detail/relocalize__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers oomwoo_localization_msgs__srv__detail__relocalize__rosidl_typesupport_introspection_c__Relocalize_service_members = {
  "oomwoo_localization_msgs__srv",  // service namespace
  "Relocalize",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // oomwoo_localization_msgs__srv__detail__relocalize__rosidl_typesupport_introspection_c__Relocalize_Request_message_type_support_handle,
  NULL,  // response message
  // oomwoo_localization_msgs__srv__detail__relocalize__rosidl_typesupport_introspection_c__Relocalize_Response_message_type_support_handle
  NULL  // event_message
  // oomwoo_localization_msgs__srv__detail__relocalize__rosidl_typesupport_introspection_c__Relocalize_Response_message_type_support_handle
};


static rosidl_service_type_support_t oomwoo_localization_msgs__srv__detail__relocalize__rosidl_typesupport_introspection_c__Relocalize_service_type_support_handle = {
  0,
  &oomwoo_localization_msgs__srv__detail__relocalize__rosidl_typesupport_introspection_c__Relocalize_service_members,
  get_service_typesupport_handle_function,
  &oomwoo_localization_msgs__srv__Relocalize_Request__rosidl_typesupport_introspection_c__Relocalize_Request_message_type_support_handle,
  &oomwoo_localization_msgs__srv__Relocalize_Response__rosidl_typesupport_introspection_c__Relocalize_Response_message_type_support_handle,
  &oomwoo_localization_msgs__srv__Relocalize_Event__rosidl_typesupport_introspection_c__Relocalize_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    oomwoo_localization_msgs,
    srv,
    Relocalize
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    oomwoo_localization_msgs,
    srv,
    Relocalize
  ),
  &oomwoo_localization_msgs__srv__Relocalize__get_type_hash,
  &oomwoo_localization_msgs__srv__Relocalize__get_type_description,
  &oomwoo_localization_msgs__srv__Relocalize__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, oomwoo_localization_msgs, srv, Relocalize_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, oomwoo_localization_msgs, srv, Relocalize_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, oomwoo_localization_msgs, srv, Relocalize_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_oomwoo_localization_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, oomwoo_localization_msgs, srv, Relocalize)(void) {
  if (!oomwoo_localization_msgs__srv__detail__relocalize__rosidl_typesupport_introspection_c__Relocalize_service_type_support_handle.typesupport_identifier) {
    oomwoo_localization_msgs__srv__detail__relocalize__rosidl_typesupport_introspection_c__Relocalize_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)oomwoo_localization_msgs__srv__detail__relocalize__rosidl_typesupport_introspection_c__Relocalize_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, oomwoo_localization_msgs, srv, Relocalize_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, oomwoo_localization_msgs, srv, Relocalize_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, oomwoo_localization_msgs, srv, Relocalize_Event)()->data;
  }

  return &oomwoo_localization_msgs__srv__detail__relocalize__rosidl_typesupport_introspection_c__Relocalize_service_type_support_handle;
}
