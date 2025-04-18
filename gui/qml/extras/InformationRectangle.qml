import QtQuick 2.15
import QtQuick.Controls 2.15

Popup {
    id: root
    width: parent.width * 0.8
    height: 100
    modal: true  // Bloquea la interacción con el contenido de fondo
    closePolicy: Popup.NoAutoClose
    focus: true  // Asegura que el Popup reciba eventos de teclado
    anchors.centerIn: parent
    background: null
    property bool __connectedToClick: false
    property alias infoRectangleText: textInfo
    property alias infoRectangleMouseArea: mouseAreaInfo
    // signal clickedFromPopup()  // Señal personalizada

    // // MouseArea externo (se activa incluso al pulsar fuera del Popup)
    // MouseArea {
    //     anchors.fill: parent  // Cubre toda la ventana padre
    //     enabled: root.opened  // Solo activo cuando el Popup está abierto
    //     onClicked: {
    //         root.clickedFromPopup()  // Emite la señal al pulsar en cualquier lugar
    //     }
    // }
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
            id: mouseAreaInfo
            anchors.fill: parent
            signal clickedFromPopup()
            onClicked: {
                clickedFromPopup()
                root.close()
            }
        }
    }
}
