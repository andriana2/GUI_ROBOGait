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
            text: qsTr("Introduce la IP ")
            anchors.verticalCenter: parent.verticalCenter
            font.pixelSize: 12
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenterOffset: -70
            anchors.horizontalCenter: parent.horizontalCenter
            scale: 3.347
        }

        Button {
            id: buttonEnviar
            text: qsTr("Enviar")
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 30
            anchors.horizontalCenter: parent.horizontalCenter
        }

        TextArea {
            id: textArea
            anchors.verticalCenter: parent.verticalCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.verticalCenterOffset: -20
            anchors.horizontalCenter: parent.horizontalCenter
            placeholderText: qsTr("Escribe la IP aquí")
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:2}D{i:3}D{i:4}D{i:1}
}
##^##*/
