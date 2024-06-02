#include "user.h"
User::User() {};
bool User::changePassWord(string oldPass, string newPass, string confirmNewPass) {
    if (oldPass == this->passWord && newPass == confirmNewPass) {
        this->passWord = newPass;
        return true;
    }
    return false;
}
