import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: signinPage
    property alias sip_login_button: sip_login_button
    property alias sip_guest_button: sip_guest_button
    property alias sip_singIn_button: singInButton
    property alias nameField: nameField
    property alias lastnameField: lastnameField
    property alias usernameField: usernameField
    property alias roleSelector: roleSelector
    property alias passwordField: passwordField
    property alias repeatpasswordField: repeatpasswordField


    // width: 1300
    // height: 700
    Rectangle {
        id: rectangle
        color: "#518bb7"
        anchors.fill: parent

        Column {
            id: column
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: -20
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20

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
                Keys.onTabPressed: lastnameField.focus = true
                Keys.onReturnPressed: lastnameField.focus = true
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
                Keys.onTabPressed: usernameField.focus = true
                Keys.onReturnPressed: usernameField.focus = true
            }
            TextArea {
                id: usernameField
                width: 400
                height: 50
                font.pointSize: 20
                placeholderText: "Nombre de usuario"
                padding: 10
                background: Rectangle {
                    radius: 10
                    color: "#FFFFFF"
                    border.color: "#CCCCCC"
                }
                Keys.onTabPressed: passwordField.focus = true
                Keys.onReturnPressed: passwordField.focus = true
            }

            ComboBox {
                id: roleSelector
                width: 400
                height: 50
                font.pointSize: 20
                font.family: "Ubuntu"
                model: ["Selecciona un rol", "DOCTOR", "MANAGER"]
                currentIndex: 0

                background: Rectangle {
                    radius: 10
                    color: "#FFFFFF"
                    border.color: "#CCCCCC"
                }

                delegate: ItemDelegate {
                    contentItem: Text {
                        text: modelData
                        font.pixelSize: 20
                        color: roleSelector.currentIndex === index ? "blue" : "black"
                    }
                }

                indicator: Canvas {
                    width: 20
                    height: 20
                    contextType: "2d"
                    onPaint: {
                        var ctx = getContext("2d")
                        ctx.clearRect(0, 0, width, height)
                        ctx.fillStyle = "#646464"
                        ctx.beginPath()
                        ctx.moveTo(4, 6)
                        ctx.lineTo(16, 6)
                        ctx.lineTo(10, 14)
                        ctx.closePath()
                        ctx.fill()
                    }
                    anchors.right: parent.right
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.margins: 10
                }
            }


            Rectangle {
                width: 400
                height: 50
                radius: 10
                color: "#FFFFFF"
                border.color: "#CCCCCC"

                TextArea {
                    id: backgroundTextArea
                    width: 400
                    height: 50
                    font.pointSize: 22
                    placeholderText: "Contraseña"
                    color: "transparent" // Fondo transparente
                    background: Rectangle {
                        color: "transparent" // Fondo completamente transparente
                    }
                    anchors.centerIn: parent // Para centrarlo si es necesario
                    focus: false // Deshabilita la interacción con el campo, no se puede escribir en él
                    visible: passwordField.text.length === 0
                    // z: -1  // Coloca el TextArea detrás de otros elementos
                }
                TextInput {
                    id: passwordField
                    anchors.fill: parent
                    font.pointSize: 20
                    padding: 15
                    echoMode: TextInput.Password // Esto oculta el texto ingresado con asteriscos
                                    Keys.onTabPressed: repeatpasswordField.focus = true
                Keys.onReturnPressed: repeatpasswordField.focus = true
                }
            }

            Rectangle {
                width: 400
                height: 50
                radius: 10
                color: "#FFFFFF"
                border.color: "#CCCCCC"

                TextArea {
                    id: repeatpsswTextArea
                    width: 400
                    height: 50
                    font.pointSize: 22
                    placeholderText: "Repetir Contraseña"
                    color: "transparent" // Fondo transparente
                    background: Rectangle {
                        color: "transparent" // Fondo completamente transparente
                    }
                    anchors.centerIn: parent // Para centrarlo si es necesario
                    focus: false // Deshabilita la interacción con el campo, no se puede escribir en él
                    visible: repeatpasswordField.text.length === 0
                    // z: -1  // Coloca el TextArea detrás de otros elementos
                }
                TextInput {
                    id: repeatpasswordField
                    anchors.fill: parent
                    font.pointSize: 20
                    padding: 15
                    echoMode: TextInput.Password // Esto oculta el texto ingresado con asteriscos
                }
            }

            Button {
                id: singInButton
                width: 400
                text: "REGISTRARSE"
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
                    id: sip_login_button
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
                    id: sip_guest_button
                    text: "Invitado"
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

/*##^##
Designer {
    D{i:0;formeditorZoom:0.66}D{i:3}D{i:5}D{i:7}D{i:10}D{i:12}D{i:9}D{i:14}D{i:16}D{i:13}
D{i:17}D{i:20}D{i:22}D{i:19}D{i:2}D{i:1}
}
##^##*/

