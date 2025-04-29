// BatteryIndicator.qml
import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: battery
    width: 60
    height: 30

    // Porcentaje de batería: 0 a 100
    property int percentage: 75

    // Cuerpo de la batería
    Rectangle {
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
        id: body
        width: 50
        height: 30
        radius: 4
        border.color: "black"
        color: "transparent"
    }

    // Terminal (punta) de la batería
    Rectangle {
        width: 6
        height: 12
        x: body.width
        y: (body.height - height) / 2
        color: "black"
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:8}D{i:2}D{i:1}D{i:3}
}
##^##*/

