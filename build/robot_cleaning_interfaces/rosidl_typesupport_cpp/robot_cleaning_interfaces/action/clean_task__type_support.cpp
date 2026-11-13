// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from robot_cleaning_interfaces:action/CleanTask.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "robot_cleaning_interfaces/action/detail/clean_task__functions.h"
#include "robot_cleaning_interfaces/action/detail/clean_task__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace robot_cleaning_interfaces
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _CleanTask_Goal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _CleanTask_Goal_type_support_ids_t;

static const _CleanTask_Goal_type_support_ids_t _CleanTask_Goal_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _CleanTask_Goal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _CleanTask_Goal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _CleanTask_Goal_type_support_symbol_names_t _CleanTask_Goal_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, robot_cleaning_interfaces, action, CleanTask_Goal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, robot_cleaning_interfaces, action, CleanTask_Goal)),
  }
};

typedef struct _CleanTask_Goal_type_support_data_t
{
  void * data[2];
} _CleanTask_Goal_type_support_data_t;

static _CleanTask_Goal_type_support_data_t _CleanTask_Goal_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _CleanTask_Goal_message_typesupport_map = {
  2,
  "robot_cleaning_interfaces",
  &_CleanTask_Goal_message_typesupport_ids.typesupport_identifier[0],
  &_CleanTask_Goal_message_typesupport_symbol_names.symbol_name[0],
  &_CleanTask_Goal_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t CleanTask_Goal_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_CleanTask_Goal_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__action__CleanTask_Goal__get_type_hash,
  &robot_cleaning_interfaces__action__CleanTask_Goal__get_type_description,
  &robot_cleaning_interfaces__action__CleanTask_Goal__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace robot_cleaning_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_Goal>()
{
  return &::robot_cleaning_interfaces::action::rosidl_typesupport_cpp::CleanTask_Goal_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, robot_cleaning_interfaces, action, CleanTask_Goal)() {
  return get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_Goal>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__functions.h"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_cleaning_interfaces
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _CleanTask_Result_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _CleanTask_Result_type_support_ids_t;

static const _CleanTask_Result_type_support_ids_t _CleanTask_Result_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _CleanTask_Result_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _CleanTask_Result_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _CleanTask_Result_type_support_symbol_names_t _CleanTask_Result_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, robot_cleaning_interfaces, action, CleanTask_Result)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, robot_cleaning_interfaces, action, CleanTask_Result)),
  }
};

typedef struct _CleanTask_Result_type_support_data_t
{
  void * data[2];
} _CleanTask_Result_type_support_data_t;

static _CleanTask_Result_type_support_data_t _CleanTask_Result_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _CleanTask_Result_message_typesupport_map = {
  2,
  "robot_cleaning_interfaces",
  &_CleanTask_Result_message_typesupport_ids.typesupport_identifier[0],
  &_CleanTask_Result_message_typesupport_symbol_names.symbol_name[0],
  &_CleanTask_Result_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t CleanTask_Result_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_CleanTask_Result_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__action__CleanTask_Result__get_type_hash,
  &robot_cleaning_interfaces__action__CleanTask_Result__get_type_description,
  &robot_cleaning_interfaces__action__CleanTask_Result__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace robot_cleaning_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_Result>()
{
  return &::robot_cleaning_interfaces::action::rosidl_typesupport_cpp::CleanTask_Result_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, robot_cleaning_interfaces, action, CleanTask_Result)() {
  return get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_Result>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__functions.h"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_cleaning_interfaces
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _CleanTask_Feedback_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _CleanTask_Feedback_type_support_ids_t;

static const _CleanTask_Feedback_type_support_ids_t _CleanTask_Feedback_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _CleanTask_Feedback_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _CleanTask_Feedback_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _CleanTask_Feedback_type_support_symbol_names_t _CleanTask_Feedback_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, robot_cleaning_interfaces, action, CleanTask_Feedback)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, robot_cleaning_interfaces, action, CleanTask_Feedback)),
  }
};

