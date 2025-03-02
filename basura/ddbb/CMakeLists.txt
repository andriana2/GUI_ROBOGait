cmake_minimum_required(VERSION 3.16)

project(ddbb VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON) # Para enlazar imágenes y recursos

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Network Concurrent)

qt_add_executable(appddbb
    src/main.cpp
    src/NetworkDDBB.cpp
    src/database.cpp
    src/utils_database.cpp
    #src/StringHandler.cpp
    #src/utils.cpp


    include/NetworkDDBB.h
    include/database.h
    include/utils_database.h
   # include/StringHandler.h
    #include/utils.h

)

qt_add_qml_module(appddbb
    URI ddbb
    VERSION 1.0

    RESOURCES
    images/pen-to-square-regular.svg
    images/check-solid.svg
    images/keyboard_left.svg
    images/saveButton.png
    images/eraser-solid.svg
    images/logo.png
    images/trash-solid.svg
    images/file-arrow-down-solid.svg
    images/my_map.png
    images/pencil-solid.svg
    images/robot_with_arrow.png
    images/map-pin-solid.svg
    images/robot.png
    images/wheel.svg


    QML_FILES
    qml/extras/CustomToolBarForm.ui.qml
    qml/extras/CustomToolBar.qml
    qml/extras/ErrorRectangle.qml

    qml/main.qml
    qml/ApplicationFlow.qml
    qml/ApplicationFlowForm.ui.qml

    qml/LoginForm.ui.qml
    qml/Login.qml
    qml/SingInForm.ui.qml
    qml/SingIn.qml
    qml/GuestForm.ui.qml
    QML_FILES qml/Guest.qml

)

set_target_properties(appddbb PROPERTIES
    #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appddbb
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appddbb
    PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Network
    Qt6::Concurrent
)


include(GNUInstallDirs)
install(TARGETS appddbb
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY qml DESTINATION ${CMAKE_INSTALL_BINDIR})
