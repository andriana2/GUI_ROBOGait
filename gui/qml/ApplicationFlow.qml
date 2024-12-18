import QtQuick 2.15

ApplicationFlowForm {
    id: applicationFlow
    state: "Home"

    home.buttonStart.onClicked: {
        mystackview.push(ip)
        // mystackview.push(menu_app)
        applicationFlow.state = "ip"
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
                backButton.opacity: 1
                backButton.enabled: false
                logo.sourceSize.width: 70
                logo.sourceSize.height: 50
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
