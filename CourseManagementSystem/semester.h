#pragma once
#include"library.h"

struct LinkedList_Courses;

class Semester {
    friend class Staff;
private:
    Date startDate;
    Date endDate;
    string nameSemester;
    LinkedList_Courses* listCoursesOfSemeter;
public:
    Semester();
    Semester(Date startDate, Date endDate,string name);
    bool operator!=(const Semester& other) const;
    Date getStartDate() const;
    Date getEndDate() const;
    string getNameSemester() const;
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

