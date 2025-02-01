import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    property alias canvas: canvas
    property alias area: area
    property string map_currentState: map_currentState
    property alias imageDisplay: imageDisplay

    ErrorRectangle {
        id: errorPopup
        anchors.centerIn: parent
        errorRectangleTextError.text: "Error: Has puesto el robot en una posicion donde esta prohibido."
    }

    // RowLayout {
    //     z: canvas.z + 1
    //     id: botones
    //     anchors.horizontalCenter: parent.horizontalCenter
    //     Button {
    //         text: 'Clear'
    //         onClicked: canvas.clear()
    //     }
    //     Button {
    //         text: 'Paint'
    //         onClicked: {
    //             mapInfo.setScreenSize(imageDisplay.width, imageDisplay.height)
    //             canvas.enablePainting = true
    //         }
    //     }
    //     Button {
    //         text: 'Exit'
    //     }
    // }

    Rectangle {
        id: mapa
        width: 2 * parent.width / 3
        height: parent.height
        anchors.bottom: parent.bottom
        anchors.top: parent.top
        anchors.left: parent.left
        color: "#518bb7"
        Image {
            id: imageDisplay
            width: Math.min(parent.width,
                            parent.height * imageDisplay.sourceSize.width
                            / imageDisplay.sourceSize.height)
            height: Math.min(parent.height,
                             parent.width * imageDisplay.sourceSize.height
                             / imageDisplay.sourceSize.width)
            anchors.centerIn: parent
            visible: true
            fillMode: Image.PreserveAspectCrop
            source: mapInfo.imgSource
        }
    }

    Canvas {
        id: canvas

        width: imageDisplay.width
        height: imageDisplay.height
        anchors.centerIn: mapa

        property var points: []
        property bool startPointExecuted: false

        property int lastX: -1
        property int lastY: -1
        property bool circleDrawn: false
        property bool enablePainting: false
        property real scale: 0.2

        property var imageRobotWithArrow: Image {
            source: "../../images/robot_with_arrow.png" // Ruta a tu imagen
        }

        property var imageRobot: Image {
            source: "../../images/robot.png" // Ruta a tu imagen
        }

        Connections {
            target: mapInfo
            function onOrientationChanged() {
                canvas.requestPaint();
            }
            function onFinalPathOrientationChanged() {
                canvas.requestPaint();
            }
        }

        function drawAndValidateImage(x, y, orientation) {
            var ctx = getContext('2d');
            // ctx.clearRect(0, 0, width, height); // Limpiar el Canvas antes de dibujar

            var scaledWidth, scaledHeight;
            if (orientation === 0.0) {
                scaledWidth = imageRobot.width * scale;
                scaledHeight = imageRobot.height * scale;
                ctx.drawImage(
                            imageRobot,
                            x - scaledWidth / 2,
                            y - scaledHeight / 2,
                            scaledWidth,
                            scaledHeight
                            );
                // console.log("Posición: X=" + x + " Y=" + y);

                if (map_currentState === "map_initialPosition")
                {
                    mapInfo.setPositionScreen(x, y);
                    circleDrawn = true;

                    if (mapInfo.checkPixelBlack(mapInfo.originalPosition.x, mapInfo.originalPosition.y)) {
                        errorPopup.open();
                        console.log("Es negro");
                        clear();
                    } else {
                        console.log("Es blanco");
                    }
                }

                else if (map_currentState === "map_goalPosePosition")
                {
                    mapInfo.setFinalScreenPosition(x, y);
                    circleDrawn = true;
                    console.log(" lastX " + lastX + " lastY " + lastY  + " mapInfoOriginalX " + mapInfo.finalPathPosition.x+ " mapInfoOriginalY " + mapInfo.finalPathPosition.y)

                    if (mapInfo.checkPixelBlack(mapInfo.finalPathPosition.x, mapInfo.finalPathPosition.y)) {
                        errorPopup.open();
                        console.log("Es negro");
                        clear();
                    } else {
                        console.log("Es blanco");
                    }
                }

            } else {
                scaledWidth = imageRobotWithArrow.width * scale;
                scaledHeight = imageRobotWithArrow.height * scale;
                ctx.save(); // Guardar el estado actual del contexto
                ctx.translate(x, y); // Trasladar el origen al punto (x, y)
                ctx.rotate((360 - orientation) * Math.PI / 180); // Rotar el contexto en radianes
                // console.log("Orientacion en MAP.QML " + orientation);
                ctx.drawImage(
                            imageRobotWithArrow,
                            -scaledWidth / 2, // Ajustar la posición para centrar la imagen
                            -scaledHeight / 2,
                            scaledWidth,
                            scaledHeight
                            );
                ctx.restore();
            }
        }
        function drawPath(x, y){
            var ctx = getContext("2d")
            // ctx.clearRect(0, 0, width, height) // Limpiar el lienzo

            if (points.length > 1) {
                ctx.beginPath()
                ctx.strokeStyle = "black"
                ctx.lineWidth = 2

                ctx.moveTo(points[0].x, points[0].y)
                for (var i = 1; i < points.length; i++) {
                    ctx.lineTo(points[i].x, points[i].y)
                }
                ctx.stroke()
            }
        }

        onPaint: {
            var ctx = getContext('2d');
            switch (map_currentState) {
            case "map_initialPosition":
                console.log("map_initialPosition")
                if(mapInfo.positionScreen.x !== 0 && mapInfo.positionScreen.y !== 0)
                {
                    ctx.clearRect(0, 0, width, height);
                    drawAndValidateImage(mapInfo.positionScreen.x, mapInfo.positionScreen.y, 0.0);
                }
                else
                {
                    if (!enablePainting || lastX === -1 || lastY === -1 || circleDrawn === true) {
                        return;
                    }
                    ctx.clearRect(0, 0, width, height);
                    drawAndValidateImage(lastX, lastY, 0.0);
                }
                break;
            case "map_initialOrientation":
                console.log("map_initialOrientation")
                ctx.clearRect(0, 0, width, height);
                console.log("Orientation: " + mapInfo.orientation);
                mp_map.canvas.enablePainting = false
                drawAndValidateImage(mapInfo.positionScreen.x, mapInfo.positionScreen.y, mapInfo.orientation);
                break;
            case "map_selectAction":
                console.log("map_selectAction")
                ctx.clearRect(0, 0, width, height);
                drawAndValidateImage(mapInfo.positionScreen.x, mapInfo.positionScreen.y, mapInfo.orientation);
                break;

            case "map_goalPosePosition":
                if(mapInfo.finalPathPosition.x !== 0 && mapInfo.finalPathPosition.y !== 0)
                {
                    ctx.clearRect(0, 0, width, height);
                    drawAndValidateImage(mapInfo.positionScreen.x, mapInfo.positionScreen.y, mapInfo.orientation);
                    drawAndValidateImage(mapInfo.finalScreenPosition.x, mapInfo.finalScreenPosition.y, 0.0);
                }
                else {
                    console.log("map_goalPosePosition")
                    console.log("enablePainting: " + enablePainting + " lastX " + lastX + " lastY " + lastY  + " circleDrawn " + circleDrawn)
                    ctx.clearRect(0, 0, width, height);
                    drawAndValidateImage(mapInfo.positionScreen.x, mapInfo.positionScreen.y, mapInfo.orientation);
                    circleDrawn = false
                    if (!enablePainting || lastX === -1 || lastY === -1 || circleDrawn === true) {
                        return;
                    }
                    drawAndValidateImage(lastX, lastY, 0.0);
                }
                break;

            case "map_goalPoseOrientation":
                console.log("map_goalPoseOrientation")
                ctx.clearRect(0, 0, width, height);
                mp_map.canvas.enablePainting = false
                drawAndValidateImage(mapInfo.positionScreen.x, mapInfo.positionScreen.y, mapInfo.orientation);
                drawAndValidateImage(mapInfo.finalScreenPosition.x, mapInfo.finalScreenPosition.y, mapInfo.finalPathOrientation);
                break;
            case "map_drawPath":
                console.log("map_drawPath")
                ctx.clearRect(0, 0, width, height);
                drawAndValidateImage(mapInfo.positionScreen.x, mapInfo.positionScreen.y, mapInfo.orientation);
                drawPath(mapInfo.positionScreen.x, mapInfo.positionScreen.y);

                break;
            default:
                console.log("Estado no reconocido: ", map_currentState);
                break;
            }
        }

        MouseArea {
            id: area
            anchors.fill: parent
            onPressed: (mouse) =>  {
                           if(map_currentState === "map_drawPath" && canvas.enablePainting)
                           {
                               if (canvas.startPointExecuted === false) {
                                   // Dibuja línea desde el último punto guardado hasta el nuevo punto inicial
                                   canvas.points = [{x: mapInfo.positionScreen.x, y: mapInfo.positionScreen.y}]
                               } else {
                                   // Si no hay último punto, inicia con el punto actual
                                   canvas.points = [{x: mouseX, y: mouseY}]
                               }
                               canvas.requestPaint()
                           }
                           else{
                               if (canvas.enablePainting) {
                                   canvas.lastX = mouseX;
                                   canvas.lastY = mouseY;
                                   canvas.requestPaint();
                               }
                           }
                       }
            onPositionChanged: (mouse) => {
                                   if(map_currentState === "map_drawPath" && canvas.enablePainting)
                                   {
                                       canvas.points.push({x: mouseX, y: mouseY})
                                       mapInfo.addInfoImageOriginal(mouseX, mouseY)
                                       canvas.requestPaint()
                                   }
                               }
            onReleased: {
                canvas.enablePainting = false;  // Desactiva la pintura cuando se suelta el clic
            }
        }


        function clear() {
            var ctx = getContext('2d');
            ctx.clearRect(0, 0, width, height);
            lastX = -1;
            lastY = -1;
            circleDrawn = false;
            if (map_currentState === "map_initialPosition")
                mapInfo.setPositionScreen(0, 0);
            else if (map_currentState === "map_goalPosePosition")
            {
                mapInfo.setFinalPathPosition(0, 0);
                drawAndValidateImage(mapInfo.positionScreen.x, mapInfo.positionScreen.y, mapInfo.orientation);
            }
            canvas.requestPaint();
        }

        function clear_internal() {
            var ctx = getContext('2d');
            ctx.clearRect(0, 0, width, height);
            lastX = -1;
            lastY = -1;
            circleDrawn = false;
            if (map_currentState === "map_drawPath")
            {
                canvas.points = []
            }
            canvas.requestPaint();
        }
    }
}




