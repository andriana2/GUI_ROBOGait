import QtQuick 2.15
import QtQuick.Controls 2.15
import "extras"

Rectangle {
    id: rectangle
    // width: 1300
    // height: 700
    color: "#518bb7"
    // property alias mapButton: mapButton
    // // property alias mapEdit: mapEdit
    // // property alias mapDelete: mapDelete
    // property alias listView: listView

    // Título
    Text {
        id: text1
        text: qsTr("SELECCIONE UN PACIENTE")
        color: "#ffffff"
        font.pixelSize: 30
        horizontalAlignment: Text.AlignHCenter
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 1
    }

    // ScrollView que contiene la lista
    ScrollView {
        id: scrollView
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            bottom: parent.bottom
            margins: 60
        }

        // ListView para mostrar los elementos
        ListView {
            id: listView
            anchors {
                left: parent.left
                right: parent.right
                top: parent.top
                bottom: parent.bottom
                rightMargin: 10
            }
            clip: true
            model: ddbb.patients

            delegate: Item {
                width: listView.width
                height: 70

                Button {
                    id: mapButton
                    width: parent.width
                    height: 60
                    background: Rectangle {
                        color: "#ffffff"
                        border.color: "#cccccc"
                        radius: 10
                    }

                                       // onClicked: {
                                       //     mapInfo.setMapName(model.display); // Mostrará el texto asociado al botón
                                       //     applicationFlow.map_path_push()
                                       // }
                    Text {
                        id: textMapName
                        text: display
                        font.pixelSize: 22
                        anchors.horizontalCenter: parent.horizontalCenter
                        color: "#000000"
                        anchors.verticalCenter: parent.verticalCenter
                    }

                    // Botón de Editar
                    Button {
                        id: mapEdit
                        text: "Editar"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: mapDelete.left
                        anchors.rightMargin: 20
                        //                                                        onClicked: console.log("Editar:", model.name)
                    }

                    // Botón de Borrar
                    Button {
                        id: mapDelete
                        text: "Borrar"
                        anchors.verticalCenter: parent.verticalCenter
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        //                                                        onClicked: listView.model.remove(index)
                    }
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;formeditorZoom:0.75}D{i:1}D{i:3}D{i:2}
}
##^##*/

