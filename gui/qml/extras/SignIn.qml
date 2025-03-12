import QtQuick 2.15

SignInForm {
    id: singin

    sip_login_botton.onClicked: {
        register_page.login_push()
    }

    sip_guest_botton.onClicked: {
        register_page.guest_push()
    }



}
