import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

MapForm{
    
    // states: [
    //     State {
    //         name: "mapping"
    //         when: customSwitch.checked === false
    //         StateChangeScript {
    //             script: {
    //                 console.log("estoy en mapping")
    //                 clearImageSource()
    //                 stringHandler.setMapping(0)
    //                 stringHandler.sendStateRemoteControlledHandler(0,1)
    //             }
    //         }
    //         PropertyChanges {
    //             target: imageDisplay
    //             visible: false
    //         }
    //         PropertyChanges {
    //             target: save_page
    //             visible: false
    //             opacity: 0
    //         }
    //         // PropertyChanges {
    //         //     target: applicationFlow.toolbar
    //         //     saveButton.opacity: 0
    //         //     saveButton.enabled: false
    //         // }
    //     },
    //     State {
    //         name: "hidden"
    //         when: visible_value === false
    //         StateChangeScript {
    //             script: {
    //                 console.log("estoy en hidden")
    //                 clearImageSource();
    //                 stringHandler.setMapping(1)
    //             }
    //         }
    //         PropertyChanges {
    //             target: imageDisplay
    //             visible: false
    //         }
    //         PropertyChanges {
    //             target: save_page
    //             visible: false
    //             opacity: 0
    //         }
    //     }
    // ]

}
