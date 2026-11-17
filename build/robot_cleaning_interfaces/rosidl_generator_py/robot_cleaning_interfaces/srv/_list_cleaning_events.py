# generated from rosidl_generator_py/resource/_idl.py.em
# with input from robot_cleaning_interfaces:srv/ListCleaningEvents.idl
# generated code does not contain a copyright notice

# This is being done at the module level and not on the instance level to avoid looking
# for the same variable multiple times on each instance. This variable is not supposed to
# change during runtime so it makes sense to only look for it once.
from os import getenv

ros_python_check_fields = getenv('ROS_PYTHON_CHECK_FIELDS', default='')


# Import statements for member types

import builtins  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_ListCleaningEvents_Request(type):
    """Metaclass of message 'ListCleaningEvents_Request'."""

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
                'robot_cleaning_interfaces.srv.ListCleaningEvents_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__list_cleaning_events__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__list_cleaning_events__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__list_cleaning_events__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__list_cleaning_events__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__list_cleaning_events__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ListCleaningEvents_Request(metaclass=Metaclass_ListCleaningEvents_Request):
    """Message class 'ListCleaningEvents_Request'."""

    __slots__ = [
        '_limit',
        '_task_id_filter',
        '_code_filter',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'limit': 'uint32',
        'task_id_filter': 'string',
        'code_filter': 'string',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
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
        self.limit = kwargs.get('limit', int())
        self.task_id_filter = kwargs.get('task_id_filter', str())
        self.code_filter = kwargs.get('code_filter', str())

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
        if self.limit != other.limit:
            return False
        if self.task_id_filter != other.task_id_filter:
            return False
        if self.code_filter != other.code_filter:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def limit(self):
        """Message field 'limit'."""
        return self._limit

    @limit.setter
    def limit(self, value):
        if self._check_fields:
            assert \
                isinstance(value, int), \
                "The 'limit' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'limit' field must be an unsigned integer in [0, 4294967295]"
        self._limit = value

    @builtins.property
    def task_id_filter(self):
        """Message field 'task_id_filter'."""
        return self._task_id_filter

    @task_id_filter.setter
    def task_id_filter(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'task_id_filter' field must be of type 'str'"
        self._task_id_filter = value

    @builtins.property
    def code_filter(self):
        """Message field 'code_filter'."""
        return self._code_filter

    @code_filter.setter
    def code_filter(self, value):
        if self._check_fields:
            assert \
                isinstance(value, str), \
                "The 'code_filter' field must be of type 'str'"
        self._code_filter = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ListCleaningEvents_Response(type):
    """Metaclass of message 'ListCleaningEvents_Response'."""

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
                'robot_cleaning_interfaces.srv.ListCleaningEvents_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__list_cleaning_events__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__list_cleaning_events__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__list_cleaning_events__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__list_cleaning_events__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__list_cleaning_events__response

            from robot_cleaning_interfaces.msg import CleaningEvent
            if CleaningEvent.__class__._TYPE_SUPPORT is None:
                CleaningEvent.__class__.__import_type_support__()

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class ListCleaningEvents_Response(metaclass=Metaclass_ListCleaningEvents_Response):
    """Message class 'ListCleaningEvents_Response'."""

    __slots__ = [
        '_success',
        '_message',
        '_events',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'success': 'boolean',
        'message': 'string',
        'events': 'sequence<robot_cleaning_interfaces/CleaningEvent>',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.NamespacedType(['robot_cleaning_interfaces', 'msg'], 'CleaningEvent')),  # noqa: E501
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
        self.message = kwargs.get('message', str())
        self.events = kwargs.get('events', [])

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
        if self.message != other.message:
            return False
        if self.events != other.events:
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
    def events(self):
        """Message field 'events'."""
        return self._events

    @events.setter
    def events(self, value):
        if self._check_fields:
            from robot_cleaning_interfaces.msg import CleaningEvent
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
                 all(isinstance(v, CleaningEvent) for v in value) and
                 True), \
                "The 'events' field must be a set or sequence and each value of type 'CleaningEvent'"
        self._events = value


# Import statements for member types

# already imported above
# import builtins

# already imported above
# import rosidl_parser.definition


class Metaclass_ListCleaningEvents_Event(type):
    """Metaclass of message 'ListCleaningEvents_Event'."""

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
                'robot_cleaning_interfaces.srv.ListCleaningEvents_Event')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__list_cleaning_events__event
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__list_cleaning_events__event
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__list_cleaning_events__event
            cls._TYPE_SUPPORT = module.type_support_msg__srv__list_cleaning_events__event
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__list_cleaning_events__event

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


