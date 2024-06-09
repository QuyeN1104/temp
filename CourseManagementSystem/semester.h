#pragma once
#include"library.h"

struct LinkedList_Courses;

class Semester {
    friend class Staff;
private:
    Date startDate;
    Date endDate;
    LinkedList_Courses* listCoursesOfSemeter;
public:
    Semester();
    Semester(Date startDate, Date endDate);
    bool operator!=(const Semester& other) const;
    Date getStartDate() const;
    Date getEndDate() const;
    LinkedList_Courses* getListCourses() const;
};

struct NodeSemester {
    Semester data;
    NodeSemester *next;
    NodeSemester(const Semester& semester);
};

struct LinkedList_Semesters {
    NodeSemester *head, *tail;
    LinkedList_Semesters();
};

