import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: rectangle
    color: "#518bb7"

    GridLayout {
        anchors.centerIn: parent // Centra el GridLayout en el contenedor
        columns: 3 // Número de columnas en la cuadrícula
        rowSpacing: 60 // Espacio entre filas
        columnSpacing: 60 // Espacio entre columnas

        Rectangle {
            id: rectangle1
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
        }

        Rectangle {
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
        }

        Rectangle {
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
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.66;height:480;width:640}D{i:3}D{i:2}D{i:5}D{i:4}
D{i:7}D{i:6}D{i:1}
}
##^##*/

