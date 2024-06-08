#pragma once
#include "library.h"

class User {
protected:
    string firstName, lastName , userName, passWord;
    Date dateofBirth;
    string gender;
    // bool isStaff;
    string socialID;
public:
    User();
    User(string firstName, string lastName, string userName, string passWord, Date dateofBirth, string gender, string socialID);
    bool changePassWord(string oldPass, string newPass, string confirmNewPass);
};
struct NodeUser {
    User data;
    NodeUser* next;
    NodeUser(User user);
};
struct LinkedList_Users {
    NodeUser* head, * tail;
    LinkedList_Users();
};
