// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robot_cleaning_interfaces:action/CleanTask.idl
// generated code does not contain a copyright notice
#include "robot_cleaning_interfaces/action/detail/clean_task__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `task_id`
// Member `regions`
#include "rosidl_runtime_c/string_functions.h"

bool
robot_cleaning_interfaces__action__CleanTask_Goal__init(robot_cleaning_interfaces__action__CleanTask_Goal * msg)
{
  if (!msg) {
    return false;
  }
  // task_id
  if (!rosidl_runtime_c__String__init(&msg->task_id)) {
    robot_cleaning_interfaces__action__CleanTask_Goal__fini(msg);
    return false;
  }
  // mode
  // regions
  if (!rosidl_runtime_c__String__Sequence__init(&msg->regions, 0)) {
    robot_cleaning_interfaces__action__CleanTask_Goal__fini(msg);
    return false;
  }
  // target_coverage
  // resume_checkpoint
  return true;
}

void
robot_cleaning_interfaces__action__CleanTask_Goal__fini(robot_cleaning_interfaces__action__CleanTask_Goal * msg)
{
  if (!msg) {
    return;
  }
  // task_id
  rosidl_runtime_c__String__fini(&msg->task_id);
  // mode
  // regions
  rosidl_runtime_c__String__Sequence__fini(&msg->regions);
  // target_coverage
  // resume_checkpoint
}

bool
robot_cleaning_interfaces__action__CleanTask_Goal__are_equal(const robot_cleaning_interfaces__action__CleanTask_Goal * lhs, const robot_cleaning_interfaces__action__CleanTask_Goal * rhs)
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
  // mode
  if (lhs->mode != rhs->mode) {
    return false;
  }
  // regions
  if (!rosidl_runtime_c__String__Sequence__are_equal(
      &(lhs->regions), &(rhs->regions)))
  {
    return false;
  }
  // target_coverage
  if (lhs->target_coverage != rhs->target_coverage) {
    return false;
  }
  // resume_checkpoint
  if (lhs->resume_checkpoint != rhs->resume_checkpoint) {
    return false;
  }
  return true;
}

bool
robot_cleaning_interfaces__action__CleanTask_Goal__copy(
  const robot_cleaning_interfaces__action__CleanTask_Goal * input,
  robot_cleaning_interfaces__action__CleanTask_Goal * output)
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
  // mode
  output->mode = input->mode;
  // regions
  if (!rosidl_runtime_c__String__Sequence__copy(
      &(input->regions), &(output->regions)))
  {
    return false;
  }
  // target_coverage
  output->target_coverage = input->target_coverage;
  // resume_checkpoint
  output->resume_checkpoint = input->resume_checkpoint;
  return true;
}

