#ifndef STUDENT_H
#define STUDENT_H
#include"course.h"
class Student
{
// private:
public:
    LinkedList_Courses enrolledCoures;
    string enrolledclass;
    string studentID;
    string no;
    string firstName;
    string lastName;
    string gender;
    string dateOfBirth;
    string socialID;

public:
    Student(string* data);
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
