#ifndef LINKEDLIST_STUDENTS_H
#define LINKEDLIST_STUDENTS_H
#include"student.h"
struct NodeStudent{
    Student data;
    NodeStudent* next;
    NodeStudent(Student student);
};
struct LinkedList_Students{
    NodeStudent *head, *tail;
    LinkedList_Students();
};

#endif // LINKEDLIST_STUDENTS_H
