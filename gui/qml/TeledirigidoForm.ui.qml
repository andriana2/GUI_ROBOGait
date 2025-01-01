import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: rectangle
    color: "#518bb7"
    property alias imageDisplay: imageDisplay
    property alias joystick: joystick
    // property alias image_button: image_button

    // property alias giro_izquierda_mouse_area: giro_izquierda_mouse_area
    // property alias giro_derecha_mouse_area: giro_derecha_mouse_area
    // property alias less_speed_mouse_area: less_speed_mouse_area
    // property alias more_speed_mouse_area: more_speed_mouse_area
    // property alias stop_mouse_area: stop_mouse_area
    // property alias down_mouse_area: down_mouse_area
    // property alias up_mouse_area: up_mouse_area

    // property alias joystickId: joystickId
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
    Connections {
        target: stringHandler
        function onImageSourceChanged() {
            // Actualizar el source cuando la señal es emitida
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

        //color: Colors.rectangle_color
        //                    color: "#a8efff"
        Joystick {
            id: joystick
            width: parent.width
            height: 250
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }

    // Button {
    //     id: image_button
    //     anchors.verticalCenter: parent.verticalCenter
    //     anchors.horizontalCenter: parent.horizontalCenter
    //     text: qsTr("image")
    //     //        onClicked: {
    //     //            imageReceiver.setImage(imageData)
    //     //            imageDisplay.visible = true
    //     //        }
    // }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:2}D{i:1}D{i:4}D{i:3}
}
##^##*/

