#pragma once
#include"library.h"
#include "user.h"
struct LinkedList_SchoolYears;
class Student : public User {
private:
    string studentID;
    string enrolledClass;
    LinkedList_SchoolYears* dataOfStudents;
public:
    Student();
    Student(string* data,string nameClass);
    string getStudentID() const;
    string getEnrolledClass() const;
    LinkedList_SchoolYears* getListSchoolYearsOfSchool() const;
    bool operator !=(const Student& other) const;

};
struct NodeStudent{
    Student data;
    NodeStudent* next;
    NodeStudent();
    NodeStudent(const Student& student);
};

struct LinkedList_Students {
    NodeStudent *head, *tail;
    LinkedList_Students();
};

