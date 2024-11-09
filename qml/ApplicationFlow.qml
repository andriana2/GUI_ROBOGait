import QtQuick 2.15

ApplicationFlowForm {
    id: applicationFlow
    home.buttonStart.onClicked: {
        mystackview.push(menu)
    }
    function backButton()
    {
        mystackview.pop()

    }


}
