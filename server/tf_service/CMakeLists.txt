cmake_minimum_required(VERSION 3.8)
project(tf_service)

# if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
#   add_compile_options(-Wall -Wextra -Wpedantic)
# endif()

# Buscar las dependencias necesarias
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)

# Crear el ejecutable
add_executable(tf_service_node
    main.cpp
)

# Especificar las dependencias de tu nodo
ament_target_dependencies(tf_service_node rclcpp geometry_msgs std_msgs)

# Generar las interfaces de servicio (incluir todas las dependencias necesarias)
rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/GetRobotPosition.srv"
  DEPENDENCIES std_msgs geometry_msgs  # Añadir geometry_msgs si es necesario
)

# Instalar el ejecutable
install(TARGETS tf_service_node DESTINATION lib/${PROJECT_NAME})

# Instalar los archivos generados de las interfaces de servicio
install(DIRECTORY
  ${CMAKE_CURRENT_BINARY_DIR}/share/${PROJECT_NAME}/srv
  DESTINATION share/${PROJECT_NAME}/srv
)

ament_package()

