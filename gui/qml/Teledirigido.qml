import QtQuick 2.15

TeledirigidoForm {
    property bool visible_value: visible_value

    // Definir los estados
    function clearImageSource() {
        stringHandler.setImageSource("") // Borra la fuente de la imagen
    }
    states: [
        State {
            name: "visible"
            when: visible_value === true
            StateChangeScript {
                script: {
                    console.log("estoy en visible")
                }
            }
            PropertyChanges {
                target: imageDisplay
                visible: true
            }
        },
        State {
            name: "hidden"
            when: visible_value === false
            StateChangeScript {
                script: {
                    console.log("estoy en hidden")
                    clearImageSource();
                }
            }

            PropertyChanges {
                target: imageDisplay
                visible: false
            }
        }
    ]


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

}
