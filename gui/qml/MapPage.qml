import QtQuick 2.15
import "extras"

MapPageForm {

    id:mapPage
    state: "mp_initialPosition"

    mapPageForm_buttonNext.onClicked: {
        mapPageForm_mystackview.push()
    }

    states: [
        State{
            name: "mp_initialPosition"
            PropertyChanges {
                target: mapPage
                mapPageForm_previousState: ""
                mapPageForm_nextState: "mp_initialOrientation"
            }
            PropertyChanges {
                target: mapPageForm_text
                text: qsTr("Al hacer clic en el mapa, se coloca el robot sobre él")
            }
        },
        State {
            name: "mp_initialOrientation"
            PropertyChanges {
                target: mapPage
                mapPageForm_previousState: ""
                mapPageForm_nextState: "mp_initialOrientation"
            }
            PropertyChanges {
                target: mapPageForm_text
                text: qsTr("Al girar la rueda situada debajo, se indica la orientación del robot")
            }
        },
        State {
            name: "selectAction"
            PropertyChanges {
                target: mapPage
                mapPageForm_previousState: "mp_initialOrientation"
            }
            PropertyChanges {
                target: mapPageForm_text
                text: qsTr("Seleccione la acción que quiere realizar a continuación:")
            }
        },
        State {
            name: "mp_goalPosePosition"
            PropertyChanges {
                target: mapPage
                mapPageForm_previousState: "selectAction"
                mapPageForm_nextState: "mp_goalPoseOrientation"
            }
            PropertyChanges {
                target: mapPageForm_text
                text: qsTr("Al hacer clic en el mapa, se coloca una pin para indicar la posición final")
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
        }
    ]
}
