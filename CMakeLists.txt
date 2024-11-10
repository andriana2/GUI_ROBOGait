cmake_minimum_required(VERSION 3.14)

project(example2 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON) # Para enlazar imágenes y recursos

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Quick Core Gui Qml)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Quick Core Gui Qml)
find_package(rclcpp REQUIRED)
find_package(ament_cmake REQUIRED)
find_package(std_msgs REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(geometry_msgs REQUIRED)

# Define el archivo de recursos de Qt (qml.qrc) con todos los archivos QML
qt_add_resources(QML_RESOURCES qml.qrc)

# Configura el ejecutable
add_executable(example2
  main.cpp
  lib/rosnode.h
  src/rosnode.cpp
  src/utils.cpp
  lib/utils.h
 ${QML_RESOURCES}
)

set_source_files_properties(Colors.qml PROPERTIES
    QT_QML_SINGLETON_TYPE TRUE
)

# Vincula las bibliotecas necesarias
target_link_libraries(example2
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Qml
)

# Define las dependencias de ament para ROS2
ament_target_dependencies(example2
    rclcpp
    std_msgs
    example_interfaces
    geometry_msgs
)

# Configuración de instalación
include(GNUInstallDirs)
install(TARGETS example2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Define el paquete ament
ament_package()

