#include "schoolyear.h"
#include "semester.h"
#include"class.h"

// Constructor mặc định của SchoolYear
SchoolYear::SchoolYear() : name("") , listSemestersOfYear(new LinkedList_Semesters()),listClassesOfYear(new LinkedList_Classes()) {}

// Constructor của SchoolYear với tên
SchoolYear::SchoolYear(const string& name) : name(name), listSemestersOfYear(new LinkedList_Semesters()),listClassesOfYear(new LinkedList_Classes()) {}

bool SchoolYear::operator !=(const SchoolYear& other) const{
    return this->name != other.name;
}

LinkedList_Classes* SchoolYear::getListClassesOfYear() const {
    return listClassesOfYear;
}
// Constructor của NodeSchoolYear
NodeSchoolYear::NodeSchoolYear() : data(SchoolYear()) , next(nullptr) {}

NodeSchoolYear::NodeSchoolYear(const SchoolYear& schoolyear) : data(schoolyear), next(nullptr) {}

// Constructor mặc định của LinkedList_SchoolYear
LinkedList_SchoolYears::LinkedList_SchoolYears() : head(nullptr), tail(nullptr) {}

// ham getter
string SchoolYear::getNameSchoolYear() const {
    return name;
}

LinkedList_Semesters* SchoolYear::getListSemesters() const{
    return listSemestersOfYear;
}
void SchoolYear::deletelistClasses(){
    delete listClassesOfYear;
    listClassesOfYear = NULL;
}
