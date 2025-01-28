import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    visible: true
    width: 400
    height: 400
    title: "Robot Rotation"

    Rectangle {
        anchors.centerIn: parent
        width: 300
        height: 300
        color: "lightgray"
        radius: width / 2

        // Circle boundary for reference
        Rectangle {
            anchors.centerIn: parent
            width: parent.width
            height: parent.height
            radius: width / 2
            color: "#a6c6de"
            border.color: "#a6c6de"
            border.width: 2
        }

        // Robot Image
        Image {
            id: robotImage
            source: "../../images/robot_with_arrow.svg" // Replace with your robot image path
            width: 200
            height: 200
            anchors.centerIn: parent
            transformOrigin: Item.Center
            rotation: -90

            //            RotationAnimator on rotation {
            //                duration: 200
            //            }
        }

        // Mouse Area for rotation
        MouseArea {
            anchors.fill: parent
            //            onClicked: {
            //                // Calculate angle based on mouse click
            //                let dx = mouse.x - width / 2
            //                let dy = mouse.y - height / 2
            //                let angleDegrees = Math.atan2(dy, dx) * (180 / Math.PI)
            //                robotImage.rotation = angleDegrees
            //                angleDisplay.text = "Ángulo: " + (Math.atan2(dy, dx)).toFixed(2) + " rad"
            //            }
        }

        // Angle Display
        Text {
            id: angleDisplay
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            font.pixelSize: 16
            color: "black"
            text: "Angle: 0 rad"
        }
    }
}
