import QtQuick 2.15
import "extras"

MapPageForm {

    id:mapPage
    state: "mp_initialPosition"
    signal mapPage_clear_pressed()
    signal mapPage_ok_pressed()
    signal mapPage_check_pressed()
    signal mapPage_edit_pressed()

    ErrorRectangle {
        id: errorPopup
        anchors.centerIn: parent
        errorRectangleTextError.text: "Error: Has puesto el robot en una posicion donde esta prohibido."
    }


    mapPageForm_buttonNext.onClicked: {
        if(state === "mp_initialPosition")
        {
            if(mapInfo.positionScreen.x === 0 || mapInfo.positionScreen.y === 0)
            {
                errorPopup.errorRectangleTextError.text = "Error: Has intentado seguir adelante sin poner el robot en el mapa"
                errorPopup.open()
                return;
            }
        }
        if(state === "mp_goalPosePosition")
        {
            if(mapInfo.finalPathPosition.x === 0 || mapInfo.finalPathPosition.y === 0)
            {
                errorPopup.errorRectangleTextError.text = "Error: Has intentado seguir adelante sin poner el robot en el mapa para indicar la poscion final"
                errorPopup.open()
                return;
            }
        }

        if(state === "mp_initialOrientation")
        {
            if(mapInfo.orientation === 0.00)
            {
                errorPopup.errorRectangleTextError.text = "Error: Has intentado seguir adelante sin poner la orientacion del robot"
                errorPopup.open()
                return;
            }
        }
        if(state === "mp_goalPoseOrientation")
        {
            if(mapInfo.finalPathOrientation === 0.00)
            {
                errorPopup.errorRectangleTextError.text = "Error: Has intentado seguir adelante sin poner la orientacion del robot en la poscion final"
                errorPopup.open()
                return;
            }
        }


        mapPage.state = mapPage.mapPageForm_nextState

    }

    mapPageForm_buttonPrevious.onClicked: {
        mapPage.state = mapPage.mapPageForm_previousState
    }

    mapPageForm_boxImages.onBif_check_pressed: {
        if (state === "selectAction")
            mapPage.state = "mp_goalPosePosition"
    }

    mapPageForm_boxImages.onBif_ok_pressed: {
        if (state === "selectAction")
            mapPage.state = "mp_drawPath"
    }



    // mapPageForm_boxImages.bif_edit_pressed: {

    // }

    mapPageForm_boxImages.onBif_clear_pressed: {
        if (state === "mp_initialPosition" || state === "mp_goalPosePosition")
            mp_map.canvas.clear()
    }

    mapPageForm_boxImages.onBif_edit_pressed: {
        if (state === "mp_initialPosition")
        {
            mapInfo.setScreenSize(mp_map.imageDisplay.width, mp_map.imageDisplay.height)
            mp_map.canvas.enablePainting = true
        }
        if (state === "mp_goalPosePosition")
        {
            mp_map.canvas.clear_internal()
            mp_map.canvas.enablePainting = true
        }
    }





    states: [
        State{
            name: "mp_initialPosition"
            StateChangeScript {
                script: console.log("estoy en mp_initialPosition")
            }
            StateChangeScript {
                script: mp_map.canvas.requestPaint()
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
                text: qsTr("Siguiente")
            }
            PropertyChanges {
                target: mapPageForm_buttonPrevious
                enabled: false
                opacity: 0
            }
            PropertyChanges {
                target: mp_map
                map_currentState: "map_initialPosition"
            }
            PropertyChanges {
                target: mapPageForm_boxImages
                state: "bi_draw_robot"
            }
        },
        State {
            name: "mp_initialOrientation"
            StateChangeScript {
                script: console.log("estoy en mp_initialOrientation")
            }
            StateChangeScript {
                script: mp_map.canvas.requestPaint()
            }
            PropertyChanges {
                target: mapPage
                mapPageForm_previousState: "mp_initialPosition"
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
                text: qsTr("Siguiente")
            }
            PropertyChanges {
                target: mapPageForm_buttonPrevious
                enabled: true
                opacity: 1
                text: qsTr("Anterior")
            }
            PropertyChanges {
                target: mp_map
                map_currentState: "map_initialOrientation"
            }
            PropertyChanges {
                target: mapPageForm_boxImages
                state: "bi_nothing"
            }
        },
        State {
            name: "selectAction"
            StateChangeScript {
                script: console.log("estoy en selectAction")
            }
            StateChangeScript {
                script: mp_map.canvas.requestPaint()
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
                target: mapPageForm_buttonPrevious
                enabled: true
                opacity: 1
                text: qsTr("Anterior")
            }
            PropertyChanges {
                target: mp_map
                map_currentState: "map_selectAction"
            }
            PropertyChanges {
                target: mapPageForm_boxImages
                state: "bi_select_action"
            }
        },
        State {
            name: "mp_goalPosePosition"
            StateChangeScript {
                script: console.log("estoy en mp_goalPosePosition")
            }
            StateChangeScript {
                script: mp_map.canvas.requestPaint()
            }
            StateChangeScript {
                script: mp_map.canvas.clear_internal()
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
                text: qsTr("Siguiente")
            }
            PropertyChanges {
                target: mapPageForm_buttonPrevious
                enabled: true
                opacity: 1
                text: qsTr("Anterior")
            }
            PropertyChanges {
                target: mp_map
                map_currentState: "map_goalPosePosition"
            }
            PropertyChanges {
                target: mapPageForm_boxImages
                state: "bi_draw_robot"
            }
        },
        State {
            name: "mp_goalPoseOrientation"
            StateChangeScript {
                script: mp_map.canvas.requestPaint()
            }
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
            }
            PropertyChanges { target: mapPage; mapPageForm_nextState_text: qsTr("Comprobación")}
            PropertyChanges {
                target: mapPageForm_buttonPrevious
                enabled: true
                opacity: 1
                text: qsTr("Anterior")
            }
            PropertyChanges {
                target: mp_map
                map_currentState: "map_goalPoseOrientation"
            }
            PropertyChanges {
                target: mapPageForm_boxImages
                state: "bi_nothing"
            }
        },
        State {
            name: "mp_drawPath"
            StateChangeScript {
                script: mp_map.canvas.requestPaint()
            }
            PropertyChanges {
                target: mapPage
                mapPageForm_previousState: "selectAction"
                mapPageForm_nextState: ""
            }
            PropertyChanges {
                target: mapPageForm_text
                text: qsTr("Dibuja la trayectoria que quieras realizar")
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
            PropertyChanges { target: mapPage; mapPageForm_nextState_text: qsTr("Comprobación")}
            PropertyChanges {
                target: mapPageForm_buttonPrevious
                enabled: true
                opacity: 1
                text: qsTr("Anterior")
            }
            PropertyChanges {
                target: mp_map
                map_currentState: "map_goalPoseOrientation"
            }
            PropertyChanges {
                target: mapPageForm_boxImages
                state: "bi_draw_path"
            }
        }
    ]
}
