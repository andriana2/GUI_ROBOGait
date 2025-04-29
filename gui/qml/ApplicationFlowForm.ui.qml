import QtQuick 2.15
import QtQuick.Controls 2.15
import "extras"

Rectangle {
    id: root
    color: "#518bb7"
    property alias home: home
    property alias robot_connection: robot_connection
    property alias menu_app: menu_app
    property alias menu_doctor: menu_doctor
    property alias register_page: register_page
    property alias register_patient: register_patient
    property alias manualControl: manualControl
    property alias selectMap: selectMap
    property alias select_patient: select_patient
    property alias mapPath: mapPath

    property string previousState: ""
    property alias mystackview: mystackview
    property alias toolbar: toolbar
    property alias bottomBar: bottomBar

    CustomToolBar {
        id: toolbar
        anchors.topMargin: parent.height / 120
        width: parent.width
        height: 20
        anchors.top: parent.top
    }

    CustomBottomBar {
        id: bottomBar
        width: parent.width
        height: 40
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        // anchors.bottomMargin: parent.height / 120
    }

    StackView {
        id: mystackview
        anchors.top: parent.top
        anchors.bottom: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.topMargin: parent.height / 20
        initialItem: Home {
            id: home
        }
        pushEnter: Transition {
            PropertyAnimation {
                property: "x"
                from: mystackview.width
                to: 0
                duration: 400
            }
        }
        //! [mystackview view]
        pushExit: Transition {
            PropertyAnimation {
                property: "x"
                from: 0
                to: -mystackview.width
                duration: 400
            }
        }
        popEnter: Transition {
            PropertyAnimation {
                property: "x"
                from: -mystackview.width
                to: 0
                duration: 400
            }
        }
        popExit: Transition {
            PropertyAnimation {
                property: "x"
                from: 0
                to: mystackview.width
                duration: 400
            }
        }
    }
    Component {
        id: robot_connection
        RobotConnection {
            visible: true
        }
    }
    Component {
        id: menu_doctor
        MenuDoctor {
            visible: true
            // anchors.fill: parent
        }
    }
    Component {
        id: select_patient
        SelectPatient {
            visible: true
        }
    }
    Component {
        id: register_patient
        SigninUser {
            visible: true
        }
    }
    Component {
        id: register_page
        RegisterPage {
            visible: true
            // anchors.fill: parent
        }
    }
    Component {
        id: menu_app
        MainMenu {
            visible: true
        }
    }
    Component {
        id: manualControl
        ManualControl {
            visible_value: applicationFlow.visible_image
            visible: true
            visible_save: applicationFlow.visible_save
            type_save: applicationFlow.type_save
        }
    }
    Component {
        id: selectMap
        SelectMap {
            visible: true
        }
    }
    Component {
        id: mapPath
        MapPage {
            visible: true
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:1}D{i:2}D{i:3}D{i:13}D{i:15}D{i:17}D{i:19}
D{i:21}D{i:23}D{i:25}D{i:27}D{i:29}
}
##^##*/

