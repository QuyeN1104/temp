#ifndef LINKEDLIST_COURSES_H
#define LINKEDLIST_COURSES_H
#include"course.h"
struct NodeCourse {
    Course data;
    NodeCourse* next;

    NodeCourse(Course course);
};

struct LinkedList_Courses
{ 
    NodeCourse* head, *tail;
    LinkedList_Courses();
};

#endif // LINKEDLIST_COURSES_H
