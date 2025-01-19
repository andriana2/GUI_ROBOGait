import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Item {
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

}




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

