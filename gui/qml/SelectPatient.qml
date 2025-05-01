import QtQuick 2.15

SelectPatientForm {
    addPatient.onClicked: {
        listView.currentIndex = -1
        descriptionPatient.visible = false
        buttonRow.visible = false
        applicationFlow.register_patient_push()
    }
    buttonAccept.onClicked: {

    }
    buttonCancel.onClicked: {
        listView.currentIndex = -1
        descriptionPatient.visible = false
        buttonRow.visible = false
    }

}
