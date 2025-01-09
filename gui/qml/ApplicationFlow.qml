import QtQuick 2.15

ApplicationFlowForm {
    id: applicationFlow
    state: "Home"
    property bool visible_image

    home.buttonStart.onClicked: {
        mystackview.push(ip)
        applicationFlow.state = "ip"
        // mystackview.push(teledirigido)
        // applicationFlow.state = "teledirigido"
    }
    function backButton()
    {
        mystackview.pop()
        if (applicationFlow.state === "teledirigido")
        {
            stringHandler.sendStateRemoteControlledHandler(1,0)
                    visible_image = 0
        }
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
        stringHandler.sendStateRemoteControlledHandler(1,1)
        visible_image = 1
        console.log("Imagen a visible 0")
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
