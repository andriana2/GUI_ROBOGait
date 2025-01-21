import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
    property alias canvas: canvas
    property alias area: area
    property string imageSource: mapInfo.imgSource // Ruta de la imagen


    RowLayout {
        z: canvas.z + 1
        id: botones
        anchors.horizontalCenter: parent.horizontalCenter
        Button{
            text: 'Clear'
            onClicked: canvas.clear()
        }
        Button{
            text: 'Paint'
            onClicked:{
                mapInfo.setScreenSize(imageDisplay.width, imageDisplay.height)
                //stringHandler.setPixelScreen(imageDisplay.width, imageDisplay.height)
                canvas.enablePainting = true
            }

        }
        Button{
            text: 'Exit'
        }
    }

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
            visible: true // Solo visible si hay una fuente válida
            fillMode: Image.PreserveAspectCrop
            source: "../images/my_map.png" // Vinculación directa al valor de stringHandler.imageSource
        }
    }

    Canvas {
        id: canvas

        width: imageDisplay.width
        height: imageDisplay.height
        anchors.centerIn: mapa

        property int lastX: -1 // Valor inicial fuera del lienzo
        property int lastY: -1 // Valor inicial fuera del lienzo
        property bool circleDrawn: false
        property bool enablePainting: false

        // Función para limpiar el lienzo
        function clear() {
            var ctx = getContext('2d');
            ctx.clearRect(0, 0, width, height); // Limpiar el lienzo
            canvas.requestPaint();
            lastX = -1
            lastY = -1
            circleDrawn = false; // Restablecer el estado de dibujo
            // enablePainting = false;
        }

        onPaint: {
            var ctx = getContext('2d');

            if (!enablePainting || lastX === -1 || lastY === -1 || circleDrawn === true) {
                return; // No dibujar si no está habilitado el modo de pintura o ya se dibujó un círculo
            }

            ctx.lineWidth = 15;
            ctx.strokeStyle = "red";  // Color de la pluma
            ctx.fillStyle = "red";


            var radius = 5; // Radio del círculo

            // Dibujar un círculo en la posición donde se hizo clic
            ctx.beginPath();
            ctx.arc(lastX, lastY, radius, 0, Math.PI * 2); // Dibuja el círculo
            ctx.fill();
            ctx.stroke();
            console.log("LastX: " + lastX + " LastY: " + lastY )
            mapInfo.setPositionScreen(lastX,lastY)
            circleDrawn = true; // Marcar que el círculo fue dibujado
        }

        MouseArea {
            id: area
            anchors.fill: parent
            onPressed: {
                if (canvas.enablePainting) {
                    canvas.lastX = mouseX; // Ajustar posición para la zona limitada
                    canvas.lastY = mouseY; // Ajustar posición para la zona limitada
                    canvas.requestPaint(); // Solicitar que se repinte el lienzo
                }
            }
        }
    }
}


// Item {
//     property alias canvas: canvas
//     property alias area: area
//     property string imageSource: "../images/my_map.png" // Ruta de la imagen


//     RowLayout {
//         z: canvas.z + 1
//         id: botones
//         anchors.horizontalCenter: parent.horizontalCenter
//         Button{
//             text: 'Clear'
//             onClicked: canvas.clear()
//         }
//         Button{
//             text: 'Exit'
//         }
//     }
//     Rectangle {
//         id: mapa
//         width: 2 * parent.width / 3
//         height: parent.height
//         anchors.bottom: parent.bottom
//         anchors.top: parent.top
//         anchors.left: parent.left
//         color: "#518bb7"

//         Image {
//             id: imageDisplay
//             width: Math.min(parent.width,
//                             parent.height * imageDisplay.sourceSize.width
//                             / imageDisplay.sourceSize.height)
//             height: Math.min(parent.height,
//                              parent.width * imageDisplay.sourceSize.height
//                              / imageDisplay.sourceSize.width)
//             anchors.centerIn: parent
//             visible: true // Solo visible si hay una fuente válida
//             fillMode: Image.PreserveAspectCrop
//             source: "../images/my_map.png" // Vinculación directa al valor de stringHandler.imageSource
//         }
//     }
//     Canvas {
//         id: canvas

//         width: imageDisplay.width
//         height: imageDisplay.height
//         anchors.centerIn: mapa

//         property int lastX
//         property int lastY
//         property bool circleDrawn: false
//         // property var img: imageSource // Aquí se almacenará la imagen cargada

//         // Función para limpiar el lienzo
//         function clear(){
//             var ctx = getContext('2d');
//             ctx.clearRect(0, 0, width, height); // Limpiar el lienzo
//             canvas.requestPaint();
//             circleDrawn= false
//         }


//         onPaint: {
//             var ctx = getContext('2d');

//             if (circleDrawn) {
//                 return; // Solo dibujar un círculo, si ya se ha dibujado uno, no hacer nada
//             }

//             ctx.lineWidth = 5;
//             ctx.strokeStyle = "red";  // Color de la pluma

//             var radius = 5; // Radio del círculo

//             // Dibujar un círculo en la posición donde se hizo clic
//             ctx.beginPath();
//             ctx.arc(lastX, lastY, radius, 0, Math.PI * 2); // Dibuja el círculo
//             ctx.stroke();

//             circleDrawn = true; // Marcar que el círculo fue dibujado
//         }

//         // Usar una instancia de Image para cargar la imagen

//         MouseArea {
//             id: area
//             anchors.fill: parent
//             onPressed: {
//                 canvas.lastX = mouseX; // Ajustar posición para la zona limitada
//                 canvas.lastY = mouseY; // Ajustar posición para la zona limitada
//             }
//             onPositionChanged: {
//                 canvas.requestPaint();
//             }
//         }
//     }
// }



