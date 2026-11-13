# generated from rosidl_generator_py/resource/_idl.py.em
# with input from robot_cleaning_interfaces:srv/PlanCoverage.idl
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


class Metaclass_PlanCoverage_Request(type):
    """Metaclass of message 'PlanCoverage_Request'."""

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
                'robot_cleaning_interfaces.srv.PlanCoverage_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__plan_coverage__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__plan_coverage__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__plan_coverage__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__plan_coverage__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__plan_coverage__request

            from geometry_msgs.msg import Point
            if Point.__class__._TYPE_SUPPORT is None:
                Point.__class__.__import_type_support__()

            from geometry_msgs.msg import PoseStamped
            if PoseStamped.__class__._TYPE_SUPPORT is None:
                PoseStamped.__class__.__import_type_support__()

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


class PlanCoverage_Request(metaclass=Metaclass_PlanCoverage_Request):
    """Message class 'PlanCoverage_Request'."""

    __slots__ = [
        '_regions',
        '_start',
        '_gap_fill',
        '_target_coverage',
        '_distance_budget_m',
        '_covered',
        '_excluded',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'regions': 'sequence<string>',
        'start': 'geometry_msgs/PoseStamped',
        'gap_fill': 'boolean',
        'target_coverage': 'float',
        'distance_budget_m': 'double',
        'covered': 'nav_msgs/OccupancyGrid',
        'excluded': 'sequence<geometry_msgs/Point>',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.UnboundedString()),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'PoseStamped'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['nav_msgs', 'msg'], 'OccupancyGrid'),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['geometry_msgs', 'msg'], 'Point')),  # noqa: E501
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
        self.regions = kwargs.get('regions', [])
        from geometry_msgs.msg import PoseStamped
        self.start = kwargs.get('start', PoseStamped())
        self.gap_fill = kwargs.get('gap_fill', bool())
        self.target_coverage = kwargs.get('target_coverage', float())
        self.distance_budget_m = kwargs.get('distance_budget_m', float())
        from nav_msgs.msg import OccupancyGrid
        self.covered = kwargs.get('covered', OccupancyGrid())
        self.excluded = kwargs.get('excluded', [])

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
        if self.regions != other.regions:
            return False
        if self.start != other.start:
            return False
        if self.gap_fill != other.gap_fill:
            return False
        if self.target_coverage != other.target_coverage:
            return False
        if self.distance_budget_m != other.distance_budget_m:
            return False
        if self.covered != other.covered:
            return False
        if self.excluded != other.excluded:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def regions(self):
        """Message field 'regions'."""
        return self._regions

    @regions.setter
    def regions(self, value):
        if self._check_fields:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, str) for v in value) and
                 True), \
                "The 'regions' field must be a set or sequence and each value of type 'str'"
        self._regions = value

    @builtins.property
    def start(self):
        """Message field 'start'."""
        return self._start

    @start.setter
    def start(self, value):
        if self._check_fields:
            from geometry_msgs.msg import PoseStamped
            assert \
                isinstance(value, PoseStamped), \
                "The 'start' field must be a sub message of type 'PoseStamped'"
        self._start = value

    @builtins.property
    def gap_fill(self):
        """Message field 'gap_fill'."""
        return self._gap_fill

    @gap_fill.setter
    def gap_fill(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'gap_fill' field must be of type 'bool'"
        self._gap_fill = value

    @builtins.property
    def target_coverage(self):
        """Message field 'target_coverage'."""
        return self._target_coverage

    @target_coverage.setter
    def target_coverage(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'target_coverage' field must be of type 'float'"
            assert not (value < -3.402823466e+38 or value > 3.402823466e+38) or math.isinf(value), \
                "The 'target_coverage' field must be a float in [-3.402823466e+38, 3.402823466e+38]"
        self._target_coverage = value

    @builtins.property
    def distance_budget_m(self):
        """Message field 'distance_budget_m'."""
        return self._distance_budget_m

    @distance_budget_m.setter
    def distance_budget_m(self, value):
        if self._check_fields:
            assert \
                isinstance(value, float), \
                "The 'distance_budget_m' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'distance_budget_m' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._distance_budget_m = value

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

    @builtins.property
    def excluded(self):
        """Message field 'excluded'."""
        return self._excluded

    @excluded.setter
    def excluded(self, value):
        if self._check_fields:
            from geometry_msgs.msg import Point
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, Point) for v in value) and
                 True), \
                "The 'excluded' field must be a set or sequence and each value of type 'Point'"
        self._excluded = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_PlanCoverage_Response(type):
    """Metaclass of message 'PlanCoverage_Response'."""

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
                'robot_cleaning_interfaces.srv.PlanCoverage_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__plan_coverage__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__plan_coverage__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__plan_coverage__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__plan_coverage__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__plan_coverage__response

            from nav_msgs.msg import Path
            if Path.__class__._TYPE_SUPPORT is None:
                Path.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class PlanCoverage_Response(metaclass=Metaclass_PlanCoverage_Response):
    """Message class 'PlanCoverage_Response'."""

    __slots__ = [
        '_success',
        '_reason',
        '_path',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'reason': 'string',
        'path': 'nav_msgs/Path',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.NamespacedType(['nav_msgs', 'msg'], 'Path'),  # noqa: E501
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
        self.success = kwargs.get('success', bool())
        self.reason = kwargs.get('reason', str())
        from nav_msgs.msg import Path
        self.path = kwargs.get('path', Path())

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
        if self.success != other.success:
            return False
        if self.reason != other.reason:
            return False
        if self.path != other.path:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def success(self):
        """Message field 'success'."""
        return self._success

    @success.setter
    def success(self, value):
        if self._check_fields:
            assert \
                isinstance(value, bool), \
                "The 'success' field must be of type 'bool'"
        self._success = value

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

    @builtins.property
    def path(self):
        """Message field 'path'."""
        return self._path

    @path.setter
    def path(self, value):
        if self._check_fields:
            from nav_msgs.msg import Path
            assert \
                isinstance(value, Path), \
                "The 'path' field must be a sub message of type 'Path'"
        self._path = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_PlanCoverage_Event(type):
    """Metaclass of message 'PlanCoverage_Event'."""

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
                'robot_cleaning_interfaces.srv.PlanCoverage_Event')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__plan_coverage__event
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__plan_coverage__event
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__plan_coverage__event
            cls._TYPE_SUPPORT = module.type_support_msg__srv__plan_coverage__event
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__plan_coverage__event

            from service_msgs.msg import ServiceEventInfo
            if ServiceEventInfo.__class__._TYPE_SUPPORT is None:
                ServiceEventInfo.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class PlanCoverage_Event(metaclass=Metaclass_PlanCoverage_Event):
    """Message class 'PlanCoverage_Event'."""

    __slots__ = [
        '_info',
        '_request',
        '_response',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'info': 'service_msgs/ServiceEventInfo',
        'request': 'sequence<robot_cleaning_interfaces/PlanCoverage_Request, 1>',
        'response': 'sequence<robot_cleaning_interfaces/PlanCoverage_Response, 1>',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['service_msgs', 'msg'], 'ServiceEventInfo'),  # noqa: E501
        rosidl_parser.definition.BoundedSequence(rosidl_parser.definition.NamespacedType(['robot_cleaning_interfaces', 'srv'], 'PlanCoverage_Request'), 1),  # noqa: E501
        rosidl_parser.definition.BoundedSequence(rosidl_parser.definition.NamespacedType(['robot_cleaning_interfaces', 'srv'], 'PlanCoverage_Response'), 1),  # noqa: E501
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
        from service_msgs.msg import ServiceEventInfo
        self.info = kwargs.get('info', ServiceEventInfo())
        self.request = kwargs.get('request', [])
        self.response = kwargs.get('response', [])

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
        if self.info != other.info:
            return False
        if self.request != other.request:
            return False
        if self.response != other.response:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def info(self):
        """Message field 'info'."""
        return self._info

    @info.setter
    def info(self, value):
        if self._check_fields:
            from service_msgs.msg import ServiceEventInfo
            assert \
                isinstance(value, ServiceEventInfo), \
                "The 'info' field must be a sub message of type 'ServiceEventInfo'"
        self._info = value

    @builtins.property
    def request(self):
        """Message field 'request'."""
        return self._request

    @request.setter
    def request(self, value):
        if self._check_fields:
            from robot_cleaning_interfaces.srv import PlanCoverage_Request
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) <= 1 and
                 all(isinstance(v, PlanCoverage_Request) for v in value) and
                 True), \
                "The 'request' field must be a set or sequence with length <= 1 and each value of type 'PlanCoverage_Request'"
        self._request = value

    @builtins.property
    def response(self):
        """Message field 'response'."""
        return self._response

    @response.setter
    def response(self, value):
        if self._check_fields:
            from robot_cleaning_interfaces.srv import PlanCoverage_Response
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) <= 1 and
                 all(isinstance(v, PlanCoverage_Response) for v in value) and
                 True), \
                "The 'response' field must be a set or sequence with length <= 1 and each value of type 'PlanCoverage_Response'"
        self._response = value


class Metaclass_PlanCoverage(type):
    """Metaclass of service 'PlanCoverage'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('robot_cleaning_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'robot_cleaning_interfaces.srv.PlanCoverage')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__plan_coverage

            from robot_cleaning_interfaces.srv import _plan_coverage
            if _plan_coverage.Metaclass_PlanCoverage_Request._TYPE_SUPPORT is None:
                _plan_coverage.Metaclass_PlanCoverage_Request.__import_type_support__()
            if _plan_coverage.Metaclass_PlanCoverage_Response._TYPE_SUPPORT is None:
                _plan_coverage.Metaclass_PlanCoverage_Response.__import_type_support__()
            if _plan_coverage.Metaclass_PlanCoverage_Event._TYPE_SUPPORT is None:
                _plan_coverage.Metaclass_PlanCoverage_Event.__import_type_support__()


class PlanCoverage(metaclass=Metaclass_PlanCoverage):
    from robot_cleaning_interfaces.srv._plan_coverage import PlanCoverage_Request as Request
    from robot_cleaning_interfaces.srv._plan_coverage import PlanCoverage_Response as Response
    from robot_cleaning_interfaces.srv._plan_coverage import PlanCoverage_Event as Event

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
