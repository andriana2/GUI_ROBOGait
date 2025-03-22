import QtQuick 2.15
import QtQuick.Controls 2.15
import "extras"

SigninUserForm {
    id: signinUserForm

    ErrorRectangle {
        id: errorPopup
        anchors.centerIn: parent
        errorRectangleTextError.text: "Error: Has dejado campos vacíos"
        visible: false
    }

    su_add_user.onClicked: {
        if (nameField.text === "" || lastnameField.text === "" || ageField.text === "" || weightField.text === "" || heightField.text === "") {
            errorPopup.errorRectangleTextError.text = "Error: Has dejado campos vacíos"
            errorPopup.visible = true
        } else {
            var age = parseInt(ageField.text);
            var weight = parseFloat(weightField.text);
            var height = parseFloat(heightField.text);

            if (isNaN(age) || isNaN(weight) || isNaN(height)) {
                errorPopup.errorRectangleTextError.text = "Error: Edad, peso y altura deben ser números válidos"
                errorPopup.visible = true
            } else if (age <= 8) {
                errorPopup.errorRectangleTextError.text = "Error: La edad debe ser mayor a 8 años"
                errorPopup.visible = true
            } else if (age > 120) {
                errorPopup.errorRectangleTextError.text = "Error: La edad debe ser menor o igual a 120 años"
                errorPopup.visible = true
            } else if (weight < 20 || weight > 200) {
                errorPopup.errorRectangleTextError.text = "Error: El peso debe estar entre 20 y 200 kg"
                errorPopup.visible = true
            } else if (height < 50 || height > 250) {
                errorPopup.errorRectangleTextError.text = "Error: La altura debe estar entre 50 y 250 cm"
                errorPopup.visible = true
            } else {
                errorPopup.visible = false
                console.log("Añadir información presionado")
                // Add user information logic here
                ddbb.addPatient(nameField.text, lastnameField.text, age, weight, height, ddbb.username)
                applicationFlow.popFunction()
            }
        }
    }

    su_start_test.onClicked: {
        if (nameField.text === "" || lastnameField.text === "" || ageField.text === "" || weightField.text === "" || heightField.text === "") {
            errorPopup.errorRectangleTextError.text = "Error: Has dejado campos vacíos"
            errorPopup.visible = true
        } else {
            var age = parseInt(ageField.text);
            var weight = parseFloat(weightField.text);
            var height = parseFloat(heightField.text);

            if (isNaN(age) || isNaN(weight) || isNaN(height)) {
                errorPopup.errorRectangleTextError.text = "Error: Edad, peso y altura deben ser números válidos"
                errorPopup.visible = true
            } else if (age <= 8) {
                errorPopup.errorRectangleTextError.text = "Error: La edad debe ser mayor a 8 años"
                errorPopup.visible = true
            } else if (age > 120) {
                errorPopup.errorRectangleTextError.text = "Error: La edad debe ser menor o igual a 120 años"
                errorPopup.visible = true
            } else if (weight < 20 || weight > 200) {
                errorPopup.errorRectangleTextError.text = "Error: El peso debe estar entre 20 y 200 kg"
                errorPopup.visible = true
            } else if (height < 50 || height > 250) {
                errorPopup.errorRectangleTextError.text = "Error: La altura debe estar entre 50 y 250 cm"
                errorPopup.visible = true
            } else {
                errorPopup.visible = false
                console.log("Iniciar prueba presionado")
                // Start test logic here
                ddbb.addPatient(nameField.text, lastnameField.text, age, weight, height, ddbb.username)
                applicationFlow.menu_push()
            }
        }
    }
}
