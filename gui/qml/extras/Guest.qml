import QtQuick 2.15

GuestForm {
    id: guest
    
    ErrorRectangle {
        id: errorPopup
        anchors.centerIn: parent
        errorRectangleTextError.text: "Error: Has dejado campos vacíos"
        visible: false
    }

    gp_login.onClicked: {
        register_page.login_push()
    }

    gp_singin.onClicked: {
        register_page.sign_in_push()
    }

    gp_guest_button.onClicked: {
        if (nameField.text === "" || lastnameField.text === "") {
            errorPopup.errorRectangleTextError.text = "Error: Has dejado campos vacíos"
            errorPopup.visible = true
        } else if (!/^[a-zA-Z\s]+$/.test(nameField.text)) { // Allow letters and spaces
            errorPopup.errorRectangleTextError.text = "Error: El nombre solo debe contener letras y espacios"
            errorPopup.visible = true
        } else if (!/^[a-zA-Z\s]+$/.test(lastnameField.text)) { // Allow letters and spaces
            errorPopup.errorRectangleTextError.text = "Error: El apellido solo debe contener letras y espacios"
            errorPopup.visible = true
        } else {
            errorPopup.visible = false
            console.log("Iniciar como invitado presionado")
            // Proceed with guest login
        }
    }
}
