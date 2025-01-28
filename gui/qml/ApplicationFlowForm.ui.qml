import QtQuick 2.15
import QtQuick.Controls 2.15
import "extras"

Rectangle {
    id: root
    color: "#518bb7"
    property alias home: home
    property alias ip: ip
    property alias menu_app: menu_app
    property alias teledirigido: teledirigido
    property alias selectMap: selectMap
    property alias mapPath: mapPath

    property string previousState: ""
    property alias mystackview: mystackview
    property alias toolbar: toolbar


    CustomToolBar {
        id: toolbar
        anchors.topMargin: parent.height / 120
        width: parent.width
        height: 20
        anchors.top: parent.top
    }

    StackView {
        id: mystackview
        anchors.top: parent.top
        anchors.bottom: parent.bottom
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
        id: ip
        Ip {
            visible: true
        }
    }
    Component {
        id: menu_app
        MenuPrincipal {
            visible:true
        }
    }
    Component {
        id: teledirigido
        Teledirigido {
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
