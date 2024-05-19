#ifndef STUDENT_H
#define STUDENT_H
#include"library.h"
#include"course.h"
class Student
{
private:
    LinkedList_Courses enrolledCoures;
    string enrolledclass;
    string id;

public:
    Student();
};
struct NodeStudent{
    Student data;
    NodeStudent* next;
    NodeStudent(Student student);
};
struct LinkedList_Students{
    NodeStudent *head, *tail;
    LinkedList_Students();
};

#endif // STUDENT_H