typedef struct _CleanTask_Feedback_type_support_data_t
{
  void * data[2];
} _CleanTask_Feedback_type_support_data_t;

static _CleanTask_Feedback_type_support_data_t _CleanTask_Feedback_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _CleanTask_Feedback_message_typesupport_map = {
  2,
  "robot_cleaning_interfaces",
  &_CleanTask_Feedback_message_typesupport_ids.typesupport_identifier[0],
  &_CleanTask_Feedback_message_typesupport_symbol_names.symbol_name[0],
  &_CleanTask_Feedback_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t CleanTask_Feedback_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_CleanTask_Feedback_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__action__CleanTask_Feedback__get_type_hash,
  &robot_cleaning_interfaces__action__CleanTask_Feedback__get_type_description,
  &robot_cleaning_interfaces__action__CleanTask_Feedback__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace robot_cleaning_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_Feedback>()
{
  return &::robot_cleaning_interfaces::action::rosidl_typesupport_cpp::CleanTask_Feedback_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, robot_cleaning_interfaces, action, CleanTask_Feedback)() {
  return get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_Feedback>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__functions.h"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_cleaning_interfaces
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _CleanTask_SendGoal_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _CleanTask_SendGoal_Request_type_support_ids_t;

static const _CleanTask_SendGoal_Request_type_support_ids_t _CleanTask_SendGoal_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _CleanTask_SendGoal_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _CleanTask_SendGoal_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _CleanTask_SendGoal_Request_type_support_symbol_names_t _CleanTask_SendGoal_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, robot_cleaning_interfaces, action, CleanTask_SendGoal_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, robot_cleaning_interfaces, action, CleanTask_SendGoal_Request)),
  }
};

typedef struct _CleanTask_SendGoal_Request_type_support_data_t
{
  void * data[2];
} _CleanTask_SendGoal_Request_type_support_data_t;

static _CleanTask_SendGoal_Request_type_support_data_t _CleanTask_SendGoal_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _CleanTask_SendGoal_Request_message_typesupport_map = {
  2,
  "robot_cleaning_interfaces",
  &_CleanTask_SendGoal_Request_message_typesupport_ids.typesupport_identifier[0],
  &_CleanTask_SendGoal_Request_message_typesupport_symbol_names.symbol_name[0],
  &_CleanTask_SendGoal_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t CleanTask_SendGoal_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_CleanTask_SendGoal_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__get_type_hash,
  &robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__get_type_description,
  &robot_cleaning_interfaces__action__CleanTask_SendGoal_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace robot_cleaning_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_SendGoal_Request>()
{
  return &::robot_cleaning_interfaces::action::rosidl_typesupport_cpp::CleanTask_SendGoal_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, robot_cleaning_interfaces, action, CleanTask_SendGoal_Request)() {
  return get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_SendGoal_Request>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__functions.h"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_cleaning_interfaces
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _CleanTask_SendGoal_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _CleanTask_SendGoal_Response_type_support_ids_t;

static const _CleanTask_SendGoal_Response_type_support_ids_t _CleanTask_SendGoal_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _CleanTask_SendGoal_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _CleanTask_SendGoal_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _CleanTask_SendGoal_Response_type_support_symbol_names_t _CleanTask_SendGoal_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, robot_cleaning_interfaces, action, CleanTask_SendGoal_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, robot_cleaning_interfaces, action, CleanTask_SendGoal_Response)),
  }
};

typedef struct _CleanTask_SendGoal_Response_type_support_data_t
{
  void * data[2];
} _CleanTask_SendGoal_Response_type_support_data_t;

