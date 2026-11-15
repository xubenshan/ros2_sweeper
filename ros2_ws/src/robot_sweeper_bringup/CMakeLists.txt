cmake_minimum_required(VERSION 3.16)
project(robot_sweeper_bringup)
find_package(ament_cmake REQUIRED)
install(DIRECTORY launch rviz DESTINATION share/${PROJECT_NAME})

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)
  ament_add_pytest_test(
    test_geometry_consistency test/test_geometry_consistency.py
    TIMEOUT 90
    ENV "SWEEPER_SOURCE_ROOT=${CMAKE_CURRENT_SOURCE_DIR}/..")
  ament_add_pytest_test(
    test_cleaning_rviz test/test_cleaning_rviz.py
    TIMEOUT 30
    ENV "SWEEPER_SOURCE_ROOT=${CMAKE_CURRENT_SOURCE_DIR}/..")
endif()

ament_package()
