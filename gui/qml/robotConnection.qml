import QtQuick 2.15
import "extras"

IpForm {
    width: parent.width
    height: parent.height
    // id: ipqml
    // property bool empty: true

    // buttonEnviar {
    //     onClicked: {
    //         var ifIPgood = stringHandler.isInSameNetwork(textArea.text)
    //         if (textArea.text === ""){
    //             empty = true
    //             errorPopup.visible = true
    //         }
    //         else if (!ifIPgood){
    //             empty = false
    //             errorPopup.visible = true
    //         }
    //         else {
    //             errorPopup.visible = false
    //             applicationFlow.register_page_push()
    //             console.log("Texto enviado: " + textArea.text)
    //         }
    //     }
    // }

    // //version previa del ErrorRectangle
    // Rectangle {
    //     id: errorPopup
    //     width: parent.width * 0.8
    //     height: 100
    //     color: "#f8d7da"  // Color rojo claro para indicar error
    //     border.color: "#f5c6cb"
    //     radius: 10
    //     anchors.centerIn: parent
    //     visible: false  // Oculto por defecto

    //     Text {
    //         anchors.centerIn: parent
    //         text: empty ? "Error: El campo no puede estar vacío." : "Error: La IP es incorrecta, conéctate o escríbela bien. Formato: 10.0.2.15"
    //         color: "#721c24"
    //         font.pixelSize: 16
    //     }

    //     MouseArea {
    //         anchors.fill: parent
    //         onClicked: errorPopup.visible = false  // Cierra el popup al hacer clic
    //     }
    // }
}