static _CleanTask_SendGoal_Response_type_support_data_t _CleanTask_SendGoal_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _CleanTask_SendGoal_Response_message_typesupport_map = {
  2,
  "robot_cleaning_interfaces",
  &_CleanTask_SendGoal_Response_message_typesupport_ids.typesupport_identifier[0],
  &_CleanTask_SendGoal_Response_message_typesupport_symbol_names.symbol_name[0],
  &_CleanTask_SendGoal_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t CleanTask_SendGoal_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_CleanTask_SendGoal_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__get_type_hash,
  &robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__get_type_description,
  &robot_cleaning_interfaces__action__CleanTask_SendGoal_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace robot_cleaning_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_SendGoal_Response>()
{
  return &::robot_cleaning_interfaces::action::rosidl_typesupport_cpp::CleanTask_SendGoal_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, robot_cleaning_interfaces, action, CleanTask_SendGoal_Response)() {
  return get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_SendGoal_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__functions.h"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_cleaning_interfaces
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _CleanTask_SendGoal_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _CleanTask_SendGoal_Event_type_support_ids_t;

static const _CleanTask_SendGoal_Event_type_support_ids_t _CleanTask_SendGoal_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _CleanTask_SendGoal_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _CleanTask_SendGoal_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _CleanTask_SendGoal_Event_type_support_symbol_names_t _CleanTask_SendGoal_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, robot_cleaning_interfaces, action, CleanTask_SendGoal_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, robot_cleaning_interfaces, action, CleanTask_SendGoal_Event)),
  }
};

typedef struct _CleanTask_SendGoal_Event_type_support_data_t
{
  void * data[2];
} _CleanTask_SendGoal_Event_type_support_data_t;

static _CleanTask_SendGoal_Event_type_support_data_t _CleanTask_SendGoal_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _CleanTask_SendGoal_Event_message_typesupport_map = {
  2,
  "robot_cleaning_interfaces",
  &_CleanTask_SendGoal_Event_message_typesupport_ids.typesupport_identifier[0],
  &_CleanTask_SendGoal_Event_message_typesupport_symbol_names.symbol_name[0],
  &_CleanTask_SendGoal_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t CleanTask_SendGoal_Event_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_CleanTask_SendGoal_Event_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__get_type_hash,
  &robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__get_type_description,
  &robot_cleaning_interfaces__action__CleanTask_SendGoal_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace robot_cleaning_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_SendGoal_Event>()
{
  return &::robot_cleaning_interfaces::action::rosidl_typesupport_cpp::CleanTask_SendGoal_Event_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, robot_cleaning_interfaces, action, CleanTask_SendGoal_Event)() {
  return get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_SendGoal_Event>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/service_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_cleaning_interfaces
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _CleanTask_SendGoal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _CleanTask_SendGoal_type_support_ids_t;

static const _CleanTask_SendGoal_type_support_ids_t _CleanTask_SendGoal_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _CleanTask_SendGoal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _CleanTask_SendGoal_type_support_symbol_names_t;
#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _CleanTask_SendGoal_type_support_symbol_names_t _CleanTask_SendGoal_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, robot_cleaning_interfaces, action, CleanTask_SendGoal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, robot_cleaning_interfaces, action, CleanTask_SendGoal)),
  }
};

typedef struct _CleanTask_SendGoal_type_support_data_t
{
  void * data[2];
} _CleanTask_SendGoal_type_support_data_t;

static _CleanTask_SendGoal_type_support_data_t _CleanTask_SendGoal_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _CleanTask_SendGoal_service_typesupport_map = {
  2,
  "robot_cleaning_interfaces",
  &_CleanTask_SendGoal_service_typesupport_ids.typesupport_identifier[0],
  &_CleanTask_SendGoal_service_typesupport_symbol_names.symbol_name[0],
  &_CleanTask_SendGoal_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t CleanTask_SendGoal_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_CleanTask_SendGoal_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
  ::rosidl_typesupport_cpp::get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_SendGoal_Request>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_SendGoal_Response>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_SendGoal_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<robot_cleaning_interfaces::action::CleanTask_SendGoal>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<robot_cleaning_interfaces::action::CleanTask_SendGoal>,
  &robot_cleaning_interfaces__action__CleanTask_SendGoal__get_type_hash,
  &robot_cleaning_interfaces__action__CleanTask_SendGoal__get_type_description,
  &robot_cleaning_interfaces__action__CleanTask_SendGoal__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace robot_cleaning_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<robot_cleaning_interfaces::action::CleanTask_SendGoal>()
{
  return &::robot_cleaning_interfaces::action::rosidl_typesupport_cpp::CleanTask_SendGoal_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, robot_cleaning_interfaces, action, CleanTask_SendGoal)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<robot_cleaning_interfaces::action::CleanTask_SendGoal>();
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__functions.h"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_cleaning_interfaces
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _CleanTask_GetResult_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _CleanTask_GetResult_Request_type_support_ids_t;

static const _CleanTask_GetResult_Request_type_support_ids_t _CleanTask_GetResult_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _CleanTask_GetResult_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _CleanTask_GetResult_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _CleanTask_GetResult_Request_type_support_symbol_names_t _CleanTask_GetResult_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, robot_cleaning_interfaces, action, CleanTask_GetResult_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, robot_cleaning_interfaces, action, CleanTask_GetResult_Request)),
  }
};

