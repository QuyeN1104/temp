#ifndef CLASS_H
#define CLASS_H
#include"student.h"
class Class
{
private:
    LinkedList_Students ListStudents;
public:
    Class();
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
