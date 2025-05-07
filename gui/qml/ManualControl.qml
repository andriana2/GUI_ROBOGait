import QtQuick 2.15
import "extras"

ManualControlForm {
    id: manualControlForm
    // property real linear_ext: lineal_ext
    // property real angular_ext: angular_ext
    Connections {
        target: stringHandler
        function onAngularVelocityChanged(){
            // console.log("angularVelocity: " + stringHandler.angularVelocity);
            angular_value = stringHandler.angularVelocity
        }
        function onLinealVelocityChanged(){
            // console.log("linealVelocity: " + stringHandler.linealVelocity);
            linear_value = stringHandler.linealVelocity
        }
    }

    Connections {
        target: joystick

        function onDirChanged(linear, angular) {
            stringHandler.linealVelocity = linear;
            stringHandler.angularVelocity = angular;
        }
    }

    // Conectando el signal pressed al manejador de presionado
    joystick.onPressed: {
        console.log("Joystick presionado");
    }

    // Conectando el signal released al manejador de liberado
    joystick.onReleased: {
        // stringHandler.setCurrentMove("0.0", "0.0")
        stringHandler.linealVelocity = 0.0
        stringHandler.angularVelocity = 0.0
        // stringHandler.setSaveMap(0)
        console.log("Joystick liberado");
    }


}
