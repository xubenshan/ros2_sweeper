// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robot_cleaning_interfaces:msg/CoverageStatus.idl
// generated code does not contain a copyright notice
#include "robot_cleaning_interfaces/msg/detail/coverage_status__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `task_id`
#include "rosidl_runtime_c/string_functions.h"
// Member `covered`
#include "nav_msgs/msg/detail/occupancy_grid__functions.h"

bool
robot_cleaning_interfaces__msg__CoverageStatus__init(robot_cleaning_interfaces__msg__CoverageStatus * msg)
{
  if (!msg) {
    return false;
  }
  // task_id
  if (!rosidl_runtime_c__String__init(&msg->task_id)) {
    robot_cleaning_interfaces__msg__CoverageStatus__fini(msg);
    return false;
  }
  // coverage
  // path_length_m
  // covered
  if (!nav_msgs__msg__OccupancyGrid__init(&msg->covered)) {
    robot_cleaning_interfaces__msg__CoverageStatus__fini(msg);
    return false;
  }
  return true;
}

void
robot_cleaning_interfaces__msg__CoverageStatus__fini(robot_cleaning_interfaces__msg__CoverageStatus * msg)
{
  if (!msg) {
    return;
  }
  // task_id
  rosidl_runtime_c__String__fini(&msg->task_id);
  // coverage
  // path_length_m
  // covered
  nav_msgs__msg__OccupancyGrid__fini(&msg->covered);
}

bool
robot_cleaning_interfaces__msg__CoverageStatus__are_equal(const robot_cleaning_interfaces__msg__CoverageStatus * lhs, const robot_cleaning_interfaces__msg__CoverageStatus * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // task_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->task_id), &(rhs->task_id)))
  {
    return false;
  }
  // coverage
  if (lhs->coverage != rhs->coverage) {
    return false;
  }
  // path_length_m
  if (lhs->path_length_m != rhs->path_length_m) {
    return false;
  }
  // covered
  if (!nav_msgs__msg__OccupancyGrid__are_equal(
      &(lhs->covered), &(rhs->covered)))
  {
    return false;
  }
  return true;
}

bool
robot_cleaning_interfaces__msg__CoverageStatus__copy(
  const robot_cleaning_interfaces__msg__CoverageStatus * input,
  robot_cleaning_interfaces__msg__CoverageStatus * output)
{
  if (!input || !output) {
    return false;
  }
  // task_id
  if (!rosidl_runtime_c__String__copy(
      &(input->task_id), &(output->task_id)))
  {
    return false;
  }
  // coverage
  output->coverage = input->coverage;
  // path_length_m
  output->path_length_m = input->path_length_m;
  // covered
  if (!nav_msgs__msg__OccupancyGrid__copy(
      &(input->covered), &(output->covered)))
  {
    return false;
  }
  return true;
}

robot_cleaning_interfaces__msg__CoverageStatus *
robot_cleaning_interfaces__msg__CoverageStatus__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__msg__CoverageStatus * msg = (robot_cleaning_interfaces__msg__CoverageStatus *)allocator.allocate(sizeof(robot_cleaning_interfaces__msg__CoverageStatus), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_cleaning_interfaces__msg__CoverageStatus));
  bool success = robot_cleaning_interfaces__msg__CoverageStatus__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_cleaning_interfaces__msg__CoverageStatus__destroy(robot_cleaning_interfaces__msg__CoverageStatus * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_cleaning_interfaces__msg__CoverageStatus__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_cleaning_interfaces__msg__CoverageStatus__Sequence__init(robot_cleaning_interfaces__msg__CoverageStatus__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__msg__CoverageStatus * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(robot_cleaning_interfaces__msg__CoverageStatus)) {
      return false;
    }
    data = (robot_cleaning_interfaces__msg__CoverageStatus *)allocator.zero_allocate(size, sizeof(robot_cleaning_interfaces__msg__CoverageStatus), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_cleaning_interfaces__msg__CoverageStatus__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_cleaning_interfaces__msg__CoverageStatus__fini(&data[i - 1]);
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
robot_cleaning_interfaces__msg__CoverageStatus__Sequence__fini(robot_cleaning_interfaces__msg__CoverageStatus__Sequence * array)
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
      robot_cleaning_interfaces__msg__CoverageStatus__fini(&array->data[i]);
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

robot_cleaning_interfaces__msg__CoverageStatus__Sequence *
robot_cleaning_interfaces__msg__CoverageStatus__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__msg__CoverageStatus__Sequence * array = (robot_cleaning_interfaces__msg__CoverageStatus__Sequence *)allocator.allocate(sizeof(robot_cleaning_interfaces__msg__CoverageStatus__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_cleaning_interfaces__msg__CoverageStatus__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_cleaning_interfaces__msg__CoverageStatus__Sequence__destroy(robot_cleaning_interfaces__msg__CoverageStatus__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_cleaning_interfaces__msg__CoverageStatus__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_cleaning_interfaces__msg__CoverageStatus__Sequence__are_equal(const robot_cleaning_interfaces__msg__CoverageStatus__Sequence * lhs, const robot_cleaning_interfaces__msg__CoverageStatus__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_cleaning_interfaces__msg__CoverageStatus__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_cleaning_interfaces__msg__CoverageStatus__Sequence__copy(
  const robot_cleaning_interfaces__msg__CoverageStatus__Sequence * input,
  robot_cleaning_interfaces__msg__CoverageStatus__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(robot_cleaning_interfaces__msg__CoverageStatus)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(robot_cleaning_interfaces__msg__CoverageStatus);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_cleaning_interfaces__msg__CoverageStatus * data =
      (robot_cleaning_interfaces__msg__CoverageStatus *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_cleaning_interfaces__msg__CoverageStatus__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_cleaning_interfaces__msg__CoverageStatus__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_cleaning_interfaces__msg__CoverageStatus__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