robot_cleaning_interfaces__action__CleanTask_Goal *
robot_cleaning_interfaces__action__CleanTask_Goal__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_Goal * msg = (robot_cleaning_interfaces__action__CleanTask_Goal *)allocator.allocate(sizeof(robot_cleaning_interfaces__action__CleanTask_Goal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_cleaning_interfaces__action__CleanTask_Goal));
  bool success = robot_cleaning_interfaces__action__CleanTask_Goal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_cleaning_interfaces__action__CleanTask_Goal__destroy(robot_cleaning_interfaces__action__CleanTask_Goal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_cleaning_interfaces__action__CleanTask_Goal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_cleaning_interfaces__action__CleanTask_Goal__Sequence__init(robot_cleaning_interfaces__action__CleanTask_Goal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_Goal * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(robot_cleaning_interfaces__action__CleanTask_Goal)) {
      return false;
    }
    data = (robot_cleaning_interfaces__action__CleanTask_Goal *)allocator.zero_allocate(size, sizeof(robot_cleaning_interfaces__action__CleanTask_Goal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_cleaning_interfaces__action__CleanTask_Goal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_cleaning_interfaces__action__CleanTask_Goal__fini(&data[i - 1]);
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
robot_cleaning_interfaces__action__CleanTask_Goal__Sequence__fini(robot_cleaning_interfaces__action__CleanTask_Goal__Sequence * array)
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
      robot_cleaning_interfaces__action__CleanTask_Goal__fini(&array->data[i]);
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

robot_cleaning_interfaces__action__CleanTask_Goal__Sequence *
robot_cleaning_interfaces__action__CleanTask_Goal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_Goal__Sequence * array = (robot_cleaning_interfaces__action__CleanTask_Goal__Sequence *)allocator.allocate(sizeof(robot_cleaning_interfaces__action__CleanTask_Goal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_cleaning_interfaces__action__CleanTask_Goal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_cleaning_interfaces__action__CleanTask_Goal__Sequence__destroy(robot_cleaning_interfaces__action__CleanTask_Goal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_cleaning_interfaces__action__CleanTask_Goal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_cleaning_interfaces__action__CleanTask_Goal__Sequence__are_equal(const robot_cleaning_interfaces__action__CleanTask_Goal__Sequence * lhs, const robot_cleaning_interfaces__action__CleanTask_Goal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_cleaning_interfaces__action__CleanTask_Goal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_cleaning_interfaces__action__CleanTask_Goal__Sequence__copy(
  const robot_cleaning_interfaces__action__CleanTask_Goal__Sequence * input,
  robot_cleaning_interfaces__action__CleanTask_Goal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(robot_cleaning_interfaces__action__CleanTask_Goal)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(robot_cleaning_interfaces__action__CleanTask_Goal);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_cleaning_interfaces__action__CleanTask_Goal * data =
      (robot_cleaning_interfaces__action__CleanTask_Goal *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_cleaning_interfaces__action__CleanTask_Goal__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_cleaning_interfaces__action__CleanTask_Goal__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_cleaning_interfaces__action__CleanTask_Goal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `reason`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
robot_cleaning_interfaces__action__CleanTask_Result__init(robot_cleaning_interfaces__action__CleanTask_Result * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // reason
  if (!rosidl_runtime_c__String__init(&msg->reason)) {
    robot_cleaning_interfaces__action__CleanTask_Result__fini(msg);
    return false;
  }
  // coverage
  // path_length_m
  // completed_waypoints
  // failed_waypoints
  return true;
}

void
robot_cleaning_interfaces__action__CleanTask_Result__fini(robot_cleaning_interfaces__action__CleanTask_Result * msg)
{
  if (!msg) {
    return;
  }
  // success
  // reason
  rosidl_runtime_c__String__fini(&msg->reason);
  // coverage
  // path_length_m
  // completed_waypoints
  // failed_waypoints
}

bool
robot_cleaning_interfaces__action__CleanTask_Result__are_equal(const robot_cleaning_interfaces__action__CleanTask_Result * lhs, const robot_cleaning_interfaces__action__CleanTask_Result * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // reason
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->reason), &(rhs->reason)))
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
  // completed_waypoints
  if (lhs->completed_waypoints != rhs->completed_waypoints) {
    return false;
  }
  // failed_waypoints
  if (lhs->failed_waypoints != rhs->failed_waypoints) {
    return false;
  }
  return true;
}

bool
robot_cleaning_interfaces__action__CleanTask_Result__copy(
  const robot_cleaning_interfaces__action__CleanTask_Result * input,
  robot_cleaning_interfaces__action__CleanTask_Result * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // reason
  if (!rosidl_runtime_c__String__copy(
      &(input->reason), &(output->reason)))
  {
    return false;
  }
  // coverage
  output->coverage = input->coverage;
  // path_length_m
  output->path_length_m = input->path_length_m;
  // completed_waypoints
  output->completed_waypoints = input->completed_waypoints;
  // failed_waypoints
  output->failed_waypoints = input->failed_waypoints;
  return true;
}

robot_cleaning_interfaces__action__CleanTask_Result *
robot_cleaning_interfaces__action__CleanTask_Result__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_Result * msg = (robot_cleaning_interfaces__action__CleanTask_Result *)allocator.allocate(sizeof(robot_cleaning_interfaces__action__CleanTask_Result), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_cleaning_interfaces__action__CleanTask_Result));
  bool success = robot_cleaning_interfaces__action__CleanTask_Result__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_cleaning_interfaces__action__CleanTask_Result__destroy(robot_cleaning_interfaces__action__CleanTask_Result * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_cleaning_interfaces__action__CleanTask_Result__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_cleaning_interfaces__action__CleanTask_Result__Sequence__init(robot_cleaning_interfaces__action__CleanTask_Result__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_Result * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(robot_cleaning_interfaces__action__CleanTask_Result)) {
      return false;
    }
    data = (robot_cleaning_interfaces__action__CleanTask_Result *)allocator.zero_allocate(size, sizeof(robot_cleaning_interfaces__action__CleanTask_Result), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_cleaning_interfaces__action__CleanTask_Result__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_cleaning_interfaces__action__CleanTask_Result__fini(&data[i - 1]);
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
robot_cleaning_interfaces__action__CleanTask_Result__Sequence__fini(robot_cleaning_interfaces__action__CleanTask_Result__Sequence * array)
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
      robot_cleaning_interfaces__action__CleanTask_Result__fini(&array->data[i]);
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

robot_cleaning_interfaces__action__CleanTask_Result__Sequence *
robot_cleaning_interfaces__action__CleanTask_Result__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_Result__Sequence * array = (robot_cleaning_interfaces__action__CleanTask_Result__Sequence *)allocator.allocate(sizeof(robot_cleaning_interfaces__action__CleanTask_Result__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_cleaning_interfaces__action__CleanTask_Result__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_cleaning_interfaces__action__CleanTask_Result__Sequence__destroy(robot_cleaning_interfaces__action__CleanTask_Result__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_cleaning_interfaces__action__CleanTask_Result__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_cleaning_interfaces__action__CleanTask_Result__Sequence__are_equal(const robot_cleaning_interfaces__action__CleanTask_Result__Sequence * lhs, const robot_cleaning_interfaces__action__CleanTask_Result__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_cleaning_interfaces__action__CleanTask_Result__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_cleaning_interfaces__action__CleanTask_Result__Sequence__copy(
  const robot_cleaning_interfaces__action__CleanTask_Result__Sequence * input,
  robot_cleaning_interfaces__action__CleanTask_Result__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(robot_cleaning_interfaces__action__CleanTask_Result)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(robot_cleaning_interfaces__action__CleanTask_Result);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_cleaning_interfaces__action__CleanTask_Result * data =
      (robot_cleaning_interfaces__action__CleanTask_Result *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_cleaning_interfaces__action__CleanTask_Result__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_cleaning_interfaces__action__CleanTask_Result__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_cleaning_interfaces__action__CleanTask_Result__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `state`
// already included above
// #include "rosidl_runtime_c/string_functions.h"
// Member `current_goal`
#include "geometry_msgs/msg/detail/pose_stamped__functions.h"

bool
robot_cleaning_interfaces__action__CleanTask_Feedback__init(robot_cleaning_interfaces__action__CleanTask_Feedback * msg)
{
  if (!msg) {
    return false;
  }
  // state
  if (!rosidl_runtime_c__String__init(&msg->state)) {
    robot_cleaning_interfaces__action__CleanTask_Feedback__fini(msg);
    return false;
  }
  // coverage
  // completed_waypoints
  // total_waypoints
  // current_goal
  if (!geometry_msgs__msg__PoseStamped__init(&msg->current_goal)) {
    robot_cleaning_interfaces__action__CleanTask_Feedback__fini(msg);
    return false;
  }
  return true;
}

void
robot_cleaning_interfaces__action__CleanTask_Feedback__fini(robot_cleaning_interfaces__action__CleanTask_Feedback * msg)
{
  if (!msg) {
    return;
  }
  // state
  rosidl_runtime_c__String__fini(&msg->state);
  // coverage
  // completed_waypoints
  // total_waypoints
  // current_goal
  geometry_msgs__msg__PoseStamped__fini(&msg->current_goal);
}

bool
robot_cleaning_interfaces__action__CleanTask_Feedback__are_equal(const robot_cleaning_interfaces__action__CleanTask_Feedback * lhs, const robot_cleaning_interfaces__action__CleanTask_Feedback * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // state
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->state), &(rhs->state)))
  {
    return false;
  }
  // coverage
  if (lhs->coverage != rhs->coverage) {
    return false;
  }
  // completed_waypoints
  if (lhs->completed_waypoints != rhs->completed_waypoints) {
    return false;
  }
  // total_waypoints
  if (lhs->total_waypoints != rhs->total_waypoints) {
    return false;
  }
  // current_goal
  if (!geometry_msgs__msg__PoseStamped__are_equal(
      &(lhs->current_goal), &(rhs->current_goal)))
  {
    return false;
  }
  return true;
}

bool
robot_cleaning_interfaces__action__CleanTask_Feedback__copy(
  const robot_cleaning_interfaces__action__CleanTask_Feedback * input,
  robot_cleaning_interfaces__action__CleanTask_Feedback * output)
{
  if (!input || !output) {
    return false;
  }
  // state
  if (!rosidl_runtime_c__String__copy(
      &(input->state), &(output->state)))
  {
    return false;
  }
  // coverage
  output->coverage = input->coverage;
  // completed_waypoints
  output->completed_waypoints = input->completed_waypoints;
  // total_waypoints
  output->total_waypoints = input->total_waypoints;
  // current_goal
  if (!geometry_msgs__msg__PoseStamped__copy(
      &(input->current_goal), &(output->current_goal)))
  {
    return false;
  }
  return true;
}

robot_cleaning_interfaces__action__CleanTask_Feedback *
robot_cleaning_interfaces__action__CleanTask_Feedback__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_Feedback * msg = (robot_cleaning_interfaces__action__CleanTask_Feedback *)allocator.allocate(sizeof(robot_cleaning_interfaces__action__CleanTask_Feedback), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_cleaning_interfaces__action__CleanTask_Feedback));
  bool success = robot_cleaning_interfaces__action__CleanTask_Feedback__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_cleaning_interfaces__action__CleanTask_Feedback__destroy(robot_cleaning_interfaces__action__CleanTask_Feedback * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_cleaning_interfaces__action__CleanTask_Feedback__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence__init(robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_Feedback * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(robot_cleaning_interfaces__action__CleanTask_Feedback)) {
      return false;
    }
    data = (robot_cleaning_interfaces__action__CleanTask_Feedback *)allocator.zero_allocate(size, sizeof(robot_cleaning_interfaces__action__CleanTask_Feedback), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_cleaning_interfaces__action__CleanTask_Feedback__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_cleaning_interfaces__action__CleanTask_Feedback__fini(&data[i - 1]);
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
robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence__fini(robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence * array)
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
      robot_cleaning_interfaces__action__CleanTask_Feedback__fini(&array->data[i]);
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

robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence *
robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence * array = (robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence *)allocator.allocate(sizeof(robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence__destroy(robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence__are_equal(const robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence * lhs, const robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_cleaning_interfaces__action__CleanTask_Feedback__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence__copy(
  const robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence * input,
  robot_cleaning_interfaces__action__CleanTask_Feedback__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(robot_cleaning_interfaces__action__CleanTask_Feedback)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(robot_cleaning_interfaces__action__CleanTask_Feedback);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_cleaning_interfaces__action__CleanTask_Feedback * data =
      (robot_cleaning_interfaces__action__CleanTask_Feedback *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_cleaning_interfaces__action__CleanTask_Feedback__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_cleaning_interfaces__action__CleanTask_Feedback__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_cleaning_interfaces__action__CleanTask_Feedback__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `goal`
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__functions.h"

bool
robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__init(robot_cleaning_interfaces__action__CleanTask_SendGoal_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__fini(msg);
    return false;
  }
  // goal
  if (!robot_cleaning_interfaces__action__CleanTask_Goal__init(&msg->goal)) {
    robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__fini(msg);
    return false;
  }
  return true;
}

void
robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__fini(robot_cleaning_interfaces__action__CleanTask_SendGoal_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // goal
  robot_cleaning_interfaces__action__CleanTask_Goal__fini(&msg->goal);
}

bool
robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__are_equal(const robot_cleaning_interfaces__action__CleanTask_SendGoal_Request * lhs, const robot_cleaning_interfaces__action__CleanTask_SendGoal_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // goal
  if (!robot_cleaning_interfaces__action__CleanTask_Goal__are_equal(
      &(lhs->goal), &(rhs->goal)))
  {
    return false;
  }
  return true;
}

bool
robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__copy(
  const robot_cleaning_interfaces__action__CleanTask_SendGoal_Request * input,
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // goal
  if (!robot_cleaning_interfaces__action__CleanTask_Goal__copy(
      &(input->goal), &(output->goal)))
  {
    return false;
  }
  return true;
}

robot_cleaning_interfaces__action__CleanTask_SendGoal_Request *
robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Request * msg = (robot_cleaning_interfaces__action__CleanTask_SendGoal_Request *)allocator.allocate(sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Request));
  bool success = robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__destroy(robot_cleaning_interfaces__action__CleanTask_SendGoal_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence__init(robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Request * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Request)) {
      return false;
    }
    data = (robot_cleaning_interfaces__action__CleanTask_SendGoal_Request *)allocator.zero_allocate(size, sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__fini(&data[i - 1]);
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
robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence__fini(robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence * array)
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
      robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__fini(&array->data[i]);
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

robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence *
robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence * array = (robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence *)allocator.allocate(sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence__destroy(robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence__are_equal(const robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence * lhs, const robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence__copy(
  const robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence * input,
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Request)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_cleaning_interfaces__action__CleanTask_SendGoal_Request * data =
      (robot_cleaning_interfaces__action__CleanTask_SendGoal_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__init(robot_cleaning_interfaces__action__CleanTask_SendGoal_Response * msg)
{
  if (!msg) {
    return false;
  }
  // accepted
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__fini(msg);
    return false;
  }
  return true;
}

void
robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__fini(robot_cleaning_interfaces__action__CleanTask_SendGoal_Response * msg)
{
  if (!msg) {
    return;
  }
  // accepted
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

bool
robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__are_equal(const robot_cleaning_interfaces__action__CleanTask_SendGoal_Response * lhs, const robot_cleaning_interfaces__action__CleanTask_SendGoal_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // accepted
  if (lhs->accepted != rhs->accepted) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  return true;
}

bool
robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__copy(
  const robot_cleaning_interfaces__action__CleanTask_SendGoal_Response * input,
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // accepted
  output->accepted = input->accepted;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  return true;
}

robot_cleaning_interfaces__action__CleanTask_SendGoal_Response *
robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Response * msg = (robot_cleaning_interfaces__action__CleanTask_SendGoal_Response *)allocator.allocate(sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Response));
  bool success = robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__destroy(robot_cleaning_interfaces__action__CleanTask_SendGoal_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence__init(robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Response * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Response)) {
      return false;
    }
    data = (robot_cleaning_interfaces__action__CleanTask_SendGoal_Response *)allocator.zero_allocate(size, sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__fini(&data[i - 1]);
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
robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence__fini(robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence * array)
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
      robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__fini(&array->data[i]);
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

robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence *
robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence * array = (robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence *)allocator.allocate(sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence__destroy(robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence__are_equal(const robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence * lhs, const robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence__copy(
  const robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence * input,
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Response)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_cleaning_interfaces__action__CleanTask_SendGoal_Response * data =
      (robot_cleaning_interfaces__action__CleanTask_SendGoal_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__functions.h"

bool
robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__init(robot_cleaning_interfaces__action__CleanTask_SendGoal_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__fini(msg);
    return false;
  }
  // request
  if (!robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence__init(&msg->request, 0)) {
    robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__fini(msg);
    return false;
  }
  // response
  if (!robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence__init(&msg->response, 0)) {
    robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__fini(msg);
    return false;
  }
  return true;
}

void
robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__fini(robot_cleaning_interfaces__action__CleanTask_SendGoal_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence__fini(&msg->request);
  // response
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence__fini(&msg->response);
}

bool
robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__are_equal(const robot_cleaning_interfaces__action__CleanTask_SendGoal_Event * lhs, const robot_cleaning_interfaces__action__CleanTask_SendGoal_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__copy(
  const robot_cleaning_interfaces__action__CleanTask_SendGoal_Event * input,
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

robot_cleaning_interfaces__action__CleanTask_SendGoal_Event *
robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Event * msg = (robot_cleaning_interfaces__action__CleanTask_SendGoal_Event *)allocator.allocate(sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Event));
  bool success = robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__destroy(robot_cleaning_interfaces__action__CleanTask_SendGoal_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence__init(robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Event * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Event)) {
      return false;
    }
    data = (robot_cleaning_interfaces__action__CleanTask_SendGoal_Event *)allocator.zero_allocate(size, sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__fini(&data[i - 1]);
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
robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence__fini(robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence * array)
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
      robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__fini(&array->data[i]);
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

robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence *
robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence * array = (robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence *)allocator.allocate(sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence__destroy(robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence__are_equal(const robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence * lhs, const robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence__copy(
  const robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence * input,
  robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Event)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(robot_cleaning_interfaces__action__CleanTask_SendGoal_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_cleaning_interfaces__action__CleanTask_SendGoal_Event * data =
      (robot_cleaning_interfaces__action__CleanTask_SendGoal_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"

bool
robot_cleaning_interfaces__action__CleanTask_GetResult_Request__init(robot_cleaning_interfaces__action__CleanTask_GetResult_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    robot_cleaning_interfaces__action__CleanTask_GetResult_Request__fini(msg);
    return false;
  }
  return true;
}

void
robot_cleaning_interfaces__action__CleanTask_GetResult_Request__fini(robot_cleaning_interfaces__action__CleanTask_GetResult_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
}

bool
robot_cleaning_interfaces__action__CleanTask_GetResult_Request__are_equal(const robot_cleaning_interfaces__action__CleanTask_GetResult_Request * lhs, const robot_cleaning_interfaces__action__CleanTask_GetResult_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  return true;
}

bool
robot_cleaning_interfaces__action__CleanTask_GetResult_Request__copy(
  const robot_cleaning_interfaces__action__CleanTask_GetResult_Request * input,
  robot_cleaning_interfaces__action__CleanTask_GetResult_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  return true;
}

robot_cleaning_interfaces__action__CleanTask_GetResult_Request *
robot_cleaning_interfaces__action__CleanTask_GetResult_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_GetResult_Request * msg = (robot_cleaning_interfaces__action__CleanTask_GetResult_Request *)allocator.allocate(sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Request));
  bool success = robot_cleaning_interfaces__action__CleanTask_GetResult_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_cleaning_interfaces__action__CleanTask_GetResult_Request__destroy(robot_cleaning_interfaces__action__CleanTask_GetResult_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_cleaning_interfaces__action__CleanTask_GetResult_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence__init(robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_GetResult_Request * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Request)) {
      return false;
    }
    data = (robot_cleaning_interfaces__action__CleanTask_GetResult_Request *)allocator.zero_allocate(size, sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_cleaning_interfaces__action__CleanTask_GetResult_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_cleaning_interfaces__action__CleanTask_GetResult_Request__fini(&data[i - 1]);
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
robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence__fini(robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence * array)
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
      robot_cleaning_interfaces__action__CleanTask_GetResult_Request__fini(&array->data[i]);
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

robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence *
robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence * array = (robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence *)allocator.allocate(sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence__destroy(robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence__are_equal(const robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence * lhs, const robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_cleaning_interfaces__action__CleanTask_GetResult_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence__copy(
  const robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence * input,
  robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Request)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_cleaning_interfaces__action__CleanTask_GetResult_Request * data =
      (robot_cleaning_interfaces__action__CleanTask_GetResult_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_cleaning_interfaces__action__CleanTask_GetResult_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_cleaning_interfaces__action__CleanTask_GetResult_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_cleaning_interfaces__action__CleanTask_GetResult_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `result`
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__functions.h"

bool
robot_cleaning_interfaces__action__CleanTask_GetResult_Response__init(robot_cleaning_interfaces__action__CleanTask_GetResult_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  // result
  if (!robot_cleaning_interfaces__action__CleanTask_Result__init(&msg->result)) {
    robot_cleaning_interfaces__action__CleanTask_GetResult_Response__fini(msg);
    return false;
  }
  return true;
}

void
robot_cleaning_interfaces__action__CleanTask_GetResult_Response__fini(robot_cleaning_interfaces__action__CleanTask_GetResult_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  // result
  robot_cleaning_interfaces__action__CleanTask_Result__fini(&msg->result);
}

bool
robot_cleaning_interfaces__action__CleanTask_GetResult_Response__are_equal(const robot_cleaning_interfaces__action__CleanTask_GetResult_Response * lhs, const robot_cleaning_interfaces__action__CleanTask_GetResult_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status
  if (lhs->status != rhs->status) {
    return false;
  }
  // result
  if (!robot_cleaning_interfaces__action__CleanTask_Result__are_equal(
      &(lhs->result), &(rhs->result)))
  {
    return false;
  }
  return true;
}

bool
robot_cleaning_interfaces__action__CleanTask_GetResult_Response__copy(
  const robot_cleaning_interfaces__action__CleanTask_GetResult_Response * input,
  robot_cleaning_interfaces__action__CleanTask_GetResult_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // status
  output->status = input->status;
  // result
  if (!robot_cleaning_interfaces__action__CleanTask_Result__copy(
      &(input->result), &(output->result)))
  {
    return false;
  }
  return true;
}

robot_cleaning_interfaces__action__CleanTask_GetResult_Response *
robot_cleaning_interfaces__action__CleanTask_GetResult_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_GetResult_Response * msg = (robot_cleaning_interfaces__action__CleanTask_GetResult_Response *)allocator.allocate(sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Response));
  bool success = robot_cleaning_interfaces__action__CleanTask_GetResult_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_cleaning_interfaces__action__CleanTask_GetResult_Response__destroy(robot_cleaning_interfaces__action__CleanTask_GetResult_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_cleaning_interfaces__action__CleanTask_GetResult_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence__init(robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_GetResult_Response * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Response)) {
      return false;
    }
    data = (robot_cleaning_interfaces__action__CleanTask_GetResult_Response *)allocator.zero_allocate(size, sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_cleaning_interfaces__action__CleanTask_GetResult_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_cleaning_interfaces__action__CleanTask_GetResult_Response__fini(&data[i - 1]);
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
robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence__fini(robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence * array)
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
      robot_cleaning_interfaces__action__CleanTask_GetResult_Response__fini(&array->data[i]);
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

robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence *
robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence * array = (robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence *)allocator.allocate(sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence__destroy(robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence__are_equal(const robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence * lhs, const robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_cleaning_interfaces__action__CleanTask_GetResult_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence__copy(
  const robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence * input,
  robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Response)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_cleaning_interfaces__action__CleanTask_GetResult_Response * data =
      (robot_cleaning_interfaces__action__CleanTask_GetResult_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_cleaning_interfaces__action__CleanTask_GetResult_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_cleaning_interfaces__action__CleanTask_GetResult_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_cleaning_interfaces__action__CleanTask_GetResult_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
// already included above
// #include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__functions.h"

bool
robot_cleaning_interfaces__action__CleanTask_GetResult_Event__init(robot_cleaning_interfaces__action__CleanTask_GetResult_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    robot_cleaning_interfaces__action__CleanTask_GetResult_Event__fini(msg);
    return false;
  }
  // request
  if (!robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence__init(&msg->request, 0)) {
    robot_cleaning_interfaces__action__CleanTask_GetResult_Event__fini(msg);
    return false;
  }
  // response
  if (!robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence__init(&msg->response, 0)) {
    robot_cleaning_interfaces__action__CleanTask_GetResult_Event__fini(msg);
    return false;
  }
  return true;
}

void
robot_cleaning_interfaces__action__CleanTask_GetResult_Event__fini(robot_cleaning_interfaces__action__CleanTask_GetResult_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence__fini(&msg->request);
  // response
  robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence__fini(&msg->response);
}

bool
robot_cleaning_interfaces__action__CleanTask_GetResult_Event__are_equal(const robot_cleaning_interfaces__action__CleanTask_GetResult_Event * lhs, const robot_cleaning_interfaces__action__CleanTask_GetResult_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
robot_cleaning_interfaces__action__CleanTask_GetResult_Event__copy(
  const robot_cleaning_interfaces__action__CleanTask_GetResult_Event * input,
  robot_cleaning_interfaces__action__CleanTask_GetResult_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!robot_cleaning_interfaces__action__CleanTask_GetResult_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!robot_cleaning_interfaces__action__CleanTask_GetResult_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

robot_cleaning_interfaces__action__CleanTask_GetResult_Event *
robot_cleaning_interfaces__action__CleanTask_GetResult_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_GetResult_Event * msg = (robot_cleaning_interfaces__action__CleanTask_GetResult_Event *)allocator.allocate(sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Event));
  bool success = robot_cleaning_interfaces__action__CleanTask_GetResult_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_cleaning_interfaces__action__CleanTask_GetResult_Event__destroy(robot_cleaning_interfaces__action__CleanTask_GetResult_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_cleaning_interfaces__action__CleanTask_GetResult_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence__init(robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_GetResult_Event * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Event)) {
      return false;
    }
    data = (robot_cleaning_interfaces__action__CleanTask_GetResult_Event *)allocator.zero_allocate(size, sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_cleaning_interfaces__action__CleanTask_GetResult_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_cleaning_interfaces__action__CleanTask_GetResult_Event__fini(&data[i - 1]);
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
robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence__fini(robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence * array)
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
      robot_cleaning_interfaces__action__CleanTask_GetResult_Event__fini(&array->data[i]);
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

robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence *
robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence * array = (robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence *)allocator.allocate(sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence__destroy(robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence__are_equal(const robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence * lhs, const robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_cleaning_interfaces__action__CleanTask_GetResult_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence__copy(
  const robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence * input,
  robot_cleaning_interfaces__action__CleanTask_GetResult_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Event)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(robot_cleaning_interfaces__action__CleanTask_GetResult_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_cleaning_interfaces__action__CleanTask_GetResult_Event * data =
      (robot_cleaning_interfaces__action__CleanTask_GetResult_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_cleaning_interfaces__action__CleanTask_GetResult_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_cleaning_interfaces__action__CleanTask_GetResult_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_cleaning_interfaces__action__CleanTask_GetResult_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `feedback`
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__functions.h"

bool
robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__init(robot_cleaning_interfaces__action__CleanTask_FeedbackMessage * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__fini(msg);
    return false;
  }
  // feedback
  if (!robot_cleaning_interfaces__action__CleanTask_Feedback__init(&msg->feedback)) {
    robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__fini(msg);
    return false;
  }
  return true;
}

void
robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__fini(robot_cleaning_interfaces__action__CleanTask_FeedbackMessage * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // feedback
  robot_cleaning_interfaces__action__CleanTask_Feedback__fini(&msg->feedback);
}

bool
robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__are_equal(const robot_cleaning_interfaces__action__CleanTask_FeedbackMessage * lhs, const robot_cleaning_interfaces__action__CleanTask_FeedbackMessage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // feedback
  if (!robot_cleaning_interfaces__action__CleanTask_Feedback__are_equal(
      &(lhs->feedback), &(rhs->feedback)))
  {
    return false;
  }
  return true;
}

bool
robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__copy(
  const robot_cleaning_interfaces__action__CleanTask_FeedbackMessage * input,
  robot_cleaning_interfaces__action__CleanTask_FeedbackMessage * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // feedback
  if (!robot_cleaning_interfaces__action__CleanTask_Feedback__copy(
      &(input->feedback), &(output->feedback)))
  {
    return false;
  }
  return true;
}

robot_cleaning_interfaces__action__CleanTask_FeedbackMessage *
robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_FeedbackMessage * msg = (robot_cleaning_interfaces__action__CleanTask_FeedbackMessage *)allocator.allocate(sizeof(robot_cleaning_interfaces__action__CleanTask_FeedbackMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_cleaning_interfaces__action__CleanTask_FeedbackMessage));
  bool success = robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__destroy(robot_cleaning_interfaces__action__CleanTask_FeedbackMessage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence__init(robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_FeedbackMessage * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(robot_cleaning_interfaces__action__CleanTask_FeedbackMessage)) {
      return false;
    }
    data = (robot_cleaning_interfaces__action__CleanTask_FeedbackMessage *)allocator.zero_allocate(size, sizeof(robot_cleaning_interfaces__action__CleanTask_FeedbackMessage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__fini(&data[i - 1]);
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
robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence__fini(robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence * array)
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
      robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__fini(&array->data[i]);
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

robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence *
robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence * array = (robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence *)allocator.allocate(sizeof(robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence__destroy(robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence__are_equal(const robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence * lhs, const robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence__copy(
  const robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence * input,
  robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(robot_cleaning_interfaces__action__CleanTask_FeedbackMessage)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(robot_cleaning_interfaces__action__CleanTask_FeedbackMessage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_cleaning_interfaces__action__CleanTask_FeedbackMessage * data =
      (robot_cleaning_interfaces__action__CleanTask_FeedbackMessage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
