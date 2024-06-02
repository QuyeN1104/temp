#include "student.h"
Student::Student() : no(""), studentID(""), firstName(""), lastName(""), gender(""), dateOfBirth(""), socialID("") {}
Student::Student(string* data){
    int i = 0;
    this->no = data[i++];
    this->studentID = data[i++];
    this->firstName = data[i++];
    this->lastName = data[i++];
    this->gender = data[i++];
    this->dateOfBirth = data[i++];
    this->socialID  = data[i++];
}
NodeStudent::NodeStudent(Student student) : data(student), next(nullptr) {};
LinkedList_Students::LinkedList_Students(): head(nullptr) ,tail(nullptr) {};
