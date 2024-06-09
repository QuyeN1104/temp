#include "schoolyear.h"
#include "semester.h"

// Constructor mặc định của SchoolYear
SchoolYear::SchoolYear() : name("") , listSemestersOfYear(new LinkedList_Semesters()) {}

// Constructor của SchoolYear với tên
SchoolYear::SchoolYear(const string& name) : name(name), listSemestersOfYear(new LinkedList_Semesters()) {}

bool SchoolYear::operator !=(const SchoolYear& other) const{
    return this->name != other.name;
}
// Constructor của NodeSchoolYear
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
