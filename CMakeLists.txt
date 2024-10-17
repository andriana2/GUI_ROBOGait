cmake_minimum_required(VERSION 3.14)

project(example2 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON) # esto sirve para las imagenes y que sea mas sencillo linkearlas

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Quick)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Quick)
find_package(rclcpp REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(std_msgs REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(geometry_msgs REQUIRED)

add_executable(example2
  main.cpp
  rosnode.h
  rosnode.cpp
  main.qml
  qml.qrc
)


target_link_libraries(example2
                Qt${QT_VERSION_MAJOR}::Quick
)

ament_target_dependencies(example2 rclcpp std_msgs
                        example_interfaces geometry_msgs )

include(GNUInstallDirs)
install(TARGETS example2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
ament_package()
