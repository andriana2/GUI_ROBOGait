import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle {
    id: rectangle
    // width: 1300
    // height: 700
    color: "#518bb7"
    // property alias mapButton: mapButton
    // property alias mapEdit: mapEdit
    // property alias mapDelete: mapDelete

    // Título
    Text {
        id: text1
        text: qsTr("SELECCIONE UN MAPA")
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
            }
            clip: true
            model: ListModel {
                ListElement {
                    name: "Elemento 1"
                }
                ListElement {
                    name: "Elemento 2"
                }
                ListElement {
                    name: "Elemento 3"
                }
                ListElement {
                    name: "Elemento 4"
                }
                ListElement {
                    name: "Elemento 5"
                }
                ListElement {
                    name: "Elemento 6"
                }
                ListElement {
                    name: "Elemento 7"
                }
                ListElement {
                    name: "Elemento 8"
                }
                ListElement {
                    name: "Elemento 9"
                }
            }

            // Delegate que define cómo se ve cada elemento
            delegate: Item {
                width: listView.width
                height: 70

                Button {
                    id: mapButton
                    width: parent.width
                    height: 60
                    text: ""
                    background: Rectangle {
                        color: "#ffffff"
                        border.color: "#cccccc"
                        radius: 10
                    }

                    // Acción al hacer clic en el Button (Rectangle)
                    //                                        onClicked: {
                    //                                            console.log("Seleccionado:", model.name)
                    //                                        }
                    Row {
                        spacing: 20
                        anchors.fill: parent
                        anchors.margins: 10

                        // Texto del nombre del elemento
                        Text {
                            text: model.name
                            font.pixelSize: 18
                            color: "#000000"
                            anchors.verticalCenter: parent.verticalCenter
                        }

                        // Botón de Editar
                        Button {
                            id: mapEdit
                            text: "Editar"
                            anchors.verticalCenter: parent.verticalCenter
                            //                                                        onClicked: console.log("Editar:", model.name)
                        }

                        // Botón de Borrar
                        Button {
                            id: mapDelete
                            text: "Borrar"
                            anchors.verticalCenter: parent.verticalCenter
                            //                                                        onClicked: listView.model.remove(index)
                        }
                    }
                }
            }
        }
    }
} //Rectangle {//    id: rectangle//    width: 1300//    height: 700//    color: "#518bb7"//    Text {//        id: text1//        x: 514//        width: 311
//        height: 0
//        color: "#ffffff"
//        text: qsTr("SELECCIONE UN MAPA")
//        anchors.verticalCenter: parent.verticalCenter
//        anchors.top: parent.top
//        font.pixelSize: 30
//        horizontalAlignment: Text.AlignHCenter
//        anchors.topMargin: 40
//    }

//    ScrollView {
//        id: scrollView
//        anchors.left: parent.left
//        anchors.right: parent.right
//        anchors.top: parent.top
//        anchors.bottom: parent.bottom
//        anchors.margins: 20
//        anchors.rightMargin: 60
//        anchors.leftMargin: 60
//        anchors.bottomMargin: 60
//        anchors.topMargin: 100

//        ListView {
//            id: listView
//            anchors.verticalCenter: scrollView.verticalCenter
//            anchors.fill: scrollView
//            anchors.horizontalCenter: scrollView.horizontalCenter
//            model: ListModel {
//                ListElement {
//                    name: "Elemento 1"
//                }
//                ListElement {
//                    name: "Elemento 2"
//                }
//                ListElement {
//                    name: "Elemento 3"
//                }
//                ListElement {
//                    name: "Elemento 4"
//                }
//                ListElement {
//                    name: "Elemento 5"
//                }
//                ListElement {
//                    name: "Elemento 6"
//                }
//            }
//            delegate: Item {
//                width: listView.width
//                height: 60
//                Rectangle {
//                    width: parent.width
//                    height: 50
//                    color: "#ffffff"
//                    border.color: "#cccccc"
//                    radius: 5
//                    anchors.margins: 5

//                    RowLayout {
//                        anchors.fill: parent
//                        anchors.margins: 10

//                        // Texto del nombre
//                        Text {
//                            text: model.name
//                            font.pixelSize: 18
//                            //Layout.fillWidth: true
//                        }

//                        // Botón de Editar
//                        Button {
//                            text: "Editar"
//                            //onClicked: console.log("Editar:", model.name)
//                        }

//                        // Botón de Borrar
//                        Button {
//                            text: "Borrar"
//                            //onClicked: listView.model.remove(index)
//                        }
//                    }
//                }
//                //                Row {
//                //                    id: row1
//                //                    spacing: 10
//                //                    Rectangle {
//                //                        width: parent.width
//                //                        height: 50
//                //                        color: "#ffffff"
//                //                        border.color: "#cccccc"
//                //                        radius: 5
//                //                        anchors.margins: 5
//                //                    }
//                //                    Text {
//                //                        text: name
//                //                        font.pixelSize: 18
//                //                        anchors.verticalCenter: parent.verticalCenter
//                //                        //                        Layout.fillWidth: true
//                //                    }
//                //                }
//                //                    RowLayout {
//                //                        anchors.fill: parent
//                //                        anchors.margins: 10

//                //                        // Texto del nombre
//                //                    Text {
//                //                        text: model.name
//                //                        font.pixelSize: 18
//                //                        Layout.fillWidth: true
//                //                    }
//                //                        Button {
//                //                            text: "Editar"
//                //                            //                            onClicked: {
//                //                            //                                console.log("Editar:", model.name)
//                //                            //                            }
//                //                        }

//                //                        // Botón de borrar
//                //                        Button {
//                //                            text: "Borrar"
//                //                            //                            onClicked: {
//                //                            //                                listView.model.remove(index)
//                //                            //                            }
//                //                        }
//                //                    }
//            }
//        }

//        //        ListView {
//        //            id: listView1
//        //            x: 452
//        //            y: 206
//        //            width: 110
//        //            height: 160
//        //            model: ListModel {
//        //                ListElement {
//        //                    name: "Grey"
//        //                    colorCode: "grey"
//        //                }

//        //                ListElement {
//        //                    name: "Red"
//        //                    colorCode: "red"
//        //                }

//        //                ListElement {
//        //                    name: "Blue"
//        //                    colorCode: "blue"
//        //                }

//        //                ListElement {
//        //                    name: "Green"
//        //                    colorCode: "green"
//        //                }
//        //            }
//        //            delegate: Item {
//        //                x: 5
//        //                width: 80
//        //                height: 40
//        //                Row {
//        //                    id: row2
//        //                    spacing: 10
//        //                    Rectangle {
//        //                        width: 40
//        //                        height: 40
//        //                        color: colorCode
//        //                    }

//        //                    Text {
//        //                        text: name
//        //                        anchors.verticalCenter: parent.verticalCenter
//        //                        font.bold: true
//        //                    }
//        //                }
//        //            }
//        //        }
//    }
//}


/*##^##
Designer {
    D{i:0;formeditorZoom:0.5}D{i:1}D{i:3}D{i:2}
}
##^##*/

