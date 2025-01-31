import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: boxImageForm
    width: 300
    height: 200

    property alias bif_check: bif_check
    property alias bif_ok: bif_ok
    property alias bif_clear: bif_clear
    property alias bif_edit: bif_edit

    property string image_source_edit
    property string image_source_clear
    property string image_source_ok
    property string image_source_check

    Button {
        id: bif_clear
        width: 70
        height: 70
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -50
        anchors.horizontalCenter: parent.horizontalCenter
        background: Image {
            source: boxImageForm.image_source_clear
            fillMode: Image.PreserveAspectFit
        }
    }

    Button {
        id: bif_edit
        width: 70
        height: 70
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -50
        anchors.horizontalCenterOffset: -90
        anchors.horizontalCenter: parent.horizontalCenter
        background: Image {
            source: boxImageForm.image_source_edit
            fillMode: Image.PreserveAspectFit
        }
    }

    Button {
        id: bif_ok
        width: 70
        height: 70
        anchors.verticalCenterOffset: -50
        anchors.horizontalCenter: parent.horizontalCenter
        background: Image {
            source: boxImageForm.image_source_ok
            fillMode: Image.PreserveAspectFit
        }
    }

    Button {
        id: bif_check
        width: 70
        height: 70
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: 50
        anchors.horizontalCenter: parent.horizontalCenter
        background: Image {
            source: boxImageForm.image_source_check
            fillMode: Image.PreserveAspectFit
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:1.5;height:700;width:1300}D{i:1}D{i:2}D{i:3}D{i:4}D{i:5}D{i:6}
}
##^##*/

