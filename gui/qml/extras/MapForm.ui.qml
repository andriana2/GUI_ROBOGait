import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
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




