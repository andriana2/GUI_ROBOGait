cmake_minimum_required(VERSION 3.16)

project(gui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON) # Para enlazar imágenes y recursos

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Network)
# find_package(OpenCV REQUIRED)

set(qml_singletons
    qml/extras/ConstantVariables.qml
)

# set_source_files_properties(${qml_singletons}
#     PROPERTIES QT_QML_SINGLETON_TYPE TRUE)

qt_add_executable(appgui
    src/main.cpp
    src/StringHandler.cpp
    src/utils.cpp
    src/cliente.cpp
    src/ToJson.cpp
    src/MapInfo.cpp


    include/StringHandler.h
    include/utils.h
    include/cliente.h
    include/ToJson.h
    include/MapInfo.h

)

qt_add_qml_module(appgui
    URI gui
    VERSION 1.0

    QML_FILES
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
    qml/MenuPrincipal.qml
    qml/MapPage.qml
    qml/MapPageForm.ui.qml
    qml/SelectMap.qml
    qml/SelectMapForm.ui.qml
    qml/MenuDoctor.ui.qml
    qml/SelectPatient.ui.qml
    qml/Menu.qml
    qml/RegisterPage.qml

    qml/extras/CustomToolBarForm.ui.qml
    qml/extras/CustomToolBar.qml
    qml/extras/Joystick.qml
    qml/extras/JoystickForm.ui.qml
    qml/extras/Map.qml
    qml/extras/MapForm.ui.qml
    qml/extras/SavePage.qml
    qml/extras/SavePageForm.ui.qml
    qml/extras/OrientationCircle.qml
    qml/extras/OrientationCircleForm.ui.qml
    qml/extras/ErrorRectangle.qml
    qml/extras/BoxImages.qml
    qml/extras/BoxImagesForm.ui.qml
    qml/extras/Guest.qml
    qml/extras/GuestForm.ui.qml
    qml/extras/Login.qml
    qml/extras/LoginForm.ui.qml
    qml/extras/SignIn.qml
    qml/extras/SignInForm.ui.qml

    ${qml_singletons}


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

    # qml/extras/qmldir

    # images/android_icons/mipmap-mdpi/logo48.png
    # images/android_icons/mipmap-hdpi/logo72.png
    # images/android_icons/mipmap-xhdpi/logo96.png
    # images/android_icons/mipmap-xxhdpi/logo144.png
    # images/android_icons/mipmap-xxxhdpi/logo192.png


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
    Qt6::Network
    ${OpenCV_LIBS}
)

# if (ANDROID)
#     # Define las rutas de los íconos
#     set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android_icons")

#     # Especifica el ícono de la aplicación
#     set(ANDROID_APK_ICON "@mipmap/ic_launcher")

#     # Incluye recursos adicionales
#     qt_add_android_apk(android_apk_target
#         PACKAGE_SOURCE_DIR ${ANDROID_PACKAGE_SOURCE_DIR}
#     )
# endif()

include(GNUInstallDirs)
install(TARGETS appgui
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(DIRECTORY qml DESTINATION ${CMAKE_INSTALL_BINDIR})
