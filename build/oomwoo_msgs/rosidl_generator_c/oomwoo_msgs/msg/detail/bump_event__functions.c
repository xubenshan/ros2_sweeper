// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from oomwoo_msgs:msg/BumpEvent.idl
// generated code does not contain a copyright notice
#include "oomwoo_msgs/msg/detail/bump_event__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `contact`
// Member `robot`
// Member `approach`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
oomwoo_msgs__msg__BumpEvent__init(oomwoo_msgs__msg__BumpEvent * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    oomwoo_msgs__msg__BumpEvent__fini(msg);
    return false;
  }
  // contact
  if (!geometry_msgs__msg__Point__init(&msg->contact)) {
    oomwoo_msgs__msg__BumpEvent__fini(msg);
    return false;
  }
  // robot
  if (!geometry_msgs__msg__Point__init(&msg->robot)) {
    oomwoo_msgs__msg__BumpEvent__fini(msg);
    return false;
  }
  // approach
  if (!geometry_msgs__msg__Point__init(&msg->approach)) {
    oomwoo_msgs__msg__BumpEvent__fini(msg);
    return false;
  }
  // heading
  // side
  // left_depress
  // right_depress
  // left_rate
  // right_rate
  return true;
}

void
oomwoo_msgs__msg__BumpEvent__fini(oomwoo_msgs__msg__BumpEvent * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // contact
  geometry_msgs__msg__Point__fini(&msg->contact);
  // robot
  geometry_msgs__msg__Point__fini(&msg->robot);
  // approach
  geometry_msgs__msg__Point__fini(&msg->approach);
  // heading
  // side
  // left_depress
  // right_depress
  // left_rate
  // right_rate
}

bool
oomwoo_msgs__msg__BumpEvent__are_equal(const oomwoo_msgs__msg__BumpEvent * lhs, const oomwoo_msgs__msg__BumpEvent * rhs)
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
  // contact
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->contact), &(rhs->contact)))
  {
    return false;
  }
  // robot
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->robot), &(rhs->robot)))
  {
    return false;
  }
  // approach
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->approach), &(rhs->approach)))
  {
    return false;
  }
  // heading
  if (lhs->heading != rhs->heading) {
    return false;
  }
  // side
  if (lhs->side != rhs->side) {
    return false;
  }
  // left_depress
  if (lhs->left_depress != rhs->left_depress) {
    return false;
  }
  // right_depress
  if (lhs->right_depress != rhs->right_depress) {
    return false;
  }
  // left_rate
  if (lhs->left_rate != rhs->left_rate) {
    return false;
  }
  // right_rate
  if (lhs->right_rate != rhs->right_rate) {
    return false;
  }
  return true;
}

bool
oomwoo_msgs__msg__BumpEvent__copy(
  const oomwoo_msgs__msg__BumpEvent * input,
  oomwoo_msgs__msg__BumpEvent * output)
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
  // contact
  if (!geometry_msgs__msg__Point__copy(
      &(input->contact), &(output->contact)))
  {
    return false;
  }
  // robot
  if (!geometry_msgs__msg__Point__copy(
      &(input->robot), &(output->robot)))
  {
    return false;
  }
  // approach
  if (!geometry_msgs__msg__Point__copy(
      &(input->approach), &(output->approach)))
  {
    return false;
  }
  // heading
  output->heading = input->heading;
  // side
  output->side = input->side;
  // left_depress
  output->left_depress = input->left_depress;
  // right_depress
  output->right_depress = input->right_depress;
  // left_rate
  output->left_rate = input->left_rate;
  // right_rate
  output->right_rate = input->right_rate;
  return true;
}

oomwoo_msgs__msg__BumpEvent *
oomwoo_msgs__msg__BumpEvent__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  oomwoo_msgs__msg__BumpEvent * msg = (oomwoo_msgs__msg__BumpEvent *)allocator.allocate(sizeof(oomwoo_msgs__msg__BumpEvent), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(oomwoo_msgs__msg__BumpEvent));
  bool success = oomwoo_msgs__msg__BumpEvent__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
oomwoo_msgs__msg__BumpEvent__destroy(oomwoo_msgs__msg__BumpEvent * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    oomwoo_msgs__msg__BumpEvent__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
oomwoo_msgs__msg__BumpEvent__Sequence__init(oomwoo_msgs__msg__BumpEvent__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  oomwoo_msgs__msg__BumpEvent * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(oomwoo_msgs__msg__BumpEvent)) {
      return false;
    }
    data = (oomwoo_msgs__msg__BumpEvent *)allocator.zero_allocate(size, sizeof(oomwoo_msgs__msg__BumpEvent), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = oomwoo_msgs__msg__BumpEvent__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        oomwoo_msgs__msg__BumpEvent__fini(&data[i - 1]);
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
oomwoo_msgs__msg__BumpEvent__Sequence__fini(oomwoo_msgs__msg__BumpEvent__Sequence * array)
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
      oomwoo_msgs__msg__BumpEvent__fini(&array->data[i]);
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

oomwoo_msgs__msg__BumpEvent__Sequence *
oomwoo_msgs__msg__BumpEvent__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  oomwoo_msgs__msg__BumpEvent__Sequence * array = (oomwoo_msgs__msg__BumpEvent__Sequence *)allocator.allocate(sizeof(oomwoo_msgs__msg__BumpEvent__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = oomwoo_msgs__msg__BumpEvent__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
oomwoo_msgs__msg__BumpEvent__Sequence__destroy(oomwoo_msgs__msg__BumpEvent__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    oomwoo_msgs__msg__BumpEvent__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
oomwoo_msgs__msg__BumpEvent__Sequence__are_equal(const oomwoo_msgs__msg__BumpEvent__Sequence * lhs, const oomwoo_msgs__msg__BumpEvent__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!oomwoo_msgs__msg__BumpEvent__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
oomwoo_msgs__msg__BumpEvent__Sequence__copy(
  const oomwoo_msgs__msg__BumpEvent__Sequence * input,
  oomwoo_msgs__msg__BumpEvent__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(oomwoo_msgs__msg__BumpEvent)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(oomwoo_msgs__msg__BumpEvent);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    oomwoo_msgs__msg__BumpEvent * data =
      (oomwoo_msgs__msg__BumpEvent *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!oomwoo_msgs__msg__BumpEvent__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          oomwoo_msgs__msg__BumpEvent__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!oomwoo_msgs__msg__BumpEvent__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
