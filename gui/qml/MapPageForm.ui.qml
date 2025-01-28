import QtQuick 2.15
import QtQuick.Controls 2.15
import "extras"

Rectangle {
    id: root
    color: "#518bb7"
    property alias mapPageForm_mystackview: mapPageForm_mystackview
    property alias mapPageForm_buttonNext: mapPageForm_buttonNext
    property alias mapPageForm_text: mapPageForm_text

    property string mapPageForm_previousState: ""
    property string mapPageForm_nextState: ""
    height: 700
    width: 1300

    property alias mp_initialPosition: initialPosition
    property alias mp_initialOrientation: initialOrientation
    property alias mp_selectAction: selectAction
    property alias mp_goalPosePosition: goalPosePosition
    property alias mp_goalPoseOrientation: goalPoseOrientation

    Text {
        id: mapPageForm_text
        x: 922
        width: 360
        height: 151
        color: "#ffffff"
        text: qsTr("Al hacer clic en el mapa, se coloca el robot sobre él")
        anchors.right: parent.right
        anchors.top: parent.top
        font.pixelSize: 40
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        font.styleName: "Medium"
        font.bold: true
        wrapMode: Text.Wrap
        anchors.rightMargin: 18
        anchors.topMargin: 0
    }

    Button {
        id: mapPageForm_buttonNext
        x: 975
        y: 616
        width: 271
        height: 68
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
                font.pointSize: 35
                color: "white" // Color del texto
                verticalAlignment: Text.AlignVCenter
            }
            Image {
                id: svgImage
                source: "../images/keyboard_left.svg"
                anchors.verticalCenterOffset: 3
                // Ruta a tu imagen
                rotation: 180
                width: 50 // Ancho de la imagen
                height: 50
                anchors.verticalCenter: parent.verticalCenter
                fillMode: Image.PreserveAspectFit
                // Alto de la imagen
            }
        }
    }

    StackView {
        id: mapPageForm_mystackview
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        initialItem: initialPosition.createObject(mapPageForm_mystackview)
        pushEnter: Transition {
            PropertyAnimation {
                property: "x"
                from: mystackview.width
                to: 0
                duration: 400
            }
        }
        //! [mystackview view]
        pushExit: Transition {
            PropertyAnimation {
                property: "x"
                from: 0
                to: -mystackview.width
                duration: 400
            }
        }
        popEnter: Transition {
            PropertyAnimation {
                property: "x"
                from: -mystackview.width
                to: 0
                duration: 400
            }
        }
        popExit: Transition {
            PropertyAnimation {
                property: "x"
                from: 0
                to: mystackview.width
                duration: 400
            }
        }
    }

    Component {
        id: initialPosition
        MapForm {
            visible: true
        }
    }
    Component {
        id: initialOrientation
        Map {
            visible: true
        }
    }
    Component {
        id: selectAction
        Map {
            visible: true
        }
    }
    Component {
        id: goalPosePosition
        Map {
            visible: true
        }
    }
    Component {
        id: goalPoseOrientation
        Map {
            visible: true
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}D{i:1}D{i:2}D{i:7}D{i:16}D{i:18}D{i:20}D{i:22}D{i:24}
}
##^##*/

