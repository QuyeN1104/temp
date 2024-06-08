#include "student.h"
#include "schoolyear.h"
Student::Student() : studentID(""),enrolledClass("") {}
bool Student::operator !=(const Student& other) const{
    return this->studentID != other.studentID;
}
NodeStudent::NodeStudent() {}
NodeStudent::NodeStudent(Student student) : data(student), next(nullptr) {}
LinkedList_Students::LinkedList_Students(): head(nullptr), tail(nullptr) {}
