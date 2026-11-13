// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from oomwoo_msgs:msg/BumpEvent.idl
// generated code does not contain a copyright notice

#include "oomwoo_msgs/msg/detail/bump_event__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_oomwoo_msgs
const rosidl_type_hash_t *
oomwoo_msgs__msg__BumpEvent__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x98, 0x24, 0x56, 0xc7, 0xf1, 0x81, 0xdf, 0xb2,
      0x89, 0xd1, 0x49, 0xe0, 0xbe, 0xb8, 0x9b, 0x62,
      0xa7, 0xbf, 0x10, 0x50, 0x87, 0x1e, 0x90, 0xb3,
      0xc9, 0x0e, 0x82, 0x33, 0x7c, 0xb9, 0x7e, 0x46,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "std_msgs/msg/detail/header__functions.h"
#include "geometry_msgs/msg/detail/point__functions.h"
#include "builtin_interfaces/msg/detail/time__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t geometry_msgs__msg__Point__EXPECTED_HASH = {1, {
    0x69, 0x63, 0x08, 0x48, 0x42, 0xa9, 0xb0, 0x44,
    0x94, 0xd6, 0xb2, 0x94, 0x1d, 0x11, 0x44, 0x47,
    0x08, 0xd8, 0x92, 0xda, 0x2f, 0x4b, 0x09, 0x84,
    0x3b, 0x9c, 0x43, 0xf4, 0x2a, 0x7f, 0x68, 0x81,
  }};
static const rosidl_type_hash_t std_msgs__msg__Header__EXPECTED_HASH = {1, {
    0xf4, 0x9f, 0xb3, 0xae, 0x2c, 0xf0, 0x70, 0xf7,
    0x93, 0x64, 0x5f, 0xf7, 0x49, 0x68, 0x3a, 0xc6,
    0xb0, 0x62, 0x03, 0xe4, 0x1c, 0x89, 0x1e, 0x17,
    0x70, 0x1b, 0x1c, 0xb5, 0x97, 0xce, 0x6a, 0x01,
  }};
#endif

static char oomwoo_msgs__msg__BumpEvent__TYPE_NAME[] = "oomwoo_msgs/msg/BumpEvent";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char geometry_msgs__msg__Point__TYPE_NAME[] = "geometry_msgs/msg/Point";
static char std_msgs__msg__Header__TYPE_NAME[] = "std_msgs/msg/Header";

// Define type names, field names, and default values
static char oomwoo_msgs__msg__BumpEvent__FIELD_NAME__header[] = "header";
static char oomwoo_msgs__msg__BumpEvent__FIELD_NAME__contact[] = "contact";
static char oomwoo_msgs__msg__BumpEvent__FIELD_NAME__robot[] = "robot";
static char oomwoo_msgs__msg__BumpEvent__FIELD_NAME__approach[] = "approach";
static char oomwoo_msgs__msg__BumpEvent__FIELD_NAME__heading[] = "heading";
static char oomwoo_msgs__msg__BumpEvent__FIELD_NAME__side[] = "side";
static char oomwoo_msgs__msg__BumpEvent__FIELD_NAME__left_depress[] = "left_depress";
static char oomwoo_msgs__msg__BumpEvent__FIELD_NAME__right_depress[] = "right_depress";
static char oomwoo_msgs__msg__BumpEvent__FIELD_NAME__left_rate[] = "left_rate";
static char oomwoo_msgs__msg__BumpEvent__FIELD_NAME__right_rate[] = "right_rate";

static rosidl_runtime_c__type_description__Field oomwoo_msgs__msg__BumpEvent__FIELDS[] = {
  {
    {oomwoo_msgs__msg__BumpEvent__FIELD_NAME__header, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    },
    {NULL, 0, 0},
  },
  {
    {oomwoo_msgs__msg__BumpEvent__FIELD_NAME__contact, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    },
    {NULL, 0, 0},
  },
  {
    {oomwoo_msgs__msg__BumpEvent__FIELD_NAME__robot, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    },
    {NULL, 0, 0},
  },
  {
    {oomwoo_msgs__msg__BumpEvent__FIELD_NAME__approach, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    },
    {NULL, 0, 0},
  },
  {
    {oomwoo_msgs__msg__BumpEvent__FIELD_NAME__heading, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {oomwoo_msgs__msg__BumpEvent__FIELD_NAME__side, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_UINT8,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {oomwoo_msgs__msg__BumpEvent__FIELD_NAME__left_depress, 12, 12},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {oomwoo_msgs__msg__BumpEvent__FIELD_NAME__right_depress, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {oomwoo_msgs__msg__BumpEvent__FIELD_NAME__left_rate, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {oomwoo_msgs__msg__BumpEvent__FIELD_NAME__right_rate, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription oomwoo_msgs__msg__BumpEvent__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    {NULL, 0, 0},
  },
  {
    {std_msgs__msg__Header__TYPE_NAME, 19, 19},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
oomwoo_msgs__msg__BumpEvent__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {oomwoo_msgs__msg__BumpEvent__TYPE_NAME, 25, 25},
      {oomwoo_msgs__msg__BumpEvent__FIELDS, 10, 10},
    },
    {oomwoo_msgs__msg__BumpEvent__REFERENCED_TYPE_DESCRIPTIONS, 3, 3},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Point__EXPECTED_HASH, geometry_msgs__msg__Point__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = geometry_msgs__msg__Point__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&std_msgs__msg__Header__EXPECTED_HASH, std_msgs__msg__Header__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[2].fields = std_msgs__msg__Header__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# A localized bump: where the vacuum physically touched something solid, and how\n"
  "# it got there. Built by the bump_map node from the two bumper switches + TF.\n"
  "#\n"
  "# The bump map is the tactile keep-out layer: LiDAR/cameras see couch skirts, bed\n"
  "# valances and curtains as solid, but only a physical contact proves something is\n"
  "# truly solid, so a coverage planner can still clean under/through the rest.\n"
  "\n"
  "std_msgs/Header header        # header.frame_id = map (or odom); stamp = bump time\n"
  "\n"
  "geometry_msgs/Point contact   # estimated contact point on the obstacle surface\n"
  "geometry_msgs/Point robot     # robot base_footprint at the bump\n"
  "geometry_msgs/Point approach  # robot base_footprint a moment before the bump\n"
  "float64 heading               # robot heading at the bump (rad, in header.frame_id)\n"
  "\n"
  "uint8 side                    # which bumper switch(es) fired (see constants)\n"
  "uint8 SIDE_BOTH=0\n"
  "uint8 SIDE_LEFT=1\n"
  "uint8 SIDE_RIGHT=2\n"
  "\n"
  "# Richer signal from optical-interrupter bumpers; all 0.0 when only the binary\n"
  "# left/right switches are available (current sim + simplest hardware). *_depress\n"
  "# is 0..1 (how far that side is pressed); *_rate is the press rate (1/s). The\n"
  "# left/right depress RATIO estimates the contact angle within the arc, replacing\n"
  "# the geometric guess bump_map makes from binary switches.\n"
  "float32 left_depress\n"
  "float32 right_depress\n"
  "float32 left_rate\n"
  "float32 right_rate";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
oomwoo_msgs__msg__BumpEvent__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {oomwoo_msgs__msg__BumpEvent__TYPE_NAME, 25, 25},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 1387, 1387},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
oomwoo_msgs__msg__BumpEvent__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[4];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 4, 4};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *oomwoo_msgs__msg__BumpEvent__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *geometry_msgs__msg__Point__get_individual_type_description_source(NULL);
    sources[3] = *std_msgs__msg__Header__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
