#include "student.h"
#include "schoolyear.h"
Student::Student() : studentID(""),enrolledClass("") , dataOfStudents(new LinkedList_SchoolYears()) {}

Student::Student(string* data) {
    int i = 0;
    this->studentID = data[i++];
    this->lastName = data[i++];
    this->firstName = data[i++];
    this->gender = data[i++];
    string tmp = data[i++];
    this->dateOfBirth = stringToDate(tmp);
    this->socialID = data[i++];
    this->userName = this->studentID;
    this->passWord = defaultPassWordStudent;
    dataOfStudents = new LinkedList_SchoolYears();
}
Student::Student(string* data,const string& nameClass) {
    int i = 0;
    this->studentID = data[i++];
    this->lastName = data[i++];
    this->firstName = data[i++];
    this->gender = data[i++];
    this->dateOfBirth = stringToDate(data[i++]);
    this->socialID = data[i++];
    this->userName = this->studentID;
    this->passWord = defaultPassWordStudent;
    this->enrolledClass = nameClass;
    dataOfStudents = new LinkedList_SchoolYears();
}

bool Student::operator !=(const Student& other) const{
    return this->studentID != other.studentID;
}
string Student::getStudentID() const{
    return studentID;
}

string Student::getEnrolledClass() const {
    return enrolledClass;
}

LinkedList_SchoolYears* Student::getListSchoolYearsOfSchool() const{
    return dataOfStudents;
}

NodeStudent::NodeStudent() {}

NodeStudent::NodeStudent(const Student& student) : data(student), next(nullptr) {}
LinkedList_Students::LinkedList_Students(): head(nullptr), tail(nullptr) {}
