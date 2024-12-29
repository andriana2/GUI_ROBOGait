import QtQuick 2.15
import QtQuick.Controls 2.15

JoystickForm {
    id:joyStick
    property int offset:30;

    signal dirChanged(string direction, string angulo)
    signal pressed()
    signal released()

    // Eventos del MouseArea
    mouseAreaJoystick.onPressed: {
        joyStick.pressed()
        // console.log("Presed");
    }

    mouseAreaJoystick.onPositionChanged: {
        var dx = mouseAreaJoystick.mouseX - totalArea.width / 2
        var dy = mouseAreaJoystick.mouseY - totalArea.height / 2
        var distance = Math.sqrt(dx * dx + dy * dy)

        // Limit the distance to the radius of the totalArea
        var maxDistance = totalArea.radius - stick.width / 2

        // Only move the stick if it's within the allowed radius
        if (distance <= maxDistance) {
            stick.x = mouseAreaJoystick.mouseX - stick.width / 2
            stick.y = mouseAreaJoystick.mouseY - stick.height / 2
        } else {
            // If the distance exceeds the allowed radius, move the stick to the edge
            var ratio = maxDistance / distance
            stick.x = totalArea.width / 2 + dx * ratio - stick.width / 2
            stick.y = totalArea.height / 2 + dy * ratio - stick.height / 2
        }
        var linearVelocity = dy / totalArea.height * 2.0  // Velocidad lineal (hacia adelante/atrás)
        var angularVelocity = dx / totalArea.width * 2.0  // Velocidad angular (giro)

        joyStick.dirChanged(linearVelocity, angularVelocity)
        // var rad = totalArea.radius
        // rad = rad * rad

        // var xDist = mouseAreaJoystick.mouseX - (totalArea.x + totalArea.radius)
        // xDist = xDist * xDist

        // var yDist = mouseAreaJoystick.mouseY - (totalArea.y + totalArea.radius)
        // yDist = yDist * yDist

        // var dist = xDist + yDist

        // if (rad < dist) {
        //     return
        // }

        // var oldX = stick.x
        // var oldY = stick.y
        // stick.x = mouseAreaJoystick.mouseX - stick.radius
        // stick.y = mouseAreaJoystick.mouseY - stick.radius

        // var dir = ""

        // if (stick.y >= totalArea.radius - stick.radius - joyStick.offset &&
        //         stick.y + stick.height <= totalArea.radius + stick.radius + joyStick.offset) {
        //     if (stick.x + stick.radius > totalArea.x + totalArea.radius) {
        //         dir = "R"
        //     } else if (stick.x < totalArea.x + totalArea.radius) {
        //         dir = "L"
        //     }
        // } else if (stick.x >= totalArea.radius - stick.radius - joyStick.offset &&
        //            stick.x + stick.width <= totalArea.radius + stick.radius + joyStick.offset) {
        //     if (stick.y + stick.radius > totalArea.y + totalArea.radius) {
        //         dir = "D"
        //     } else if (stick.y < totalArea.y + totalArea.radius) {
        //         dir = "U"
        //     }
        // } else if (stick.y < totalArea.radius - stick.radius) {
        //     if (stick.x + stick.radius > totalArea.x + totalArea.radius) {
        //         dir = "R"
        //     } else if (stick.x < totalArea.x + totalArea.radius) {
        //         dir = "L"
        //     }
        //     dir = dir + "U"
        // } else if (stick.y + stick.radius >= totalArea.radius + stick.radius) {
        //     if (stick.x + stick.radius > totalArea.x + totalArea.radius) {
        //         dir = "R"
        //     } else if (stick.x < totalArea.x + totalArea.radius) {
        //         dir = "L"
        //     }
        //     dir = dir + "D"
        // }

        // joyStick.dirChanged(dir)
        // Tedirigido.handleDirChanged(dir)
    }



    mouseAreaJoystick.onReleased: {
        stick.x = totalArea.width / 2 - stick.radius
        stick.y = totalArea.height / 2 - stick.radius
        joyStick.released()
        // console.log("UNPresed");

    }
}

// // Item {
// //     id:joyStick;
// //     property int offset:30;

