import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
  //width: Constants.width
  height: 700
  width: 1300
  //width: 500
  // height: Constants.height
  visible: true
  title:   qsTr("Ip")
  //color: lightgrey

  ApplicationFlow {
      width: parent.width
      height: parent.height
      //mode: (Screen.height > Screen.width) ? "portrait" : "landscape"
  }
}
