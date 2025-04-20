import QtQuick 2.15
import QtQuick.Controls 2.15
import "extras"

Item {
    id: home
    property alias buttonStart: buttonStart

    Rectangle {
        id: rectangle
        color: "#518bb7"
        anchors.top: home.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right

        // anchors.horizontalCenter: parent.horizontalCenter
        Image {
            id: image
            width: parent.height < 500 ? 150 : 197
            height: width
            anchors.verticalCenter: parent.verticalCenter
            source: "../images/logo.png"
            anchors.horizontalCenterOffset: 0
            anchors.verticalCenterOffset: -110
            anchors.horizontalCenter: parent.horizontalCenter
            fillMode: Image.PreserveAspectFit
        }

        Button {
            id: buttonStart
            height: parent.height < 500 ? 80 : 100
            anchors.top: image.bottom
            anchors.topMargin: parent.height < 500 ? 20 : 40
            anchors.horizontalCenter: parent.horizontalCenter
            width: contentItem.implicitWidth + (parent.height < 500 ? 60 : 80)

            // Definimos los colores
            // property color normalColor: "#ffffff"
            // property color pressedColor: "#00C8FF"  // Color cuando está presionado
            // property color textColor: "#045671"
            // property color borderColor: "#045671"
            background: Rectangle {
                color: buttonStart.down ? "#e9e9e9" : "#aed2ea"
                radius: 15
                border.color: "#e9e9e9"
                border.width: 2

                // Animación solo para el cambio de color
                //                Behavior on color {
                //                    ColorAnimation {
                //                        duration: 100
                //                    } // Duración muy corta para respuesta inmediata
                //                }
            }

            contentItem: Label {
                id: buttonLabel
                text: qsTr("START")
                color: "#518bb7"
                font.pixelSize: rectangle.height < 500 ? 40 : 60
                font.bold: true
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.styleName: "Regular"
                font.weight: Font.Light
                anchors.fill: parent
                padding: 0
            }
        }

        Image {
            id: upm
            width: 190
            height: 190
            anchors.left: parent.left
            anchors.top: parent.top
            source: "../images/sponsors/upm.png"
            anchors.topMargin: -80
            anchors.leftMargin: -40
            fillMode: Image.PreserveAspectFit
        }
        Image {
            id: car
            width: 110
            height: 90
            anchors.left: upm.right
            anchors.top: parent.top
            source: "../images/sponsors/car.png"
            anchors.topMargin: -50
            anchors.leftMargin: -42

            fillMode: Image.PreserveAspectFit
        }
        Image {
            id: etsidi
            width: 120
            height: 140
            anchors.right: parent.right
            //            height: parent.height < 500 ? 80 : 130
            //            width: parent.width < 500 ? 80 : 130
            anchors.top: parent.top
            source: "../images/sponsors/etsidi.png"
            anchors.rightMargin: 20
            anchors.topMargin: -76

            fillMode: Image.PreserveAspectFit
        }
        Image {
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
        //        Image {
        //            id: car
        //            height: parent.height < 500 ? 80 : 130
        //            width: parent.width < 500 ? 80 : 130
        //            anchors.left: upm.right
        //            anchors.top: parent.top
        //            source: "../images/sponsors/car.png"
        //            anchors.leftMargin: -52
        //            anchors.topMargin: parent.height < 500 ? -30 : -50

        //            fillMode: Image.PreserveAspectFit
        //        }
        //        Button {
        //            id: buttonStart
        //            text: qsTr("START")
        //            anchors.verticalCenter: parent.verticalCenter
        //            anchors.verticalCenterOffset: 110
        //            anchors.horizontalCenter: parent.horizontalCenter
        //            focusPolicy: Qt.StrongFocus
        //            z: 0
        //            scale: 4.036
        //        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.5;height:700;width:1300}D{i:2}D{i:3}D{i:6}D{i:7}
D{i:8}D{i:9}D{i:1}
}
##^##*/

