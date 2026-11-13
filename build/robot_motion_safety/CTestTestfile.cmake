# CMake generated Testfile for 
# Source directory: /home/xbs/ros2_sweeper_resume_project/ros2_ws/src/robot_motion_safety
# Build directory: /home/xbs/ros2_sweeper_resume_project/build/robot_motion_safety
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(safety_test "/usr/bin/python3" "-u" "/opt/ros/jazzy/share/ament_cmake_test/cmake/run_test.py" "/home/xbs/ros2_sweeper_resume_project/build/robot_motion_safety/test_results/robot_motion_safety/safety_test.gtest.xml" "--package-name" "robot_motion_safety" "--output-file" "/home/xbs/ros2_sweeper_resume_project/build/robot_motion_safety/ament_cmake_gtest/safety_test.txt" "--command" "/home/xbs/ros2_sweeper_resume_project/build/robot_motion_safety/safety_test" "--gtest_output=xml:/home/xbs/ros2_sweeper_resume_project/build/robot_motion_safety/test_results/robot_motion_safety/safety_test.gtest.xml")
set_tests_properties(safety_test PROPERTIES  LABELS "gtest" REQUIRED_FILES "/home/xbs/ros2_sweeper_resume_project/build/robot_motion_safety/safety_test" TIMEOUT "60" WORKING_DIRECTORY "/home/xbs/ros2_sweeper_resume_project/build/robot_motion_safety" _BACKTRACE_TRIPLES "/opt/ros/jazzy/share/ament_cmake_test/cmake/ament_add_test.cmake;125;add_test;/opt/ros/jazzy/share/ament_cmake_gtest/cmake/ament_add_gtest_test.cmake;95;ament_add_test;/opt/ros/jazzy/share/ament_cmake_gtest/cmake/ament_add_gtest.cmake;93;ament_add_gtest_test;/home/xbs/ros2_sweeper_resume_project/ros2_ws/src/robot_motion_safety/CMakeLists.txt;16;ament_add_gtest;/home/xbs/ros2_sweeper_resume_project/ros2_ws/src/robot_motion_safety/CMakeLists.txt;0;")
subdirs("gtest")
