#ifndef _SCHOOLYEAR_H_
#define _SCHOOLYEAR_H_
#include "class.h"
class SchoolYear {
private:
	string name;
	LinkedList_Classes llClass;
public:
	SchoolYear();
};
struct NodeSchoolYear {
	SchoolYear data;
	NodeSchoolYear* next;
	//NodeSchoolYear(SchoolYear schoolyear);
};
struct LinkedsList_SchoolYear {
	NodeSchoolYear* head, * tail;
	//LinkedList_SchoolYear();
};
#endif // !_SCHOOLYEAR_H_