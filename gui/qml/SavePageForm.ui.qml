import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: root
    property alias no_save: no_save
    property alias save: save
    property alias cancel: cancel
    property alias text_name: text_name
    property alias text_header: text_header
    color: "white"
    border.color: "#3A64A5"
    border.width: 2
    radius: 20
    width: 540
    height: 210
    Text {
        id: text_header
        //        width: 492
        //        height: 34
        text: qsTr("¿Guardar los cambios en este archivo?")
        anchors.left: parent.left
        anchors.top: parent.top
        font.pixelSize: 30
        font.bold: true
        horizontalAlignment: Text.AlignHCenter
        anchors.topMargin: 18
        anchors.leftMargin: 24
        font.styleName: "Light Italic"
    }

    Text {
        id: text1
        x: 309
        width: 142
        height: 22
        text: qsTr("Nombre del archivo")
        anchors.left: parent.left
        anchors.top: text_header.bottom
        font.pixelSize: 16
        anchors.leftMargin: 36
        anchors.topMargin: 10
    }
    Rectangle {
        id: rectangle1
        border.color: "black"
        color: parent.color
        border.width: 2
        anchors.left: parent.left
        anchors.top: text1.bottom
        anchors.leftMargin: 26
        anchors.topMargin: 20
        radius: 4 // Opcional: Esquinas redondeadas

        // padding: 4 // Opcional: Espacio alrededor del texto
        // Text {
        //     id: text_name
        //     text: qsTr("                       .pgm")
        //     anchors.left: parent.left
        //     anchors.top: parent.top
        //     font.pixelSize: 20
        //     horizontalAlignment: Text.AlignHCenter
        //     verticalAlignment: Text.AlignVCenter
        //     anchors.leftMargin: -232
        //     anchors.topMargin: -46
        //     anchors.verticalCenterOffset: -23
        //     anchors.horizontalCenterOffset: -29
        //     anchors.centerIn: parent
        // }
        TextArea {
            id: text_name
            color: "#454545"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            placeholderText: qsTr("Nombre del mapa")
            font.pixelSize: 20
            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignVCenter
            anchors.leftMargin: 0
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
    D{i:0;height:210}D{i:1}D{i:2}D{i:4}D{i:3}D{i:5}D{i:6}D{i:7}
}
##^##*/

