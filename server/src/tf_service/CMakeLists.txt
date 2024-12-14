cmake_minimum_required(VERSION 3.8)
project(tf_service)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(interface_srv REQUIRED)


add_executable(tf_service_node src/tf_service.cpp)
ament_target_dependencies(tf_service_node rclcpp tf2_ros geometry_msgs tf2_geometry_msgs interface_srv)
target_link_libraries(tf_service_node ${cpp_typesupport_target})


install(TARGETS
  tf_service_node
  DESTINATION lib/${PROJECT_NAME})

ament_package()

