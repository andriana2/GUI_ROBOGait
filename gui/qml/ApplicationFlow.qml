import QtQuick 2.15

ApplicationFlowForm {
    id: applicationFlow
    state: "Home"

    home.buttonStart.onClicked: {
        mystackview.push(ip)
        // mystackview.push(menu_app)
    }
    function backButton()
    {
        mystackview.pop()
        applictionFlow.state = applicationFlow.previousState
    }
    function confirmButton() {

        applicationFlow.state = "Insert"
    }
    function menu_push(){
        mystackview.push(menu_app)

    }
    function teledirigido_push()
    {
        mystackview.push(teledirigido)
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
        },
        State {
            name: "teledirigido"
            PropertyChanges {
                target:applicationFlow
                previousState: "menu_app"
            }
        }
    ]


}
