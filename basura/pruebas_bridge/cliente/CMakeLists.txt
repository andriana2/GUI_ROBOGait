cmake_minimum_required(VERSION 3.16)

project(app_con_socket VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Network)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

find_package(Qt6 REQUIRED COMPONENTS Core)

qt_add_executable(appapp_con_socket
    main.cpp
)

qt_add_qml_module(appapp_con_socket
    URI app_con_socket
    VERSION 1.0
    QML_FILES main.qml
    SOURCES Connection2Client.h Connection2Client.cpp
    image_client.cpp ImageClient.h
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appapp_con_socket PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appapp_con_socket
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appapp_con_socket
    PRIVATE Qt6::Quick
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
)

include(GNUInstallDirs)
install(TARGETS appapp_con_socket
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
