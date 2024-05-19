#include "student.h"

Student::Student() {}
NodeStudent::NodeStudent(Student student) : data(student), next(nullptr) {};
LinkedList_Students::LinkedList_Students() : head(nullptr) ,tail(nullptr) {};
