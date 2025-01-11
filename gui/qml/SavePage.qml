import QtQuick 2.15

SavePageForm {

    property int state_save_page: state_save_page

    states: [
        State {
            name: "out_save"
            when: visible_value === 1
            StateChangeScript {
                script: {
                    console.log("estoy en saliendo por eso me pregunta que hacer si guardar sin cambios")
                }
            }
            PropertyChanges {
                target: text_header
                visible: true
            }
        },
        State {
            name: "save"
            when: visible_value === 2
            StateChangeScript {
                script: {
                    console.log("estoy en guardar")
                }
            }
            PropertyChanges {
                target: text_header
                visible: true
            }
        },
        State {
            name: "save_again"
            when: visible_value === 3
            StateChangeScript {
                script: {
                    console.log("estoy en guardar de nuevo")
                    clearImageSource();
                }
            }
            PropertyChanges {
                target: text_header
                visible: false
            }
        }
    ]
}
