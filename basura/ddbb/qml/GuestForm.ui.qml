import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: guestPage

    // width: 1300
    // height: 700
    Rectangle {
        id: rectangle
        color: "#518bb7"
        anchors.fill: parent

        Column {
            id: column
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -60
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20

            Image {
                source: "../images/logo.png"
                anchors.horizontalCenter: parent.horizontalCenter
                width: 220
                height: 220
            }

            TextArea {
                id: nameField
                width: 400
                height: 50
                font.pointSize: 20
                placeholderText: "Nombre"
                padding: 10
                background: Rectangle {
                    radius: 10
                    color: "#FFFFFF"
                    border.color: "#CCCCCC"
                }
            }
            TextArea {
                id: lastnameField
                width: 400
                height: 50
                font.pointSize: 20
                placeholderText: "Apellidos"
                padding: 10
                background: Rectangle {
                    radius: 10
                    color: "#FFFFFF"
                    border.color: "#CCCCCC"
                }
            }

            Button {
                width: 400
                text: "Iniciar como invitado"
                font.capitalization: Font.AllUppercase
                font.weight: Font.Medium
                font.bold: true
                font.pointSize: 24
                height: 50
                background: Rectangle {
                    radius: 10
                    color: "#aed2ea"
                    border.color: "#aed2ea"
                }
                //                    onClicked: console.log("Registrarse presionado")
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 20

                Button {
                    text: "Iniciar Sesion"
                    font.weight: Font.Light
                    font.capitalization: Font.AllUppercase
                    width: 190
                    height: 50
                    font.pointSize: 18
                    background: Rectangle {
                        radius: 10
                        color: "#c2d9e9"
                        border.color: "#c2d9e9"
                    }
                    //                    onClicked: console.log("Registrarse presionado")
                }

                Button {
                    text: "Registrarse"
                    font.weight: Font.Light
                    font.capitalization: Font.AllUppercase
                    width: 190
                    height: 50
                    font.pointSize: 18
                    background: Rectangle {
                        radius: 10
                        color: "#c2d9e9"
                        border.color: "#c2d9e9"
                    }
                    //                    onClicked: console.log("Modo invitado")
                }
            }
        }
    }
}
