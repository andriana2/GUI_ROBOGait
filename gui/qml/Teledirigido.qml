import QtQuick 2.15
import "extras"

TeledirigidoForm {
    property bool visible_value: visible_value
    // property bool savePageVisible: savePageVisible
    property bool visible_save: visible_save
    property int type_save: type_save
    // property bool mapping: mapping

    states: [
        State {
            name: "mapping"
            when: customSwitch.checked === false
            StateChangeScript {
                script: {
                    console.log("estoy en mapping")
                    clearImageSource()
                    stringHandler.setMapping(0)
                    stringHandler.sendStateRemoteControlledHandler(0,1)
                }
            }
            PropertyChanges {
                target: imageDisplay
                visible: false
            }
            PropertyChanges {
                target: save_page
                visible: false
                opacity: 0
            }
            // PropertyChanges {
            //     target: applicationFlow.toolbar
            //     saveButton.opacity: 0
            //     saveButton.enabled: false
            // }
        },
        State {
            name: "hidden"
            when: visible_value === false
            StateChangeScript {
                script: {
                    console.log("estoy en hidden")
                    clearImageSource();
                    stringHandler.setMapping(1)
                }
            }
            PropertyChanges {
                target: imageDisplay
                visible: false
            }
            PropertyChanges {
                target: save_page
                visible: false
                opacity: 0
            }
        },
        State {
            name: "nothing"
            when: (type_save === 0 || type_save === -1) && visible_value === true
            StateChangeScript {
                script: {
                    console.log("estoy en nothing")

                    stringHandler.setMapping(1)
                    stringHandler.sendStateRemoteControlledHandler(1,1)
                }
            }
            PropertyChanges {
                target: imageDisplay
                visible: true
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
            // PropertyChanges {
            //     target: applicationFlow.toolbar
            //     saveButton.opacity: 1
            //     saveButton.enabled: true
            // }
        },
        State {
            name: "no_save"
            when: type_save === 1 && visible_value === true
            StateChangeScript {
                script: {
                    console.log("estoy en no_save")

                    stringHandler.setMapping(1)
                }
            }
            PropertyChanges {
                target: imageDisplay
                visible: true
            }
            PropertyChanges {
                target: save_page
                visible: true
                state_save_page: 1
                opacity: 1
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
            when: type_save === 2 && visible_value === true
            StateChangeScript {
                script: {
                    console.log("estoy en save")

                    stringHandler.setMapping(1)
                }
            }
            PropertyChanges {
                target: imageDisplay
                visible: true
            }
            PropertyChanges {
                target: save_page
                visible: true
                state_save_page: 2
                opacity: 1
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
            when: type_save === 3 && visible_value === true
            StateChangeScript {
                script: {
                    console.log("estoy en save_again")

                    stringHandler.setMapping(1)
                }
            }
            PropertyChanges {
                target: imageDisplay
                visible: true
            }
            PropertyChanges {
                target: save_page
                visible: true
                state_save_page: 3
                opacity: 1
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

    save_page.cancel.onClicked: {
        console.log("Presionado Cancelar")

        applicationFlow.type_save = -1
        stringHandler.setSaveMap(0)
        stringHandler.setTypeSaveMap(-1)
        console.log(type_save)
    }

    save_page.no_save.onClicked: {
        console.log("Presionado no guardar")
        stringHandler.setSaveMap(1)
        applicationFlow.backButton()
    }

    save_page.save.onClicked: {
        console.log("Presionado Guardar")
        applicationFlow.type_save = 0
        stringHandler.setSaveMap(1)
        stringHandler.setTypeSaveMap(1)
        stringHandler.setNameMap(save_page.text_name.text)
    }

}
