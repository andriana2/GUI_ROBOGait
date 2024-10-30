import QtQuick 2.15

Item {
  QtObject {
    id: dark
    readonly property color background: "#001212"
    //readonly property color textColor: "#FEFEFE"
  //  readonly property color borderColor: "#3E3E3E"
//    readonly property color cardColor: "#212121"
  //  readonly property color caption: "#898989"
  }

  property var currentTheme: dark

}
