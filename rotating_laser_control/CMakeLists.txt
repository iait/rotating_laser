cmake_minimum_required(VERSION 2.8.3)
project(rotating_laser_control)

## Package
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  controller_manager
  joint_state_controller
  robot_state_publisher
)

catkin_package()

## Build

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(rotating_laser_control src/rotating_laser_control.cpp)
target_link_libraries(rotating_laser_control ${catkin_LIBRARIES})
