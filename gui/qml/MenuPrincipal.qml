import QtQuick 2.15

MenuForm {

    teledirigido_mouse_area.onClicked: {
        applicationFlow.teledirigido_push()
    }
    mapa_mouse_area.onClicked: {
        applicationFlow.map_path_push()
    }

    // mapa{
    //     MouseArea{
    //         anchors.fill: parent
    //         onClicked: {

    //             applicationFlow.teledirigido_push()
    //         }
    //     }
    // }

}
