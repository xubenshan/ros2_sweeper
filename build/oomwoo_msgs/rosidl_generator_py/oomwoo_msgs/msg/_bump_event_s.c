// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from oomwoo_msgs:msg/BumpEvent.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "oomwoo_msgs/msg/detail/bump_event__struct.h"
#include "oomwoo_msgs/msg/detail/bump_event__functions.h"

ROSIDL_GENERATOR_C_IMPORT
bool std_msgs__msg__header__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * std_msgs__msg__header__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__point__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__point__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__point__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__point__convert_to_py(void * raw_ros_message);
ROSIDL_GENERATOR_C_IMPORT
bool geometry_msgs__msg__point__convert_from_py(PyObject * _pymsg, void * _ros_message);
ROSIDL_GENERATOR_C_IMPORT
PyObject * geometry_msgs__msg__point__convert_to_py(void * raw_ros_message);

ROSIDL_GENERATOR_C_EXPORT
bool oomwoo_msgs__msg__bump_event__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[38];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("oomwoo_msgs.msg._bump_event.BumpEvent", full_classname_dest, 37) == 0);
  }
  oomwoo_msgs__msg__BumpEvent * ros_message = _ros_message;
  {  // header
    PyObject * field = PyObject_GetAttrString(_pymsg, "header");
    if (!field) {
      return false;
    }
    if (!std_msgs__msg__header__convert_from_py(field, &ros_message->header)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // contact
    PyObject * field = PyObject_GetAttrString(_pymsg, "contact");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__point__convert_from_py(field, &ros_message->contact)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // robot
    PyObject * field = PyObject_GetAttrString(_pymsg, "robot");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__point__convert_from_py(field, &ros_message->robot)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // approach
    PyObject * field = PyObject_GetAttrString(_pymsg, "approach");
    if (!field) {
      return false;
    }
    if (!geometry_msgs__msg__point__convert_from_py(field, &ros_message->approach)) {
      Py_DECREF(field);
      return false;
    }
    Py_DECREF(field);
  }
  {  // heading
    PyObject * field = PyObject_GetAttrString(_pymsg, "heading");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->heading = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // side
    PyObject * field = PyObject_GetAttrString(_pymsg, "side");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->side = (uint8_t)PyLong_AsUnsignedLong(field);
    Py_DECREF(field);
  }
  {  // left_depress
    PyObject * field = PyObject_GetAttrString(_pymsg, "left_depress");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->left_depress = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // right_depress
    PyObject * field = PyObject_GetAttrString(_pymsg, "right_depress");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->right_depress = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // left_rate
    PyObject * field = PyObject_GetAttrString(_pymsg, "left_rate");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->left_rate = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // right_rate
    PyObject * field = PyObject_GetAttrString(_pymsg, "right_rate");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->right_rate = (float)PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * oomwoo_msgs__msg__bump_event__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of BumpEvent */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("oomwoo_msgs.msg._bump_event");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "BumpEvent");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  oomwoo_msgs__msg__BumpEvent * ros_message = (oomwoo_msgs__msg__BumpEvent *)raw_ros_message;
  {  // header
    PyObject * field = NULL;
    field = std_msgs__msg__header__convert_to_py(&ros_message->header);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "header", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // contact
    PyObject * field = NULL;
    field = geometry_msgs__msg__point__convert_to_py(&ros_message->contact);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "contact", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // robot
    PyObject * field = NULL;
    field = geometry_msgs__msg__point__convert_to_py(&ros_message->robot);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "robot", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // approach
    PyObject * field = NULL;
    field = geometry_msgs__msg__point__convert_to_py(&ros_message->approach);
    if (!field) {
      return NULL;
    }
    {
      int rc = PyObject_SetAttrString(_pymessage, "approach", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // heading
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->heading);
    {
      int rc = PyObject_SetAttrString(_pymessage, "heading", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // side
    PyObject * field = NULL;
    field = PyLong_FromUnsignedLong(ros_message->side);
    {
      int rc = PyObject_SetAttrString(_pymessage, "side", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // left_depress
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->left_depress);
    {
      int rc = PyObject_SetAttrString(_pymessage, "left_depress", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // right_depress
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->right_depress);
    {
      int rc = PyObject_SetAttrString(_pymessage, "right_depress", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // left_rate
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->left_rate);
    {
      int rc = PyObject_SetAttrString(_pymessage, "left_rate", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // right_rate
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->right_rate);
    {
      int rc = PyObject_SetAttrString(_pymessage, "right_rate", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
