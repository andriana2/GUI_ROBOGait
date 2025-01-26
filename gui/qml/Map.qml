import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "extras"

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
            source: imageSource // Vinculación directa al valor de stringHandler.imageSource
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

            if(mapInfo.checkPixelBlack())
            {
                errorPopup.visible = true
                console.log("Es negro");
                clear()
            }
            else
                console.log("Es blanco");
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

    Rectangle {
        id: errorPopup
        width: parent.width * 0.8
        height: 100
        color: "#f8d7da"  // Color rojo claro para indicar error
        border.color: "#f5c6cb"
        radius: 10
        anchors.centerIn: parent
        visible: false  // Oculto por defecto

        Text {
            anchors.centerIn: parent
            text: "Error: Has puesto el robot en una posicion donde esta prohibido."
            color: "#721c24"
            font.pixelSize: 16
        }

        MouseArea {
            anchors.fill: parent
            onClicked: errorPopup.visible = false  // Cierra el popup al hacer clic
        }
    }
}
