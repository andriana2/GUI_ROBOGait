import QtQuick 2.15
import QtQuick.Controls 2.15
import "extras"

Item {
    id: root
    property alias textArea: textArea
    property alias buttonEnviar: buttonEnviar

    Rectangle {
        id: rectangle
        color: "#518bb7"
        anchors.fill: parent

        Text {
            id: text1
            color: "#000000"
            text: qsTr("Introduce la IP ")
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 40

            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenterOffset: -110
            anchors.horizontalCenter: parent.horizontalCenter
        }

        Button {
            id: buttonEnviar
            width: 81
            height: 40
            text: qsTr("Enviar")
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -15
            anchors.horizontalCenter: parent.horizontalCenter

            background: Rectangle {
                color: "#ffffff" // Color inicial
                radius: 6
                border.color: "#045671" // Borde del mismo color que el texto
                border.width: 2
            }

            contentItem: Label {
                text: parent.text
                color: "#454545"
                font.pixelSize: 15
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }
        }

        TextArea {
            id: textArea
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            font.pointSize: 15
            anchors.verticalCenterOffset: -60
            anchors.horizontalCenter: parent.horizontalCenter
            placeholderText: qsTr("Dirección IP")
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:2}D{i:3}D{i:6}D{i:1}
}
##^##*/

