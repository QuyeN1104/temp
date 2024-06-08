#pragma once
#include"library.h"

struct LinkedList_Courses;

class Semester {
    friend class Staff;
public:
    Semester();
    Semester(Date startDate, Date endDate);
    LinkedList_Courses* listCoursesOfSemeter;
    bool operator!=(const Semester& other) const;
 public:
    Date startDate;
    Date endDate;
};

struct NodeSemester {
    Semester data;
    NodeSemester *next;
    NodeSemester(Semester semester);
};

struct LinkedList_Semesters {
    NodeSemester *head, *tail;
     LinkedList_Semesters();
    // Semester getDataSemester(NodeSemester* node) const ;
};

