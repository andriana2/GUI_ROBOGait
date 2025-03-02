import QtQuick 2.15

GuestForm {
    id: guest

    gp_login.onClicked: {
        register_page.login_push()
    }

    gp_singin.onClicked: {
        register_page.sign_in_push()
    }
}
