import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 6.0

Item {
    // width: 1920
    // height: 1080
    id: root
    property alias backButton: backButton
    property alias logo: logo
    property alias title: title

    RowLayout {
        width: parent.width
        Button {
            id: backButton
            flat: true
            background: null
            transitions: Transition {
                NumberAnimation {
                    properties: "scale"
                    duration: 100
                    easing.type: Easing.InOutQuad
                }
            }
        }
        Image {
            id: logo
            source: "../images/logo.png"
            Layout.alignment: Qt.AlignCenter
            sourceSize.height: 25
            sourceSize.width: height * 1.4
        }
        Text {
            id: title
            text: "ROBOGAIT"
            Layout.alignment: Qt.AlignVCenter
            font.pixelSize: 20
            color: "white"
        }
    }
}

