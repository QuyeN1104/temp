#include "user.h"
User::User() {};
void User::changePassWord() {
    string oldPass, newPass, confirmPass;
    bool passwordChanged = false;
    while (!passwordChanged) {
        cout << "Enter old password: ";
        cin >> oldPass;
        if (oldPass == passWord) {
            while (true) {
                cout << "Enter new password: ";
                cin >> newPass;
                cout << "Confirm new password: ";
                cin >> confirmPass;
                if (newPass == confirmPass) {
                    passWord = newPass;
                    cout << "Password changed successfully!" << endl;
                    passwordChanged = true;
                    break;
                }
                else {
                    cout << "New password and confirmation do not match. Please try again." << endl;
                }
            }
        }
        else
            cout << "Old password is incorrect. Please try again." << endl;
    }
}
