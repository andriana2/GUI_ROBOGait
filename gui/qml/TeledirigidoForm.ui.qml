import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: rectangle
    color: "#518bb7"
    property alias imageDisplay: imageDisplay
    property alias joystick: joystick

    Rectangle {
        width: 150
        height: 60
        radius: 30
        color: isToggled ? "#4CAF50" : "#B0BEC5"

        property bool isToggled: false

        Rectangle {
            width: 60
            height: 60
            radius: 30
            color: "white"
            anchors.verticalCenter: parent.verticalCenter
            x: parent.isToggled ? parent.width - width : 0

            //            Behavior on x {
            //                NumberAnimation { duration: 200 }
            //            }
        }

        MouseArea {
            anchors.fill: parent
            onClicked: parent.isToggled = !parent.isToggled
        }
    }

    Rectangle {
        id: teledirigido
        width: 2 * parent.width / 3
        height: parent.height
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.left: parent.left
        color: "#518bb7"

        Image {
            id: imageDisplay
            width: Math.min(parent.width,
                            parent.height * imageDisplay.sourceSize.width
                            / imageDisplay.sourceSize.height)
            height: Math.min(parent.height,
                             parent.width * imageDisplay.sourceSize.height
                             / imageDisplay.sourceSize.width)
            anchors.centerIn: parent
            visible: stringHandler.imageSource !== "" // Solo visible si hay una fuente válida
            fillMode: Image.PreserveAspectCrop
            source: stringHandler.imageSource // Vinculación directa al valor de stringHandler.imageSource
        }
    }

    Item {
        id: mapa
        width: 250
        height: 250
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenterOffset: teledirigido.width / 2
        anchors.horizontalCenter: parent.horizontalCenter

        Joystick {
            id: joystick
            width: parent.width
            height: 250
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:2}D{i:3}D{i:1}D{i:5}D{i:4}D{i:7}D{i:6}
}
##^##*/

