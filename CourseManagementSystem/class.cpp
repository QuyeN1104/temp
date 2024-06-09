#include "class.h"
#include "student.h"
Class::Class() :  nameClass(""), listStudentsOfClass(new LinkedList_Students()) {}
Class::Class(string name) : nameClass(name), listStudentsOfClass(new LinkedList_Students()) {}
bool Class::operator != (const Class& other) const{
    return this->nameClass != other.nameClass;
}
// Getter for nameClass
string Class::getNameClass() const {
    return nameClass;
}

// Getter for listStudents
LinkedList_Students* Class::getListStudents() const {
    return listStudentsOfClass;
}
NodeClass::NodeClass(const Class& Class) : data(Class) , next(nullptr) {}
LinkedList_Classes::LinkedList_Classes() : head(nullptr) , tail(nullptr) {}
