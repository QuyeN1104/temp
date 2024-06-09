#pragma once

#include"library.h"

struct LinkedList_Semesters;
class SchoolYear {
    friend class Staff;
private:
    string name;
    LinkedList_Semesters* listSemestersOfYear;
public:
    bool operator !=(const SchoolYear& other) const;
    SchoolYear();
    SchoolYear(const string& name);
    string getNameSchoolYear() const;
    LinkedList_Semesters* getListSemesters() const;
};

struct NodeSchoolYear {
    SchoolYear data;
    NodeSchoolYear* next;
    NodeSchoolYear(const SchoolYear& schoolyear);
};

struct LinkedList_SchoolYears {
    NodeSchoolYear* head, *tail;
    LinkedList_SchoolYears();
};

