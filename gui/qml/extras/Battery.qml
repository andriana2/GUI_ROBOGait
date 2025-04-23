import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: battery
    width: 30
    height: 15


    // Porcentaje de batería: 0 a 100
    property int percentage: 75

    // Cuerpo de la batería
    Rectangle {
        id: body
        width: 25
        height: 15
        radius: 4
        border.color: "white"
        color: "transparent"

        // Nivel de batería (relleno)
        Rectangle {
            id: level
            width: body.width * battery.percentage / 100
            height: body.height - 2
            color: battery.percentage < 20 ? "red" : battery.percentage < 50 ? "orange" : "green"
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.leftMargin: 1
            anchors.verticalCenterOffset: 0
        }
    }

    // Terminal (punta) de la batería
    Rectangle {
        width: 3
        height: 6
        x: body.width
        y: (body.height - height) / 2
        color: "white"
    }
}