// import QtQuick 2.15
// import QtQuick.Controls 2.15
// import QtQuick.Layouts 1.15
// import "extras"

// Item {
// anchors.fill: parent

// property alias clear:clear
// property alias exit: exit
// property alias canvas: canvas
// property alias area: area
// RowLayout {
//     z: canvas.z + 1
//     id: botones
//     anchors.horizontalCenter: parent.horizontalCenter
//     Button{
//         id:clear
//         text: 'Clear'
//     }
//     Button{
//         id: exit
//         text: 'Exit'
//     }
// }
// Canvas {
//     id:canvas
//     anchors.fill: parent
//     property int lastX: 0
//     property int lastY: 0
//     // function clearPaint()
//     MouseArea{
//         id: area
//         anchors.fill: parent

//     }
//     onPaint: {
//             var ctx = getContext('2d');
//             ctx.lineWidth = 5;
//             ctx.beginPath();
//             ctx.moveTo(canvas.lastX, canvas.lastY);
//             canvas.lastX = area.mouseX;
//             canvas.lastY = area.mouseY;
//             ctx.lineTo(canvas.lastX, canvas.lastY);
//             ctx.stroke();
//         }



// }

// }




// Item {

//     // property alias clear:clear
//     // property alias exit: exit
//     property alias canvas: canvas
//     property alias area: area
//     RowLayout {
//         z: canvas.z + 1
//         id: botones
//         anchors.horizontalCenter: parent.horizontalCenter
//         Button{
//             // id:clear
//             text: 'Clear'
//             onClicked: canvas.clear()
//         }
//         Button{
//             // id: exit
//             text: 'Exit'
//         }
//     }
//     Canvas {
//         id:canvas
//         anchors.fill: parent
//         property int lastX: 0
//         property int lastY: 0
//         function clear(){
//             var ctx = getContext('2d');
//             ctx.reset();
//             canvas.requestPaint();
//         }
//         // function clearPaint()
//         MouseArea{
//             id: area
//             anchors.fill: parent
//             onPressed: {
//                 canvas.lastX = area.mouseX;
//                 canvas.lastY = area.mouseY;
//             }
//             onPositionChanged: {
//                 canvas.requestPaint();
//             }

