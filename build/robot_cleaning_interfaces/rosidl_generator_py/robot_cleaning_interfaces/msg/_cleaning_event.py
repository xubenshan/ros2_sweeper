# generated from rosidl_generator_py/resource/_idl.py.em
# with input from robot_cleaning_interfaces:msg/CleaningEvent.idl
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


class Metaclass_CleaningEvent(type):
    """Metaclass of message 'CleaningEvent'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'INFO': 0,
        'WARNING': 1,
        'ERROR': 2,
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
                'robot_cleaning_interfaces.msg.CleaningEvent')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__cleaning_event
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__cleaning_event
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__cleaning_event
            cls._TYPE_SUPPORT = module.type_support_msg__msg__cleaning_event
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__cleaning_event

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'INFO': cls.__constants['INFO'],
            'WARNING': cls.__constants['WARNING'],
            'ERROR': cls.__constants['ERROR'],
        }

    @property
    def INFO(self):
        """Message constant 'INFO'."""
        return Metaclass_CleaningEvent.__constants['INFO']

    @property
    def WARNING(self):
        """Message constant 'WARNING'."""
        return Metaclass_CleaningEvent.__constants['WARNING']

    @property
    def ERROR(self):
        """Message constant 'ERROR'."""
        return Metaclass_CleaningEvent.__constants['ERROR']


class CleaningEvent(metaclass=Metaclass_CleaningEvent):
    """
    Message class 'CleaningEvent'.

    Constants:
      INFO
      WARNING
      ERROR
    """

    __slots__ = [
        '_header',
        '_sequence',
        '_severity',
        '_task_id',
        '_code',
        '_state',
        '_previous_state',
        '_recoverable',
        '_message',
        '_coverage',
        '_completed_waypoints',
        '_failed_waypoints',
        '_total_waypoints',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'sequence': 'uint64',
        'severity': 'uint8',
        'task_id': 'string',
        'code': 'string',
        'state': 'string',
        'previous_state': 'string',
        'recoverable': 'boolean',
        'message': 'string',
        'coverage': 'float',
        'completed_waypoints': 'uint32',
        'failed_waypoints': 'uint32',
        'total_waypoints': 'uint32',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
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
        self.sequence = kwargs.get('sequence', int())
        self.severity = kwargs.get('severity', int())
        self.task_id = kwargs.get('task_id', str())
        self.code = kwargs.get('code', str())
        self.state = kwargs.get('state', str())
        self.previous_state = kwargs.get('previous_state', str())
        self.recoverable = kwargs.get('recoverable', bool())
        self.message = kwargs.get('message', str())
        self.coverage = kwargs.get('coverage', float())
        self.completed_waypoints = kwargs.get('completed_waypoints', int())
        self.failed_waypoints = kwargs.get('failed_waypoints', int())
        self.total_waypoints = kwargs.get('total_waypoints', int())

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
        if self.sequence != other.sequence:
            return False
        if self.severity != other.severity:
            return False
        if self.task_id != other.task_id:
            return False
        if self.code != other.code:
            return False
        if self.state != other.state:
            return False
        if self.previous_state != other.previous_state:
            return False
        if self.recoverable != other.recoverable:
            return False
        if self.message != other.message:
            return False
        if self.coverage != other.coverage:
            return False
        if self.completed_waypoints != other.completed_waypoints:
            return False
        if self.failed_waypoints != other.failed_waypoints:
            return False
        if self.total_waypoints != other.total_waypoints:
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
    def sequence(self):
        """Message field 'sequence'."""
        return self._sequence

    @sequence.setter
    def sequence(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'sequence' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'sequence' field must be an unsigned integer in [0, 18446744073709551615]"
        self._sequence = value

    @builtins.property
    def severity(self):
        """Message field 'severity'."""
        return self._severity

    @severity.setter
    def severity(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'severity' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'severity' field must be an unsigned integer in [0, 255]"
        self._severity = value

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
    def code(self):
        """Message field 'code'."""
        return self._code

    @code.setter
    def code(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'code' field must be of type 'str'"
        self._code = value

    @builtins.property
    def state(self):
        """Message field 'state'."""
        return self._state

    @state.setter
    def state(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'state' field must be of type 'str'"
        self._state = value

    @builtins.property
    def previous_state(self):
        """Message field 'previous_state'."""
        return self._previous_state

    @previous_state.setter
    def previous_state(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'previous_state' field must be of type 'str'"
        self._previous_state = value

    @builtins.property
    def recoverable(self):
        """Message field 'recoverable'."""
        return self._recoverable

    @recoverable.setter
    def recoverable(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'recoverable' field must be of type 'bool'"
        self._recoverable = value

    @builtins.property
    def message(self):
        """Message field 'message'."""
        return self._message

    @message.setter
    def message(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'message' field must be of type 'str'"
        self._message = value

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
    def completed_waypoints(self):
        """Message field 'completed_waypoints'."""
        return self._completed_waypoints

    @completed_waypoints.setter
    def completed_waypoints(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'completed_waypoints' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'completed_waypoints' field must be an unsigned integer in [0, 4294967295]"
        self._completed_waypoints = value

    @builtins.property
    def failed_waypoints(self):
        """Message field 'failed_waypoints'."""
        return self._failed_waypoints

    @failed_waypoints.setter
    def failed_waypoints(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'failed_waypoints' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'failed_waypoints' field must be an unsigned integer in [0, 4294967295]"
        self._failed_waypoints = value

    @builtins.property
    def total_waypoints(self):
        """Message field 'total_waypoints'."""
        return self._total_waypoints

    @total_waypoints.setter
    def total_waypoints(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'total_waypoints' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'total_waypoints' field must be an unsigned integer in [0, 4294967295]"
        self._total_waypoints = value
