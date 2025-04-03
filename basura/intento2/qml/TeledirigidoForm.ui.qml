import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle {
    id: rectangle
    color: "#518bb7"
    property alias giro_izquierda_mouse_area: giro_izquierda_mouse_area
    property alias giro_derecha_mouse_area: giro_derecha_mouse_area
    property alias less_speed_mouse_area: less_speed_mouse_area
    property alias more_speed_mouse_area: more_speed_mouse_area
    property alias stop_mouse_area: stop_mouse_area
    property alias down_mouse_area: down_mouse_area
    property alias up_mouse_area: up_mouse_area

    GridLayout {
        id: grid
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        columns: 2
        columnSpacing: 60

        Rectangle {
            id: manualControl
            width: 250
            height: 250
            //color: Colors.rectangle_color
            color: "#235c87"
            Text {
                id: text1
                color: "#ffffff"
                text: qsTr("TELEDIRIGIDO")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 12
                anchors.horizontalCenter: parent.horizontalCenter
                scale: 2
            }
        }
        Rectangle {
            id: mapa
            width: 250
            height: 250
            //color: Colors.rectangle_color
            color: "#a8efff"

            Image {
                id: up
                width: 40
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                source: "../images/up.png"
                anchors.verticalCenterOffset: -50
                anchors.horizontalCenter: parent.horizontalCenter
                fillMode: Image.PreserveAspectFit
                MouseArea {
                    id: up_mouse_area
                    anchors.fill: parent
                }
            }

            Image {
                id: down
                width: 40
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                source: "../images/down.png"
                anchors.verticalCenterOffset: 50
                anchors.horizontalCenter: parent.horizontalCenter
                fillMode: Image.PreserveAspectFit
                MouseArea {
                    id: down_mouse_area
                    anchors.fill: parent
                }
            }

            Image {
                id: stop
                width: 40
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                source: "../images/x.png"
                anchors.horizontalCenter: parent.horizontalCenter
                fillMode: Image.PreserveAspectFit
                MouseArea {
                    id: stop_mouse_area
                    anchors.fill: parent
                }
            }

            Image {
                id: more_speed
                width: 40
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                source: "../images/up.png"
                anchors.verticalCenterOffset: -90
                anchors.horizontalCenter: parent.horizontalCenter
                fillMode: Image.PreserveAspectFit

                Text {
                    id: text_speed_more
                    text: qsTr("+Speed")
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 12
                    scale: 1.5
                    anchors.horizontalCenterOffset: -70
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                MouseArea {
                    id: more_speed_mouse_area
                    anchors.fill: parent
                }
            }

            Image {
                id: less_speed
                width: 40
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                source: "../images/down.png"
                anchors.verticalCenterOffset: 90
                anchors.horizontalCenter: parent.horizontalCenter
                fillMode: Image.PreserveAspectFit

                Text {
                    id: text_speed_less
                    x: -60
                    y: -167
                    text: qsTr("-Speed")
                    anchors.verticalCenter: parent.verticalCenter
                    font.pixelSize: 12
                    anchors.horizontalCenterOffset: -60
                    scale: 1.5
                    anchors.horizontalCenter: parent.horizontalCenter
                }
                MouseArea {
                    id: less_speed_mouse_area
                    anchors.fill: parent
                }
            }

            Image {
                id: giro_derecha
                width: 40
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                source: "../images/giro_der.png"
                anchors.horizontalCenterOffset: -50
                anchors.horizontalCenter: parent.horizontalCenter
                fillMode: Image.PreserveAspectFit
                MouseArea {
                    id: giro_derecha_mouse_area
                    anchors.fill: parent
                }
            }

            Image {
                id: giro_izquierda
                width: 40
                height: 40
                anchors.verticalCenter: parent.verticalCenter
                source: "../images/giro_izq.png"
                anchors.horizontalCenterOffset: 50
                anchors.horizontalCenter: parent.horizontalCenter
                fillMode: Image.PreserveAspectFit
                MouseArea {
                    id: giro_izquierda_mouse_area
                    anchors.fill: parent
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}D{i:3}D{i:2}D{i:6}D{i:5}D{i:8}D{i:7}D{i:10}
D{i:9}D{i:12}D{i:13}D{i:11}D{i:15}D{i:16}D{i:14}D{i:18}D{i:17}D{i:20}D{i:19}D{i:4}
D{i:1}
}
##^##*/

