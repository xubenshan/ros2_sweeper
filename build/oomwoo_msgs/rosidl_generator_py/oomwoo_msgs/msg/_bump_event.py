# generated from rosidl_generator_py/resource/_idl.py.em
# with input from oomwoo_msgs:msg/BumpEvent.idl
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


class Metaclass_BumpEvent(type):
    """Metaclass of message 'BumpEvent'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'SIDE_BOTH': 0,
        'SIDE_LEFT': 1,
        'SIDE_RIGHT': 2,
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('oomwoo_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'oomwoo_msgs.msg.BumpEvent')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__bump_event
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__bump_event
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__bump_event
            cls._TYPE_SUPPORT = module.type_support_msg__msg__bump_event
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__bump_event

            from geometry_msgs.msg import Point
            if Point.__class__._TYPE_SUPPORT is None:
                Point.__class__.__import_type_support__()

            from std_msgs.msg import Header
            if Header.__class__._TYPE_SUPPORT is None:
                Header.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'SIDE_BOTH': cls.__constants['SIDE_BOTH'],
            'SIDE_LEFT': cls.__constants['SIDE_LEFT'],
            'SIDE_RIGHT': cls.__constants['SIDE_RIGHT'],
        }

    @property
    def SIDE_BOTH(self):
        """Message constant 'SIDE_BOTH'."""
        return Metaclass_BumpEvent.__constants['SIDE_BOTH']

    @property
    def SIDE_LEFT(self):
        """Message constant 'SIDE_LEFT'."""
        return Metaclass_BumpEvent.__constants['SIDE_LEFT']

    @property
    def SIDE_RIGHT(self):
        """Message constant 'SIDE_RIGHT'."""
        return Metaclass_BumpEvent.__constants['SIDE_RIGHT']


class BumpEvent(metaclass=Metaclass_BumpEvent):
    """
    Message class 'BumpEvent'.

    Constants:
      SIDE_BOTH
      SIDE_LEFT
      SIDE_RIGHT
    """

    __slots__ = [
        '_header',
        '_contact',
        '_robot',
        '_approach',
        '_heading',
        '_side',
        '_left_depress',
        '_right_depress',
        '_left_rate',
        '_right_rate',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'header': 'std_msgs/Header',
        'contact': 'geometry_msgs/Point',
        'robot': 'geometry_msgs/Point',
        'approach': 'geometry_msgs/Point',
        'heading': 'double',
        'side': 'uint8',
        'left_depress': 'float',
        'right_depress': 'float',
        'left_rate': 'float',
        'right_rate': 'float',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['std_msgs', 'msg'], 'Header'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
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
        from geometry_msgs.msg import Point
        self.contact = kwargs.get('contact', Point())
        from geometry_msgs.msg import Point
        self.robot = kwargs.get('robot', Point())
        from geometry_msgs.msg import Point
        self.approach = kwargs.get('approach', Point())
        self.heading = kwargs.get('heading', float())
        self.side = kwargs.get('side', int())
        self.left_depress = kwargs.get('left_depress', float())
        self.right_depress = kwargs.get('right_depress', float())
        self.left_rate = kwargs.get('left_rate', float())
        self.right_rate = kwargs.get('right_rate', float())

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
        if self.contact != other.contact:
            return False
        if self.robot != other.robot:
            return False
        if self.approach != other.approach:
            return False
        if self.heading != other.heading:
            return False
        if self.side != other.side:
            return False
        if self.left_depress != other.left_depress:
            return False
        if self.right_depress != other.right_depress:
            return False
        if self.left_rate != other.left_rate:
            return False
        if self.right_rate != other.right_rate:
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
    def contact(self):
        """Message field 'contact'."""
        return self._contact

    @contact.setter
    def contact(self, value):
        if self._check_fields:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'contact' field must be a sub message of type 'Point'"
        self._contact = value

    @builtins.property
    def robot(self):
        """Message field 'robot'."""
        return self._robot

    @robot.setter
    def robot(self, value):
        if self._check_fields:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'robot' field must be a sub message of type 'Point'"
        self._robot = value

    @builtins.property
    def approach(self):
        """Message field 'approach'."""
        return self._approach

    @approach.setter
    def approach(self, value):
        if self._check_fields:
            from geometry_msgs.msg import Point
            assert \
                isinstance(value, Point), \
                "The 'approach' field must be a sub message of type 'Point'"
        self._approach = value

    @builtins.property
    def heading(self):
        """Message field 'heading'."""
        return self._heading

    @heading.setter
    def heading(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'heading' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'heading' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._heading = value

    @builtins.property
    def side(self):
        """Message field 'side'."""
        return self._side

    @side.setter
    def side(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'side' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'side' field must be an unsigned integer in [0, 255]"
        self._side = value

    @builtins.property
    def left_depress(self):
        """Message field 'left_depress'."""
        return self._left_depress

    @left_depress.setter
    def left_depress(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'left_depress' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'left_depress' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._left_depress = value

    @builtins.property
    def right_depress(self):
        """Message field 'right_depress'."""
        return self._right_depress

    @right_depress.setter
    def right_depress(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'right_depress' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'right_depress' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._right_depress = value

    @builtins.property
    def left_rate(self):
        """Message field 'left_rate'."""
        return self._left_rate

    @left_rate.setter
    def left_rate(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'left_rate' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'left_rate' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._left_rate = value

    @builtins.property
    def right_rate(self):
        """Message field 'right_rate'."""
        return self._right_rate

    @right_rate.setter
    def right_rate(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'right_rate' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'right_rate' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._right_rate = value
