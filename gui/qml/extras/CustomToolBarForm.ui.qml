import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 6.0

Item {
    id: root
    property alias backButton: backButton
    // property alias saveButton: saveButton
    property alias logo: logo
    property alias title: title
    property alias config: config
    property alias username: username

    Rectangle {
        // x: 0
        // y: 0
        // width: parent.width
        anchors.fill: parent
        color: "transparent"

        // Botón de regreso (Flecha)
        Button {
            id: backButton
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            icon.source: "../../images/icon_app/keyboard_left.svg"
            icon.color: "white"
            icon.width: 24
            icon.height: 24
            background: null
            transitions: Transition {
                NumberAnimation {
                    properties: "scale"
                    duration: 100
                    easing.type: Easing.InOutQuad
                }
            }
        }

        // Boton de guardar
        // Button {
        //     id: saveButton
        //     anchors.left: backButton.right
        //     anchors.verticalCenter: parent.verticalCenter
        //     icon.source: "../../images/icon_app/saveButton.png"
        //     icon.width: 24
        //     icon.height: 24
        //     icon.color: "white"
        //     background: null
        //     transitions: Transition {
        //         NumberAnimation {
        //             properties: "scale"
        //             duration: 100
        //             easing.type: Easing.InOutQuad
        //         }
        //     }
        // }

        Text {
            id: username
            text: ddbb.username
            anchors.right: config.left
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 17
            color: "white"
            font.bold: true
            anchors.margins: 5
            anchors.topMargin: 5
        }

        ConfigurationMenu {
            id: config
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            width: 30
            height: 30
            anchors.margins: 5
            anchors.topMargin: 5
        }

        // Logo y Título
        Row {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenterOffset: -5
            spacing: 10

            Image {
                id: logo
                source: "../../images/logo.png"
                sourceSize.height: 25
                sourceSize.width: height * 1.4
            }

            Text {
                id: title
                text: "ROBOGAIT"
                font.pixelSize: 20
                color: "white"
                font.bold: true
            }
        }
    }
}


/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:1.1;height:480;width:640}D{i:2}D{i:5}D{i:8}D{i:1}
}
##^##*/

