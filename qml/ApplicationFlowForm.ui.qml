import QtQuick 2.15
import QtQuick.Controls 2.15

//import QtQuick.Layouts 2.15
Rectangle {
    id: root
    property alias home: home
    property alias mystackview: mystackview
    property alias ip: ip
    property alias menu: menu
    StackView{
        anchors.fill: parent
        id: mystackview
        initialItem: Home {
            id: home
        }
    }
    Component {
        id: ip
        IP {
        }
    }
    Component {
        id: menu
        MenuForm {

        }
    }
    // Component {
    //     id: Home_
    // }
    // Component {
    //     id: Home_
    // }

    //color: Colors.currentTheme.background
}

/*##^##
Designer {
    D{i:0;autoSize:true;formeditorZoom:0.66;height:480;width:640}D{i:1}
}
##^##*/

