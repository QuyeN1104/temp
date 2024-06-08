#include "user.h"
User::User() : firstName(""), lastName(""), userName(""), passWord(""), gender(""), socialID("") {
    dateofBirth = {0, 0, 0}; // Khởi tạo ngày sinh mặc định
}

User::User(string firstName, string lastName,string userName, string passWord, Date dateofBirth,
string gender, string socialID)
    : firstName(firstName), lastName(lastName), userName(userName), passWord(passWord), dateofBirth(dateofBirth), gender(gender), socialID(socialID) {}
bool User::changePassWord(string oldPass, string newPass, string confirmNewPass) {
    if (oldPass == this->passWord && newPass == confirmNewPass) {
        this->passWord = newPass;
        return true;
    }
    return false;
}
LinkedList_Users::LinkedList_Users() : head(nullptr), tail(nullptr) {}
