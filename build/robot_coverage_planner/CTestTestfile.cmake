# CMake generated Testfile for 
# Source directory: /home/xbs/ros2_sweeper_resume_project/ros2_ws/src/robot_coverage_planner
# Build directory: /home/xbs/ros2_sweeper_resume_project/build/robot_coverage_planner
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(coverage_test "/usr/bin/python3" "-u" "/opt/ros/jazzy/share/ament_cmake_test/cmake/run_test.py" "/home/xbs/ros2_sweeper_resume_project/build/robot_coverage_planner/test_results/robot_coverage_planner/coverage_test.gtest.xml" "--package-name" "robot_coverage_planner" "--output-file" "/home/xbs/ros2_sweeper_resume_project/build/robot_coverage_planner/ament_cmake_gtest/coverage_test.txt" "--command" "/home/xbs/ros2_sweeper_resume_project/build/robot_coverage_planner/coverage_test" "--gtest_output=xml:/home/xbs/ros2_sweeper_resume_project/build/robot_coverage_planner/test_results/robot_coverage_planner/coverage_test.gtest.xml")
set_tests_properties(coverage_test PROPERTIES  LABELS "gtest" REQUIRED_FILES "/home/xbs/ros2_sweeper_resume_project/build/robot_coverage_planner/coverage_test" TIMEOUT "60" WORKING_DIRECTORY "/home/xbs/ros2_sweeper_resume_project/build/robot_coverage_planner" _BACKTRACE_TRIPLES "/opt/ros/jazzy/share/ament_cmake_test/cmake/ament_add_test.cmake;125;add_test;/opt/ros/jazzy/share/ament_cmake_gtest/cmake/ament_add_gtest_test.cmake;95;ament_add_test;/opt/ros/jazzy/share/ament_cmake_gtest/cmake/ament_add_gtest.cmake;93;ament_add_gtest_test;/home/xbs/ros2_sweeper_resume_project/ros2_ws/src/robot_coverage_planner/CMakeLists.txt;37;ament_add_gtest;/home/xbs/ros2_sweeper_resume_project/ros2_ws/src/robot_coverage_planner/CMakeLists.txt;0;")
subdirs("gtest")
