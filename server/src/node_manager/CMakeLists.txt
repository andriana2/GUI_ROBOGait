cmake_minimum_required(VERSION 3.8)
project(node_manager)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(interface_srv REQUIRED)
find_package(yaml-cpp REQUIRED)

add_executable(node_manager
    main.cpp
    src/servidor.cpp
    src/NodeManager.cpp
    src/utils.cpp
)

ament_target_dependencies(node_manager rclcpp geometry_msgs interface_srv yaml-cpp)

target_compile_features(node_manager PUBLIC cxx_std_17)

install(TARGETS node_manager DESTINATION lib/${PROJECT_NAME})

ament_package()
