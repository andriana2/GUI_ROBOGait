import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: rectangle
    Text {
        id: text_header
        width: 492
        height: 34
        text: qsTr("¿Guardar los cambios en este archivo?")
        anchors.verticalCenter: parent.verticalCenter
        font.pixelSize: 30
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        anchors.verticalCenterOffset: -100
        anchors.horizontalCenterOffset: 0
        anchors.horizontalCenter: parent.horizontalCenter
        font.styleName: "Light Italic"
    }

    Text {
        id: text1
        x: 309
        text: qsTr("Nombre del archivo")
        anchors.verticalCenter: parent.verticalCenter
        anchors.top: text_header.bottom
        font.pixelSize: 16
        anchors.topMargin: 10
        anchors.verticalCenterOffset: -68
        anchors.horizontalCenterOffset: -161
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Rectangle {
        id: rectangle1
        anchors.centerIn: parent
        border.color: "black"
        color: parent.color
        border.width: 2
        anchors.left: parent.left
        anchors.top: text1.bottom
        anchors.leftMargin: 270
        anchors.topMargin: 20
        radius: 4 // Opcional: Esquinas redondeadas
        padding: 4 // Opcional: Espacio alrededor del texto

        Text {
            id: text_name
            text: qsTr("                                  .pgm")
            anchors.left: parent.left
            anchors.top: parent.top
            font.pixelSize: 20
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            anchors.leftMargin: -232
            anchors.topMargin: -46
            anchors.verticalCenterOffset: -23
            anchors.horizontalCenterOffset: -29
            anchors.centerIn: parent
        }
    }

    Button {
        id: cancel
        text: qsTr("Cancelar")
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 28
        anchors.bottomMargin: 28
    }

    Button {
        id: no_save
        x: 344
        y: 207
        text: qsTr("No Guardar")
        anchors.right: cancel.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 28
        anchors.rightMargin: 10
    }

    Button {
        id: save
        x: 251
        y: 207
        text: qsTr("Guardar")
        anchors.right: no_save.left
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 28
        anchors.rightMargin: 10
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:260;width:540}D{i:1}D{i:2}D{i:4}D{i:3}D{i:5}D{i:6}D{i:7}
}
##^##*/

