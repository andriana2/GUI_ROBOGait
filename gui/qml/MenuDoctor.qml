import QtQuick 2.15

MenuDoctorForm {

    mouseAreaSelectUser.onClicked: {
        console.log("Botón presionado mouseAreaSelectUser")
        ddbb.selectAllPatient(ddbb.username)
        applicationFlow.select_patient_push()
    }
    mouseAreaAddUser.onClicked: {
        console.log("Botón presionado mouseAreaAddUser")
        applicationFlow.register_patient_push()
    }
    mouseAreaLogout.onClicked: {
        console.log("Botón presionado mouseAreaLogout")
        ddbb.clear();
        applicationFlow.popFunction()
    }
}
