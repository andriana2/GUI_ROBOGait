import QtQuick 2.15
import "extras"


ApplicationFlowForm {
    id: applicationFlow
    state: "login"

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
        }
    ]

}
