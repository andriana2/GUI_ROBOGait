import QtQuick 2.15

SavePageForm {

    property int state_save_page: state_save_page

    states: [
        State {
            name: "out_save"
            when: state_save_page === 1
            // StateChangeScript {
            //     script: {
            //         console.log("estoy en saliendo por eso me pregunta que hacer si guardar sin cambios")
            //     }
            // }
            PropertyChanges {
                target: text_header
                text: "¿Guardar los cambios?"
            }
            PropertyChanges {
                target: no_save
                visible: true
                opacity: 1

            }
        },
        State {
            name: "save"
            when: state_save_page === 2
            // StateChangeScript {
            //     script: {
            //         console.log("estoy en guardar")
            //     }
            // }
            PropertyChanges {
                target: text_header
                text: "Guardar este mapa"
            }
            PropertyChanges {
                target: no_save
                visible: false
                opacity: 0

            }
            PropertyChanges {
                target: save
                anchors.right: cancel.left
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 28
                anchors.rightMargin: 10
            }
        },
        State {
            name: "save_again"
            when: state_save_page === 3
            // StateChangeScript {
            //     script: {
            //         console.log("estoy en guardar de nuevo")
            //     }
            // }
            PropertyChanges {
                target: text_header
                text: "¿Guardar los cambios en este archivo?"
            }
            PropertyChanges {
                target: no_save
                visible: true
                opacity: 1

            }
        }
    ]
}
