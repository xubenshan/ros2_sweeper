// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_cleaning_interfaces:msg/CoverageStatus.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "robot_cleaning_interfaces/msg/coverage_status.h"


#ifndef ROBOT_CLEANING_INTERFACES__MSG__DETAIL__COVERAGE_STATUS__STRUCT_H_
#define ROBOT_CLEANING_INTERFACES__MSG__DETAIL__COVERAGE_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'task_id'
#include "rosidl_runtime_c/string.h"
// Member 'covered'
#include "nav_msgs/msg/detail/occupancy_grid__struct.h"

/// Struct defined in msg/CoverageStatus in the package robot_cleaning_interfaces.
typedef struct robot_cleaning_interfaces__msg__CoverageStatus
{
  rosidl_runtime_c__String task_id;
  float coverage;
  double path_length_m;
  nav_msgs__msg__OccupancyGrid covered;
} robot_cleaning_interfaces__msg__CoverageStatus;

// Struct for a sequence of robot_cleaning_interfaces__msg__CoverageStatus.
typedef struct robot_cleaning_interfaces__msg__CoverageStatus__Sequence
{
  robot_cleaning_interfaces__msg__CoverageStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_cleaning_interfaces__msg__CoverageStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_CLEANING_INTERFACES__MSG__DETAIL__COVERAGE_STATUS__STRUCT_H_
