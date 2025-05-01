import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: guestPage
    property alias gp_login: gp_login
    property alias gp_singin: gp_singin
    property alias gp_guest_button: gp_guest_button

    property alias nameField: nameField
    property alias lastnameField: lastnameField

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
                source: "../../images/logo.png"
                anchors.horizontalCenter: parent.horizontalCenter
                width: 220
                height: 220
            }

            TextField {
                id: nameField
                width: 400
                height: 50
                font.pointSize: 20
                placeholderText: "Nombre"
                color: "#000000"
                padding: 10
                background: Rectangle {
                    radius: 10
                    color: "#FFFFFF"
                    border.color: "#CCCCCC"
                }
                Keys.onTabPressed: lastnameField.focus = true
                Keys.onReturnPressed: lastnameField.focus = true
            }

            TextField {
                id: lastnameField
                width: 400
                height: 50
                font.pointSize: 20
                placeholderText: "Apellidos"
                color: "#000000"
                padding: 10
                background: Rectangle {
                    radius: 10
                    color: "#FFFFFF"
                    border.color: "#CCCCCC"
                }
                Keys.onTabPressed: gp_guest_button.focus = true
                Keys.onReturnPressed: gp_guest_button.focus = true
            }

            Button {
                width: 400
                id: gp_guest_button
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
                // onClicked: console.log("Iniciar como invitado presionado")
            }

            Row {
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 20

                Button {
                    id: gp_login
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
                    // onClicked: console.log("Iniciar Sesion presionado")
                }

                Button {
                    id: gp_singin
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
                    // onClicked: console.log("Registrarse presionado")
                }
            }
        }
    }
}
