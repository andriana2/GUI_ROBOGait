import QtQuick 2.15

ApplicationFlowForm {
    id: applicationFlow
    state: "Home"

    home.buttonStart.onClicked: {
        mystackview.push(ip)
    }
    function backButton()
    {
        mystackview.pop()
        applictionFlow.state = applicationFlow.previousState
    }
    // function confirmButton() {
    //     stack.push(insert)
    //     applicationFlow.state = "Insert"
    // }
    function menu_push(){
        mystackview.push(menu)

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
