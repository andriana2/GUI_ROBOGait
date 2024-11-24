import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: rectangle
    color: "#518bb7"
    border.color: "#ffffff"
    property alias hacer_mapa_mouse_area: hacer_mapa_mouse_area
    property alias mapa_mouse_area: mapa_mouse_area
    property alias teledirigido_mouse_area: teledirigido_mouse_area

    GridLayout {
        anchors.centerIn: parent // Centra el GridLayout en el contenedor
        columns: 3 // Número de columnas en la cuadrícula
        rowSpacing: 60 // Espacio entre filas
        columnSpacing: 60 // Espacio entre columnas

        Rectangle {
            id: teledirigido_button
            width: 150
            height: 150
            color: "#235c87"
            Text {
                id: text1
                color: "#ffffff"
                text: qsTr("TELEDIRIGIDO")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 12
                anchors.horizontalCenter: parent.horizontalCenter
                scale: 2
            }
            MouseArea {
                id: teledirigido_mouse_area
                anchors.fill: parent
            }
        }

        Rectangle {
            id: mapa
            width: 150
            height: 150
            color: "#235c87"
            Text {
                id: text2
                x: -174
                y: 68
                color: "#ffffff"
                text: qsTr("MAPA")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 12
                anchors.horizontalCenter: parent.horizontalCenter
                scale: 2
            }
            MouseArea {
                id: mapa_mouse_area
                anchors.fill: parent
            }
        }

        Rectangle {
            id: hacer_mapa
            width: 150
            height: 150
            color: "#235c87"
            Text {
                id: text3
                x: -174
                y: 68
                color: "#ffffff"
                text: qsTr("HACER MAPA")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 12
                anchors.horizontalCenter: parent.horizontalCenter
                scale: 2
            }
            MouseArea {
                id: hacer_mapa_mouse_area
                anchors.fill: parent
            }
        }
     }
}
