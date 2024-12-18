import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 6.0

Item {
    // width: 1300
    // height: 700
    id: root
    property alias backButton: backButton
    property alias logo: logo
    property alias title: title

    RowLayout {
        width: parent.width
        spacing: 10
        Button {
            id: backButton
            scale: 2
            icon.source: "../images/keyboard_left.svg"
            flat: true
            background: null
            Layout.alignment: Qt.AlignLeft
            transitions: Transition {
                NumberAnimation {
                    properties: "scale"
                    duration: 100
                    easing.type: Easing.InOutQuad
                }
            }
        }
        Item {
            Layout.fillWidth: true // Este espaciador empuja los siguientes elementos al centro
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
        Item {
            Layout.fillWidth: true // Este espaciador permite que el logo y el texto estén centrados
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.9;height:480;width:640}D{i:2}D{i:5}D{i:6}D{i:7}
D{i:8}D{i:1}
}
##^##*/
