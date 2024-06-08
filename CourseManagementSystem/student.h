#pragma once
#include"library.h"
#include "user.h"
struct LinkedList_SchoolYears;
class Student : public User {
public:
    string studentID;
    string enrolledClass;
public:
    LinkedList_SchoolYears* dataOfStudents;
    Student();
    bool operator !=(const Student& other) const;
};
struct NodeStudent{
    Student data;
    NodeStudent* next;
    NodeStudent();
    NodeStudent(Student student);
};

struct LinkedList_Students {
    NodeStudent *head, *tail;
    LinkedList_Students();
};

