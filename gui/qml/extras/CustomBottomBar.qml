import QtQuick 2.15

CustomBottomBarForm {
    id: root
    property alias currentState: root.state

    states: [
        State {
            name: "MapaYpaciente"
            PropertyChanges { target: root; textoMapaTitulo: "HAY MAPA ACTIVO:"; textoMapaValor: "MAPA1"; colorMapaValor: "#cce54d" }
            PropertyChanges { target: root; textoPacienteTitulo: "HAY PACIENTE ACTIVO:"; textoPacienteValor: "PACIENTE1"; colorPacienteValor: "#cce54d" }
        },
        State {
            name: "NoMapaYpaciente"
            PropertyChanges { target: root; textoMapaTitulo: "NO HAY MAPA ACTIVO"; textoMapaValor: ""; colorMapaValor: "#ffffff" }
            PropertyChanges { target: root; textoPacienteTitulo: "HAY PACIENTE ACTIVO:"; textoPacienteValor: "PACIENTE1"; colorPacienteValor: "#cce54d" }
        },
        State {
            name: "MapaYnoPaciente"
            PropertyChanges { target: root; textoMapaTitulo: "HAY MAPA ACTIVO:"; textoMapaValor: "MAPA1"; colorMapaValor: "#cce54d" }
            PropertyChanges { target: root; textoPacienteTitulo: "NO HAY PACIENTE ACTIVO"; textoPacienteValor: ""; colorPacienteValor: "#ffffff" }
        },
        State {
            name: "NoMapaYnoPaciente"
            PropertyChanges { target: root; textoMapaTitulo: "NO HAY MAPA ACTIVO"; textoMapaValor: ""; colorMapaValor: "#ffffff" }
            PropertyChanges { target: root; textoPacienteTitulo: "NO HAY PACIENTE ACTIVO"; textoPacienteValor: ""; colorPacienteValor: "#ffffff" }
        },
        State {
            name: "nothing_cbb"
            PropertyChanges{
                target: customBottomBarItem
                enabled: false
                opacity: 0
            }
            PropertyChanges {
                target: batteryItem
                enabled: false
                opacity: 0
            }
        }
    ]

    Component.onCompleted: root.state = "nothing_cbb"


}
