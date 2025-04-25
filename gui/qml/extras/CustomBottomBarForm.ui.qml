import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 6.0

Item {
    id: root

    property alias textoMapaTitulo: mapaTitulo.text
    property alias textoMapaValor: mapaValor.text
    property alias colorMapaValor: mapaValor.color

    property alias textoPacienteTitulo: pacienteTitulo.text
    property alias textoPacienteValor: pacienteValor.text
    property alias colorPacienteValor: pacienteValor.color

    property alias batteryPercentage: battery.percentage
    property alias batteryItem: batteryItem
    property alias customBottomBarItem: customBottomBarItem


    Rectangle {
        id: customBottomBarItem
        width: parent.width
        height: 40
        color: "#518bb7"
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter

        // Contenedor de textos y batería
        Item {
            id: content
            anchors.fill: parent
            anchors.centerIn: parent
            anchors.leftMargin: 20
            anchors.rightMargin: 80

            // Contenedor de textos
            Row {
                anchors.centerIn: parent
                spacing: 10

                Text {
                    id: mapaTitulo
                    text: "HAY MAPA ACTIVO:"
                    font.pixelSize: 17
                    font.bold: true
                    color: "#ffffff"
                }

                Text {
                    id: mapaValor
                    text: "MAPA1"
                    font.pixelSize: 17
                    font.bold: true
                    color: "#cce54d"
                }

                Text {
                    text: "–"
                    font.pixelSize: 17
                    color: "white"
                }

                Text {
                    id: pacienteTitulo
                    text: "HAY PACIENTE ACTIVO:"
                    font.pixelSize: 17
                    font.bold: true
                    color: "#ffffff"
                }

                Text {
                    id: pacienteValor
                    text: "PACIENTE1"
                    font.pixelSize: 17
                    font.bold: true
                    color: "#cce54d"
                }
            }
        }

        // Battery widget a la derecha
        Item {
            id: batteryItem
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 5
            anchors.rightMargin: 5

            // Porcentaje de batería
            Text {
                text: battery.percentage + "%"
                font.pixelSize: 15
                color: "white"
                anchors.right: battery.left
                anchors.rightMargin: 5
                anchors.verticalCenter: battery.verticalCenter
            }

            // Battery widget a la derecha
            Battery {
                id: battery
                width: 30
                height: 15
                percentage: 27
                anchors.right: parent.right
                anchors.bottom: parent.bottom
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorColor:"#808080"}D{i:4}D{i:5}D{i:6}D{i:7}D{i:8}D{i:3}
D{i:2}D{i:9}D{i:1}
}
##^##*/

