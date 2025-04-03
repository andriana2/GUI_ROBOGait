import QtQuick 2.15
import "extras"

MainMenuForm {

    manualControl_mouse_area.onClicked: {
        applicationFlow.manualControl_push()
    }
    mapa_mouse_area.onClicked: {
        // applicationFlow.map_path_push()
        applicationFlow.select_map_push()
    }
    hacer_mapa_mouse_area.onClicked: {
        mapInfo.sendStopProcesses()

    }

    // mapa{
    //     MouseArea{
    //         anchors.fill: parent
    //         onClicked: {

    //             applicationFlow.manualControl_push()
    //         }
    //     }
    // }

}
