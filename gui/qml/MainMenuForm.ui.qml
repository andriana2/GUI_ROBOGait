import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "extras"

Rectangle {
    id: rectangle
    color: "#518bb7"
    border.color: "#ffffff"
    property alias select_patient_mouse_area: select_patient_mouse_area
    property alias select_map_mouse_area: select_map_mouse_area
    property alias hacer_mapa_mouse_area: hacer_mapa_mouse_area
    property alias mapa_mouse_area: mapa_mouse_area
    property alias manualControl_mouse_area: manualControl_mouse_area

    Column {
        anchors.verticalCenter: parent.verticalCenter
        anchors.verticalCenterOffset: -60
        anchors.horizontalCenter: parent.horizontalCenter
        spacing: 40

        Row {
            spacing: 60
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {
                id: select_map
                width: 150
                height: 150
                color: "transparent"

                Image {
                    id: select_map_image
                    anchors.fill: parent
                    source: "../images/menu/select_map.png"
                    fillMode: Image.PreserveAspectCrop
                }

                MouseArea {
                    id: select_map_mouse_area
                    anchors.fill: parent
                }
            }

            Rectangle {
                id: select_patient
                width: 150
                height: 150
                color: "transparent"

                Image {
                    id: select_patient_image
                    anchors.fill: parent
                    source: "../images/menu/select_patient.png"
                    fillMode: Image.PreserveAspectCrop
                }

                MouseArea {
                    id: select_patient_mouse_area
                    anchors.fill: parent
                }
            }
        }

        Row {
            spacing: 60
            anchors.horizontalCenter: parent.horizontalCenter

            Rectangle {
                id: manualControl_button
                width: 150
                height: 150
                color: "transparent"

                Image {
                    id: manualControl
                    anchors.fill: parent
                    source: "../images/menu/manual_control.png"
                    fillMode: Image.PreserveAspectCrop
                }

                MouseArea {
                    id: manualControl_mouse_area
                    anchors.fill: parent
                }
            }

            Rectangle {
                id: mapa
                width: 150
                height: 150
                color: "transparent"

                Image {
                    id: testImage
                    anchors.fill: parent
                    source: "../images/menu/image_test.png"
                    fillMode: Image.PreserveAspectCrop
                }

                MouseArea {
                    id: mapa_mouse_area
                    anchors.fill: parent
                }
            }

            Rectangle {
                id: hacer_mapa
                width: 150
                height: 150
                color: "#235c87"

                Text {
                    id: text3
                    color: "#ffffff"
                    text: qsTr("HACER MAPA")
                    anchors.centerIn: parent
                    font.pixelSize: 24
                }

                MouseArea {
                    id: hacer_mapa_mouse_area
                    anchors.fill: parent
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:1.1;height:480;width:640}D{i:4}D{i:5}D{i:3}D{i:7}
D{i:8}D{i:6}D{i:2}D{i:11}D{i:12}D{i:10}D{i:14}D{i:15}D{i:13}D{i:17}D{i:18}D{i:16}
D{i:9}D{i:1}
}
##^##*/

