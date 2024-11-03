import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: root
    color: Colors.currentTheme.background

  StackView {
      id: stackView
      anchors.fill: parent

      ListView {
          id: listView
          x: 282
          y: 253
          width: 110
          height: 160
          model: ListModel {
              ListElement {
                  name: "Grey"
                  colorCode: "grey"
              }

              ListElement {
                  name: "Red"
                  colorCode: "red"
              }

              ListElement {
                  name: "Blue"
                  colorCode: "blue"
              }

              ListElement {
                  name: "Green"
                  colorCode: "green"
              }
          }
          delegate: Item {
              x: 5
              width: 80
              height: 40
              Row {
                  id: row1
                  Rectangle {
                      width: 40
                      height: 40
                      color: colorCode
                  }

                  Text {
                      text: name
                      anchors.verticalCenter: parent.verticalCenter
                      font.bold: true
                  }
                  spacing: 10
              }
          }
      }
  }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.66;height:480;width:640}D{i:2}D{i:1}
}
##^##*/
