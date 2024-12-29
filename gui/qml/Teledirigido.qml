import QtQuick 2.15

TeledirigidoForm {

    // joystickId:
    //     Joystick {
    //         id:joyStick
    //         anchors.bottom: parent.bottom
    //         anchors.left: parent.left
    //         anchors.bottomMargin: 10
    //         anchors.leftMargin: 10
    //         width:150;height:150
    //     }


    joystick.onDirChanged: {
        console.log("Velocidad lineal: " + direction + " Velocidad angular: " + angulo);
    }
    // function handleDirChanged(direction) {
    //     console.log("Dirección cambiada a: " + direction);
    // }

    // Conectando el signal pressed al manejador de presionado
    joystick.onPressed: {
        console.log("Joystick presionado");
    }

    // Conectando el signal released al manejador de liberado
    joystick.onReleased: {
        console.log("Joystick liberado");
    }
    // up_mouse_area
    // {
    //     onClicked: {
    //         stringHandler.currentMove = stringHandler.stringToMove("Recto")
    //     }
    // }
    // down_mouse_area
    // {
    //     onClicked: {
    //         stringHandler.currentMove = stringHandler.stringToMove("Atras")
    //     }
    // }
    // stop_mouse_area
    // {
    //     onClicked: {
    //         stringHandler.currentMove = stringHandler.stringToMove("Stop")
    //     }
    // }
    // more_speed_mouse_area
    // {
    //     onClicked: {
    //         stringHandler.currentMove = stringHandler.stringToMove("Mas_Rapido")
    //     }
    // }
    // less_speed_mouse_area
    // {
    //     onClicked: {
    //         stringHandler.currentMove = stringHandler.stringToMove("Mas_Lento")
    //     }
    // }
    // giro_derecha_mouse_area
    // {
    //     onClicked: {
    //         stringHandler.currentMove = stringHandler.stringToMove("Giro_Derecha")
    //     }
    // }
    // giro_izquierda_mouse_area
    // {
    //     onClicked: {
    //         stringHandler.currentMove = stringHandler.stringToMove("Giro_Izquierda")
    //     }
    // }
    // image_button
    // {
    //     onClicked: {

    //         imageDisplay.source = stringHandler.getImageSource()
    //         imageDisplay.visible = true
    //         console.log(imageDisplay.source)
    //     }
    // }


}
