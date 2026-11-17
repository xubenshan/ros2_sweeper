// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robot_cleaning_interfaces:msg/LocalizationHealth.idl
// generated code does not contain a copyright notice
#include "robot_cleaning_interfaces/msg/detail/localization_health__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `reason`
#include "rosidl_runtime_c/string_functions.h"

bool
robot_cleaning_interfaces__msg__LocalizationHealth__init(robot_cleaning_interfaces__msg__LocalizationHealth * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    robot_cleaning_interfaces__msg__LocalizationHealth__fini(msg);
    return false;
  }
  // state
  // healthy
  // covariance_xy
  // lost_covariance_threshold
  // pose_age_s
  // reason
  if (!rosidl_runtime_c__String__init(&msg->reason)) {
    robot_cleaning_interfaces__msg__LocalizationHealth__fini(msg);
    return false;
  }
  return true;
}

void
robot_cleaning_interfaces__msg__LocalizationHealth__fini(robot_cleaning_interfaces__msg__LocalizationHealth * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // state
  // healthy
  // covariance_xy
  // lost_covariance_threshold
  // pose_age_s
  // reason
  rosidl_runtime_c__String__fini(&msg->reason);
}

bool
robot_cleaning_interfaces__msg__LocalizationHealth__are_equal(const robot_cleaning_interfaces__msg__LocalizationHealth * lhs, const robot_cleaning_interfaces__msg__LocalizationHealth * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // state
  if (lhs->state != rhs->state) {
    return false;
  }
  // healthy
  if (lhs->healthy != rhs->healthy) {
    return false;
  }
  // covariance_xy
  if (lhs->covariance_xy != rhs->covariance_xy) {
    return false;
  }
  // lost_covariance_threshold
  if (lhs->lost_covariance_threshold != rhs->lost_covariance_threshold) {
    return false;
  }
  // pose_age_s
  if (lhs->pose_age_s != rhs->pose_age_s) {
    return false;
  }
  // reason
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->reason), &(rhs->reason)))
  {
    return false;
  }
  return true;
}

bool
robot_cleaning_interfaces__msg__LocalizationHealth__copy(
  const robot_cleaning_interfaces__msg__LocalizationHealth * input,
  robot_cleaning_interfaces__msg__LocalizationHealth * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // state
  output->state = input->state;
  // healthy
  output->healthy = input->healthy;
  // covariance_xy
  output->covariance_xy = input->covariance_xy;
  // lost_covariance_threshold
  output->lost_covariance_threshold = input->lost_covariance_threshold;
  // pose_age_s
  output->pose_age_s = input->pose_age_s;
  // reason
  if (!rosidl_runtime_c__String__copy(
      &(input->reason), &(output->reason)))
  {
    return false;
  }
  return true;
}

robot_cleaning_interfaces__msg__LocalizationHealth *
robot_cleaning_interfaces__msg__LocalizationHealth__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__msg__LocalizationHealth * msg = (robot_cleaning_interfaces__msg__LocalizationHealth *)allocator.allocate(sizeof(robot_cleaning_interfaces__msg__LocalizationHealth), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_cleaning_interfaces__msg__LocalizationHealth));
  bool success = robot_cleaning_interfaces__msg__LocalizationHealth__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_cleaning_interfaces__msg__LocalizationHealth__destroy(robot_cleaning_interfaces__msg__LocalizationHealth * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_cleaning_interfaces__msg__LocalizationHealth__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_cleaning_interfaces__msg__LocalizationHealth__Sequence__init(robot_cleaning_interfaces__msg__LocalizationHealth__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__msg__LocalizationHealth * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(robot_cleaning_interfaces__msg__LocalizationHealth)) {
      return false;
    }
    data = (robot_cleaning_interfaces__msg__LocalizationHealth *)allocator.zero_allocate(size, sizeof(robot_cleaning_interfaces__msg__LocalizationHealth), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_cleaning_interfaces__msg__LocalizationHealth__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_cleaning_interfaces__msg__LocalizationHealth__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
robot_cleaning_interfaces__msg__LocalizationHealth__Sequence__fini(robot_cleaning_interfaces__msg__LocalizationHealth__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      robot_cleaning_interfaces__msg__LocalizationHealth__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

robot_cleaning_interfaces__msg__LocalizationHealth__Sequence *
robot_cleaning_interfaces__msg__LocalizationHealth__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__msg__LocalizationHealth__Sequence * array = (robot_cleaning_interfaces__msg__LocalizationHealth__Sequence *)allocator.allocate(sizeof(robot_cleaning_interfaces__msg__LocalizationHealth__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_cleaning_interfaces__msg__LocalizationHealth__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_cleaning_interfaces__msg__LocalizationHealth__Sequence__destroy(robot_cleaning_interfaces__msg__LocalizationHealth__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_cleaning_interfaces__msg__LocalizationHealth__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_cleaning_interfaces__msg__LocalizationHealth__Sequence__are_equal(const robot_cleaning_interfaces__msg__LocalizationHealth__Sequence * lhs, const robot_cleaning_interfaces__msg__LocalizationHealth__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_cleaning_interfaces__msg__LocalizationHealth__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_cleaning_interfaces__msg__LocalizationHealth__Sequence__copy(
  const robot_cleaning_interfaces__msg__LocalizationHealth__Sequence * input,
  robot_cleaning_interfaces__msg__LocalizationHealth__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(robot_cleaning_interfaces__msg__LocalizationHealth)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(robot_cleaning_interfaces__msg__LocalizationHealth);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_cleaning_interfaces__msg__LocalizationHealth * data =
      (robot_cleaning_interfaces__msg__LocalizationHealth *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_cleaning_interfaces__msg__LocalizationHealth__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_cleaning_interfaces__msg__LocalizationHealth__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_cleaning_interfaces__msg__LocalizationHealth__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
