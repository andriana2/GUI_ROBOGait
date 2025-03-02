import QtQuick 2.15
import "extras"


ApplicationFlowForm {
    id: applicationFlow
    state: "login"

    function backButton()
    {
        mystackview.pop()
        applicationFlow.state = applicationFlow.previousState
    }


    // ! [State]
    states: [
        State{
            name: "login"
            PropertyChanges {
                target: toolbar
                backButton.opacity: 0
                backButton.enabled: false
                saveButton.opacity: 0
                saveButton.enabled: false
            }
            PropertyChanges {
                target: mystackview
                anchors.top: toolbar.bottom
            }
        },
        State {
            name: "sign_in"
            StateChangeScript {
                script: stringHandler.menu_page(0)
            }
            PropertyChanges {
                target: toolbar
                backButton.opacity: 0
                backButton.enabled: false
                saveButton.opacity: 0
                saveButton.enabled: false
                logo.opacity: 0
                logo.enabled: false
                title.opacity: 0
                title.enabled: false
            }
            PropertyChanges {
                target: mystackview
                anchors.top: toolbar.bottom
            }
        },
        State {
            name: "guest"
            // when: stringHandler.mapping === 1
            StateChangeScript {
                script: {
                    console.log("teledirigido_mapping")
                }
            }
            PropertyChanges {
                target:applicationFlow
                previousState: "menu_app"
            }
            PropertyChanges {
                target: mystackview
                anchors.top: toolbar.bottom
            }
            PropertyChanges {
                target: toolbar
                saveButton.opacity: 1
                saveButton.enabled: true
                backButton.opacity: 1
                backButton.enabled: true
            }
        }
    ]


}
