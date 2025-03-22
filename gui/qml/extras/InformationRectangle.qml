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
    property alias infoRectangleText: textInfo

    // Contenido del Popup
    Rectangle {
        width: parent.width
        height: parent.height
        color: "#d1ecf1"  // Light blue color to indicate a positive status
        border.color: "#bee5eb"
        radius: 10

        Text {
            id: textInfo
            anchors.centerIn: parent
            text: "Todo está bien: El robot está en una posición permitida."
            color: "#0c5460"
            font.pixelSize: 16
        }

        MouseArea {
            anchors.fill: parent
            onClicked: root.close()  // Cierra el popup al hacer clic
        }
    }
}
