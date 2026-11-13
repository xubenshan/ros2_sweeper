// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from robot_cleaning_interfaces:srv/PlanCoverage.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "robot_cleaning_interfaces/srv/detail/plan_coverage__functions.h"
#include "robot_cleaning_interfaces/srv/detail/plan_coverage__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace robot_cleaning_interfaces
{

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _PlanCoverage_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _PlanCoverage_Request_type_support_ids_t;

static const _PlanCoverage_Request_type_support_ids_t _PlanCoverage_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _PlanCoverage_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _PlanCoverage_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _PlanCoverage_Request_type_support_symbol_names_t _PlanCoverage_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, robot_cleaning_interfaces, srv, PlanCoverage_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, robot_cleaning_interfaces, srv, PlanCoverage_Request)),
  }
};

typedef struct _PlanCoverage_Request_type_support_data_t
{
  void * data[2];
} _PlanCoverage_Request_type_support_data_t;

static _PlanCoverage_Request_type_support_data_t _PlanCoverage_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _PlanCoverage_Request_message_typesupport_map = {
  2,
  "robot_cleaning_interfaces",
  &_PlanCoverage_Request_message_typesupport_ids.typesupport_identifier[0],
  &_PlanCoverage_Request_message_typesupport_symbol_names.symbol_name[0],
  &_PlanCoverage_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t PlanCoverage_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_PlanCoverage_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__srv__PlanCoverage_Request__get_type_hash,
  &robot_cleaning_interfaces__srv__PlanCoverage_Request__get_type_description,
  &robot_cleaning_interfaces__srv__PlanCoverage_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace robot_cleaning_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<robot_cleaning_interfaces::srv::PlanCoverage_Request>()
{
  return &::robot_cleaning_interfaces::srv::rosidl_typesupport_cpp::PlanCoverage_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, robot_cleaning_interfaces, srv, PlanCoverage_Request)() {
  return get_message_type_support_handle<robot_cleaning_interfaces::srv::PlanCoverage_Request>();
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
// #include "robot_cleaning_interfaces/srv/detail/plan_coverage__functions.h"
// already included above
// #include "robot_cleaning_interfaces/srv/detail/plan_coverage__struct.hpp"
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

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _PlanCoverage_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _PlanCoverage_Response_type_support_ids_t;

static const _PlanCoverage_Response_type_support_ids_t _PlanCoverage_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _PlanCoverage_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _PlanCoverage_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _PlanCoverage_Response_type_support_symbol_names_t _PlanCoverage_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, robot_cleaning_interfaces, srv, PlanCoverage_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, robot_cleaning_interfaces, srv, PlanCoverage_Response)),
  }
};

typedef struct _PlanCoverage_Response_type_support_data_t
{
  void * data[2];
} _PlanCoverage_Response_type_support_data_t;

static _PlanCoverage_Response_type_support_data_t _PlanCoverage_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _PlanCoverage_Response_message_typesupport_map = {
  2,
  "robot_cleaning_interfaces",
  &_PlanCoverage_Response_message_typesupport_ids.typesupport_identifier[0],
  &_PlanCoverage_Response_message_typesupport_symbol_names.symbol_name[0],
  &_PlanCoverage_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t PlanCoverage_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_PlanCoverage_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__srv__PlanCoverage_Response__get_type_hash,
  &robot_cleaning_interfaces__srv__PlanCoverage_Response__get_type_description,
  &robot_cleaning_interfaces__srv__PlanCoverage_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace robot_cleaning_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<robot_cleaning_interfaces::srv::PlanCoverage_Response>()
{
  return &::robot_cleaning_interfaces::srv::rosidl_typesupport_cpp::PlanCoverage_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, robot_cleaning_interfaces, srv, PlanCoverage_Response)() {
  return get_message_type_support_handle<robot_cleaning_interfaces::srv::PlanCoverage_Response>();
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
// #include "robot_cleaning_interfaces/srv/detail/plan_coverage__functions.h"
// already included above
// #include "robot_cleaning_interfaces/srv/detail/plan_coverage__struct.hpp"
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

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _PlanCoverage_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _PlanCoverage_Event_type_support_ids_t;

static const _PlanCoverage_Event_type_support_ids_t _PlanCoverage_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _PlanCoverage_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _PlanCoverage_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _PlanCoverage_Event_type_support_symbol_names_t _PlanCoverage_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, robot_cleaning_interfaces, srv, PlanCoverage_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, robot_cleaning_interfaces, srv, PlanCoverage_Event)),
  }
};

