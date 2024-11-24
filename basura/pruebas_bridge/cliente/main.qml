import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    height: 700
    width: 1300
    visible: true
    title:   qsTr("Ip")
    //color: lightgrey
     property string imagePath: "file:/home/andri/Desktop/app_con_socket/build/Desktop_Qt_6_7_2-Debug/imagen_recibida.jpg"


    Rectangle {
        anchors.fill: parent
        color: "grey"
        Button {
            anchors.centerIn: parent
            id: buttonStart
            text: qsTr("START")
            scale: 2.036
            onClicked:
            {
                receivedImage.visible = false;
                receivedImage.source = "";
                connection.ejecutar_imagen()
                showImageTimer.start()
            }
        }
        Image {
            id: receivedImage
            // source: "file:/home/andri/Desktop/app_con_socket/build/Desktop_Qt_6_7_2-Debug/imagen_recibida.jpg"  // Ruta del archivo de la imagen
            width: 300
            height: 300
            fillMode: Image.PreserveAspectFit
            visible: false
        }

    }
    Timer {
        id: showImageTimer
        interval: 3000 // 3 segundos
        running: false
        repeat: false
        onTriggered: {
            receivedImage.visible = false; // Asegura que el componente esté "apagado"
            receivedImage.source = ""; // Limpia el source para forzar recarga
            receivedImage.source = imagePath; // Vuelve a asignar la ruta
            receivedImage.visible = true; // Activa la visibilidad
        }


    }
}