class ListCleaningEvents_Event(metaclass=Metaclass_ListCleaningEvents_Event):
    """Message class 'ListCleaningEvents_Event'."""

    __slots__ = [
        '_info',
        '_request',
        '_response',
        '_check_fields',
    ]

    _fields_and_field_types = {
        'info': 'service_msgs/ServiceEventInfo',
        'request': 'sequence<robot_cleaning_interfaces/ListCleaningEvents_Request, 1>',
        'response': 'sequence<robot_cleaning_interfaces/ListCleaningEvents_Response, 1>',
    }

    # This attribute is used to store an rosidl_parser.definition variable
    # related to the data type of each of the components the message.
    SLOT_TYPES = (
        rosidl_parser.definition.NamespacedType(['service_msgs', 'msg'], 'ServiceEventInfo'),  # noqa: E501
        rosidl_parser.definition.BoundedSequence(rosidl_parser.definition.NamespacedType(['robot_cleaning_interfaces', 'srv'], 'ListCleaningEvents_Request'), 1),  # noqa: E501
        rosidl_parser.definition.BoundedSequence(rosidl_parser.definition.NamespacedType(['robot_cleaning_interfaces', 'srv'], 'ListCleaningEvents_Response'), 1),  # noqa: E501
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
            from robot_cleaning_interfaces.srv import ListCleaningEvents_Request
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
                 all(isinstance(v, ListCleaningEvents_Request) for v in value) and
                 True), \
                "The 'request' field must be a set or sequence with length <= 1 and each value of type 'ListCleaningEvents_Request'"
        self._request = value

    @builtins.property
    def response(self):
        """Message field 'response'."""
        return self._response

    @response.setter
    def response(self, value):
        if self._check_fields:
            from robot_cleaning_interfaces.srv import ListCleaningEvents_Response
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
                 all(isinstance(v, ListCleaningEvents_Response) for v in value) and
                 True), \
                "The 'response' field must be a set or sequence with length <= 1 and each value of type 'ListCleaningEvents_Response'"
        self._response = value


class Metaclass_ListCleaningEvents(type):
    """Metaclass of service 'ListCleaningEvents'."""

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
                'robot_cleaning_interfaces.srv.ListCleaningEvents')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__list_cleaning_events

            from robot_cleaning_interfaces.srv import _list_cleaning_events
            if _list_cleaning_events.Metaclass_ListCleaningEvents_Request._TYPE_SUPPORT is None:
                _list_cleaning_events.Metaclass_ListCleaningEvents_Request.__import_type_support__()
            if _list_cleaning_events.Metaclass_ListCleaningEvents_Response._TYPE_SUPPORT is None:
                _list_cleaning_events.Metaclass_ListCleaningEvents_Response.__import_type_support__()
            if _list_cleaning_events.Metaclass_ListCleaningEvents_Event._TYPE_SUPPORT is None:
                _list_cleaning_events.Metaclass_ListCleaningEvents_Event.__import_type_support__()


class ListCleaningEvents(metaclass=Metaclass_ListCleaningEvents):
    from robot_cleaning_interfaces.srv._list_cleaning_events import ListCleaningEvents_Request as Request
    from robot_cleaning_interfaces.srv._list_cleaning_events import ListCleaningEvents_Response as Response
    from robot_cleaning_interfaces.srv._list_cleaning_events import ListCleaningEvents_Event as Event

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
