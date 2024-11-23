import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: root
    property alias home: home
    // property alias ip: ip
    // property alias menu: menu

    property string previousState: ""
    property alias mystackview: mystackview

    StackView {
        anchors.fill: parent
        id: mystackview
        initialItem: Home {
            id: home
        }
    }
    // Component {
    //     id: ip
    //     IP {
    //         visible: true
    //     }
    // }
    // Component {
    //     id: menu
    //     MenuForm {
    //         visible: true
    //     }
    // }
}
