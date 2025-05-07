import QtQuick 2.15

CustomBottomBarForm {
    id: root
    state: "nothing_cbb"


    Connections {
        target: stringHandler
        function onBatteryPercentageChanged() {
            console.log("HOLAAAA")
            if (stringHandler.batteryPercentage < 0) {
                console.log("Battery percentage is negative")
                batteryItem.enabled = false
                batteryItem.opacity = 0
            }
            else {
                if (state !== "nothing_cbb"){
                    batteryPercentage = stringHandler.batteryPercentage
                    batteryItem.enabled = true
                    batteryItem.opacity = 1
                }
            }
        }
    }

    states: [
        State {
            // map and patient active
            name: "MP_cbb"
            PropertyChanges { target: root; textoMapaTitulo: "HAY MAPA ACTIVO:"; textoMapaValor: stringHandler.mapNameTest; colorMapaValor: "#cce54d" }
            PropertyChanges { target: root; textoPacienteTitulo: "HAY PACIENTE ACTIVO:"; textoPacienteValor: stringHandler.patientName; colorPacienteValor: "#cce54d" }
            PropertyChanges { target: batteryItem; enabled: true; opacity: 1 }
        },
        State {
            // map active, patient inactive
            name: "nMP_cbb"
            PropertyChanges { target: root; textoMapaTitulo: "<font color='#953737'>NO</font>  <font color='#ffffff'>HAY MAPA ACTIVO</font>"; textoMapaValor: ""}
            PropertyChanges { target: root; textoPacienteTitulo: "HAY PACIENTE ACTIVO:"; textoPacienteValor: stringHandler.patientName; colorPacienteValor: "#cce54d" }
            PropertyChanges { target: batteryItem; enabled: true; opacity: 1 }
        },
        State {
            // map inactive, patient active
            name: "MnP_cbb"
            PropertyChanges { target: root; textoMapaTitulo: "HAY MAPA ACTIVO:"; textoMapaValor: stringHandler.mapNameTest; colorMapaValor: "#cce54d" }
            PropertyChanges { target: root; textoPacienteTitulo: "<font color='#953737'>NO </font> <font color='#ffffff'>HAY PACIENTE ACTIVO</font>"; textoPacienteValor: ""}
            PropertyChanges { target: batteryItem; enabled: true; opacity: 1 }
        },
        State {
            // map and patient inactive
            name: "nMnP_cbb"
            PropertyChanges { target: root; textoMapaTitulo: "<font color='#953737'>NO </font> <font color='#ffffff'>HAY MAPA ACTIVO</font>"; textoMapaValor: ""}
            PropertyChanges { target: root; textoPacienteTitulo: "<font color='#953737'>NO </font> <font color='#ffffff'>HAY PACIENTE ACTIVO</font>"; textoPacienteValor: ""}
            PropertyChanges { target: batteryItem; enabled: true; opacity: 1 }
        },
        State {
            // map and patient inactive, no battery
            name: "nothing_cbb"
            PropertyChanges{target: customBottomBarItem; enabled: false; opacity: 0 }
        },
        State {
            // map and patient inactive, battery active
            name: "onlyBattery"
            PropertyChanges{target: content; enabled: false; opacity: 0 }
            PropertyChanges { target: batteryItem; enabled: true; opacity: 1 }

        }

    ]

}
