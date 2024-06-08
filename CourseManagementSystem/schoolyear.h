#pragma once

#include"library.h"

struct LinkedList_Semesters;
class SchoolYear {
    friend class Staff;
public:
    string name;
    bool operator !=(const SchoolYear& other) const;

public:
    LinkedList_Semesters* listSemestersOfYear;
    SchoolYear();
    SchoolYear(const string& name);
};

struct NodeSchoolYear {
    SchoolYear data;
    NodeSchoolYear* next;
    NodeSchoolYear(const SchoolYear& schoolyear);
};

struct LinkedList_SchoolYears {
    NodeSchoolYear* head, *tail;
    LinkedList_SchoolYears();
    // SchoolYear getDataSchoolYear(NodeSchoolYear* node) const ;
};

