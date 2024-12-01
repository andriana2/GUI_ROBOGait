import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    // width: Constants.width
    // height: Constants.height
    height: 700
    width: 1300
    visible: true
    title:   qsTr("Robogait")


    ApplicationFlow {
        width: parent.width
        height: parent.height
    }
}
