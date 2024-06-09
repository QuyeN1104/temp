#pragma once
#include"library.h"
struct LinkedList_Students;
class Staff;
class Class {
    friend class Staff;
// private:
private:
    string nameClass;
    LinkedList_Students* listStudentsOfClass;
public:
    Class();
    Class(string name);
    bool operator !=(const Class& other) const;
    // Getter for nameClass
    string getNameClass() const;

    // Getter for listStudents
    LinkedList_Students* getListStudents() const;
};
struct NodeClass{
    Class data;
    NodeClass* next;
    NodeClass(const Class& Class);
};
struct LinkedList_Classes{
    NodeClass *head, *tail;
    LinkedList_Classes();
};

