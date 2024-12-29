import QtQuick 2.15

ApplicationFlowForm {
    id: applicationFlow
    state: "Home"

    home.buttonStart.onClicked: {
        // mystackview.push(ip)
        // applicationFlow.state = "ip"
        mystackview.push(teledirigido)
        applicationFlow.state = "teledirigido"
    }
    function backButton()
    {
        mystackview.pop()
        applicationFlow.state = applicationFlow.previousState
    }
    function confirmButton() {
        applicationFlow.state = "Insert"
    }
    function menu_push(){
        mystackview.push(menu_app)
        applicationFlow.state = "menu_app"

    }
    function teledirigido_push()
    {
        mystackview.push(teledirigido)
        applicationFlow.state = "teledirigido"
    }

    // ! [State]
    states: [
        State{
            name: "Home"
            PropertyChanges {
                target: toolbar
                backButton.opacity: 0
                backButton.enabled: false
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
            name: "ip"
            PropertyChanges {
                target:applicationFlow
                previousState: "Home"
            }
            PropertyChanges {
                target: toolbar
                backButton.opacity: 0
                backButton.enabled: false
            }
            PropertyChanges {
                target: mystackview
                anchors.top: toolbar.bottom
            }
        },
        State {
            name: "menu_app"
            PropertyChanges {
                target:applicationFlow
                previousState: "ip"
            }
            PropertyChanges {
                target: toolbar
                backButton.opacity: 0
                backButton.enabled: false
            }
            PropertyChanges {
                target: mystackview
                anchors.top: toolbar.bottom
            }
        },
        State {
            name: "teledirigido"
            PropertyChanges {
                target:applicationFlow
                previousState: "menu_app"
            }
            PropertyChanges {
                target: mystackview
                anchors.top: toolbar.bottom
            }
        }
    ]


}