//         }
//         onPaint: {
//             var ctx = getContext('2d');
//             ctx.lineWidth = 5;
//             ctx.beginPath();
//             ctx.moveTo(canvas.lastX, canvas.lastY);
//             canvas.lastX = area.mouseX;
//             canvas.lastY = area.mouseY;
//             ctx.lineTo(canvas.lastX, canvas.lastY);
//             ctx.stroke();
//         }
// Cargar y dibujar la imagen cuando esté disponible
// onPaint: {
//     var ctx = getContext('2d');

//     ctx.lineWidth = 5;
//     ctx.strokeStyle = "red";
//     ctx.beginPath()
//     ctx.moveTo(lastX, lastY);
//     lastX = area.mouseX; // Ajustar posición para la zona limitada
//     lastY = area.mouseY;
//     ctx.lineTo(lastX, lastY);
//     ctx.stroke()
// }
//     }

// }











// Canvas {
//     id: canvas

//     width: imageDisplay.width
//     height: imageDisplay.height
//     anchors.centerIn: mapa

//     property int lastX: -1 // Valor inicial fuera del lienzo
//     property int lastY: -1 // Valor inicial fuera del lienzo
//     property bool circleDrawn: false
//     property bool enablePainting: false

//     // Función para limpiar el lienzo
//     function clear() {
//         var ctx = getContext('2d');
//         ctx.clearRect(0, 0, width, height); // Limpiar el lienzo
//         canvas.requestPaint();
//         lastX = -1
//         lastY = -1
//         circleDrawn = false; // Restablecer el estado de dibujo
//         // enablePainting = false;
//     }

