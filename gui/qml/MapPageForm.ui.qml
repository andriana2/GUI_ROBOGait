import QtQuick 2.15
import QtQuick.Controls 2.15
import "extras"

Rectangle {
    id: root
    // width: 13/*00
    // height: 70*/0
    color: "#518bb7"
    property alias mapPageForm_mystackview: mapPageForm_mystackview
    property alias mapPageForm_buttonNext: mapPageForm_buttonNext
    property alias mapPageForm_text: mapPageForm_text
    property alias mapPageForm_orientationCircleForm: orientationCircle

    property string mapPageForm_previousState: ""
    property string mapPageForm_nextState: ""

    property alias mp_mapPage: mapPage

    // property alias mp_initialOrientation: initialOrientation
    // property alias mp_selectAction: selectAction
    // property alias mp_goalPosePosition: goalPosePosition
    // property alias mp_goalPoseOrientation: goalPoseOrientation
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

            contentItem: Row {
                id: row
                // Contenido del botón
                anchors.centerIn: parent
                spacing: 10

                Text {
                    text: qsTr("Siguiente")
                    horizontalAlignment: Text.AlignRight
                    font.pointSize: 25
                    color: "white" // Color del texto
                    verticalAlignment: Text.AlignVCenter
                }
                Image {
                    id: svgImage
                    source: "../images/keyboard_left.svg"
                    anchors.verticalCenterOffset: 3
                    // Ruta a tu imagen
                    rotation: 180
                    width: 40 // Ancho de la imagen
                    height: 40
                    anchors.verticalCenter: parent.verticalCenter
                    fillMode: Image.PreserveAspectFit
                    // Alto de la imagen
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
            id: mapPage
        }
        pushEnter: null
        pushExit: null
        popEnter: null
        popExit: null
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:2}D{i:3}D{i:4}D{i:1}D{i:9}
}
##^##*/

