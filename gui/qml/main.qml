import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import "extras"


ApplicationWindow {
    // property int xwidth: ConstantVariables.xwidth
    // property int xheight: ConstantVariables.xheight

    // Component.onCompleted: {
    //     console.log("xwidth:", xwidth)
    //     console.log("xheight:", xheight)
    // }
    // width: ConstantVariables.xwidth
    // height: ConstantVariables.xheight

    height: 700
    width: 1300
    visible: true
    title:   qsTr("Robogait")

    ApplicationFlow {
        width: parent.width
        height: parent.height
    }
}
