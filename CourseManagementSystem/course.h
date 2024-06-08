#pragma once
#include"library.h"
struct LinkedList_Students;
class Course  {
    friend class Staff;
public:
    string idCourse, nameCourse, className, teacherName;
    int numCredits;
    string dayofWeek;
    string session;
    int maxStudents = 50;
    LinkedList_Students* listStudentsOfCourse;
public:
    Course();
    Course(string id, string name, string className, string teacherName, int numCredits, string dayofWeek, string session);
     bool operator!=(const Course& other) const;
};

struct NodeCourse {
    Course data;
    NodeCourse* next;
    NodeCourse(Course course);
};

struct LinkedList_Courses {
    NodeCourse *head, *tail;
    // LinkedList_Courses();
    // bool operator !=(const LinkedList_Courses& other) const{
    //     return head != other.head || tail!=other.tail;
    // }
     // Course getDataCourse(NodeCourse* node) const ;
};

