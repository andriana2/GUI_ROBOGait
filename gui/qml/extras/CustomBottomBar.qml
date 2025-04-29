import QtQuick 2.15

CustomBottomBarForm {
    id: root
    state: "nothing_cbb"

    states: [
        State {
            // map and patient active
            name: "MP_cbb"
            PropertyChanges { target: root; textoMapaTitulo: "HAY MAPA ACTIVO:"; textoMapaValor: "MAPA1"; colorMapaValor: "#cce54d" }
            PropertyChanges { target: root; textoPacienteTitulo: "HAY PACIENTE ACTIVO:"; textoPacienteValor: "PACIENTE1"; colorPacienteValor: "#cce54d" }
            PropertyChanges { target: batteryItem; enabled: true; opacity: 1 }
        },
        State {
            // map active, patient inactive
            name: "nMP_cbb"
            PropertyChanges { target: root; textoMapaTitulo: "NO HAY MAPA ACTIVO"; textoMapaValor: ""; colorMapaValor: "#953737" }
            PropertyChanges { target: root; textoPacienteTitulo: "HAY PACIENTE ACTIVO:"; textoPacienteValor: "PACIENTE1"; colorPacienteValor: "#cce54d" }
            PropertyChanges { target: batteryItem; enabled: true; opacity: 1 }
        },
        State {
            // map inactive, patient active
            name: "MnP_cbb"
            PropertyChanges { target: root; textoMapaTitulo: "HAY MAPA ACTIVO:"; textoMapaValor: "MAPA1"; colorMapaValor: "#cce54d" }
            PropertyChanges { target: root; textoPacienteTitulo: "NO HAY PACIENTE ACTIVO"; textoPacienteValor: ""; colorPacienteValor: "#953737" }
            PropertyChanges { target: batteryItem; enabled: true; opacity: 1 }
        },
        State {
            // map and patient inactive
            name: "nMnP_cbb"
            PropertyChanges { target: root; textoMapaTitulo: "NO HAY MAPA ACTIVO"; textoMapaValor: ""; colorMapaValor: "#953737" }
            PropertyChanges { target: root; textoPacienteTitulo: "NO HAY PACIENTE ACTIVO"; textoPacienteValor: ""; colorPacienteValor: "#953737" }
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