typedef struct _PlanCoverage_Event_type_support_data_t
{
  void * data[2];
} _PlanCoverage_Event_type_support_data_t;

static _PlanCoverage_Event_type_support_data_t _PlanCoverage_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _PlanCoverage_Event_message_typesupport_map = {
  2,
  "robot_cleaning_interfaces",
  &_PlanCoverage_Event_message_typesupport_ids.typesupport_identifier[0],
  &_PlanCoverage_Event_message_typesupport_symbol_names.symbol_name[0],
  &_PlanCoverage_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t PlanCoverage_Event_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_PlanCoverage_Event_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__srv__PlanCoverage_Event__get_type_hash,
  &robot_cleaning_interfaces__srv__PlanCoverage_Event__get_type_description,
  &robot_cleaning_interfaces__srv__PlanCoverage_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace robot_cleaning_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<robot_cleaning_interfaces::srv::PlanCoverage_Event>()
{
  return &::robot_cleaning_interfaces::srv::rosidl_typesupport_cpp::PlanCoverage_Event_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, robot_cleaning_interfaces, srv, PlanCoverage_Event)() {
  return get_message_type_support_handle<robot_cleaning_interfaces::srv::PlanCoverage_Event>();
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
// #include "robot_cleaning_interfaces/srv/detail/plan_coverage__struct.hpp"
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

namespace srv
{

namespace rosidl_typesupport_cpp
{

typedef struct _PlanCoverage_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _PlanCoverage_type_support_ids_t;

static const _PlanCoverage_type_support_ids_t _PlanCoverage_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _PlanCoverage_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _PlanCoverage_type_support_symbol_names_t;
#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _PlanCoverage_type_support_symbol_names_t _PlanCoverage_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, robot_cleaning_interfaces, srv, PlanCoverage)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, robot_cleaning_interfaces, srv, PlanCoverage)),
  }
};

typedef struct _PlanCoverage_type_support_data_t
{
  void * data[2];
} _PlanCoverage_type_support_data_t;

static _PlanCoverage_type_support_data_t _PlanCoverage_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _PlanCoverage_service_typesupport_map = {
  2,
  "robot_cleaning_interfaces",
  &_PlanCoverage_service_typesupport_ids.typesupport_identifier[0],
  &_PlanCoverage_service_typesupport_symbol_names.symbol_name[0],
  &_PlanCoverage_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t PlanCoverage_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_PlanCoverage_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
  ::rosidl_typesupport_cpp::get_message_type_support_handle<robot_cleaning_interfaces::srv::PlanCoverage_Request>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<robot_cleaning_interfaces::srv::PlanCoverage_Response>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<robot_cleaning_interfaces::srv::PlanCoverage_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<robot_cleaning_interfaces::srv::PlanCoverage>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<robot_cleaning_interfaces::srv::PlanCoverage>,
  &robot_cleaning_interfaces__srv__PlanCoverage__get_type_hash,
  &robot_cleaning_interfaces__srv__PlanCoverage__get_type_description,
  &robot_cleaning_interfaces__srv__PlanCoverage__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace srv

}  // namespace robot_cleaning_interfaces

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<robot_cleaning_interfaces::srv::PlanCoverage>()
{
  return &::robot_cleaning_interfaces::srv::rosidl_typesupport_cpp::PlanCoverage_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, robot_cleaning_interfaces, srv, PlanCoverage)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<robot_cleaning_interfaces::srv::PlanCoverage>();
}

#ifdef __cplusplus
}
#endif
