import QtQuick 2.15
import "extras"

MainMenuForm {

    manualControl_mouse_area.onClicked: {
        applicationFlow.manualControl_push()
    }

    mapa_mouse_area.onClicked: {
        if (stringHandler.stateBottomBar === "MP_cbb")
        {
            mapInfo.setMapName(stringHandler.mapNameTest)
            applicationFlow.map_path_push()
        }
    }
    
    select_map_mouse_area.onClicked: {
        applicationFlow.select_map_push()
        ddbb.selectAllMap()
    }

    select_patient_mouse_area.onClicked: {
        ddbb.selectAllPatient(ddbb.username)
        applicationFlow.select_patient_push()
    }

}
