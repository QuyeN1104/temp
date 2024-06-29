#pragma once
#include "library.h"

class User {
protected:
    string firstName, lastName , userName, passWord;
    Date dateOfBirth;
    string gender;
    // bool isStaff;
    string socialID;
public:
    User();
    User(string firstName, string lastName, string userName, string passWord, Date dateofBirth, string gender, string socialID);
    int changePassWord(string oldPass, string newPass, string confirmNewPass);
    string getFirstName() const;
    string getLastName() const;
    string getUserName() const;
    string getPassWord() const;
    Date getDateOfBirth() const;
    string getSocialID() const;
    string getGender() const;
    // các hàm setter
    void setFirstName(const string& newFirstName);
    void setLastName(const string& newLastName);
    void setUserName(const string& newUserName);
    void setPassWord(const string& newPassWord);
    void setDateOfBirth(const Date& newDateOfBirth);
    void setGender(const string& newGender);
    void setSocialID(const string& newSocialID);
};
