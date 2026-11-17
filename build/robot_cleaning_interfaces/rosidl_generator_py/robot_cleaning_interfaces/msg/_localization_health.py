# generated from rosidl_generator_py/resource/_idl.py.em
# with input from robot_cleaning_interfaces:msg/LocalizationHealth.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_LocalizationHealth(type):
    """Metaclass of message 'LocalizationHealth'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'UNKNOWN': 0,
        'HEALTHY': 1,
        'DEGRADED': 2,
        'LOST': 3,
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('robot_cleaning_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'robot_cleaning_interfaces.msg.LocalizationHealth')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__localization_health
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__localization_health
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__localization_health
            cls._TYPE_SUPPORT = module.type_support_msg__msg__localization_health
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__localization_health

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'UNKNOWN': cls.__constants['UNKNOWN'],
            'HEALTHY': cls.__constants['HEALTHY'],
            'DEGRADED': cls.__constants['DEGRADED'],
            'LOST': cls.__constants['LOST'],
        }

    @property
    def UNKNOWN(self):
        """Message constant 'UNKNOWN'."""
        return Metaclass_LocalizationHealth.__constants['UNKNOWN']

    @property
    def HEALTHY(self):
        """Message constant 'HEALTHY'."""
        return Metaclass_LocalizationHealth.__constants['HEALTHY']

    @property
    def DEGRADED(self):
        """Message constant 'DEGRADED'."""
        return Metaclass_LocalizationHealth.__constants['DEGRADED']

    @property
    def LOST(self):
        """Message constant 'LOST'."""
        return Metaclass_LocalizationHealth.__constants['LOST']


class LocalizationHealth(metaclass=Metaclass_LocalizationHealth):
    """
    Message class 'LocalizationHealth'.

    Constants:
      UNKNOWN
      HEALTHY
      DEGRADED
      LOST
    """

    __slots__ = [
        '_header',
        '_state',
        '_healthy',
        '_covariance_xy',
        '_lost_covariance_threshold',
        '_pose_age_s',
        '_reason',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'state': 'uint8',
        'healthy': 'boolean',
        'covariance_xy': 'double',
        'lost_covariance_threshold': 'double',
        'pose_age_s': 'double',
        'reason': 'string',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
    )

    def __init__(self, **kwargs):
        if 'check_fields' in kwargs:
            self._check_fields = kwargs['check_fields']
        else:
            self._check_fields = ros_python_check_fields == '1'
        if self._check_fields:
            assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
                'Invalid arguments passed to constructor: %s' % \
                ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        from std_msgs.msg import Header
        self.header = kwargs.get('header', Header())
        self.state = kwargs.get('state', int())
        self.healthy = kwargs.get('healthy', bool())
        self.covariance_xy = kwargs.get('covariance_xy', float())
        self.lost_covariance_threshold = kwargs.get('lost_covariance_threshold', float())
        self.pose_age_s = kwargs.get('pose_age_s', float())
        self.reason = kwargs.get('reason', str())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.get_fields_and_field_types().keys(), self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    if self._check_fields:
                        assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.header != other.header:
            return False
        if self.state != other.state:
            return False
        if self.healthy != other.healthy:
            return False
        if self.covariance_xy != other.covariance_xy:
            return False
        if self.lost_covariance_threshold != other.lost_covariance_threshold:
            return False
        if self.pose_age_s != other.pose_age_s:
            return False
        if self.reason != other.reason:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def header(self):
        """Message field 'header'."""
        return self._header

    @header.setter
    def header(self, value):
        if self._check_fields:
            from std_msgs.msg import Header
            assert \
                isinstance(value, Header), \
                "The 'header' field must be a sub message of type 'Header'"
        self._header = value

    @builtins.property
    def state(self):
        """Message field 'state'."""
        return self._state

    @state.setter
    def state(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'state' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'state' field must be an unsigned integer in [0, 255]"
        self._state = value

    @builtins.property
    def healthy(self):
        """Message field 'healthy'."""
        return self._healthy

    @healthy.setter
    def healthy(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'healthy' field must be of type 'bool'"
        self._healthy = value

    @builtins.property
    def covariance_xy(self):
        """Message field 'covariance_xy'."""
        return self._covariance_xy

    @covariance_xy.setter
    def covariance_xy(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'covariance_xy' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'covariance_xy' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._covariance_xy = value

    @builtins.property
    def lost_covariance_threshold(self):
        """Message field 'lost_covariance_threshold'."""
        return self._lost_covariance_threshold

    @lost_covariance_threshold.setter
    def lost_covariance_threshold(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'lost_covariance_threshold' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'lost_covariance_threshold' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._lost_covariance_threshold = value

    @builtins.property
    def pose_age_s(self):
        """Message field 'pose_age_s'."""
        return self._pose_age_s

    @pose_age_s.setter
    def pose_age_s(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'pose_age_s' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'pose_age_s' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._pose_age_s = value

    @builtins.property
    def reason(self):
        """Message field 'reason'."""
        return self._reason

    @reason.setter
    def reason(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'reason' field must be of type 'str'"
        self._reason = value
