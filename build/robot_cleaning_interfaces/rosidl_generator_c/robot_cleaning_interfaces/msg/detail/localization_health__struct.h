// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_cleaning_interfaces:msg/LocalizationHealth.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/msg/localization_health.h"


#ifndef ROBOT_CLEANING_INTERFACES__MSG__DETAIL__LOCALIZATION_HEALTH__STRUCT_H_
#define ROBOT_CLEANING_INTERFACES__MSG__DETAIL__LOCALIZATION_HEALTH__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'UNKNOWN'.
enum
{
  robot_cleaning_interfaces__msg__LocalizationHealth__UNKNOWN = 0
};

/// Constant 'HEALTHY'.
enum
{
  robot_cleaning_interfaces__msg__LocalizationHealth__HEALTHY = 1
};

/// Constant 'DEGRADED'.
enum
{
  robot_cleaning_interfaces__msg__LocalizationHealth__DEGRADED = 2
};

/// Constant 'LOST'.
enum
{
  robot_cleaning_interfaces__msg__LocalizationHealth__LOST = 3
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'reason'
#include "rosidl_runtime_c/string.h"

/// Struct defined in msg/LocalizationHealth in the package robot_cleaning_interfaces.
typedef struct robot_cleaning_interfaces__msg__LocalizationHealth
{
  std_msgs__msg__Header header;
  uint8_t state;
  /// healthy means motion and coverage accounting may continue. A transient
  /// DEGRADED state remains operational until the configured loss hold expires.
  bool healthy;
  double covariance_xy;
  double lost_covariance_threshold;
  double pose_age_s;
  rosidl_runtime_c__String reason;
} robot_cleaning_interfaces__msg__LocalizationHealth;

// Struct for a sequence of robot_cleaning_interfaces__msg__LocalizationHealth.
typedef struct robot_cleaning_interfaces__msg__LocalizationHealth__Sequence
{
  robot_cleaning_interfaces__msg__LocalizationHealth * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_cleaning_interfaces__msg__LocalizationHealth__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_CLEANING_INTERFACES__MSG__DETAIL__LOCALIZATION_HEALTH__STRUCT_H_
