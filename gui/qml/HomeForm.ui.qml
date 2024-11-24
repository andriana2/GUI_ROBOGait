import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: home
    property alias buttonStart: buttonStart

    Rectangle {
        id: rectangle
        color: "#518bb7"
        anchors.fill: parent

        Image {
            id: image
            width: 197
            height: 191
            anchors.verticalCenter: parent.verticalCenter
            source: "../images/logo.png"
            anchors.verticalCenterOffset: -50
            anchors.horizontalCenter: parent.horizontalCenter
            fillMode: Image.PreserveAspectFit
        }

        Button {
            id: buttonStart
            text: qsTr("START")
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 150
            anchors.horizontalCenter: parent.horizontalCenter
            focusPolicy: Qt.StrongFocus
            z: 0
            scale: 4.036
        }
    }
}
