#ifndef CLASSES_H
#define CLASSES_H
#include"linkedlist_students.h"
class Class
{
private:
    string nameClass;
    LinkedList_Students ListofStudents;
public:

    Class();
};
struct NodeClass{
    Class data;
    NodeClass* next;
    NodeClass(Class Class);
};
struct LinkedList_Classes{
    NodeClass* head, *tail;
    LinkedList_Classes();
};

#endif // CLASSES_H
