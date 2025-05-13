import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "extras"

Rectangle {
    id: rectangle
    color: "#518bb7"
    property alias joystick: joystick
    property real linear_value
    property real angular_value

    Rectangle {
        id: information
        width: 2 * parent.width / 3 - 40
        color: "#518bb7"
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: 30
        anchors.bottomMargin: 30
        anchors.topMargin: 30
        Image {
            id: svgImage
            source: "../images/logo.png"
            anchors.topMargin: 20
            anchors.horizontalCenter: parent.horizontalCenter
            width: 240
            height: 240
            anchors.top: parent.top
            fillMode: Image.PreserveAspectFit
        }

        Column {
            width: information.width - 40
            anchors.top: svgImage.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 0
            spacing: 20

            // Título 1
            Text {
                text: qsTr("Movimiento del joystick")
                color: "#00C8FF"
                font.pixelSize: 26
                styleColor: "#e9e9e9"
                font.bold: true
            }

            Text {
                id: step1Text
                width: parent.width
                color: "#ffffff"
                font.pixelSize: 21
                wrapMode: Text.WordWrap
                text: qsTr("Desplace el círculo pequeño para comenzar a moverse. La velocidad de movimiento aumentará cuanto más se aleje del centro. Para más detalles presione el botón de información.")
            }

            // Título 2
            Text {
                text: qsTr("¡¡ADVERTENCIA!!")
                color: "#c52020"
                font.pixelSize: 26
                font.bold: true
            }

            Text {
                id: step2Text
                width: parent.width
                color: "#ffffff"
                font.pixelSize: 21
                wrapMode: Text.WordWrap
                text: qsTr("Este robot no cuenta con un sistema de gestión de colisiones. Asegúrese de evitar obstáculos y supervisar su desplazamiento en todo momento.")
            }
        }
    }

    Item {
        id: manualControl
        width: Math.min(275, Math.max(175, parent.width / 4))
        height: width
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenterOffset: information.width / 2
        anchors.horizontalCenter: parent.horizontalCenter

        Joystick {
            id: joystick
            width: parent.width
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
    Button {
        id: infoButton
        width: 33
        height: 33
        anchors.left: information.right
        anchors.bottom: information.bottom
        background: Image {
            source: "../images/icon_app/circle-info-solid.svg"
            fillMode: Image.PreserveAspectFit
        }
        Behavior on scale {
            NumberAnimation {
                duration: 150
                easing.type: Easing.OutQuad
            }
        }

        onPressed: scale = 1.2
        onReleased: scale = 1.0
    }

    Text {
        id: text1
        x: 1018
        y: 174
        width: 182
        height: 32
        color: "#ffffff"

        text: qsTr("%1 m/s  %2 rad/s").arg(linear_value.toFixed(3)).arg(
                  angular_value.toFixed(3))
        anchors.right: manualControl.right
        anchors.bottom: manualControl.top
        font.pixelSize: 20
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
    }
}