//     onPaint: {
//         var ctx = getContext('2d');

//         if (!enablePainting || lastX === -1 || lastY === -1 || circleDrawn === true) {
//             return; // No dibujar si no está habilitado el modo de pintura o ya se dibujó un círculo
//         }

//         ctx.lineWidth = 15;
//         ctx.strokeStyle = "red";  // Color de la pluma
//         ctx.fillStyle = "red";


//         var radius = 5; // Radio del círculo

//         // Dibujar un círculo en la posición donde se hizo clic
//         ctx.beginPath();
//         ctx.arc(lastX, lastY, radius, 0, Math.PI * 2); // Dibuja el círculo
//         ctx.fill();
//         ctx.stroke();
//         console.log("LastX: " + lastX + " LastY: " + lastY )
//         mapInfo.setPositionScreen(lastX,lastY)
//         circleDrawn = true; // Marcar que el círculo fue dibujado

//         if(mapInfo.checkPixelBlack())
//         {
//             errorPopup.visible = true
//             console.log("Es negro");
//             clear()
//         }
//         else
//             console.log("Es blanco");
//     }

//     MouseArea {
//         id: area
//         anchors.fill: parent
//         onPressed: {
//             if (canvas.enablePainting) {
//                 canvas.lastX = mouseX; // Ajustar posición para la zona limitada
//                 canvas.lastY = mouseY; // Ajustar posición para la zona limitada
//                 canvas.requestPaint(); // Solicitar que se repinte el lienzo
//             }
//         }
//     }
// }




