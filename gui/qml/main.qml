import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import "extras"

ApplicationWindow {
    height: 700
    width: 1300
    visible: true
    visibility: Qt.platform.os === "android" ? Window.FullScreen : Window.Windowed

    title:   qsTr("Robogait")

    ApplicationFlow {
        width: parent.width
        height: parent.height
    }
    onClosing: {
        stringHandler.closeConnection();
    }

}
