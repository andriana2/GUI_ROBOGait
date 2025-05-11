import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "extras"

Rectangle {
    id: rectangle
    color: "#518bb7"
    property alias select_patient_mouse_area: select_patient_mouse_area
    property alias select_map_mouse_area: select_map_mouse_area
    // property alias hacer_mapa_mouse_area: hacer_mapa_mouse_area
    property alias mapa_mouse_area: mapa_mouse_area
    property alias manualControl_mouse_area: manualControl_mouse_area

    Column {
        id: column
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
                    opacity: stringHandler.stateBottomBar === "MP_cbb" ? 1 : 0.5

                    source: "../images/menu/image_test.png"
                    fillMode: Image.PreserveAspectCrop
                }

                MouseArea {
                    id: mapa_mouse_area
                    anchors.fill: parent
                }
            }

            // Rectangle {
            //     id: hacer_mapa
            //     width: 150
            //     height: 150
            //     color: "#235c87"

            //     Text {
            //         id: text3
            //         color: "#ffffff"
            //         text: qsTr("HACER MAPA")
            //         anchors.centerIn: parent
            //         font.pixelSize: 24
            //     }

            //     MouseArea {
            //         id: hacer_mapa_mouse_area
            //         anchors.fill: parent
            //     }
            // }
        }
    }
    Image {
        opacity: 0.7
        id: upm
        width: 190
        height: 190
        anchors.left: parent.left
        anchors.top: parent.top
        source: "../images/sponsors/upm.png"
        anchors.topMargin: -60
        anchors.leftMargin: -40
        fillMode: Image.PreserveAspectFit
    }
    Image {
        opacity: 0.7
        id: car
        width: 110
        height: 90
        anchors.left: upm.right
        anchors.top: parent.top
        source: "../images/sponsors/car.png"
        anchors.topMargin: -30
        anchors.leftMargin: -42

        fillMode: Image.PreserveAspectFit
    }
    Image {
        opacity: 0.7
        id: etsidi
        width: 120
        height: 140
        anchors.right: parent.right
        //            height: parent.height < 500 ? 80 : 130
        //            width: parent.width < 500 ? 80 : 130
        anchors.top: parent.top
        source: "../images/sponsors/etsidi.png"
        anchors.rightMargin: 20
        anchors.topMargin: -56

        fillMode: Image.PreserveAspectFit
    }
    Image {
        opacity: 0.7
        id: ministerio
        width: 360
        height: 130
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        source: "../images/sponsors/ministerio.png"
        anchors.leftMargin: -20
        anchors.bottomMargin: -20
        fillMode: Image.PreserveAspectFit
    }

    Text {
        id: explain
        y: 547
        width: 862
        height: 39
        color: "#ffffff"
        text: qsTr("Bienvenido a la aplicación de ROBOGait. Para comenzar, seleccione un mapa y un paciente. Puede acceder al control manual desde esta pantalla. Para más detalles, presione el botón de información.")
        anchors.bottom: parent.bottom
        wrapMode: Text.Wrap
        anchors.bottomMargin: 81
        font.pixelSize: 16
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignTop
        anchors.horizontalCenter: parent.horizontalCenter
    }
    Button {
        id: infoButton
        width: 37
        height: 37
        anchors.verticalCenter: explain.verticalCenter
        anchors.left: explain.right
        anchors.leftMargin: 10
        background: Image {
            source: "../images/icon_app/circle-info-solid.svg"
            fillMode: Image.PreserveAspectFit
        }
               Behavior on scale {
                   NumberAnimation {
                       duration: 150
                       easing.type: Easing.OutQuad
                   }
               }

               // Change scale when pressed/released
               onPressed: scale = 1.2
               onReleased: scale = 1.0
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.75;height:700;width:1300}D{i:4}D{i:5}D{i:3}D{i:7}
D{i:8}D{i:6}D{i:2}D{i:11}D{i:12}D{i:10}D{i:14}D{i:15}D{i:13}D{i:9}D{i:1}D{i:16}D{i:17}
D{i:18}D{i:19}D{i:20}D{i:21}
}
##^##*/

