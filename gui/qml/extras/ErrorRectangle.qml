import QtQuick 2.15

Item{
    width: parent.width * 0.8
    height: 100
    property alias errorRectangleErrorPopup: errorPopup
    property alias errorRectangleTextError: textError

    Rectangle {
        id: errorPopup
        width: parent.width
        height: parent.height
        color: "#f8d7da"  // Color rojo claro para indicar error
        border.color: "#f5c6cb"
        radius: 10
        anchors.centerIn: parent
        visible: false  // Oculto por defecto

        Text {
            id: textError
            anchors.centerIn: parent
            text: "Error: Has puesto el robot en una posicion donde esta prohibido."
            color: "#721c24"
            font.pixelSize: 16
        }

        MouseArea {
            anchors.fill: parent
            onClicked: errorPopup.visible = false  // Cierra el popup al hacer clic
        }
    }
}
