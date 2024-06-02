#ifndef _USER_H_
#define _USER_H_
#include "student.h"
struct Date {
    int day, month, year;
};
class User {
private:
    string firstName, lastName , userName, passWord;
    Date dayofBirth;
    string gender;
    bool isStaff;
    string socialID;
public:
    User();
    bool changePassWord(string oldPass, string newPass, string confirmNewPass);
};
struct NodeUser {
    User data;
    NodeUser* next;
    //NodeUser(User user);
};
struct LinkedList_User {
    NodeUser* head, * tail;
    //LinkedList_User();
};
#endif // !_USER_H_
