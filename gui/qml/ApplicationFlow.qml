import QtQuick 2.15
import "extras"


ApplicationFlowForm {
    id: applicationFlow
    state: "Home"
    property bool visible_image
    property bool visible_save: visible_save = 0
    property int type_save: type_save = -1

    home.buttonStart.onClicked: {
        mystackview.push(robot_connection)
        applicationFlow.state = "robot_connection"
        // mystackview.push(menu_app)
        // applicationFlow.state = "menu_app"
    }
    function backButton()
    {
        console.log("backButton")
        // console.log(type_save)
        // console.log(visible_save)
        if (applicationFlow.state === "manualControl")
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
                stringHandler.sendStateRemoteControlledHandler(1,0)

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
    function popFunction()
    {
        mystackview.pop()
        applicationFlow.state = applicationFlow.previousState
    }
    function popToLogin() {
        console.log("_________________estoy en el estado: " + applicationFlow.state)
        while (applicationFlow.state !== "register_page" && mystackview.depth > 1) {
            mystackview.pop();
            applicationFlow.state = applicationFlow.previousState;
            console.log("_________________estoy en el estado: " + applicationFlow.state)
        }
    }

    function popToHome() {
        // console.log("_________________estoy en el estado: " + applicationFlow.state)
        while (applicationFlow.state !== "Home" && mystackview.depth > 1) {
            mystackview.pop();
            applicationFlow.state = applicationFlow.previousState;
            // console.log("_________________estoy en el estado: " + applicationFlow.state)
        }
        stringHandler.errorConnection = false
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
        // if (applicationFlow.state === "select_patient")
        //     popFunction()
        // if (applicationFlow.state === "register_patient")
        //     popFunction()
        mystackview.push(menu_app)
        console.log("roleChanged cambió a: -" + ddbb.role + "-");
        applicationFlow.state = "menu_app"
    }
    function menu_doctor_push(){
        mystackview.push(menu_doctor)
        applicationFlow.state = "menu_doctor"
    }
    function register_patient_push(){
        mystackview.push(register_patient)
        applicationFlow.state = "register_patient"
    }
    function select_patient_push(){
        mystackview.push(select_patient)
        applicationFlow.state = "select_patient"
    }
    function register_page_push(){

        mystackview.push(register_page)
        applicationFlow.state = "register_page"

        // // harcodeado
        // ddbb.role =("doctor")
        // ddbb.username = "mariaRosa"
        // // menu_push()
        // mystackview.push(menu_app)
        // console.log("roleChanged cambió a: -" + ddbb.role + "-");
        // applicationFlow.state = "menu_app"
    }
    function manualControl_push()
    {
        stringHandler.setSaveMap(0)
        visible_image = 1
        console.log("Imagen a visible 0")
        mystackview.push(manualControl)
        applicationFlow.state = "manualControl"
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
            StateChangeScript {
                script: ddbb.clear()
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
                config.opacity: 0
                config.enabled: false
                username.opacity: 0
                username.enabled: false
            }
            PropertyChanges {
                target: bottomBar
                state: "nothing_cbb"
            }
            PropertyChanges {
                target: mystackview
                anchors.top: toolbar.bottom
                anchors.bottom: parent.bottom
            }
        },
        State {
            name: "robot_connection"
            PropertyChanges {
                target:applicationFlow
                previousState: "Home"
            }
            StateChangeScript {
                script: ddbb.clear()
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
                config.opacity: 0
                config.enabled: false
                username.opacity: 0
                username.enabled: false
            }
            PropertyChanges {
                target: bottomBar
                state: "onlyBattery"
            }
            PropertyChanges {
                target: mystackview
                anchors.top: toolbar.bottom
                anchors.bottom: bottomBar.top
                // anchors.bottom: parent.bottom
                // anchors.bottom: bottomBar.bottom
            }
        },
        State {
            name: "register_page"
            StateChangeScript {
                // script: stringHandler.menu_doctor(1)
            }
            StateChangeScript {
                script: stringHandler.strFindRobot = ""
            }
            PropertyChanges {
                target:applicationFlow
                previousState: "robot_connection"
            }
            PropertyChanges {
                target: toolbar
                backButton.opacity: 0
                backButton.enabled: false
                saveButton.opacity: 0
                saveButton.enabled: false
                config.opacity: 0
                config.enabled: false
                username.opacity: 0
                username.enabled: false
            }
            PropertyChanges {
                target: bottomBar
                state: "nothing_cbb"
            }
            PropertyChanges {
                target: mystackview
                anchors.top: toolbar.bottom
                anchors.bottom: bottomBar.top
            }
        },
        State {
            name: "menu_app"
            StateChangeScript {
                script: stringHandler.menu_page(1)
            }
            StateChangeScript {
                script: mapInfo.clearInfoImage() // this clear the map info container
            }
            StateChangeScript { // eliminar cuando este todo el funcionamiento
                script: stringHandler.strFindRobot = ""
            }
            PropertyChanges {
                target:applicationFlow
                previousState: "register_page"
            }
            PropertyChanges {
                target: toolbar
                backButton.opacity: 0
                backButton.enabled: false
                saveButton.opacity: 0
                saveButton.enabled: false
                config.opacity: 1
                config.enabled: true
                username.opacity: 1
                username.enabled: true
            }
            PropertyChanges {
                target: bottomBar
                state: stringHandler.stateBottomBar
            }
            PropertyChanges {
                target: mystackview
                anchors.top: toolbar.bottom
                anchors.bottom: bottomBar.top
            }
        },
        State {
            name: "manualControl"
            // when: stringHandler.mapping === 1
            StateChangeScript {
                script: {
                    console.log("manualControl_mapping")
                }
            }
            PropertyChanges {
                target:applicationFlow
                previousState: "menu_app"
            }
            PropertyChanges {
                target: toolbar
                saveButton.opacity: 1
                saveButton.enabled: true
                backButton.opacity: 1
                backButton.enabled: true
                config.opacity: 1
                config.enabled: true
                username.opacity: 1
                username.enabled: true
            }
            PropertyChanges {
                target: bottomBar
                state: "onlyBattery"
            }
            PropertyChanges {
                target: mystackview
                anchors.top: toolbar.bottom
                anchors.bottom: bottomBar.top
            }
        },
        State {
            name: "select_patient"
            StateChangeScript {
                // script: stringHandler.menu_page(1)
            }
            PropertyChanges {
                target:applicationFlow
                previousState: "menu_app"

            }
            PropertyChanges {
                target: toolbar
                backButton.opacity: 1
                backButton.enabled: true
                saveButton.opacity: 0
                saveButton.enabled: false
                config.opacity: 1
                config.enabled: true
                username.opacity: 1
                username.enabled: true
            }
            PropertyChanges { target: bottomBar; state: "onlyBattery" }
            PropertyChanges {
                target: mystackview
                anchors.top: toolbar.bottom
                anchors.bottom: bottomBar.top
            }

        },
        State {
            name: "register_patient"
            StateChangeScript {
                // script: stringHandler.menu_page(1)
            }
            PropertyChanges {
                target:applicationFlow
                previousState: "select_patient"
            }
            PropertyChanges {
                target: toolbar
                backButton.opacity: 1
                backButton.enabled: true
                saveButton.opacity: 0
                saveButton.enabled: false
                config.opacity: 1
                config.enabled: true
                username.opacity: 1
                username.enabled: true
            }
            PropertyChanges {
                target: bottomBar
                state: "onlyBattery"
            }
            PropertyChanges {
                target: mystackview
                anchors.top: toolbar.bottom
                anchors.bottom: bottomBar.top
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
                target: toolbar
                saveButton.opacity: 0
                saveButton.enabled: false
                backButton.opacity: 1
                backButton.enabled: true
                config.opacity: 1
                config.enabled: true
                username.opacity: 1
                username.enabled: true
            }
            PropertyChanges {
                target: bottomBar
                state: "onlyBattery"
            }
            PropertyChanges {
                target: mystackview
                anchors.top: toolbar.bottom
                anchors.bottom: bottomBar.top
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
                target: toolbar
                saveButton.opacity: 0
                saveButton.enabled: false
                backButton.opacity: 1
                backButton.enabled: true
                config.opacity: 1
                config.enabled: true
                username.opacity: 1
                username.enabled: true
            }
            PropertyChanges {
                target: bottomBar
                state: "onlyBattery"
            }
            PropertyChanges {
                target: mystackview
                anchors.top: toolbar.bottom
                anchors.bottom: bottomBar.top
            }
        }
    ]

    ErrorRectangle {
        id: errorPopup
        anchors.centerIn: parent
        errorRectangleTextError.text: qsTr("Error: En la conexión")
        visible: false
        mode: "delayed" // Ensure this property exists in your ErrorRectangle component
    }

    Connections {
        target: stringHandler
        // console.log("HE PASADO POR Connections en ApplicationFlow")
        function onErrorConnectionChanged() {
            // console.log("HE PASADO POR onErrorConnectionChanged() en ApplicationFlow")
            if(stringHandler.errorConnection === true)
            {
                // console.log("HE PASADO POR onErrorConnectionChanged() en ApplicationFlow")
                errorPopup.mode = "delayed"
                errorPopup.errorRectangleTextError.text = qsTr("Error: Perdida de conexion con el servidor")
                errorPopup.visible = true
                mapInfo.clearInfoImage()
                popToHome()
            }
        }
    }


}
