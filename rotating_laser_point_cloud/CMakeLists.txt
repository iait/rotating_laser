cmake_minimum_required(VERSION 2.8.3)
project(rotating_laser_point_cloud)

find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  tf
  sensor_msgs
  laser_geometry
)

catkin_package()

include_directories(${catkin_INCLUDE_DIRS})

add_executable(laser_scan_to_pc src/laser_scan_to_pc.cpp)

target_link_libraries(laser_scan_to_pc ${catkin_LIBRARIES})
