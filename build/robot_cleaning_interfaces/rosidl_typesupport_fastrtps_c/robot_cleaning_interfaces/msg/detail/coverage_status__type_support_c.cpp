// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from robot_cleaning_interfaces:msg/CoverageStatus.idl
// generated code does not contain a copyright notice
#include "robot_cleaning_interfaces/msg/detail/coverage_status__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <cstddef>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/serialization_helpers.hpp"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "robot_cleaning_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "robot_cleaning_interfaces/msg/detail/coverage_status__struct.h"
#include "robot_cleaning_interfaces/msg/detail/coverage_status__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "nav_msgs/msg/detail/occupancy_grid__functions.h"  // covered
#include "rosidl_runtime_c/string.h"  // task_id
#include "rosidl_runtime_c/string_functions.h"  // task_id

// forward declare type support functions

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_robot_cleaning_interfaces
bool cdr_serialize_nav_msgs__msg__OccupancyGrid(
  const nav_msgs__msg__OccupancyGrid * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_robot_cleaning_interfaces
bool cdr_deserialize_nav_msgs__msg__OccupancyGrid(
  eprosima::fastcdr::Cdr & cdr,
  nav_msgs__msg__OccupancyGrid * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_robot_cleaning_interfaces
size_t get_serialized_size_nav_msgs__msg__OccupancyGrid(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_robot_cleaning_interfaces
size_t max_serialized_size_nav_msgs__msg__OccupancyGrid(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_robot_cleaning_interfaces
bool cdr_serialize_key_nav_msgs__msg__OccupancyGrid(
  const nav_msgs__msg__OccupancyGrid * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_robot_cleaning_interfaces
size_t get_serialized_size_key_nav_msgs__msg__OccupancyGrid(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_robot_cleaning_interfaces
size_t max_serialized_size_key_nav_msgs__msg__OccupancyGrid(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_robot_cleaning_interfaces
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, nav_msgs, msg, OccupancyGrid)();


using _CoverageStatus__ros_msg_type = robot_cleaning_interfaces__msg__CoverageStatus;


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_cleaning_interfaces
bool cdr_serialize_robot_cleaning_interfaces__msg__CoverageStatus(
  const robot_cleaning_interfaces__msg__CoverageStatus * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: task_id
  {
    const rosidl_runtime_c__String * str = &ros_message->task_id;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: coverage
  {
    cdr << ros_message->coverage;
  }

  // Field name: path_length_m
  {
    cdr << ros_message->path_length_m;
  }

  // Field name: covered
  {
    cdr_serialize_nav_msgs__msg__OccupancyGrid(
      &ros_message->covered, cdr);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_cleaning_interfaces
bool cdr_deserialize_robot_cleaning_interfaces__msg__CoverageStatus(
  eprosima::fastcdr::Cdr & cdr,
  robot_cleaning_interfaces__msg__CoverageStatus * ros_message)
{
  // Field name: task_id
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->task_id.data) {
      rosidl_runtime_c__String__init(&ros_message->task_id);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->task_id,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'task_id'\n");
      return false;
    }
  }

  // Field name: coverage
  {
    cdr >> ros_message->coverage;
  }

  // Field name: path_length_m
  {
    cdr >> ros_message->path_length_m;
  }

  // Field name: covered
  {
    cdr_deserialize_nav_msgs__msg__OccupancyGrid(cdr, &ros_message->covered);
  }

  return true;
}  // NOLINT(readability/fn_size)


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_cleaning_interfaces
size_t get_serialized_size_robot_cleaning_interfaces__msg__CoverageStatus(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _CoverageStatus__ros_msg_type * ros_message = static_cast<const _CoverageStatus__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: task_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->task_id.size + 1);

  // Field name: coverage
  {
    size_t item_size = sizeof(ros_message->coverage);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: path_length_m
  {
    size_t item_size = sizeof(ros_message->path_length_m);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: covered
  current_alignment += get_serialized_size_nav_msgs__msg__OccupancyGrid(
    &(ros_message->covered), current_alignment);

  return current_alignment - initial_alignment;
}


ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_cleaning_interfaces
size_t max_serialized_size_robot_cleaning_interfaces__msg__CoverageStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // Field name: task_id
  {
    size_t array_size = 1;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Field name: coverage
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: path_length_m
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: covered
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_nav_msgs__msg__OccupancyGrid(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }


  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = robot_cleaning_interfaces__msg__CoverageStatus;
    is_plain =
      (
      offsetof(DataType, covered) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_cleaning_interfaces
bool cdr_serialize_key_robot_cleaning_interfaces__msg__CoverageStatus(
  const robot_cleaning_interfaces__msg__CoverageStatus * ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Field name: task_id
  {
    const rosidl_runtime_c__String * str = &ros_message->task_id;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: coverage
  {
    cdr << ros_message->coverage;
  }

  // Field name: path_length_m
  {
    cdr << ros_message->path_length_m;
  }

  // Field name: covered
  {
    cdr_serialize_key_nav_msgs__msg__OccupancyGrid(
      &ros_message->covered, cdr);
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_cleaning_interfaces
size_t get_serialized_size_key_robot_cleaning_interfaces__msg__CoverageStatus(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _CoverageStatus__ros_msg_type * ros_message = static_cast<const _CoverageStatus__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;

  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Field name: task_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->task_id.size + 1);

  // Field name: coverage
  {
    size_t item_size = sizeof(ros_message->coverage);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: path_length_m
  {
    size_t item_size = sizeof(ros_message->path_length_m);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  // Field name: covered
  current_alignment += get_serialized_size_key_nav_msgs__msg__OccupancyGrid(
    &(ros_message->covered), current_alignment);

  return current_alignment - initial_alignment;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_robot_cleaning_interfaces
size_t max_serialized_size_key_robot_cleaning_interfaces__msg__CoverageStatus(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;
  // Field name: task_id
  {
    size_t array_size = 1;
    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Field name: coverage
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Field name: path_length_m
  {
    size_t array_size = 1;
    last_member_size = array_size * sizeof(uint64_t);
    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  // Field name: covered
  {
    size_t array_size = 1;
    last_member_size = 0;
    for (size_t index = 0; index < array_size; ++index) {
      bool inner_full_bounded;
      bool inner_is_plain;
      size_t inner_size;
      inner_size =
        max_serialized_size_key_nav_msgs__msg__OccupancyGrid(
        inner_full_bounded, inner_is_plain, current_alignment);
      last_member_size += inner_size;
      current_alignment += inner_size;
      full_bounded &= inner_full_bounded;
      is_plain &= inner_is_plain;
    }
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = robot_cleaning_interfaces__msg__CoverageStatus;
    is_plain =
      (
      offsetof(DataType, covered) +
      last_member_size
      ) == ret_val;
  }
  return ret_val;
}


static bool _CoverageStatus__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const robot_cleaning_interfaces__msg__CoverageStatus * ros_message = static_cast<const robot_cleaning_interfaces__msg__CoverageStatus *>(untyped_ros_message);
  (void)ros_message;
  return cdr_serialize_robot_cleaning_interfaces__msg__CoverageStatus(ros_message, cdr);
}

static bool _CoverageStatus__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  robot_cleaning_interfaces__msg__CoverageStatus * ros_message = static_cast<robot_cleaning_interfaces__msg__CoverageStatus *>(untyped_ros_message);
  (void)ros_message;
  return cdr_deserialize_robot_cleaning_interfaces__msg__CoverageStatus(cdr, ros_message);
}

static uint32_t _CoverageStatus__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_robot_cleaning_interfaces__msg__CoverageStatus(
      untyped_ros_message, 0));
}

static size_t _CoverageStatus__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_robot_cleaning_interfaces__msg__CoverageStatus(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_CoverageStatus = {
  "robot_cleaning_interfaces::msg",
  "CoverageStatus",
  _CoverageStatus__cdr_serialize,
  _CoverageStatus__cdr_deserialize,
  _CoverageStatus__get_serialized_size,
  _CoverageStatus__max_serialized_size,
  nullptr
};

static rosidl_message_type_support_t _CoverageStatus__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_CoverageStatus,
  get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__msg__CoverageStatus__get_type_hash,
  &robot_cleaning_interfaces__msg__CoverageStatus__get_type_description,
  &robot_cleaning_interfaces__msg__CoverageStatus__get_type_description_sources,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_cleaning_interfaces, msg, CoverageStatus)() {
  return &_CoverageStatus__type_support;
}

#if defined(__cplusplus)
}
#endif
