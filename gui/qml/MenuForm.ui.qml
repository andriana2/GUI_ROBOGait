import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "extras"

Rectangle {
    id: rectangle
    color: "#518bb7"
    property alias hacer_mapa_mouse_area: hacer_mapa_mouse_area
    property alias mapa_mouse_area: mapa_mouse_area
    property alias teledirigido_mouse_area: teledirigido_mouse_area

    Flow {
        anchors.verticalCenterOffset: -39
        anchors.centerIn: parent // Centra el GridLayout en el contenedor
        spacing: 60 // Espacio entre filas

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
                font.pixelSize: 24
                anchors.horizontalCenter: parent.horizontalCenter
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
                font.pixelSize: 24
                anchors.horizontalCenter: parent.horizontalCenter
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
                font.pixelSize: 24
                anchors.horizontalCenter: parent.horizontalCenter
            }
            MouseArea {
                id: hacer_mapa_mouse_area
                anchors.fill: parent
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:3}D{i:4}D{i:2}D{i:6}D{i:7}D{i:5}D{i:9}
D{i:10}D{i:8}D{i:1}
}
##^##*/

