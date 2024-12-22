import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: home
    property alias buttonStart: buttonStart

    Rectangle {
        id: rectangle
        color: "#518bb7"
        anchors.top: home.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        // anchors.horizontalCenter: parent.horizontalCenter
        Image {
            id: image
            width: 197
            height: 191
            anchors.verticalCenter: parent.verticalCenter
            source: "../images/logo.png"
            anchors.verticalCenterOffset: -90
            anchors.horizontalCenter: parent.horizontalCenter
            fillMode: Image.PreserveAspectFit
        }

        Button {
            id: buttonStart
            text: qsTr("START")
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 110
            anchors.horizontalCenter: parent.horizontalCenter
            focusPolicy: Qt.StrongFocus
            z: 0
            scale: 4.036
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:2}D{i:3}D{i:1}
}
##^##*/
