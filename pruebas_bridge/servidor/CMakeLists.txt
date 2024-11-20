cmake_minimum_required(VERSION 3.16)

project(socket2 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Network)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

find_package(Qt6 REQUIRED COMPONENTS Core)

add_executable(cliente

    ImageClient.h image_client.cpp
    cliente.cpp

)
target_link_libraries(cliente
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
)


add_executable(servidor

    ImageServer.h image_server.cpp
    servidor.cpp
)
target_link_libraries(servidor
    Qt6::Core
    Qt6::Network
    Qt6::Widgets
)

include(GNUInstallDirs)
install(TARGETS cliente
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(TARGETS servidor
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
