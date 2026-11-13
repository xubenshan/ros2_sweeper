// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from oomwoo_msgs:msg/BumpEvent.idl
// generated code does not contain a copyright notice
#ifndef OOMWOO_MSGS__MSG__DETAIL__BUMP_EVENT__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define OOMWOO_MSGS__MSG__DETAIL__BUMP_EVENT__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "oomwoo_msgs/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "oomwoo_msgs/msg/detail/bump_event__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_oomwoo_msgs
bool cdr_serialize_oomwoo_msgs__msg__BumpEvent(
  const oomwoo_msgs__msg__BumpEvent * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_oomwoo_msgs
bool cdr_deserialize_oomwoo_msgs__msg__BumpEvent(
  eprosima::fastcdr::Cdr &,
  oomwoo_msgs__msg__BumpEvent * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_oomwoo_msgs
size_t get_serialized_size_oomwoo_msgs__msg__BumpEvent(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_oomwoo_msgs
size_t max_serialized_size_oomwoo_msgs__msg__BumpEvent(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_oomwoo_msgs
bool cdr_serialize_key_oomwoo_msgs__msg__BumpEvent(
  const oomwoo_msgs__msg__BumpEvent * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_oomwoo_msgs
size_t get_serialized_size_key_oomwoo_msgs__msg__BumpEvent(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_oomwoo_msgs
size_t max_serialized_size_key_oomwoo_msgs__msg__BumpEvent(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_oomwoo_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, oomwoo_msgs, msg, BumpEvent)();

#ifdef __cplusplus
}
#endif

#endif  // OOMWOO_MSGS__MSG__DETAIL__BUMP_EVENT__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
