import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: loginPage
    property alias lp_singin_button: lp_singin_button
    property alias lp_guest_button: lp_guest_button
    property alias lp_login_button: lp_login_button
    property alias usernameField: usernameField
    property alias passwordField: passwordField
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
                source: "../../images/logo.png"
                anchors.horizontalCenter: parent.horizontalCenter
                width: 220
                height: 220
            }

            TextField {
                id: usernameField
                width: 400
                height: 50
                color: "#000000"
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 20
                verticalAlignment: TextInput.AlignVCenter
                leftPadding: 10
                rightPadding: 10
                background: Rectangle {
                    radius: 10
                    color: "#FFFFFF"
                    border.color: usernameField.activeFocus ? "#518bb7" : "#CCCCCC"

                    Text {
                        visible: usernameField.text === "" && !usernameField.activeFocus
                        text: qsTr("Usuario")
                        color: "#808080"
                        anchors {
                            left: parent.left
                            leftMargin: 15
                            top: parent.top
                            topMargin: 15
                        }
                        font: usernameField.font
                    }
                }
                Keys.onTabPressed: passwordField.focus = true
                Keys.onReturnPressed: passwordField.focus = true
            }

            TextField {
                id: passwordField
                width: 400
                height: 50
                color: "#000000"
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 20
                verticalAlignment: TextInput.AlignVCenter
                leftPadding: 10
                rightPadding: 10
                echoMode: TextInput.Password // Ensure this is set to mask the input

                background: Rectangle {
                    radius: 10
                    color: "#FFFFFF"
                    border.color: passwordField.activeFocus ? "#518bb7" : "#CCCCCC"

                    Text {
                        visible: passwordField.text === "" && !passwordField.activeFocus
                        text: qsTr("Contraseña")
                        color: "#808080"
                        anchors {
                            left: parent.left
                            leftMargin: 15
                            top: parent.top
                            topMargin: 15
                        }
                        font: passwordField.font
                    }
                }

                // Ensure focus behavior is correct
                Keys.onTabPressed: usernameField.focus = true
                Keys.onReturnPressed: usernameField.focus = true
            }

            Button {
                id: lp_login_button
                width: 400
                text: "Iniciar Sesion"
                font.capitalization: Font.AllUppercase
                font.weight: Font.Medium
                font.bold: true
                font.pointSize: 28
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
                    id: lp_singin_button
                    text: "Registrarse"
                    font.weight: Font.Light
                    font.capitalization: Font.AllUppercase
                    width: 190
                    height: 50
                    font.pointSize: 22
                    background: Rectangle {
                        radius: 10
                        color: "#c2d9e9"
                        border.color: "#c2d9e9"
                    }
                    //                    onClicked: console.log("Registrarse presionado")
                }

                Button {
                    id: lp_guest_button
                    text: "Invitado"
                    font.weight: Font.Light
                    font.capitalization: Font.AllUppercase
                    width: 190
                    height: 50
                    font.pointSize: 22
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

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.75;height:480;width:640}D{i:3}D{i:4}D{i:7}D{i:9}
D{i:6}D{i:10}D{i:13}D{i:15}D{i:12}D{i:2}D{i:1}
}
##^##*/

