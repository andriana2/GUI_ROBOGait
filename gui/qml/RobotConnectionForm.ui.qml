import QtQuick 2.15
import QtQuick.Controls 2.15
import "extras"

Item {
    id: root
    property alias buttonSearchRobot: buttonSearchRobot
    property alias background: background
    Rectangle {
        id: background
        color: "#518bb7"
        anchors.fill: parent

        // Título
        Text {
            id: titleText
            color: "#ffffff"
            text: qsTr("CONEXIÓN AL ROBOT")
            font.pixelSize: 32
            font.styleName: "Medium"
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: parent.height < 600 ? 10 : 20
        }

        // Texto principal con scroll
        ScrollView {
            id: scrollView
            width: Math.min(900, parent.width * 0.90)
            height: parent.height * 0.6
            anchors.top: titleText.bottom
            anchors.topMargin: parent.height < 600 ? 20 : 40
            anchors.horizontalCenter: parent.horizontalCenter
            clip: true

            Column {
                width: scrollView.width
                spacing: 20

                // Título 1
                Text {
                    text: qsTr("1º ENCENDER EL ORDENADOR DEL ROBOT MÓVIL")
                    color: "#00C8FF"
                    font.pixelSize: 20
                    font.bold: true
                }

                Text {
                    id: step1Text
                    width: scrollView.width
                    color: "#ffffff"
                    font.pixelSize: 17
                    wrapMode: Text.WordWrap
                    text: qsTr("Para encenderlo, sigue estos pasos:\n\n    1.  Conecta el ordenador (NUC) a la batería portátil (power bank).\n    2.  Enciende la batería portátil y ajusta el voltaje hasta que marque 20V.\n    3.  Comprueba que los dos cables de las antenas WiFi estén bien conectados al ordenador.\n    4.  Enciende el ordenador (NUC).\n    5.  Espera unos segundos hasta que el indicador LED de la conexión WiFi se mantenga en verde fijo (sin parpadear).")
                }

                // Título 2
                Text {
                    text: qsTr("2º CONEXIÓN A LA RED WIFI")
                    color: "#00C8FF"
                    font.pixelSize: 20
                    font.bold: true
                }

                Text {
                    id: step2Text
                    width: scrollView.width
                    color: "#ffffff"
                    font.pixelSize: 17
                    wrapMode: Text.WordWrap
                    text: qsTr("Conéctate a la red WiFi del robot móvil desde la tablet.\nEnciende la tablet, abre la configuración de WiFi y selecciona la red con el nombre robogait2024.")
                }

                // Título 3
                Text {
                    text: qsTr("3º ENCENDER LA BASE DEL ROBOT")
                    color: "#00C8FF"
                    font.pixelSize: 20
                    font.bold: true
                }

                Text {
                    id: step3Text
                    width: scrollView.width
                    color: "#ffffff"
                    font.pixelSize: 17
                    wrapMode: Text.WordWrap
                    text: qsTr("Presiona el botón que se encuentra en la base del robot.\nSabrás que se ha encendido correctamente cuando:\n\n     1.  Se encienda un LED azul.\n     2.  Escuches un pitido agudo.")
                }
            }
        }


        // Botón
        Button {
            id: buttonSearchRobot
            height: 45
            anchors.top: scrollView.bottom
            anchors.topMargin: parent.height < 600 ? 20 : 40
            anchors.horizontalCenter: parent.horizontalCenter

            // El ancho se ajusta automáticamente al texto + 8 píxeles (4 a cada lado)
            width: contentItem.implicitWidth + 20

            background: Rectangle {
                color: "#ffffff"
                radius: 8
                border.color: "#045671"
                border.width: 2
            }

            contentItem: Label {
                id: buttonLabel
                text: qsTr("Buscar Robot")
                color: "#045671"
                font.pixelSize: 16
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                anchors.fill: parent
                padding: 0
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:2}D{i:4}D{i:3}D{i:5}D{i:1}
}
##^##*/

