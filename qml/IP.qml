import QtQuick 2.15

IPForm {
  buttonEnviar {
    onClicked: {
      console.log(textArea.text)
      var ifIPgood = _rosNode.stringIP(textArea.text)
      if (!ifIPgood)
        errorPopup.visible = true
      else {
        errorPopup.visible = false
        console.log("Texto enviado: " + textArea.text)
      }

    }
  }
  Rectangle {
    id: errorPopup
    width: parent.width * 0.8
    height: 100
    color: "#f8d7da"  // Color rojo claro para indicar error
    border.color: "#f5c6cb"
    radius: 10
    anchors.centerIn: parent
    visible: false  // Oculto por defecto

    Text {
      anchors.centerIn: parent
      text: "Error: El campo no puede estar vacío."
      color: "#721c24"
      font.pixelSize: 16
    }

    MouseArea {
      anchors.fill: parent
      onClicked: errorPopup.visible = false  // Cierra el popup al hacer clic
    }
  }
}
