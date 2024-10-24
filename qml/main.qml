import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

ApplicationWindow {

  width: 1300
  height: 700
  visible: true
  title:   qsTr("Ip")

  Rectangle {
    id: menuStart
    width: parent.width    // Ocupa el ancho de la ventana
    height: parent.height  // Ocupa el alto de la ventana
    color: "lightgray"

    Rectangle {
      id: childRectangle
      width: 100
      height: 100
      color: "blue"
      anchors.top: parent.top   // Anclado al borde superior del padre (Window)
      anchors.horizontalCenter: parent.horizontalCenter  // Centrado horizontalmente
      //anchors.topMargin: 30     // Margen de 30 píxeles por encima
    }
  }
}

