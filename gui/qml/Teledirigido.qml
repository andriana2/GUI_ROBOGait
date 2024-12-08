import QtQuick 2.15

TeledirigidoForm {

    up_mouse_area
    {
        onClicked: {
            stringHandler.currentMove = stringHandler.stringToMove("Recto")
        }
    }
    down_mouse_area
    {
        onClicked: {
            stringHandler.currentMove = stringHandler.stringToMove("Atras")
        }
    }
    stop_mouse_area
    {
        onClicked: {
            stringHandler.currentMove = stringHandler.stringToMove("Stop")
        }
    }
    more_speed_mouse_area
    {
        onClicked: {
            stringHandler.currentMove = stringHandler.stringToMove("Mas_Rapido")
        }
    }
    less_speed_mouse_area
    {
        onClicked: {
            stringHandler.currentMove = stringHandler.stringToMove("Mas_Lento")
        }
    }
    giro_derecha_mouse_area
    {
        onClicked: {
            stringHandler.currentMove = stringHandler.stringToMove("Giro_Derecha")
        }
    }
    giro_izquierda_mouse_area
    {
        onClicked: {
            stringHandler.currentMove = stringHandler.stringToMove("Giro_Izquierda")
        }
    }
    image_button
    {
        onClicked: {

            imageDisplay.source = stringHandler.getImageSource()
            imageDisplay.visible = true
            console.log(imageDisplay.source)
        }
    }


}
