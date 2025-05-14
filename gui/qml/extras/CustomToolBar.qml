import QtQuick 2.15

CustomToolBarForm {
    backButton.onClicked: applicationFlow.backButton()
    backButton.states: State {
        name: "pressed"
        when: backButton.pressed
        PropertyChanges {
            target: backButton
            scale: 1.1
        }
    }

    // saveButton.onClicked: applicationFlow.saveButton()
    // saveButton.states: State {
    //     name: "pressed"
    //     when: saveButton.pressed
    //     PropertyChanges {
    //         target: saveButton
    //         scale: 1.1
    //     }
    // }

}

