#ifndef CLASS_H
#define CLASS_H
#include"student.h"
class Class
{
private:
    string nameClass;
    LinkedList_Students ListStudents;
public:
    Class();
    Class(string name);
};
struct NodeClass{
    Class data;
    NodeClass* next;
    NodeClass(Class Class);
};
struct LinkedList_Classes{
    NodeClass *head, *tail;
    LinkedList_Classes();
};

#endif // CLASS_H
