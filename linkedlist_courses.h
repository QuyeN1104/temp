#ifndef LINKEDLIST_COURSES_H
#define LINKEDLIST_COURSES_H
#include"course.h"
struct NodeCourse {
    Course data;
    NodeCourse* next;

    NodeCourse(Course course);
};

class LinkedList_Courses
{
private:
    NodeCourse* head;

public:
    LinkedList_Courses();
    ~LinkedList_Courses();

    // void insert(Course course);
    // void display() const;
};

#endif // LINKEDLIST_COURSES_H
