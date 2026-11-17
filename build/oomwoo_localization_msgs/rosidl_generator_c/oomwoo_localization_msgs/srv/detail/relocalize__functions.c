// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from oomwoo_localization_msgs:srv/Relocalize.idl
// generated code does not contain a copyright notice
#include "oomwoo_localization_msgs/srv/detail/relocalize__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
oomwoo_localization_msgs__srv__Relocalize_Request__init(oomwoo_localization_msgs__srv__Relocalize_Request * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
oomwoo_localization_msgs__srv__Relocalize_Request__fini(oomwoo_localization_msgs__srv__Relocalize_Request * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

bool
oomwoo_localization_msgs__srv__Relocalize_Request__are_equal(const oomwoo_localization_msgs__srv__Relocalize_Request * lhs, const oomwoo_localization_msgs__srv__Relocalize_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // structure_needs_at_least_one_member
  if (lhs->structure_needs_at_least_one_member != rhs->structure_needs_at_least_one_member) {
    return false;
  }
  return true;
}

bool
oomwoo_localization_msgs__srv__Relocalize_Request__copy(
  const oomwoo_localization_msgs__srv__Relocalize_Request * input,
  oomwoo_localization_msgs__srv__Relocalize_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // structure_needs_at_least_one_member
  output->structure_needs_at_least_one_member = input->structure_needs_at_least_one_member;
  return true;
}

oomwoo_localization_msgs__srv__Relocalize_Request *
oomwoo_localization_msgs__srv__Relocalize_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  oomwoo_localization_msgs__srv__Relocalize_Request * msg = (oomwoo_localization_msgs__srv__Relocalize_Request *)allocator.allocate(sizeof(oomwoo_localization_msgs__srv__Relocalize_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(oomwoo_localization_msgs__srv__Relocalize_Request));
  bool success = oomwoo_localization_msgs__srv__Relocalize_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
oomwoo_localization_msgs__srv__Relocalize_Request__destroy(oomwoo_localization_msgs__srv__Relocalize_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    oomwoo_localization_msgs__srv__Relocalize_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
oomwoo_localization_msgs__srv__Relocalize_Request__Sequence__init(oomwoo_localization_msgs__srv__Relocalize_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  oomwoo_localization_msgs__srv__Relocalize_Request * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(oomwoo_localization_msgs__srv__Relocalize_Request)) {
      return false;
    }
    data = (oomwoo_localization_msgs__srv__Relocalize_Request *)allocator.zero_allocate(size, sizeof(oomwoo_localization_msgs__srv__Relocalize_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = oomwoo_localization_msgs__srv__Relocalize_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        oomwoo_localization_msgs__srv__Relocalize_Request__fini(&data[i - 1]);
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
oomwoo_localization_msgs__srv__Relocalize_Request__Sequence__fini(oomwoo_localization_msgs__srv__Relocalize_Request__Sequence * array)
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
      oomwoo_localization_msgs__srv__Relocalize_Request__fini(&array->data[i]);
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

oomwoo_localization_msgs__srv__Relocalize_Request__Sequence *
oomwoo_localization_msgs__srv__Relocalize_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  oomwoo_localization_msgs__srv__Relocalize_Request__Sequence * array = (oomwoo_localization_msgs__srv__Relocalize_Request__Sequence *)allocator.allocate(sizeof(oomwoo_localization_msgs__srv__Relocalize_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = oomwoo_localization_msgs__srv__Relocalize_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
oomwoo_localization_msgs__srv__Relocalize_Request__Sequence__destroy(oomwoo_localization_msgs__srv__Relocalize_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    oomwoo_localization_msgs__srv__Relocalize_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
oomwoo_localization_msgs__srv__Relocalize_Request__Sequence__are_equal(const oomwoo_localization_msgs__srv__Relocalize_Request__Sequence * lhs, const oomwoo_localization_msgs__srv__Relocalize_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!oomwoo_localization_msgs__srv__Relocalize_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
oomwoo_localization_msgs__srv__Relocalize_Request__Sequence__copy(
  const oomwoo_localization_msgs__srv__Relocalize_Request__Sequence * input,
  oomwoo_localization_msgs__srv__Relocalize_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(oomwoo_localization_msgs__srv__Relocalize_Request)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(oomwoo_localization_msgs__srv__Relocalize_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    oomwoo_localization_msgs__srv__Relocalize_Request * data =
      (oomwoo_localization_msgs__srv__Relocalize_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!oomwoo_localization_msgs__srv__Relocalize_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          oomwoo_localization_msgs__srv__Relocalize_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!oomwoo_localization_msgs__srv__Relocalize_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `pose`
#include "geometry_msgs/msg/detail/pose_with_covariance_stamped__functions.h"
// Member `message`
#include "rosidl_runtime_c/string_functions.h"

bool
oomwoo_localization_msgs__srv__Relocalize_Response__init(oomwoo_localization_msgs__srv__Relocalize_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // pose
  if (!geometry_msgs__msg__PoseWithCovarianceStamped__init(&msg->pose)) {
    oomwoo_localization_msgs__srv__Relocalize_Response__fini(msg);
    return false;
  }
  // score
  // score_normalized
  // confidence
  // runtime_s
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    oomwoo_localization_msgs__srv__Relocalize_Response__fini(msg);
    return false;
  }
  return true;
}

void
oomwoo_localization_msgs__srv__Relocalize_Response__fini(oomwoo_localization_msgs__srv__Relocalize_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // pose
  geometry_msgs__msg__PoseWithCovarianceStamped__fini(&msg->pose);
  // score
  // score_normalized
  // confidence
  // runtime_s
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
oomwoo_localization_msgs__srv__Relocalize_Response__are_equal(const oomwoo_localization_msgs__srv__Relocalize_Response * lhs, const oomwoo_localization_msgs__srv__Relocalize_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // pose
  if (!geometry_msgs__msg__PoseWithCovarianceStamped__are_equal(
      &(lhs->pose), &(rhs->pose)))
  {
    return false;
  }
  // score
  if (lhs->score != rhs->score) {
    return false;
  }
  // score_normalized
  if (lhs->score_normalized != rhs->score_normalized) {
    return false;
  }
  // confidence
  if (lhs->confidence != rhs->confidence) {
    return false;
  }
  // runtime_s
  if (lhs->runtime_s != rhs->runtime_s) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
oomwoo_localization_msgs__srv__Relocalize_Response__copy(
  const oomwoo_localization_msgs__srv__Relocalize_Response * input,
  oomwoo_localization_msgs__srv__Relocalize_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // pose
  if (!geometry_msgs__msg__PoseWithCovarianceStamped__copy(
      &(input->pose), &(output->pose)))
  {
    return false;
  }
  // score
  output->score = input->score;
  // score_normalized
  output->score_normalized = input->score_normalized;
  // confidence
  output->confidence = input->confidence;
  // runtime_s
  output->runtime_s = input->runtime_s;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

oomwoo_localization_msgs__srv__Relocalize_Response *
oomwoo_localization_msgs__srv__Relocalize_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  oomwoo_localization_msgs__srv__Relocalize_Response * msg = (oomwoo_localization_msgs__srv__Relocalize_Response *)allocator.allocate(sizeof(oomwoo_localization_msgs__srv__Relocalize_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(oomwoo_localization_msgs__srv__Relocalize_Response));
  bool success = oomwoo_localization_msgs__srv__Relocalize_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
oomwoo_localization_msgs__srv__Relocalize_Response__destroy(oomwoo_localization_msgs__srv__Relocalize_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    oomwoo_localization_msgs__srv__Relocalize_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
oomwoo_localization_msgs__srv__Relocalize_Response__Sequence__init(oomwoo_localization_msgs__srv__Relocalize_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  oomwoo_localization_msgs__srv__Relocalize_Response * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(oomwoo_localization_msgs__srv__Relocalize_Response)) {
      return false;
    }
    data = (oomwoo_localization_msgs__srv__Relocalize_Response *)allocator.zero_allocate(size, sizeof(oomwoo_localization_msgs__srv__Relocalize_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = oomwoo_localization_msgs__srv__Relocalize_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        oomwoo_localization_msgs__srv__Relocalize_Response__fini(&data[i - 1]);
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
oomwoo_localization_msgs__srv__Relocalize_Response__Sequence__fini(oomwoo_localization_msgs__srv__Relocalize_Response__Sequence * array)
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
      oomwoo_localization_msgs__srv__Relocalize_Response__fini(&array->data[i]);
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

oomwoo_localization_msgs__srv__Relocalize_Response__Sequence *
oomwoo_localization_msgs__srv__Relocalize_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  oomwoo_localization_msgs__srv__Relocalize_Response__Sequence * array = (oomwoo_localization_msgs__srv__Relocalize_Response__Sequence *)allocator.allocate(sizeof(oomwoo_localization_msgs__srv__Relocalize_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = oomwoo_localization_msgs__srv__Relocalize_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
oomwoo_localization_msgs__srv__Relocalize_Response__Sequence__destroy(oomwoo_localization_msgs__srv__Relocalize_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    oomwoo_localization_msgs__srv__Relocalize_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
oomwoo_localization_msgs__srv__Relocalize_Response__Sequence__are_equal(const oomwoo_localization_msgs__srv__Relocalize_Response__Sequence * lhs, const oomwoo_localization_msgs__srv__Relocalize_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!oomwoo_localization_msgs__srv__Relocalize_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
oomwoo_localization_msgs__srv__Relocalize_Response__Sequence__copy(
  const oomwoo_localization_msgs__srv__Relocalize_Response__Sequence * input,
  oomwoo_localization_msgs__srv__Relocalize_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(oomwoo_localization_msgs__srv__Relocalize_Response)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(oomwoo_localization_msgs__srv__Relocalize_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    oomwoo_localization_msgs__srv__Relocalize_Response * data =
      (oomwoo_localization_msgs__srv__Relocalize_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!oomwoo_localization_msgs__srv__Relocalize_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          oomwoo_localization_msgs__srv__Relocalize_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!oomwoo_localization_msgs__srv__Relocalize_Response__copy(
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
// #include "oomwoo_localization_msgs/srv/detail/relocalize__functions.h"

bool
oomwoo_localization_msgs__srv__Relocalize_Event__init(oomwoo_localization_msgs__srv__Relocalize_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    oomwoo_localization_msgs__srv__Relocalize_Event__fini(msg);
    return false;
  }
  // request
  if (!oomwoo_localization_msgs__srv__Relocalize_Request__Sequence__init(&msg->request, 0)) {
    oomwoo_localization_msgs__srv__Relocalize_Event__fini(msg);
    return false;
  }
  // response
  if (!oomwoo_localization_msgs__srv__Relocalize_Response__Sequence__init(&msg->response, 0)) {
    oomwoo_localization_msgs__srv__Relocalize_Event__fini(msg);
    return false;
  }
  return true;
}

void
oomwoo_localization_msgs__srv__Relocalize_Event__fini(oomwoo_localization_msgs__srv__Relocalize_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  oomwoo_localization_msgs__srv__Relocalize_Request__Sequence__fini(&msg->request);
  // response
  oomwoo_localization_msgs__srv__Relocalize_Response__Sequence__fini(&msg->response);
}

bool
oomwoo_localization_msgs__srv__Relocalize_Event__are_equal(const oomwoo_localization_msgs__srv__Relocalize_Event * lhs, const oomwoo_localization_msgs__srv__Relocalize_Event * rhs)
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
  if (!oomwoo_localization_msgs__srv__Relocalize_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!oomwoo_localization_msgs__srv__Relocalize_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
oomwoo_localization_msgs__srv__Relocalize_Event__copy(
  const oomwoo_localization_msgs__srv__Relocalize_Event * input,
  oomwoo_localization_msgs__srv__Relocalize_Event * output)
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
  if (!oomwoo_localization_msgs__srv__Relocalize_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!oomwoo_localization_msgs__srv__Relocalize_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

oomwoo_localization_msgs__srv__Relocalize_Event *
oomwoo_localization_msgs__srv__Relocalize_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  oomwoo_localization_msgs__srv__Relocalize_Event * msg = (oomwoo_localization_msgs__srv__Relocalize_Event *)allocator.allocate(sizeof(oomwoo_localization_msgs__srv__Relocalize_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(oomwoo_localization_msgs__srv__Relocalize_Event));
  bool success = oomwoo_localization_msgs__srv__Relocalize_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
oomwoo_localization_msgs__srv__Relocalize_Event__destroy(oomwoo_localization_msgs__srv__Relocalize_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    oomwoo_localization_msgs__srv__Relocalize_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
oomwoo_localization_msgs__srv__Relocalize_Event__Sequence__init(oomwoo_localization_msgs__srv__Relocalize_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  oomwoo_localization_msgs__srv__Relocalize_Event * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(oomwoo_localization_msgs__srv__Relocalize_Event)) {
      return false;
    }
    data = (oomwoo_localization_msgs__srv__Relocalize_Event *)allocator.zero_allocate(size, sizeof(oomwoo_localization_msgs__srv__Relocalize_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = oomwoo_localization_msgs__srv__Relocalize_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        oomwoo_localization_msgs__srv__Relocalize_Event__fini(&data[i - 1]);
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
oomwoo_localization_msgs__srv__Relocalize_Event__Sequence__fini(oomwoo_localization_msgs__srv__Relocalize_Event__Sequence * array)
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
      oomwoo_localization_msgs__srv__Relocalize_Event__fini(&array->data[i]);
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

oomwoo_localization_msgs__srv__Relocalize_Event__Sequence *
oomwoo_localization_msgs__srv__Relocalize_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  oomwoo_localization_msgs__srv__Relocalize_Event__Sequence * array = (oomwoo_localization_msgs__srv__Relocalize_Event__Sequence *)allocator.allocate(sizeof(oomwoo_localization_msgs__srv__Relocalize_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = oomwoo_localization_msgs__srv__Relocalize_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
oomwoo_localization_msgs__srv__Relocalize_Event__Sequence__destroy(oomwoo_localization_msgs__srv__Relocalize_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    oomwoo_localization_msgs__srv__Relocalize_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
oomwoo_localization_msgs__srv__Relocalize_Event__Sequence__are_equal(const oomwoo_localization_msgs__srv__Relocalize_Event__Sequence * lhs, const oomwoo_localization_msgs__srv__Relocalize_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!oomwoo_localization_msgs__srv__Relocalize_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
oomwoo_localization_msgs__srv__Relocalize_Event__Sequence__copy(
  const oomwoo_localization_msgs__srv__Relocalize_Event__Sequence * input,
  oomwoo_localization_msgs__srv__Relocalize_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(oomwoo_localization_msgs__srv__Relocalize_Event)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(oomwoo_localization_msgs__srv__Relocalize_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    oomwoo_localization_msgs__srv__Relocalize_Event * data =
      (oomwoo_localization_msgs__srv__Relocalize_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!oomwoo_localization_msgs__srv__Relocalize_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          oomwoo_localization_msgs__srv__Relocalize_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!oomwoo_localization_msgs__srv__Relocalize_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
