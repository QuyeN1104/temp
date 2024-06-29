#pragma once

#include"library.h"

struct LinkedList_Semesters;
struct LinkedList_Classes;
class SchoolYear {
    friend class Staff;
private:
    string name;
    LinkedList_Classes*  listClassesOfYear;
    LinkedList_Semesters* listSemestersOfYear;
public:
    LinkedList_Classes* getListClassesOfYear() const;
    bool operator !=(const SchoolYear& other) const;
    SchoolYear();
    SchoolYear(const string& name);
    string getNameSchoolYear() const;
    LinkedList_Semesters* getListSemesters() const;
    void deletelistClasses(); // do data của học sinh không cần Class trong SchoolYear nên nếu là Student thì xóa đi
};

struct NodeSchoolYear {
    SchoolYear data;
    NodeSchoolYear* next;
    NodeSchoolYear(const SchoolYear& schoolyear);
    NodeSchoolYear();
};

struct LinkedList_SchoolYears {
    NodeSchoolYear* head, *tail;
    LinkedList_SchoolYears();
};

