import QtQuick 2.15
import "extras"


ApplicationFlowForm {
    id: applicationFlow
    state: "Home"
    property bool visible_image
    property bool visible_save: visible_save = 0
    property int type_save: type_save = -1

    home.buttonStart.onClicked: {
        mystackview.push(ip)
        applicationFlow.state = "ip"
        // mystackview.push(menu_app)
        // applicationFlow.state = "menu_app"
    }
    function backButton()
    {
        console.log("backButton")
        // console.log(type_save)
        // console.log(visible_save)
        if (applicationFlow.state === "teledirigido")
        {
            if (stringHandler.mapping)
            {
                // console.log("estoy en backButton mapping")

                if(stringHandler.saveMap)
                {
                    // console.log("estoy en backButton stringHandler.saveMap")
                    mystackview.pop()
                    applicationFlow.state = applicationFlow.previousState
                    stringHandler.sendStateRemoteControlledHandler(1,0)
                    stringHandler.setNameMap("")
                    visible_image = 0
                    stringHandler.setTypeSaveMap(-1)
                    type_save = -1
                    stringHandler.setSaveMap(0)
                    stringHandler.setMapping(0)
                }
                else
                {
                    // console.log("estoy en backButton !stringHandler.saveMap")
                    if(stringHandler.typeSaveMap === -1)
                    {
                        stringHandler.setTypeSaveMap(1)
                        type_save = 1
                    }
                    else
                    {
                        stringHandler.setTypeSaveMap(3)
                        type_save = 3
                    }
                }
            }
            else
            {
                // console.log("estoy en backButton !mapping")
                mystackview.pop()
                applicationFlow.state = applicationFlow.previousState
            }
        }
        else if (applicationFlow.state === "mapPath")
        {
            // mapInfo.clearInfoImage()
            mystackview.pop()
            applicationFlow.state = applicationFlow.previousState
        }
        else{
            mystackview.pop()
            applicationFlow.state = applicationFlow.previousState
        }

    }
    function saveButton()
    {
        if(!stringHandler.saveMap)
        {
            console.log("saveButton FALSE")
            console.log(type_save)
            console.log(visible_save)

            if (stringHandler.typeSaveMap === 1)
            {
                stringHandler.setTypeSaveMap(0)
                type_save = 0
                visible_save = 1
                stringHandler.setSaveMap(1)
                stringHandler.setNameMap(stringHandler.nameMap) // BUENOO |- |- JIJI
            }
            else
            {
                stringHandler.setTypeSaveMap(2)
                type_save = 2
                visible_save = 1
                stringHandler.setSaveMap(1)
            }

        }
        else
        {
            // if (stringHandler.typeSaveMap === 2)
            // {

            // }

            console.log("saveButton TRUE")
            console.log(type_save)
            console.log(visible_save)
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
        stringHandler.setSaveMap(0)
        visible_image = 1
        console.log("Imagen a visible 0")
        mystackview.push(teledirigido)
        applicationFlow.state = "teledirigido"
    }
    function select_map_push()
    {
        console.log("UUUUUUUUUUUUUUUUUUUUUUUUUUU")
        stringHandler.requestMapName()
        //stringHandler.loadData(["Mapa 1", "Mapa 2", "Mapa 3"])
        mystackview.push(selectMap)
        applicationFlow.state = "selectMap"
    }
    function map_path_push()
    {
        //stringHandler.requestMapName()
        //stringHandler.loadData(["Mapa 1", "Mapa 2", "Mapa 3"])
        mystackview.push(mapPath)
        applicationFlow.state = "mapPath"
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
            name: "menu_app"
            StateChangeScript {
                script: stringHandler.menu_page(1)
            }
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
        },
        State {
            name: "selectMap"
            StateChangeScript {
                script: {
                    console.log("selectMap")
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
                saveButton.opacity: 0
                saveButton.enabled: false
                backButton.opacity: 1
                backButton.enabled: true
            }
        },
        State {
            name: "mapPath"
            StateChangeScript {
                script: {
                    console.log("mapPath")
                }
            }
            PropertyChanges {
                target:applicationFlow
                previousState: "selectMap"
            }
            PropertyChanges {
                target: mystackview
                anchors.top: toolbar.bottom
            }
            PropertyChanges {
                target: toolbar
                saveButton.opacity: 0
                saveButton.enabled: false
                backButton.opacity: 1
                backButton.enabled: true
            }
        }
    ]


}
