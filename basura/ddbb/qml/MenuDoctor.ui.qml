import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: signinPage

    width: 1300
    height: 700
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

            Rectangle {
                id: selectUser
                width: 500
                height: 50
                radius: 10
                color: "#FFFFFF"
                border.color: "#CCCCCC"
                border.width: 1

                Text {
                    id: buttonSelectUser
                    anchors.centerIn: parent
                    font.pointSize: 20
                    text: "SELECCIONAR UN PACIENTE"
                    font.styleName: "Light"
                }

                MouseArea {
                    anchors.fill: parent
                    //                    onClicked: {
                    //                        console.log("Botón presionado")
                    //                    }
                }
            }

            Rectangle {
                id: addUser
                width: 500
                height: 50
                radius: 10
                color: "#FFFFFF"
                border.color: "#CCCCCC"
                border.width: 1

                Text {
                    id: buttonAddUser
                    anchors.centerIn: parent
                    font.pointSize: 20
                    text: "AÑADIR UN PACIENTE"
                    font.styleName: "Light"
                }

                MouseArea {
                    anchors.fill: parent
                    //                    onClicked: {
                    //                        console.log("Botón presionado")
                    //                    }
                }
            }

            Rectangle {
                id: button
                width: 500
                height: 50
                radius: 10
                color: "#FFFFFF"
                border.color: "#CCCCCC"
                border.width: 1

                Text {
                    id: buttonText
                    anchors.centerIn: parent
                    font.pointSize: 20
                    text: "CERRAR SESIÓN"
                    font.styleName: "Light"
                }

                MouseArea {
                    anchors.fill: parent
                    //                    onClicked: {
                    //                        console.log("Botón presionado")
                    //                    }
                }
            }
        }

        Text {
            id: text1
            color: "#ffffff"
            text: qsTr("Bienvenido Doctor")
            anchors.top: column.top
            font.pixelSize: 50
            horizontalAlignment: Text.AlignHCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: -120
            font.styleName: "Medium"
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.5;height:480;width:640}D{i:3}D{i:6}D{i:9}D{i:2}
D{i:12}D{i:1}
}
##^##*/

