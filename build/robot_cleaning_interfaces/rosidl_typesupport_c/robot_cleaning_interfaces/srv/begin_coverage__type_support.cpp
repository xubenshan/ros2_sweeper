// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from robot_cleaning_interfaces:srv/BeginCoverage.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "robot_cleaning_interfaces/srv/detail/begin_coverage__struct.h"
#include "robot_cleaning_interfaces/srv/detail/begin_coverage__type_support.h"
#include "robot_cleaning_interfaces/srv/detail/begin_coverage__functions.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace robot_cleaning_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _BeginCoverage_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _BeginCoverage_Request_type_support_ids_t;

static const _BeginCoverage_Request_type_support_ids_t _BeginCoverage_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _BeginCoverage_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _BeginCoverage_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _BeginCoverage_Request_type_support_symbol_names_t _BeginCoverage_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_cleaning_interfaces, srv, BeginCoverage_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_cleaning_interfaces, srv, BeginCoverage_Request)),
  }
};

typedef struct _BeginCoverage_Request_type_support_data_t
{
  void * data[2];
} _BeginCoverage_Request_type_support_data_t;

static _BeginCoverage_Request_type_support_data_t _BeginCoverage_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _BeginCoverage_Request_message_typesupport_map = {
  2,
  "robot_cleaning_interfaces",
  &_BeginCoverage_Request_message_typesupport_ids.typesupport_identifier[0],
  &_BeginCoverage_Request_message_typesupport_symbol_names.symbol_name[0],
  &_BeginCoverage_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t BeginCoverage_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_BeginCoverage_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__srv__BeginCoverage_Request__get_type_hash,
  &robot_cleaning_interfaces__srv__BeginCoverage_Request__get_type_description,
  &robot_cleaning_interfaces__srv__BeginCoverage_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace robot_cleaning_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, robot_cleaning_interfaces, srv, BeginCoverage_Request)() {
  return &::robot_cleaning_interfaces::srv::rosidl_typesupport_c::BeginCoverage_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "robot_cleaning_interfaces/srv/detail/begin_coverage__struct.h"
// already included above
// #include "robot_cleaning_interfaces/srv/detail/begin_coverage__type_support.h"
// already included above
// #include "robot_cleaning_interfaces/srv/detail/begin_coverage__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_cleaning_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _BeginCoverage_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _BeginCoverage_Response_type_support_ids_t;

static const _BeginCoverage_Response_type_support_ids_t _BeginCoverage_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _BeginCoverage_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _BeginCoverage_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _BeginCoverage_Response_type_support_symbol_names_t _BeginCoverage_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_cleaning_interfaces, srv, BeginCoverage_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_cleaning_interfaces, srv, BeginCoverage_Response)),
  }
};

typedef struct _BeginCoverage_Response_type_support_data_t
{
  void * data[2];
} _BeginCoverage_Response_type_support_data_t;

static _BeginCoverage_Response_type_support_data_t _BeginCoverage_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _BeginCoverage_Response_message_typesupport_map = {
  2,
  "robot_cleaning_interfaces",
  &_BeginCoverage_Response_message_typesupport_ids.typesupport_identifier[0],
  &_BeginCoverage_Response_message_typesupport_symbol_names.symbol_name[0],
  &_BeginCoverage_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t BeginCoverage_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_BeginCoverage_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__srv__BeginCoverage_Response__get_type_hash,
  &robot_cleaning_interfaces__srv__BeginCoverage_Response__get_type_description,
  &robot_cleaning_interfaces__srv__BeginCoverage_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace robot_cleaning_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, robot_cleaning_interfaces, srv, BeginCoverage_Response)() {
  return &::robot_cleaning_interfaces::srv::rosidl_typesupport_c::BeginCoverage_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "robot_cleaning_interfaces/srv/detail/begin_coverage__struct.h"
// already included above
// #include "robot_cleaning_interfaces/srv/detail/begin_coverage__type_support.h"
// already included above
// #include "robot_cleaning_interfaces/srv/detail/begin_coverage__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace robot_cleaning_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _BeginCoverage_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _BeginCoverage_Event_type_support_ids_t;

static const _BeginCoverage_Event_type_support_ids_t _BeginCoverage_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _BeginCoverage_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _BeginCoverage_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _BeginCoverage_Event_type_support_symbol_names_t _BeginCoverage_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_cleaning_interfaces, srv, BeginCoverage_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_cleaning_interfaces, srv, BeginCoverage_Event)),
  }
};

typedef struct _BeginCoverage_Event_type_support_data_t
{
  void * data[2];
} _BeginCoverage_Event_type_support_data_t;

static _BeginCoverage_Event_type_support_data_t _BeginCoverage_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _BeginCoverage_Event_message_typesupport_map = {
  2,
  "robot_cleaning_interfaces",
  &_BeginCoverage_Event_message_typesupport_ids.typesupport_identifier[0],
  &_BeginCoverage_Event_message_typesupport_symbol_names.symbol_name[0],
  &_BeginCoverage_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t BeginCoverage_Event_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_BeginCoverage_Event_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &robot_cleaning_interfaces__srv__BeginCoverage_Event__get_type_hash,
  &robot_cleaning_interfaces__srv__BeginCoverage_Event__get_type_description,
  &robot_cleaning_interfaces__srv__BeginCoverage_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace robot_cleaning_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, robot_cleaning_interfaces, srv, BeginCoverage_Event)() {
  return &::robot_cleaning_interfaces::srv::rosidl_typesupport_c::BeginCoverage_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "robot_cleaning_interfaces/srv/detail/begin_coverage__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
#include "service_msgs/msg/service_event_info.h"
#include "builtin_interfaces/msg/time.h"

namespace robot_cleaning_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{
typedef struct _BeginCoverage_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _BeginCoverage_type_support_ids_t;

static const _BeginCoverage_type_support_ids_t _BeginCoverage_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _BeginCoverage_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _BeginCoverage_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _BeginCoverage_type_support_symbol_names_t _BeginCoverage_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, robot_cleaning_interfaces, srv, BeginCoverage)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, robot_cleaning_interfaces, srv, BeginCoverage)),
  }
};

typedef struct _BeginCoverage_type_support_data_t
{
  void * data[2];
} _BeginCoverage_type_support_data_t;

static _BeginCoverage_type_support_data_t _BeginCoverage_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _BeginCoverage_service_typesupport_map = {
  2,
  "robot_cleaning_interfaces",
  &_BeginCoverage_service_typesupport_ids.typesupport_identifier[0],
  &_BeginCoverage_service_typesupport_symbol_names.symbol_name[0],
  &_BeginCoverage_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t BeginCoverage_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_BeginCoverage_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
  &BeginCoverage_Request_message_type_support_handle,
  &BeginCoverage_Response_message_type_support_handle,
  &BeginCoverage_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    robot_cleaning_interfaces,
    srv,
    BeginCoverage
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    robot_cleaning_interfaces,
    srv,
    BeginCoverage
  ),
  &robot_cleaning_interfaces__srv__BeginCoverage__get_type_hash,
  &robot_cleaning_interfaces__srv__BeginCoverage__get_type_description,
  &robot_cleaning_interfaces__srv__BeginCoverage__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace robot_cleaning_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, robot_cleaning_interfaces, srv, BeginCoverage)() {
  return &::robot_cleaning_interfaces::srv::rosidl_typesupport_c::BeginCoverage_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif
