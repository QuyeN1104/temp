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
void User::setFirstName(const string& newFirstName) {
    firstName = newFirstName;
}

void User::setLastName(const string& newLastName) {
    lastName = newLastName;
}

void User::setUserName(const string& newUserName) {
    userName = newUserName;
}

void User::setPassWord(const string& newPassWord) {
    passWord = newPassWord;
}

void User::setDateOfBirth(const Date& newDateOfBirth) {
    dateOfBirth = newDateOfBirth;
}

void User::setGender(const string& newGender) {
    gender = newGender;
}

void User::setSocialID(const string& newSocialID) {
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
