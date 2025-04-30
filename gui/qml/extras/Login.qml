import QtQuick 2.15

LoginForm {
    id: login
    
    ErrorRectangle {
        id: errorPopup
        anchors.centerIn: parent
        errorRectangleTextError.text: "Error: Has dejado campos vacíos"
        visible: false
    }

    lp_singin_button.onClicked: {
        // this is to clean the .text
        usernameField.text = ""
        passwordField.text = ""
        register_page.sign_in_push()
    }

    lp_guest_button.onClicked: {
        usernameField.text = ""
        passwordField.text = ""
        register_page.guest_push()
    }

    lp_login_button.onClicked: {
        if (usernameField.text === "" || passwordField.text === "") {
            errorPopup.errorRectangleTextError.text = "Error: Has dejado campos vacíos"
            errorPopup.visible = true
        }else {
            errorPopup.visible = false
            console.log("Iniciar sesión presionado")
            ddbb.login(usernameField.text, passwordField.text)
        }
    }

    Connections {
        target: ddbb
        function onRoleChanged() {
            console.log("⚡ roleChanged cambió a:", ddbb.role);
            usernameField.text = ""
            passwordField.text = ""
            applicationFlow.menu_push()
        }
    }


}
