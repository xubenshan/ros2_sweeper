// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robot_cleaning_interfaces:msg/CleaningEvent.idl
// generated code does not contain a copyright notice
#include "robot_cleaning_interfaces/msg/detail/cleaning_event__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `task_id`
// Member `code`
// Member `state`
// Member `previous_state`
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

bool
robot_cleaning_interfaces__msg__CleaningEvent__init(robot_cleaning_interfaces__msg__CleaningEvent * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    robot_cleaning_interfaces__msg__CleaningEvent__fini(msg);
    return false;
  }
  // sequence
  // severity
  // task_id
  if (!rosidl_runtime_c__String__init(&msg->task_id)) {
    robot_cleaning_interfaces__msg__CleaningEvent__fini(msg);
    return false;
  }
  // code
  if (!rosidl_runtime_c__String__init(&msg->code)) {
    robot_cleaning_interfaces__msg__CleaningEvent__fini(msg);
    return false;
  }
  // state
  if (!rosidl_runtime_c__String__init(&msg->state)) {
    robot_cleaning_interfaces__msg__CleaningEvent__fini(msg);
    return false;
  }
  // previous_state
  if (!rosidl_runtime_c__String__init(&msg->previous_state)) {
    robot_cleaning_interfaces__msg__CleaningEvent__fini(msg);
    return false;
  }
  // recoverable
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    robot_cleaning_interfaces__msg__CleaningEvent__fini(msg);
    return false;
  }
  // coverage
  // completed_waypoints
  // failed_waypoints
  // total_waypoints
  return true;
}

void
robot_cleaning_interfaces__msg__CleaningEvent__fini(robot_cleaning_interfaces__msg__CleaningEvent * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // sequence
  // severity
  // task_id
  rosidl_runtime_c__String__fini(&msg->task_id);
  // code
  rosidl_runtime_c__String__fini(&msg->code);
  // state
  rosidl_runtime_c__String__fini(&msg->state);
  // previous_state
  rosidl_runtime_c__String__fini(&msg->previous_state);
  // recoverable
  // message
  rosidl_runtime_c__String__fini(&msg->message);
  // coverage
  // completed_waypoints
  // failed_waypoints
  // total_waypoints
}

bool
robot_cleaning_interfaces__msg__CleaningEvent__are_equal(const robot_cleaning_interfaces__msg__CleaningEvent * lhs, const robot_cleaning_interfaces__msg__CleaningEvent * rhs)
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
  // sequence
  if (lhs->sequence != rhs->sequence) {
    return false;
  }
  // severity
  if (lhs->severity != rhs->severity) {
    return false;
  }
  // task_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->task_id), &(rhs->task_id)))
  {
    return false;
  }
  // code
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->code), &(rhs->code)))
  {
    return false;
  }
  // state
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->state), &(rhs->state)))
  {
    return false;
  }
  // previous_state
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->previous_state), &(rhs->previous_state)))
  {
    return false;
  }
  // recoverable
  if (lhs->recoverable != rhs->recoverable) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
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
  // failed_waypoints
  if (lhs->failed_waypoints != rhs->failed_waypoints) {
    return false;
  }
  // total_waypoints
  if (lhs->total_waypoints != rhs->total_waypoints) {
    return false;
  }
  return true;
}

bool
robot_cleaning_interfaces__msg__CleaningEvent__copy(
  const robot_cleaning_interfaces__msg__CleaningEvent * input,
  robot_cleaning_interfaces__msg__CleaningEvent * output)
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
  // sequence
  output->sequence = input->sequence;
  // severity
  output->severity = input->severity;
  // task_id
  if (!rosidl_runtime_c__String__copy(
      &(input->task_id), &(output->task_id)))
  {
    return false;
  }
  // code
  if (!rosidl_runtime_c__String__copy(
      &(input->code), &(output->code)))
  {
    return false;
  }
  // state
  if (!rosidl_runtime_c__String__copy(
      &(input->state), &(output->state)))
  {
    return false;
  }
  // previous_state
  if (!rosidl_runtime_c__String__copy(
      &(input->previous_state), &(output->previous_state)))
  {
    return false;
  }
  // recoverable
  output->recoverable = input->recoverable;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  // coverage
  output->coverage = input->coverage;
  // completed_waypoints
  output->completed_waypoints = input->completed_waypoints;
  // failed_waypoints
  output->failed_waypoints = input->failed_waypoints;
  // total_waypoints
  output->total_waypoints = input->total_waypoints;
  return true;
}

robot_cleaning_interfaces__msg__CleaningEvent *
robot_cleaning_interfaces__msg__CleaningEvent__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__msg__CleaningEvent * msg = (robot_cleaning_interfaces__msg__CleaningEvent *)allocator.allocate(sizeof(robot_cleaning_interfaces__msg__CleaningEvent), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_cleaning_interfaces__msg__CleaningEvent));
  bool success = robot_cleaning_interfaces__msg__CleaningEvent__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_cleaning_interfaces__msg__CleaningEvent__destroy(robot_cleaning_interfaces__msg__CleaningEvent * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_cleaning_interfaces__msg__CleaningEvent__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_cleaning_interfaces__msg__CleaningEvent__Sequence__init(robot_cleaning_interfaces__msg__CleaningEvent__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__msg__CleaningEvent * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(robot_cleaning_interfaces__msg__CleaningEvent)) {
      return false;
    }
    data = (robot_cleaning_interfaces__msg__CleaningEvent *)allocator.zero_allocate(size, sizeof(robot_cleaning_interfaces__msg__CleaningEvent), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_cleaning_interfaces__msg__CleaningEvent__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_cleaning_interfaces__msg__CleaningEvent__fini(&data[i - 1]);
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
robot_cleaning_interfaces__msg__CleaningEvent__Sequence__fini(robot_cleaning_interfaces__msg__CleaningEvent__Sequence * array)
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
      robot_cleaning_interfaces__msg__CleaningEvent__fini(&array->data[i]);
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

robot_cleaning_interfaces__msg__CleaningEvent__Sequence *
robot_cleaning_interfaces__msg__CleaningEvent__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_cleaning_interfaces__msg__CleaningEvent__Sequence * array = (robot_cleaning_interfaces__msg__CleaningEvent__Sequence *)allocator.allocate(sizeof(robot_cleaning_interfaces__msg__CleaningEvent__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_cleaning_interfaces__msg__CleaningEvent__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_cleaning_interfaces__msg__CleaningEvent__Sequence__destroy(robot_cleaning_interfaces__msg__CleaningEvent__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_cleaning_interfaces__msg__CleaningEvent__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_cleaning_interfaces__msg__CleaningEvent__Sequence__are_equal(const robot_cleaning_interfaces__msg__CleaningEvent__Sequence * lhs, const robot_cleaning_interfaces__msg__CleaningEvent__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_cleaning_interfaces__msg__CleaningEvent__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_cleaning_interfaces__msg__CleaningEvent__Sequence__copy(
  const robot_cleaning_interfaces__msg__CleaningEvent__Sequence * input,
  robot_cleaning_interfaces__msg__CleaningEvent__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(robot_cleaning_interfaces__msg__CleaningEvent)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(robot_cleaning_interfaces__msg__CleaningEvent);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    robot_cleaning_interfaces__msg__CleaningEvent * data =
      (robot_cleaning_interfaces__msg__CleaningEvent *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_cleaning_interfaces__msg__CleaningEvent__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          robot_cleaning_interfaces__msg__CleaningEvent__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_cleaning_interfaces__msg__CleaningEvent__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
