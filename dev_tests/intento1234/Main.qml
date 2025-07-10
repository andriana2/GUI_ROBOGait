import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window {
    // width: 640
    // height: 480
    visible: true
    title: qsTr("Hello World")
    Rectangle {
        visible: true
        width: 500
        height: 400

        // ScrollView para contener el ListView
        ScrollView {
            anchors.fill: parent
            clip: true

            // ListView para mostrar los elementos
            ListView {
                id: listView
                model: stringHandler.model  // Modelo que se enlaza con el StringHandler de C++

                delegate: Item {
                    width: listView.width
                    height: 70

                    Rectangle {
                        width: parent.width
                        height: 60
                        color: "#ffffff"
                        border.color: "#cccccc"
                        radius: 10

                        Row {
                            anchors.fill: parent
                            spacing: 20
                            anchors.margins: 10

                            Text {
                                text: modelData  // Se accede al modelo de datos
                                font.pixelSize: 18
                                color: "#000000"
                                anchors.verticalCenter: parent.verticalCenter
                            }

                            Button {
                                text: "Editar"
                                anchors.verticalCenter: parent.verticalCenter
                                onClicked: console.log("Editar", modelData)
                            }

                            Button {
                                text: "Borrar"
                                anchors.verticalCenter: parent.verticalCenter
                                onClicked: console.log("Borrar", modelData)
                            }
                        }
                    }
                }
            }
        }
    }
}
