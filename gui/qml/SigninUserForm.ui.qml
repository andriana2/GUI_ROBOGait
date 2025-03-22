import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: signinPage
    property alias su_add_user: addInformation
    property alias su_start_test: startTest
    property alias nameField: nameField
    property alias lastnameField: lastnameField
    property alias ageField: ageField
    property alias weightField: weightField
    property alias heightField: heightField

    //    width: 1300
    //    height: 700
    Rectangle {
        id: rectangle
        color: "#518bb7"
        anchors.fill: parent

        Column {
            id: column
            anchors.verticalCenter: parent.verticalCenter
            anchors.verticalCenterOffset: 20
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 20

            TextArea {
                id: nameField
                width: 450
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
                width: 450
                height: 50
                font.pointSize: 20
                placeholderText: "Apellidos"
                padding: 10
                background: Rectangle {
                    radius: 10
                    color: "#FFFFFF"
                    border.color: "#CCCCCC"
                }
                Keys.onTabPressed: ageField.focus = true
                Keys.onReturnPressed: ageField.focus = true
            }
            TextArea {
                id: ageField
                width: 450
                height: 50
                font.pointSize: 20
                placeholderText: "Edad (años)"
                padding: 10
                background: Rectangle {
                    radius: 10
                    color: "#FFFFFF"
                    border.color: "#CCCCCC"
                }
                Keys.onTabPressed: weightField.focus = true
                Keys.onReturnPressed: weightField.focus = true
            }

            TextArea {
                id: weightField
                width: 450
                height: 50
                font.pointSize: 20
                placeholderText: "Peso (Kg)"
                padding: 10
                background: Rectangle {
                    radius: 10
                    color: "#FFFFFF"
                    border.color: "#CCCCCC"
                }
                Keys.onTabPressed: heightField.focus = true
                Keys.onReturnPressed: heightField.focus = true
            }
            TextArea {
                id: heightField
                width: 450
                height: 50
                font.pointSize: 20
                placeholderText: "Altura (cm)"
                padding: 10
                background: Rectangle {
                    radius: 10
                    color: "#FFFFFF"
                    border.color: "#CCCCCC"
                }
                Keys.onTabPressed: addInformation.focus = true
                Keys.onReturnPressed: addInformation.focus = true
            }

            Row {
                spacing: 20

                Button {
                    id: addInformation
                    width: 215
                    height: 50
                    text: "AÑADIR"
                    font.styleName: "Medium"
                    font.capitalization: Font.AllUppercase
                    font.weight: Font.Light
                    font.bold: true
                    font.pointSize: 19
                    background: Rectangle {
                        radius: 10
                        color: "#aed2ea"
                        border.color: "#aed2ea"
                    }
                }

                Button {
                    id: startTest
                    width: 215
                    height: 50
                    text: "INICIAR PRUEBA"
                    font.styleName: "Medium"
                    font.capitalization: Font.AllUppercase
                    font.weight: Font.Normal
                    font.bold: true
                    font.pointSize: 19
                    background: Rectangle {
                        radius: 10
                        color: "#aed2ea"
                        border.color: "#aed2ea"
                    }
                }
            }
        }

        Text {
            id: text1
            color: "#ffffff"
            text: qsTr("Registrar paciente")
            anchors.top: column.top
            font.pixelSize: 50
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: -80
            font.styleName: "Medium"
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.75;height:480;width:640}D{i:3}D{i:5}D{i:7}D{i:9}
D{i:11}D{i:14}D{i:16}D{i:13}D{i:2}D{i:18}D{i:1}
}
##^##*/

