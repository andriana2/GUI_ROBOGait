import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: rectangle
    color: "#518bb7"
    property alias imageDisplay: imageDisplay
    property alias joystick: joystick

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
        id: teledirigido
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
        anchors.horizontalCenter: teledirigido.horizontalCenter
        anchors.verticalCenter: teledirigido.top
        anchors.horizontalCenterOffset: -text_mapear.minimumPixelSize
        anchors.verticalCenterOffset: -teledirigido.height / 3
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

    // Switch {
    //     id: switchDelegate
    //     width: 50
    //     height: 30
    //     Rectangle {
    //         width: parent.width
    //         height: parent.height
    //         radius: height / 2
    //         color: switchDelegate.checked ? "#4CAF50" : "#B0BEC5"
    //         border.color: "gray"
    //     }
    //     Rectangle {
    //         width: 24
    //         height: 24
    //         radius: width / 2
    //         color: "white"
    //         border.color: "gray"
    //         x: switchDelegate.checked ? parent.width - width - 3 : 3
    //         y: (parent.height - height) / 2
    //     }
    // }

    // Switch {
    //     id: switch1
    //     width: 111
    //     height: 29
    //     text: qsTr("Mapear")
    //     anchors.verticalCenter: mapa.verticalCenter
    //     anchors.verticalCenterOffset: -1 * mapa.width
    //     anchors.horizontalCenterOffset: 0
    //     anchors.horizontalCenter: mapa.horizontalCenter
    // }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:2}D{i:1}D{i:4}D{i:3}D{i:6}D{i:7}D{i:5}
}
##^##*/

