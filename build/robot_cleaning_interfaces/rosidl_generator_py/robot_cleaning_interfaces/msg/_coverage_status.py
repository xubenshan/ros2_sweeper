# generated from rosidl_generator_py/resource/_idl.py.em
# with input from robot_cleaning_interfaces:msg/CoverageStatus.idl
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


class Metaclass_CoverageStatus(type):
    """Metaclass of message 'CoverageStatus'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
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
                'robot_cleaning_interfaces.msg.CoverageStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__coverage_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__coverage_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__coverage_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__coverage_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__coverage_status

            from nav_msgs.msg import OccupancyGrid
            if OccupancyGrid.__class__._TYPE_SUPPORT is None:
                OccupancyGrid.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class CoverageStatus(metaclass=Metaclass_CoverageStatus):
    """Message class 'CoverageStatus'."""

    __slots__ = [
        '_task_id',
        '_coverage',
        '_path_length_m',
        '_covered',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'task_id': 'string',
        'coverage': 'float',
        'path_length_m': 'double',
        'covered': 'nav_msgs/OccupancyGrid',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['nav_msgs', 'msg'], 'OccupancyGrid'),  # noqa: E501
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
        self.task_id = kwargs.get('task_id', str())
        self.coverage = kwargs.get('coverage', float())
        self.path_length_m = kwargs.get('path_length_m', float())
        from nav_msgs.msg import OccupancyGrid
        self.covered = kwargs.get('covered', OccupancyGrid())

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
        if self.task_id != other.task_id:
            return False
        if self.coverage != other.coverage:
            return False
        if self.path_length_m != other.path_length_m:
            return False
        if self.covered != other.covered:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def task_id(self):
        """Message field 'task_id'."""
        return self._task_id

    @task_id.setter
    def task_id(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'task_id' field must be of type 'str'"
        self._task_id = value

    @builtins.property
    def coverage(self):
        """Message field 'coverage'."""
        return self._coverage

    @coverage.setter
    def coverage(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'coverage' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'coverage' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._coverage = value

    @builtins.property
    def path_length_m(self):
        """Message field 'path_length_m'."""
        return self._path_length_m

    @path_length_m.setter
    def path_length_m(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'path_length_m' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'path_length_m' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._path_length_m = value

    @builtins.property
    def covered(self):
        """Message field 'covered'."""
        return self._covered

    @covered.setter
    def covered(self, value):
        if self._check_fields:
            from nav_msgs.msg import OccupancyGrid
            assert \
                isinstance(value, OccupancyGrid), \
                "The 'covered' field must be a sub message of type 'OccupancyGrid'"
        self._covered = value
