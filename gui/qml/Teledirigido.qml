import QtQuick 2.15

TeledirigidoForm {
    property bool visible_value: visible_value
    // property bool savePageVisible: savePageVisible
    property bool visible_save: visible_save
    property int type_save: type_save

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
        // State {
        //     name: "hidden"
        //     when: visible_value === false
        //     StateChangeScript {
        //         script: {
        //             console.log("estoy en hidden")
        //             clearImageSource();
        //         }
        //     }

        //     PropertyChanges {
        //         target: imageDisplay
        //         visible: false
        //     }
        // },
        State {
            name: "nothing"
            when: type_save === 0 || type_save === -1
            StateChangeScript {
                script: {
                    console.log("estoy en nothing")
                }
            }
            PropertyChanges {
                target: save_page
                visible: false
                opacity: 0
            }
            PropertyChanges {
                target: joystick
                enabled: true // Deshabilitar joystick
            }
            PropertyChanges {
                target: switchRow
                enabled: true
            }
        },
        State {
            name: "no_save"
            when: type_save === 1
            StateChangeScript {
                script: {
                    console.log("estoy en no_save")
                }
            }
            PropertyChanges {
                target: save_page
                visible: true
                state_save_page: 1
            }
            PropertyChanges {
                target: joystick
                enabled: false // Deshabilitar joystick
            }
            PropertyChanges {
                target: switchRow
                enabled: false
            }
        },
        State {
            name: "save"
            when: type_save === 2
            StateChangeScript {
                script: {
                    console.log("estoy en save")
                }
            }
            PropertyChanges {
                target: save_page
                visible: true
                state_save_page: 2
            }
            PropertyChanges {
                target: joystick
                enabled: false // Deshabilitar joystick
            }
            PropertyChanges {
                target: switchRow
                enabled: false
            }
        },
        State {
            name: "save_again"
            when: type_save === 3
            StateChangeScript {
                script: {
                    console.log("estoy en save_again")
                }
            }
            PropertyChanges {
                target: save_page
                visible: true
                state_save_page: 3
            }
            PropertyChanges {
                target: joystick
                enabled: false // Deshabilitar joystick
            }
            PropertyChanges {
                target: switchRow
                enabled: false
            }
        }
    ]


    // Definir los estados
    function clearImageSource() {
        stringHandler.setImageSource("") // Borra la fuente de la imagen
    }



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
        stringHandler.setSaveMap(0)
        console.log("Joystick liberado");
    }

}