typedef struct _CleanTask_GetResult_Request_type_support_data_t
{
  void * data[2];
} _CleanTask_GetResult_Request_type_support_data_t;

static _CleanTask_GetResult_Request_type_support_data_t _CleanTask_GetResult_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _CleanTask_GetResult_Request_message_typesupport_map = {
  2,
  "robot_cleaning_interfaces",
  &_CleanTask_GetResult_Request_message_typesupport_ids.typesupport_identifier[0],
  &_CleanTask_GetResult_Request_message_typesupport_symbol_names.symbol_name[0],
  &_CleanTask_GetResult_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t CleanTask_GetResult_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_CleanTask_GetResult_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__action__CleanTask_GetResult_Request__get_type_hash,
  &robot_cleaning_interfaces__action__CleanTask_GetResult_Request__get_type_description,
  &robot_cleaning_interfaces__action__CleanTask_GetResult_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace robot_cleaning_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_GetResult_Request>()
{
  return &::robot_cleaning_interfaces::action::rosidl_typesupport_cpp::CleanTask_GetResult_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, robot_cleaning_interfaces, action, CleanTask_GetResult_Request)() {
  return get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_GetResult_Request>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__functions.h"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_cleaning_interfaces
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _CleanTask_GetResult_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _CleanTask_GetResult_Response_type_support_ids_t;

static const _CleanTask_GetResult_Response_type_support_ids_t _CleanTask_GetResult_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _CleanTask_GetResult_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _CleanTask_GetResult_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _CleanTask_GetResult_Response_type_support_symbol_names_t _CleanTask_GetResult_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, robot_cleaning_interfaces, action, CleanTask_GetResult_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, robot_cleaning_interfaces, action, CleanTask_GetResult_Response)),
  }
};

typedef struct _CleanTask_GetResult_Response_type_support_data_t
{
  void * data[2];
} _CleanTask_GetResult_Response_type_support_data_t;

static _CleanTask_GetResult_Response_type_support_data_t _CleanTask_GetResult_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _CleanTask_GetResult_Response_message_typesupport_map = {
  2,
  "robot_cleaning_interfaces",
  &_CleanTask_GetResult_Response_message_typesupport_ids.typesupport_identifier[0],
  &_CleanTask_GetResult_Response_message_typesupport_symbol_names.symbol_name[0],
  &_CleanTask_GetResult_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t CleanTask_GetResult_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_CleanTask_GetResult_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__action__CleanTask_GetResult_Response__get_type_hash,
  &robot_cleaning_interfaces__action__CleanTask_GetResult_Response__get_type_description,
  &robot_cleaning_interfaces__action__CleanTask_GetResult_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace robot_cleaning_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_GetResult_Response>()
{
  return &::robot_cleaning_interfaces::action::rosidl_typesupport_cpp::CleanTask_GetResult_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, robot_cleaning_interfaces, action, CleanTask_GetResult_Response)() {
  return get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_GetResult_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__functions.h"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_cleaning_interfaces
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _CleanTask_GetResult_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _CleanTask_GetResult_Event_type_support_ids_t;

static const _CleanTask_GetResult_Event_type_support_ids_t _CleanTask_GetResult_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _CleanTask_GetResult_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _CleanTask_GetResult_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _CleanTask_GetResult_Event_type_support_symbol_names_t _CleanTask_GetResult_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, robot_cleaning_interfaces, action, CleanTask_GetResult_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, robot_cleaning_interfaces, action, CleanTask_GetResult_Event)),
  }
};

