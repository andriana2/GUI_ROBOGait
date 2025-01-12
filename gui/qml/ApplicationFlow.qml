import QtQuick 2.15

ApplicationFlowForm {
    id: applicationFlow
    state: "Home"
    property bool visible_image
    property bool visible_save: visible_save = 0
    property int type_save: type_save = -1

    home.buttonStart.onClicked: {
        // mystackview.push(ip)
        // applicationFlow.state = "ip"
        mystackview.push(teledirigido)
        applicationFlow.state = "teledirigido"
    }
    function backButton()
    {
        console.log("backButton")
        console.log(type_save)
        console.log(visible_save)
        if (applicationFlow.state === "teledirigido")
        {
            if(stringHandler.saveMap)
            {
                mystackview.pop()
                applicationFlow.state = applicationFlow.previousState
                stringHandler.sendStateRemoteControlledHandler(1,0)
                visible_image = 0
                stringHandler.setTypeSaveMap(-1)
                type_save = -1
                stringHandler.setSaveMap(0)
            }
            else
            {
                if(type_save === -1)
                {
                    stringHandler.setTypeSaveMap(1)
                    type_save = 1
                    console.log("Estoy en backButton !saveMap y typeSaveMap -1")
                }
                else
                {
                    stringHandler.setTypeSaveMap(3)
                    console.log(type_save)
                    type_save = 3
                    console.log("Estoy en backButton !saveMap y typeSaveMap else")
                }
            }
        }
        else{
            mystackview.pop()
            applicationFlow.state = applicationFlow.previousState
        }
        console.log(type_save)

    }
    function saveButton()
    {
        console.log("saveButton")
        console.log(type_save)
        console.log(visible_save)
        if(!stringHandler.saveMap)
        {
            stringHandler.setTypeSaveMap(2)
            type_save = 2
            visible_save = 1
            stringHandler.setSaveMap(1)
        }
        else
        {
            stringHandler.setTypeSaveMap(0)
            type_save = 0
            visible_save = 1
            stringHandler.setSaveMap(1)
        }
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
        stringHandler.setSaveMap = 0
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
            name: "ip"
            PropertyChanges {
                target:applicationFlow
                previousState: "Home"
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
            name: "menu_app"
            PropertyChanges {
                target:applicationFlow
                previousState: "ip"
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
