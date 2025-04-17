import QtQuick 2.15
import "extras"

RobotConnectionForm {
    width: parent.width
    height: parent.height

    buttonSearchRobot{
        onClicked:  stringHandler.searchRobotIp()
    }

    InformationRectangle {
        id: infoPopup
        anchors.centerIn: parent
        infoRectangleText.text: ""
    }
    Connections {
        target: stringHandler
        function onStrFindRobotChanged() {
            infoPopup.open()
            infoPopup.infoRectangleText.text = qsTr(stringHandler.strFindRobot)
            if (!infoPopup.__connectedToClick) {
                infoPopup.__connectedToClick = true
                infoPopup.infoRectangleMouseArea.clickedFromPopup.connect(function() {
                    applicationFlow.register_page_push()
                })
            }
        }
    }

}

