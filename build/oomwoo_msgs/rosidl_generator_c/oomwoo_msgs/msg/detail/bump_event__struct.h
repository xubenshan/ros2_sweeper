// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from oomwoo_msgs:msg/BumpEvent.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "oomwoo_msgs/msg/bump_event.h"


#ifndef OOMWOO_MSGS__MSG__DETAIL__BUMP_EVENT__STRUCT_H_
#define OOMWOO_MSGS__MSG__DETAIL__BUMP_EVENT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

/// Constant 'SIDE_BOTH'.
enum
{
  oomwoo_msgs__msg__BumpEvent__SIDE_BOTH = 0
};

/// Constant 'SIDE_LEFT'.
enum
{
  oomwoo_msgs__msg__BumpEvent__SIDE_LEFT = 1
};

/// Constant 'SIDE_RIGHT'.
enum
{
  oomwoo_msgs__msg__BumpEvent__SIDE_RIGHT = 2
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'contact'
// Member 'robot'
// Member 'approach'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/BumpEvent in the package oomwoo_msgs.
/**
  * A localized bump: where the vacuum physically touched something solid, and how
  * it got there. Built by the bump_map node from the two bumper switches + TF.
  *
  * The bump map is the tactile keep-out layer: LiDAR/cameras see couch skirts, bed
  * valances and curtains as solid, but only a physical contact proves something is
  * truly solid, so a coverage planner can still clean under/through the rest.
 */
typedef struct oomwoo_msgs__msg__BumpEvent
{
  /// header.frame_id = map (or odom); stamp = bump time
  std_msgs__msg__Header header;
  /// estimated contact point on the obstacle surface
  geometry_msgs__msg__Point contact;
  /// robot base_footprint at the bump
  geometry_msgs__msg__Point robot;
  /// robot base_footprint a moment before the bump
  geometry_msgs__msg__Point approach;
  /// robot heading at the bump (rad, in header.frame_id)
  double heading;
  /// which bumper switch(es) fired (see constants)
  uint8_t side;
  /// Richer signal from optical-interrupter bumpers; all 0.0 when only the binary
  /// left/right switches are available (current sim + simplest hardware). *_depress
  /// is 0..1 (how far that side is pressed); *_rate is the press rate (1/s). The
  /// left/right depress RATIO estimates the contact angle within the arc, replacing
  /// the geometric guess bump_map makes from binary switches.
  float left_depress;
  float right_depress;
  float left_rate;
  float right_rate;
} oomwoo_msgs__msg__BumpEvent;

// Struct for a sequence of oomwoo_msgs__msg__BumpEvent.
typedef struct oomwoo_msgs__msg__BumpEvent__Sequence
{
  oomwoo_msgs__msg__BumpEvent * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} oomwoo_msgs__msg__BumpEvent__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // OOMWOO_MSGS__MSG__DETAIL__BUMP_EVENT__STRUCT_H_
