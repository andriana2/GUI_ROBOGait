import QtQuick 2.15

SelectPatientForm {
    addPatient.onClicked: {

        applicationFlow.register_patient_push()
    }

}
