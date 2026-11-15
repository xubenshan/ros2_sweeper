cmake_minimum_required(VERSION 3.16)
project(robot_cleaning_interfaces)
find_package(ament_cmake REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(std_msgs REQUIRED)
rosidl_generate_interfaces(${PROJECT_NAME}
  "action/CleanTask.action"
  "msg/CleaningEvent.msg"
  "msg/CoverageStatus.msg"
  "msg/LocalizationHealth.msg"
  "srv/BeginCoverage.srv"
  "srv/ListCleaningEvents.srv"
  "srv/PlanCoverage.srv"
  DEPENDENCIES geometry_msgs nav_msgs std_msgs)
ament_export_dependencies(rosidl_default_runtime)
ament_package()
