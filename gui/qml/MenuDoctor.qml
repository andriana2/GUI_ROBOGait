import QtQuick 2.15

MenuDoctorForm {

    mouseAreaSelectUser.onClicked: {
        console.log("Botón presionado mouseAreaSelectUser")
    }
    mouseAreaAddUser.onClicked: {
        console.log("Botón presionado mouseAreaAddUser")
    }
    mouseAreaLogout.onClicked: {
        console.log("Botón presionado mouseAreaLogout")
        applicationFlow.popFunction()
    }
}
