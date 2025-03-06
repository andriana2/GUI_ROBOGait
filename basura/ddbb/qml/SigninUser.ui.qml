import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: signinPage
    property alias sip_login_botton: sip_login_botton
    property alias sip_guest_botton: sip_guest_botton

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
            TextArea {
                id: ageField
                width: 400
                height: 50
                font.pointSize: 20
                placeholderText: "Edad"
                padding: 10
                background: Rectangle {
                    radius: 10
                    color: "#FFFFFF"
                    border.color: "#CCCCCC"
                }
            }

            TextArea {
                id: weightField
                width: 400
                height: 50
                font.pointSize: 20
                placeholderText: "Peso"
                padding: 10
                background: Rectangle {
                    radius: 10
                    color: "#FFFFFF"
                    border.color: "#CCCCCC"
                }
            }
            TextArea {
                id: heightField
                width: 400
                height: 50
                font.pointSize: 20
                placeholderText: "Altura"
                padding: 10
                background: Rectangle {
                    radius: 10
                    color: "#FFFFFF"
                    border.color: "#CCCCCC"
                }
            }

            Button {
                width: 400
                text: "REGISTRAR"
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



