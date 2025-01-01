import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: rectangle
    color: "#518bb7"
    property alias imageDisplay: imageDisplay
    property alias joystick: joystick

    Rectangle {
        id: teledirigido
        width: 2 * parent.width / 3
        height: parent.height
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.left: parent.left
        //color: Colors.rectangle_color
        //        color: "#235c87"
        color: "#518bb7"
        Image {
            id: imageDisplay
            width: Math.min(parent.width, parent.height * imageDisplay.sourceSize.width / imageDisplay.sourceSize.height)
            height: Math.min(parent.height, parent.width * imageDisplay.sourceSize.height / imageDisplay.sourceSize.width)
            anchors.centerIn: parent
            // width: parent.width
            // height: parent.height
            visible: false
            fillMode: Image.PreserveAspectCrop
            // source: ""
            source: ""
        }
    }

    // funcion para actualizar el source de imageDisplay
    Connections {
        target: stringHandler
        function onImageSourceChanged() {
            imageDisplay.visible = true
            imageDisplay.source = stringHandler.imageSource
        }
    }

    Item {
        id: mapa
        width: 250
        height: 250
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenterOffset: teledirigido.width / 2
        anchors.horizontalCenter: parent.horizontalCenter

        Joystick {
            id: joystick
            width: parent.width
            height: 250
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:2}D{i:1}D{i:4}D{i:3}
}
##^##*/

