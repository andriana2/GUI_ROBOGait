import QtQuick 2.15
import QtQuick.Controls 2.15
import "extras"

RegisterMapForm {
    id: registerPatientForm

    ErrorRectangle {
        id: errorPopup
        anchors.centerIn: parent
        errorRectangleTextError.text: qsTr("Error: Has dejado campos vacíos")
        visible: false
    }

    rm_add_map.onClicked: {
        if (mapNameField.text === "" || descriptionField.text === "") {
            errorPopup.errorRectangleTextError.text = qsTr("Error: Has dejado campos vacíos")
            errorPopup.visible = true
        } else {
            errorPopup.visible = false
            console.log("Añadir información del mapa presionado")
            // Add user information logic here
// TODO crear un addMapInformation en mapInfo o database tiene pinta que la info del mapa ira alli
            // ddbb.addPatient(nameField.text, lastnameField.text, age, weight, height, ddbb.username, descriptionField.text)
    // TODO un push to CreateMap
// applicationFlow.popFunction()
        }
    }

    rm_cancel_test.onClicked: {
        applicationFlow.popFunction()
    }
}
