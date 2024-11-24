cmake_minimum_required(VERSION 3.8)
project(turtlesim_controller)

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(turtlesim_controller
    main.cpp
    src/servidor.cpp
    src/controlador_turtle.cpp
)

ament_target_dependencies(turtlesim_controller rclcpp geometry_msgs)

target_compile_features(turtlesim_controller PUBLIC cxx_std_17)

install(TARGETS turtlesim_controller DESTINATION lib/${PROJECT_NAME})

ament_package()