// //     signal dirChanged(string direction);
// //     signal pressed();
// //     signal released();

// //     Rectangle {
// //         id:totalArea
// //         color:"gray"
// //         radius: parent.width/2
// //         opacity: 0.5
// //         width:parent.width;height:parent.height
// //     }

// //     Rectangle{
// //         id:stick
// //         width:totalArea.width/2; height: width
// //         radius: width/2
// //         x: totalArea.width/2 - radius;
// //         y: totalArea.height/2 - radius;
// //         color:"black"
// //     }

// //     MouseArea{
// //         id:mouseArea
// //         anchors.fill: parent

// //         onPressed: {
// //             joyStick.pressed();
// //         }
// //         onContainsMouseChanged: {
// //             //(x-center_x)^2 + (y - center_y)^2 < radius^2
// //             //if stick need to remain inside larger circle
// //             //var rad = (totalArea.radius - stick.radius);
// //             //if stick can go outside larger circle
// //             var rad = totalArea.radius;
// //             rad =  rad * rad;

// //             // calculate distance in x direction
// //             var xDist = mousex - (totalArea.x + totalArea.radius);
// //             xDist = xDist * xDist;

// //             // calculate distance in y direction
// //             var yDist = mousey - (totalArea.y + totalArea.radius);
// //             yDist = yDist * yDist;

// //             //total distance for inner circle
// //             var dist = xDist + yDist;

// //             //if distance if less then radius then inner circle is inside larger circle
// //             if( rad < dist) {
// //                 return;
// //             }

// //             //center of larger circle
// //             var oldX = stick.x; var oldY = stick.y;
// //             stick.x = mousex - stick.radius;
// //             stick.y = mousey - stick.radius;

// //             //using L R U D LU RU LD RD for describe direction
// //             var dir="";

// //             //check if Right or left direction,
// //             //by checking if inner circle's y is near center of larger circle
// //             if( stick.y >= totalArea.radius - stick.radius - joyStick.offset
// //                     && stick.y+stick.height <= totalArea.radius + stick.radius + joyStick.offset) {
// //                 if( stick.x + stick.radius > totalArea.x + totalArea.radius) {
// //                     dir = "R";
// //                 } else if( stick.x < totalArea.x + totalArea.radius) {
// //                     dir = "L";
// //                 }
// //             }
// //             //check if Up or Down direction,
// //             //by checking if inner circle's x is near center of larger circle
// //             else if( stick.x >= totalArea.radius - stick.radius - joyStick.offset
// //                     && stick.x + stick.width <= totalArea.radius + stick.radius + joyStick.offset) {
// //                 if( stick.y + stick.radius > totalArea.y + totalArea.radius) {
// //                     dir = "D";
// //                 } else if( stick.y < totalArea.y + totalArea.radius) {
// //                     dir = "U";
// //                 }
// //             }
// //             //check if Up Left or Up Right direction,
// //             //by checking if inner circle is near one of top corner of larger circle
// //             else if( stick.y < totalArea.radius - stick.radius ) {
// //                 if( stick.x + stick.radius > totalArea.x + totalArea.radius) {
// //                     dir = "R";
// //                 } else if( stick.x < totalArea.x + totalArea.radius) {
// //                     dir = "L";
// //                 }
// //                 dir = dir +"U";
// //             }
// //             //check if Down Left or Down Right direction,
// //             //by checking if inner circle is near one of bottom corner of larger circle
// //             else if ( stick.y + stick.radius >= totalArea.radius + stick.radius ) {
// //                 if( stick.x + stick.radius > totalArea.x + totalArea.radius) {
// //                     dir = "R";
// //                 } else if( stick.x < totalArea.x + totalArea.radius) {
// //                     dir = "L";
// //                 }
// //                 dir = dir +"D";
// //             }

// //             joyStick.dirChanged(dir);
// //         }

// //         onReleased: {
// //             //snap to center
// //             stick.x = totalArea.width /2 - stick.radius;
// //             stick.y = totalArea.height/2 - stick.radius;

// //             joyStick.released();
// //         }
// //     }
// // }