typedef struct _CleanTask_GetResult_Event_type_support_data_t
{
  void * data[2];
} _CleanTask_GetResult_Event_type_support_data_t;

static _CleanTask_GetResult_Event_type_support_data_t _CleanTask_GetResult_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _CleanTask_GetResult_Event_message_typesupport_map = {
  2,
  "robot_cleaning_interfaces",
  &_CleanTask_GetResult_Event_message_typesupport_ids.typesupport_identifier[0],
  &_CleanTask_GetResult_Event_message_typesupport_symbol_names.symbol_name[0],
  &_CleanTask_GetResult_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t CleanTask_GetResult_Event_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_CleanTask_GetResult_Event_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__action__CleanTask_GetResult_Event__get_type_hash,
  &robot_cleaning_interfaces__action__CleanTask_GetResult_Event__get_type_description,
  &robot_cleaning_interfaces__action__CleanTask_GetResult_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace robot_cleaning_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_GetResult_Event>()
{
  return &::robot_cleaning_interfaces::action::rosidl_typesupport_cpp::CleanTask_GetResult_Event_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, robot_cleaning_interfaces, action, CleanTask_GetResult_Event)() {
  return get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_GetResult_Event>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/service_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_cleaning_interfaces
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _CleanTask_GetResult_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _CleanTask_GetResult_type_support_ids_t;

static const _CleanTask_GetResult_type_support_ids_t _CleanTask_GetResult_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _CleanTask_GetResult_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _CleanTask_GetResult_type_support_symbol_names_t;
#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _CleanTask_GetResult_type_support_symbol_names_t _CleanTask_GetResult_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, robot_cleaning_interfaces, action, CleanTask_GetResult)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, robot_cleaning_interfaces, action, CleanTask_GetResult)),
  }
};

typedef struct _CleanTask_GetResult_type_support_data_t
{
  void * data[2];
} _CleanTask_GetResult_type_support_data_t;

static _CleanTask_GetResult_type_support_data_t _CleanTask_GetResult_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _CleanTask_GetResult_service_typesupport_map = {
  2,
  "robot_cleaning_interfaces",
  &_CleanTask_GetResult_service_typesupport_ids.typesupport_identifier[0],
  &_CleanTask_GetResult_service_typesupport_symbol_names.symbol_name[0],
  &_CleanTask_GetResult_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t CleanTask_GetResult_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_CleanTask_GetResult_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
  ::rosidl_typesupport_cpp::get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_GetResult_Request>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_GetResult_Response>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_GetResult_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<robot_cleaning_interfaces::action::CleanTask_GetResult>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<robot_cleaning_interfaces::action::CleanTask_GetResult>,
  &robot_cleaning_interfaces__action__CleanTask_GetResult__get_type_hash,
  &robot_cleaning_interfaces__action__CleanTask_GetResult__get_type_description,
  &robot_cleaning_interfaces__action__CleanTask_GetResult__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace robot_cleaning_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<robot_cleaning_interfaces::action::CleanTask_GetResult>()
{
  return &::robot_cleaning_interfaces::action::rosidl_typesupport_cpp::CleanTask_GetResult_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, robot_cleaning_interfaces, action, CleanTask_GetResult)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<robot_cleaning_interfaces::action::CleanTask_GetResult>();
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__functions.h"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_cleaning_interfaces
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _CleanTask_FeedbackMessage_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _CleanTask_FeedbackMessage_type_support_ids_t;

static const _CleanTask_FeedbackMessage_type_support_ids_t _CleanTask_FeedbackMessage_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _CleanTask_FeedbackMessage_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _CleanTask_FeedbackMessage_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _CleanTask_FeedbackMessage_type_support_symbol_names_t _CleanTask_FeedbackMessage_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, robot_cleaning_interfaces, action, CleanTask_FeedbackMessage)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, robot_cleaning_interfaces, action, CleanTask_FeedbackMessage)),
  }
};

