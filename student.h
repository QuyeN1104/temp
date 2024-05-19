#ifndef STUDENT_H
#define STUDENT_H
#include"linkedlist_courses.h"
#include"library.h"
class Student
{
private:
    LinkedList_Courses enrolledCoures;
    string enrolledclass;
    string id;

public:
    Student();
};

#endif // STUDENT_H
