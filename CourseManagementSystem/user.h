#ifndef _USER_H_
#define _USER_H_
#include "student.h"
struct Date {
	int day, month, year;
};
class User {
private:
	string name, userName, passWord;
	Date dmy;
	bool sex;
	bool isStaff;
public:
	User();
	void changePassWord();
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
