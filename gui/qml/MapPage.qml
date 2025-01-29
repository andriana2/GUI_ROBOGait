import QtQuick 2.15
import "extras"

MapPageForm {

    id:mapPage
    state: "mp_initialPosition"

    mapPageForm_buttonNext.onClicked: {
        mapPage.state = mapPage.mapPageForm_nextState
    }

    states: [
        State{
            name: "mp_initialPosition"
            StateChangeScript {
                script: console.log("estoy en mp_initialPosition")
            }
            PropertyChanges {
                target: mapPage
                mapPageForm_previousState: ""
                mapPageForm_nextState: "mp_initialOrientation"
            }
            PropertyChanges {
                target: mapPageForm_text
                text: qsTr("Al hacer clic en el mapa, se coloca el robot sobre él")
            }
            PropertyChanges {
                target: mapPageForm_orientationCircleForm
                state: "nothing"
            }
            PropertyChanges {
                target: mapPageForm_buttonNext
                enabled: true
                opacity: 1
            }
            PropertyChanges {
                target: mp_mapPage
                map_currentState: "map_initialPosition"
            }
        },
        State {
            name: "mp_initialOrientation"
            StateChangeScript {
                script: console.log("estoy en mp_initialOrientation")
            }
            PropertyChanges {
                target: mapPage
                mapPageForm_previousState: ""
                mapPageForm_nextState: "selectAction"
            }
            PropertyChanges {
                target: mapPageForm_text
                text: qsTr("Al girar la rueda situada debajo, se indica la orientación del robot")
            }
            PropertyChanges {
                target: mapPageForm_orientationCircleForm
                state: "orientacion_inicial"
            }
            PropertyChanges {
                target: mapPageForm_buttonNext
                enabled: true
                opacity: 1
            }
            PropertyChanges {
                target: mp_mapPage
                map_currentState: "map_initialOrientation"
            }
        },
        State {
            name: "selectAction"
            StateChangeScript {
                script: console.log("estoy en selectAction")
            }
            PropertyChanges {
                target: mapPage
                mapPageForm_previousState: "mp_initialOrientation"
                mapPageForm_nextState: ""
            }
            PropertyChanges {
                target: mapPageForm_text
                text: qsTr("Seleccione la acción que quiere realizar a continuación:")

            }
            PropertyChanges {
                target: mapPageForm_orientationCircleForm
                state: "nothing"
            }
            PropertyChanges {
                target: mapPageForm_buttonNext
                enabled: false
                opacity: 0
            }
            PropertyChanges {
                target: mp_mapPage
                map_currentState: "map_selectAction"
            }
        },
        State {
            name: "mp_goalPosePosition"
            StateChangeScript {
                script: console.log("estoy en mp_goalPosePosition")
            }
            PropertyChanges {
                target: mapPage
                mapPageForm_previousState: "selectAction"
                mapPageForm_nextState: "mp_goalPoseOrientation"
            }
            PropertyChanges {
                target: mapPageForm_text
                text: qsTr("Al hacer clic en el mapa, se coloca una pin para indicar la posición final")
            }
            PropertyChanges {
                target: mapPageForm_orientationCircleForm
                state: "nothing"
            }
            PropertyChanges {
                target: mapPageForm_buttonNext
                enabled: true
                opacity: 1
            }
            PropertyChanges {
                target: mp_mapPage
                map_currentState: "map_goalPosePosition"
            }
        },
        State {
            name: "mp_goalPoseOrientation"
            PropertyChanges {
                target: mapPage
                mapPageForm_previousState: "mp_goalPosePosition"
                mapPageForm_nextState: ""
            }
            PropertyChanges {
                target: mapPageForm_text
                text: qsTr("Al girar la rueda situada debajo, se indica la orientación del robot al final")
            }
            PropertyChanges {
                target: mapPageForm_orientationCircleForm
                state: "orientacion_final"
            }
            PropertyChanges {
                target: mapPageForm_buttonNext
                enabled: true
                opacity: 1
                text: qsTr("Comprobación")
            }
            PropertyChanges {
                target: mp_mapPage
                map_currentState: "map_goalPoseOrientation"
            }
        }
    ]
}
