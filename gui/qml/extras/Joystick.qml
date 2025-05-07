import QtQuick 2.15
import QtQuick.Controls 2.15

JoystickForm {
    id:joyStick
    property int offset:30;

    signal dirChanged(double linear, double angular)
    signal pressed()
    signal released()

    // Eventos del MouseArea
    mouseAreaJoystick.onPressed: {
        joyStick.pressed()
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
        var linearVelocity = dy / totalArea.height * -1.0  // Velocidad lineal (hacia adelante/atrás)
        var angularVelocity = dx / totalArea.width * -1.0  // Velocidad angular (giro)

        joyStick.dirChanged(linearVelocity, angularVelocity)
    }



    mouseAreaJoystick.onReleased: {
        stick.x = totalArea.width / 2 - stick.radius
        stick.y = totalArea.height / 2 - stick.radius
        joyStick.released()

    }
}
