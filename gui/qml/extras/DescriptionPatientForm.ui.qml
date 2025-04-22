import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    color: "#e9e9e9"
    radius: 15
    border.color: "#235c87"
    border.width: 2

    Column {
        anchors.fill: parent
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 5
        spacing: 10

        Text {
            text: qsTr("Doctor: Luis martin")
            font.pixelSize: 16
        }
        Text {
            text: qsTr("Fecha de creación: 2025-04-22 20:11:01")
            wrapMode: Text.Wrap
            width: parent.width - 40
            font.pixelSize: 16
        }
        Text {
            text: qsTr("Nombre completo: Luis Perez")
            font.pixelSize: 16
        }
        Text {
            text: qsTr("Edad: 56 años")
            font.pixelSize: 16
        }
        Text {
            text: qsTr("Peso: 98 Kg")
            font.pixelSize: 16
        }
        Text {
            text: qsTr("Altura: 178 cm")
            font.pixelSize: 16
        }
        Text {
            text: qsTr("Descripción: Se trata de un paciente con un problema en ...")
            font.pixelSize: 16
            wrapMode: Text.Wrap
            width: parent.width - 40
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:500;width:200}D{i:2}D{i:3}D{i:4}D{i:5}D{i:6}D{i:7}D{i:8}
D{i:1}
}
##^##*/

