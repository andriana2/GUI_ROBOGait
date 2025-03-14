import QtQuick 2.15

SignInForm {
    id: singin
    
    ErrorRectangle {
        id: errorPopup
        anchors.centerIn: parent
        errorRectangleTextError.text: "Error: Has dejado campos vacíos"
        visible: false
    }

    sip_login_button.onClicked: {
        register_page.login_push()
    }

    sip_guest_button.onClicked: {
        register_page.guest_push()
    }
    sip_singIn_button.onClicked: {
        if (nameField.text === "" || lastnameField.text === "" || usernameField.text === "" || passwordField.text === "" || repeatpasswordField.text === "") {
            errorPopup.errorRectangleTextError.text = "Error: Has dejado campos vacíos"
            errorPopup.visible = true
        } else if (!/^[a-zA-Z]+$/.test(nameField.text)) {
            errorPopup.errorRectangleTextError.text = "Error: El nombre solo debe contener letras"
            errorPopup.visible = true
        } else if (!/^[a-zA-Z]+$/.test(lastnameField.text)) {
            errorPopup.errorRectangleTextError.text = "Error: El apellido solo debe contener letras"
            errorPopup.visible = true
        } else if (passwordField.text.length < 8) {
            errorPopup.errorRectangleTextError.text = "Error: La contraseña debe tener al menos 8 caracteres"
            errorPopup.visible = true
        } else if (!passwordField.text.match(/[A-Z]/)) {
            errorPopup.errorRectangleTextError.text = "Error: La contraseña debe contener al menos una letra mayúscula"
            errorPopup.visible = true
        } else if (!passwordField.text.match(/[a-z]/)) {
            errorPopup.errorRectangleTextError.text = "Error: La contraseña debe contener al menos una letra minúscula"
            errorPopup.visible = true
        } else if (!passwordField.text.match(/[0-9]/)) {
            errorPopup.errorRectangleTextError.text = "Error: La contraseña debe contener al menos un número"
            errorPopup.visible = true
        } else if (!passwordField.text.match(/[\W_]/)) {
            errorPopup.errorRectangleTextError.text = "Error: La contraseña debe contener al menos un carácter especial"
            errorPopup.visible = true
        } else if (passwordField.text !== repeatpasswordField.text) {
            errorPopup.errorRectangleTextError.text = "Error: Las contraseñas no coinciden"
            errorPopup.visible = true
        } else {
            errorPopup.visible = false
            console.log("Registrarse presionado")
            // Proceed with registration
        }
    }


}
