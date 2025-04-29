import QtQuick 6.5
import QtQuick.Controls 6.5

Rectangle {
    width: 50
    height: 50
    // color: "#f0f0f0" // Light gray background
    color: "transparent"
    radius: 10
    // border.color: "#cccccc"
    // border.width: 1

    // En el futuro, aquí irá la imagen
    Image {
        source: "../../images/icon_app/circle-user-regular.svg"
        anchors.fill: parent
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            menu.x = parent.x;            // Alinear con el rectángulo
            menu.y = parent.y + parent.height + 4;  // Posicionar debajo del rectángulo
            menu.open();
        }
    }

    Menu {
        id: menu
        width: Math.max(logout.implicitWidth, close.implicitWidth) + 30
        background: Rectangle {
            color: "#ffffff" // White background for the menu
            border.color: "#cccccc"
            radius: 5
        }

        // MenuItem {
        //     id: modify
        //     contentItem: Text {
        //         text: "Modificar datos"
        //         font.family: "Ubuntu"
        //         font.pixelSize: 14
        //         color: "#000000" // Negro
        //     }
        //     background: Rectangle {
        //         color: modify.hovered ? "#B0BEC5" : "transparent" // Light gray on hover
        //     }
        //     onTriggered: console.log("Modificar datos")
        // }
        // MenuItem {
        //     id: changePass
        //     contentItem: Text {
        //         text: "Cambiar contraseña"
        //         font.family: "Ubuntu"
        //         font.pixelSize: 14
        //         color: "#000000" // Negro
        //     }
        //     background: Rectangle {
        //         color: changePass.hovered ? "#B0BEC5" : "transparent" // Light gray on hover
        //     }
        //     onTriggered: console.log("Cambiar contraseña")
        // }
        MenuItem {
            id: close
            contentItem: Text {
                text: "Apagar Robot"
                font.family: "Ubuntu"
                font.pixelSize: 14
                color: "#000000" // Negro
            }
            background: Rectangle {
                color: close.hovered ? "#B0BEC5" : "transparent" // Light gray on hover
            }
            onTriggered: console.log("Apagar")
        }
        MenuItem {
            id: logout
            contentItem: Text {
                text: "Cerrar sesión"
                font.family: "Ubuntu"
                font.pixelSize: 14
                color: "#000000" // Negro
            }
            background: Rectangle {
                color: logout.hovered ? "#B0BEC5" : "transparent" // Light gray on hover
            }
            onTriggered: {
                applicationFlow.popToLogin();
                ddbb.clear();
            }
        }
    }

    MouseArea {
        anchors.fill: parent
        z: -1
        onClicked: menu.close()
    }

    // Para ocultar el cuadrado, comenta esta línea:
    // visible: false
}
