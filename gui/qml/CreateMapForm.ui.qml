import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "extras"

Rectangle {
    id: rectangle
    color: "#518bb7"
    property alias imageDisplay: imageDisplay
    property alias joystick: joystick
    property alias switchRow: switchRow
    property alias customSwitch: customSwitch

    property alias save_page: save_page
    property bool save_page_visible: save_page_visible

    Rectangle {
        id: mapa
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
        id: manualControl
        width: Math.min(275, Math.max(175, parent.width / 4))
        height: width
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenterOffset: mapa.width / 2
        anchors.horizontalCenter: parent.horizontalCenter

        Joystick {
            id: joystick
            width: parent.width
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    Row {
        id: switchRow
        anchors.horizontalCenter: manualControl.horizontalCenter
        anchors.verticalCenter: manualControl.top
        anchors.horizontalCenterOffset: -text_mapear.minimumPixelSize
        anchors.verticalCenterOffset: -manualControl.height / 3
        spacing: 10

        // Texto a la izquierda
        Text {
            id: text_mapear
            text: qsTr("Mapear")
            anchors.verticalCenter: parent.verticalCenter
            color: "white"
            font.pixelSize: 16
            verticalAlignment: Text.AlignVCenter
        }

        // Switch redondo personalizado
        Rectangle {
            id: customSwitch
            width: 50
            height: 30
            radius: height / 2
            color: checked ? "#D02833" : "#B0BEC5"
            border.color: "gray"

            // Declaramos la propiedad `checked`
            property bool checked: false

            // Círculo que se mueve
            Rectangle {
                id: handle
                width: 24
                height: 24
                radius: width / 2
                color: "white"
                border.color: "gray"
                anchors.verticalCenter: parent.verticalCenter
                x: customSwitch.checked ? parent.width - width - 3 : 3

                // Animación suave
                Behavior on x {
                    NumberAnimation {
                        duration: 200
                        easing.type: Easing.InOutQuad
                    }
                }
            }

            // Área de interacción
            MouseArea {
                anchors.fill: parent
                onClicked: customSwitch.checked = !customSwitch.checked
            }
        }
    }
    SavePage {
        id: save_page
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -60
        anchors.horizontalCenter: parent.horizontalCenter
        // state_save_page: state_save_page
    }
}
