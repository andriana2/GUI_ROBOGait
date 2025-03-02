import QtQuick 2.15

LoginForm {
    id: login

    lp_singin_botton.onClicked: {
        register_page.sign_in_push()
    }

    lp_guest_botton.onClicked: {
        register_page.guest_push()
    }


}
