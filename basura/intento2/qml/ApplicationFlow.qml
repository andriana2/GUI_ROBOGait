import QtQuick 2.15

ApplicationFlowForm {
    id: applicationFlow
    state: "Home"

    home.buttonStart.onClicked: {
        // mystackview.push(ip)
        mystackview.push(menu_app)
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

    //! [State]
    // states: [
    //     State{
    //         name: "Home"
    //         PropertyChanges {
    //             target: applicationFlow

    //         }
    //     }

    // ]


}
