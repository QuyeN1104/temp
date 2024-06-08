#include "class.h"
#include "student.h"
Class::Class() :  nameClass("") {}
Class::Class(string name) : nameClass(name) {}
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
NodeClass::NodeClass(Class Class) : data(Class) , next(nullptr) {}
LinkedList_Classes::LinkedList_Classes() : head(nullptr) , tail(nullptr) {}
// Class LinkedList_Classes::getDataClass(NodeClass* node) const {
//     return node->data;
// }
