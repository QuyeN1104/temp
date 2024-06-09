#include "user.h"
User::User() : firstName(""), lastName(""), userName(""), passWord(""), gender(""), socialID("") {
    dateOfBirth = {0, 0, 0}; // Khởi tạo ngày sinh mặc định
}

// Các hàm getter
string User::getFirstName() const{
    return firstName;
}
string User::getLastName() const{
    return lastName;
}
string User::getUserName() const{
    return userName;
}
string User::getPassWord() const{
    return passWord;
}
Date User::getDateOfBirth() const{
    return dateOfBirth;
}
string User::getSocialID() const{
    return socialID;
}
string User::getGender() const{
    return gender;
}
// Các hàm setter
void User::setFirstName(const std::string& newFirstName) {
    firstName = newFirstName;
}

void User::setLastName(const std::string& newLastName) {
    lastName = newLastName;
}

void User::setUserName(const std::string& newUserName) {
    userName = newUserName;
}

void User::setPassWord(const std::string& newPassWord) {
    passWord = newPassWord;
}

void User::setDateOfBirth(const Date& newDateOfBirth) {
    dateOfBirth = newDateOfBirth;
}

void User::setGender(const std::string& newGender) {
    gender = newGender;
}

void User::setSocialID(const std::string& newSocialID) {
    socialID = newSocialID;
}

User::User(string firstName, string lastName,string userName, string passWord, Date dateofBirth,
string gender, string socialID): firstName(firstName), lastName(lastName), userName(userName),
    passWord(passWord), dateOfBirth(dateofBirth), gender(gender), socialID(socialID) {}

bool User::changePassWord(string oldPass, string newPass, string confirmNewPass) {
    if (oldPass == this->passWord && newPass == confirmNewPass) {
        this->passWord = newPass;
        return true;
    }
    return false;
}
NodeUser::NodeUser(const User &user) : data(user), next(nullptr) {}
LinkedList_Users::LinkedList_Users() : head(nullptr), tail(nullptr) {}
