import QtQuick 2.15
import QtQuick.Controls 2.15

Popup {
    id: root
    width: parent.width * 0.8
    height: 100
    modal: true  // Bloquea la interacción con el contenido de fondo
    focus: true  // Asegura que el Popup reciba eventos de teclado
    anchors.centerIn: parent
    background: null
    property alias errorRectangleTextError: textError


    // Contenido del Popup
    Rectangle {
        width: parent.width
        height: parent.height
        color: "#f8d7da"  // Color rojo claro para indicar error
        border.color: "#f5c6cb"
        radius: 10

        Text {
            id: textError
            anchors.centerIn: parent
            text: "Error: Has puesto el robot en una posicion donde esta prohibido."
            color: "#721c24"
            font.pixelSize: 16
        }

        MouseArea {
            anchors.fill: parent
            onClicked: root.close()  // Cierra el popup al hacer clic
        }
    }
}
