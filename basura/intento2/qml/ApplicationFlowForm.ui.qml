import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: root
    property alias home: home
    property alias ip: ip
    property alias menu_app: menu_app
    property alias manualControl: manualControl

    property string previousState: ""
    property alias mystackview: mystackview

    StackView {
        anchors.fill: parent
        id: mystackview
        initialItem: Home {
            id: home
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
        MainMenu {
            visible:true
        }
    }
    Component {
        id: manualControl
        ManualControl {
            visible: true
        }
    }
}
