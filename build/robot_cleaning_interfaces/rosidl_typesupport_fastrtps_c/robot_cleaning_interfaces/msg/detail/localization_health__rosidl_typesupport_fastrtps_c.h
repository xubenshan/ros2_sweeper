// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from robot_cleaning_interfaces:msg/LocalizationHealth.idl
// generated code does not contain a copyright notice
#ifndef ROBOT_CLEANING_INTERFACES__MSG__DETAIL__LOCALIZATION_HEALTH__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define ROBOT_CLEANING_INTERFACES__MSG__DETAIL__LOCALIZATION_HEALTH__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "robot_cleaning_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "robot_cleaning_interfaces/msg/detail/localization_health__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_cleaning_interfaces
bool cdr_serialize_robot_cleaning_interfaces__msg__LocalizationHealth(
  const robot_cleaning_interfaces__msg__LocalizationHealth * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_cleaning_interfaces
bool cdr_deserialize_robot_cleaning_interfaces__msg__LocalizationHealth(
  eprosima::fastcdr::Cdr &,
  robot_cleaning_interfaces__msg__LocalizationHealth * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_cleaning_interfaces
size_t get_serialized_size_robot_cleaning_interfaces__msg__LocalizationHealth(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_cleaning_interfaces
size_t max_serialized_size_robot_cleaning_interfaces__msg__LocalizationHealth(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_cleaning_interfaces
bool cdr_serialize_key_robot_cleaning_interfaces__msg__LocalizationHealth(
  const robot_cleaning_interfaces__msg__LocalizationHealth * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_cleaning_interfaces
size_t get_serialized_size_key_robot_cleaning_interfaces__msg__LocalizationHealth(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_cleaning_interfaces
size_t max_serialized_size_key_robot_cleaning_interfaces__msg__LocalizationHealth(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_cleaning_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_cleaning_interfaces, msg, LocalizationHealth)();

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_CLEANING_INTERFACES__MSG__DETAIL__LOCALIZATION_HEALTH__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
