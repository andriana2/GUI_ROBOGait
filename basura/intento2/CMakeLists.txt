cmake_minimum_required(VERSION 3.16)

project(gui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON) # Para enlazar imágenes y recursos

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick)

set_source_files_properties(qml/Constants.qml PROPERTIES
    QT_QML_SINGLETON_TYPE TRUE
)

qt_add_executable(appgui
    src/main.cpp
    src/StringHandler.cpp
    src/utils.cpp

    include/StringHandler.h
    include/utils.h
)

qt_add_qml_module(appgui
    URI gui
    VERSION 1.0

QML_FILES
    qml/Constants.qml
    qml/main.qml
    qml/ApplicationFlow.qml
    qml/ApplicationFlowForm.ui.qml
    qml/Home.qml
    qml/HomeForm.ui.qml
    qml/Ip.qml
    qml/IpForm.ui.qml

    qml/MenuForm.ui.qml
    qml/Teledirigido.qml
    qml/TeledirigidoForm.ui.qml



RESOURCES
    images/logo.png
    images/x.png
    images/down.png
    images/giro_der.png
    images/giro_izq.png
    images/up.png
    QML_FILES qml/MenuPrincipal.qml

)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appgui PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appgui
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appgui
    PRIVATE     Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appgui
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
