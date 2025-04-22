import QtQuick 2.15
import QtQuick.Controls 2.15

Page {
    id: signinPage
    property alias su_add_user: addInformation
    property alias su_cancel_test: cancelRegisterPatient
    property alias nameField: nameField
    property alias lastnameField: lastnameField
    property alias ageField: ageField
    property alias weightField: weightField
    property alias heightField: heightField
    property alias descriptionField: descriptionField

    Rectangle {
        id: rectangle
        color: "#518bb7"
        anchors.fill: parent

        ScrollView {
            id: formScroll
            width: 450 + 50
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            clip: true
            ScrollBar.vertical.policy: ScrollBar.AsNeeded

            function focusOnItem(item) {
                // Esperamos un poco a que el teclado aparezca
                Qt.callLater(() => {
                                 contentItem.children.forEach((child, index) => {
                                                                  if (child === item) {
                                                                      formScroll.contentItem.positionViewAtIndex(index, ListView.Center)
                                                                  }
                                                              })
                             })
            }
            Column {
                id: column
                width: 450
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.horizontalCenter
                anchors.leftMargin: -225
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 15
                padding: 50

                Text {
                    id: text1
                    color: "#ffffff"
                    text: qsTr("Registrar paciente")
                    font.pixelSize: 40
                    horizontalAlignment: Text.AlignHCenter
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.styleName: "Medium"
                    padding: 10
                }

                TextArea {
                    id: nameField
                    width: 450
                    height: 40
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: 15
                    placeholderText: qsTr("Nombre")
                    padding: 10
                    background: Rectangle {
                        radius: 10
                        color: "#FFFFFF"
                        border.color: "#CCCCCC"
                    }
                    Keys.onTabPressed: lastnameField.focus = true
                    Keys.onReturnPressed: lastnameField.focus = true
                    onActiveFocusChanged: {
                        if (activeFocus && Qt.inputMethod.visible) {
                            formScroll.focusOnItem(nameField)
                        }
                    }
                }

                TextArea {
                    id: lastnameField
                    width: 450
                    height: 40
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: 15
                    placeholderText: qsTr("Apellidos")
                    padding: 10
                    background: Rectangle {
                        radius: 10
                        color: "#FFFFFF"
                        border.color: "#CCCCCC"
                    }
                    Keys.onTabPressed: ageField.focus = true
                    Keys.onReturnPressed: ageField.focus = true
                    onActiveFocusChanged: {
                        if (activeFocus && Qt.inputMethod.visible) {
                            formScroll.focusOnItem(lastnameField)
                        }
                    }
                }

                TextArea {
                    id: ageField
                    width: 450
                    height: 40
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: 15
                    placeholderText: qsTr("Edad (años)")
                    padding: 10
                    background: Rectangle {
                        radius: 10
                        color: "#FFFFFF"
                        border.color: "#CCCCCC"
                    }
                    Keys.onTabPressed: weightField.focus = true
                    Keys.onReturnPressed: weightField.focus = true
                    onActiveFocusChanged: {
                        if (activeFocus && Qt.inputMethod.visible) {
                            formScroll.focusOnItem(ageField)
                        }
                    }
                }

                TextArea {
                    id: weightField
                    width: 450
                    height: 40
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: 15
                    placeholderText: qsTr("Peso (Kg)")
                    padding: 10
                    background: Rectangle {
                        radius: 10
                        color: "#FFFFFF"
                        border.color: "#CCCCCC"
                    }
                    Keys.onTabPressed: heightField.focus = true
                    Keys.onReturnPressed: heightField.focus = true
                    onActiveFocusChanged: {
                        if (activeFocus && Qt.inputMethod.visible) {
                            formScroll.focusOnItem(weightField)
                        }
                    }
                }

                TextArea {
                    id: heightField
                    width: 450
                    height: 40
                    anchors.horizontalCenter: parent.horizontalCenter
                    font.pointSize: 15
                    placeholderText: qsTr("Altura (cm)")
                    padding: 10
                    background: Rectangle {
                        radius: 10
                        color: "#FFFFFF"
                        border.color: "#CCCCCC"
                    }
                    Keys.onTabPressed: descriptionField.focus = true
                    Keys.onReturnPressed: descriptionField.focus = true

                    onActiveFocusChanged: {
                        if (activeFocus && Qt.inputMethod.visible) {
                            formScroll.focusOnItem(heightField)
                        }
                    }
                }

                ScrollView {
                    width: 450
                    height: 150
                    anchors.horizontalCenter: parent.horizontalCenter
                    clip: true
                    ScrollBar.vertical.policy: ScrollBar.AsNeeded

                    TextArea {
                        id: descriptionField
                        width: parent.width
                        height: parent.height
                        wrapMode: TextEdit.Wrap
                        font.pointSize: 15
                        placeholderText: qsTr("Descripción Patología")
                        padding: 10
                        selectByMouse: true

                        background: Rectangle {
                            radius: 10
                            color: "#FFFFFF"
                            border.color: "#CCCCCC"
                            border.width: 1
                        }
                        Keys.onTabPressed: addInformation.focus = true
                    }
                    onActiveFocusChanged: {
                        if (activeFocus && Qt.inputMethod.visible) {
                            formScroll.focusOnItem(descriptionField)
                        }
                    }
                }

                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 20

                    Button {
                        id: addInformation
                        width: 215
                        height: 40
                        text: qsTr("AÑADIR")
                        font.styleName: "Medium"
                        font.capitalization: Font.AllUppercase
                        font.weight: Font.Light
                        font.bold: true
                        font.pointSize: 19
                        background: Rectangle {
                            radius: 10
                            color: "#aed2ea"
                            border.color: "#aed2ea"
                        }
                    }

                    Button {
                        id: cancelRegisterPatient
                        width: 215
                        height: 40
                        text: qsTr("CANCELAR")
                        font.styleName: "Medium"
                        font.capitalization: Font.AllUppercase
                        font.weight: Font.Normal
                        font.bold: true
                        font.pointSize: 19
                        background: Rectangle {
                            radius: 10
                            color: "#aed2ea"
                            border.color: "#aed2ea"
                        }
                    }
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.75;height:700;width:1300}D{i:4}D{i:5}D{i:7}D{i:9}
D{i:11}D{i:13}D{i:16}D{i:15}D{i:19}D{i:21}D{i:18}D{i:3}D{i:2}D{i:1}
}
##^##*/