typedef struct _CleanTask_FeedbackMessage_type_support_data_t
{
  void * data[2];
} _CleanTask_FeedbackMessage_type_support_data_t;

static _CleanTask_FeedbackMessage_type_support_data_t _CleanTask_FeedbackMessage_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _CleanTask_FeedbackMessage_message_typesupport_map = {
  2,
  "robot_cleaning_interfaces",
  &_CleanTask_FeedbackMessage_message_typesupport_ids.typesupport_identifier[0],
  &_CleanTask_FeedbackMessage_message_typesupport_symbol_names.symbol_name[0],
  &_CleanTask_FeedbackMessage_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t CleanTask_FeedbackMessage_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_CleanTask_FeedbackMessage_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__get_type_hash,
  &robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__get_type_description,
  &robot_cleaning_interfaces__action__CleanTask_FeedbackMessage__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace robot_cleaning_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_FeedbackMessage>()
{
  return &::robot_cleaning_interfaces::action::rosidl_typesupport_cpp::CleanTask_FeedbackMessage_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, robot_cleaning_interfaces, action, CleanTask_FeedbackMessage)() {
  return get_message_type_support_handle<robot_cleaning_interfaces::action::CleanTask_FeedbackMessage>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

#include "action_msgs/msg/goal_status_array.hpp"
#include "action_msgs/srv/cancel_goal.hpp"
// already included above
// #include "robot_cleaning_interfaces/action/detail/clean_task__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_typesupport_cpp/action_type_support.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_cpp/service_type_support.hpp"

namespace robot_cleaning_interfaces
{

namespace action
{

namespace rosidl_typesupport_cpp
{

static rosidl_action_type_support_t CleanTask_action_type_support_handle = {
  NULL, NULL, NULL, NULL, NULL,
  &robot_cleaning_interfaces__action__CleanTask__get_type_hash,
  &robot_cleaning_interfaces__action__CleanTask__get_type_description,
  &robot_cleaning_interfaces__action__CleanTask__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace robot_cleaning_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_action_type_support_t *
get_action_type_support_handle<robot_cleaning_interfaces::action::CleanTask>()
{
  using ::robot_cleaning_interfaces::action::rosidl_typesupport_cpp::CleanTask_action_type_support_handle;
  // Thread-safe by always writing the same values to the static struct
  CleanTask_action_type_support_handle.goal_service_type_support = get_service_type_support_handle<::robot_cleaning_interfaces::action::CleanTask::Impl::SendGoalService>();
  CleanTask_action_type_support_handle.result_service_type_support = get_service_type_support_handle<::robot_cleaning_interfaces::action::CleanTask::Impl::GetResultService>();
  CleanTask_action_type_support_handle.cancel_service_type_support = get_service_type_support_handle<::robot_cleaning_interfaces::action::CleanTask::Impl::CancelGoalService>();
  CleanTask_action_type_support_handle.feedback_message_type_support = get_message_type_support_handle<::robot_cleaning_interfaces::action::CleanTask::Impl::FeedbackMessage>();
  CleanTask_action_type_support_handle.status_message_type_support = get_message_type_support_handle<::robot_cleaning_interfaces::action::CleanTask::Impl::GoalStatusMessage>();
  return &CleanTask_action_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_action_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__ACTION_SYMBOL_NAME(rosidl_typesupport_cpp, robot_cleaning_interfaces, action, CleanTask)() {
  return ::rosidl_typesupport_cpp::get_action_type_support_handle<robot_cleaning_interfaces::action::CleanTask>();
}

#ifdef __cplusplus
}
#endif
