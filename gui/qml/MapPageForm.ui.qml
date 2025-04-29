import QtQuick 2.15
import QtQuick.Controls 2.15
import "extras"

Rectangle {
    id: root
    color: "#518bb7"
    property alias mapPageForm_buttonStop: buttonStop

    property alias mapPageForm_mystackview: mapPageForm_mystackview
    property alias mapPageForm_buttonNext: mapPageForm_buttonNext
    property alias mapPageForm_buttonPrevious: mapPageForm_buttonPrevious
    property alias mapPageForm_text: mapPageForm_text
    property alias mapPageForm_orientationCircleForm: orientationCircle
    property alias mapPageForm_boxImages: boxImages

    property string mapPageForm_previousState: ""
    property string mapPageForm_nextState: ""

    property string mapPageForm_previousState_text: "Anterior"
    property string mapPageForm_nextState_text: "Siguiente"

    property alias mp_map: map

    Item {
        id: rectagle_conteiner
        width: parent.width / 3
        height: parent.height
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.topMargin: 40
        anchors.right: parent.right
        Text {
            id: mapPageForm_text
            x: 922
            width: parent.width - 20
            height: parent.width / 8
            color: "#ffffff"
            text: qsTr("Al hacer clic en el mapa, se coloca el robot sobre él")
            anchors.right: parent.right
            anchors.top: parent.top
            font.pixelSize: 30
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Medium"
            font.bold: true
            wrapMode: Text.Wrap
            anchors.rightMargin: 18
            anchors.topMargin: -20
        }

        OrientationCircle {
            id: orientationCircle
            anchors.top: mapPageForm_text.bottom
            anchors.horizontalCenter: mapPageForm_text.horizontalCenter
            anchors.topMargin: 100
        }

        BoxImages {
            id: boxImages
            anchors.top: mapPageForm_text.bottom
            anchors.horizontalCenterOffset: 40
            anchors.horizontalCenter: mapPageForm_text.horizontalCenter
            anchors.topMargin: 70
        }

        Button {
            id: mapPageForm_buttonNext
            x: 8
            y: 376
            width: 196
            height: 48
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.rightMargin: 9
            anchors.bottomMargin: 16
            font.pointSize: 40
            background: Rectangle {
                color: "transparent" // Fondo transparente
                border.color: "transparent" // Sin bordes
            }

            contentItem: Item {
                id: row
                anchors.centerIn: parent

                Text {
                    anchors.right: svgImage.left
                    anchors.verticalCenter: parent.verticalCenter
                    font.pointSize: 25
                    color: "white"
                    text: qsTr(mapPageForm_nextState_text)
                    anchors.rightMargin: 10
                }
                Image {
                    id: svgImage
                    source: "../images/icon_app/keyboard_left.svg"
                    rotation: 180
                    width: 40
                    height: 40
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    fillMode: Image.PreserveAspectFit
                }
            }
        }

        Button {
            id: mapPageForm_buttonPrevious
            width: 196
            height: 48
            anchors.right: mapPageForm_buttonNext.left
            anchors.bottom: parent.bottom
            anchors.rightMargin: 20
            anchors.bottomMargin: 16
            font.pointSize: 40
            background: Rectangle {
                color: "transparent" // Fondo transparente
                border.color: "transparent" // Sin bordes
            }

            contentItem: Row {
                id: row2
                // Contenido del botón
                anchors.centerIn: parent
                spacing: 10

                Image {
                    id: svgImage2
                    source: "../images/icon_app/keyboard_left.svg"
                    anchors.verticalCenterOffset: 3
                    width: 40
                    height: 40
                    anchors.verticalCenter: parent.verticalCenter
                    fillMode: Image.PreserveAspectFit
                    // Alto de la imagen
                }
                Text {
                    text: qsTr(mapPageForm_previousState_text)
                    horizontalAlignment: Text.AlignRight
                    font.pointSize: 25
                    color: "white" // Color del texto
                    verticalAlignment: Text.AlignVCenter
                }
            }
        }
    }

    StackView {
        id: mapPageForm_mystackview
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        initialItem: Map {
            id: map
        }
        pushEnter: null
        pushExit: null
        popEnter: null
        popExit: null
    }
    Button {
        id: buttonStop
        height: 50
        anchors.top: parent.top
        anchors.topMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter
        width: 100

        background: Rectangle {
            color: buttonStop.down ? "#f8d7da" : "#f5c6cb"
            radius: 15
            border.color: "#721c24"
            border.width: 2
        }

        contentItem: Label {
            id: buttonLabel
            text: qsTr("STOP")
            color: "#721c24"
            font.pixelSize: 30
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            font.styleName: "Regular"
            font.weight: Font.Light
            anchors.fill: parent
            padding: 0
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:2}D{i:3}D{i:4}D{i:5}D{i:10}D{i:1}D{i:15}
D{i:17}
}
##^##*/

