import QtQuick 2.15

TeledirigidoForm {

    joystick.onDirChanged: {
        stringHandler.setCurrentMove(linear, angular)
        // console.log("Velocidad lineal: "+ linear + " Velocidad angular: " + angular);
    }

    // Conectando el signal pressed al manejador de presionado
    joystick.onPressed: {
        console.log("Joystick presionado");
    }

    // Conectando el signal released al manejador de liberado
    joystick.onReleased: {
        stringHandler.setCurrentMove("0.0", "0.0")
        console.log("Joystick liberado");
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
