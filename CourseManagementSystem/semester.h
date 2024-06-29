#pragma once
#include"library.h"

struct LinkedList_Courses;
struct LinkedList_Marks;
class Semester {
    friend class Staff;
private:
    Date startDate;
    Date endDate;
    string nameSemester;
    LinkedList_Courses* listCoursesOfSemeter;
    LinkedList_Marks* marksOfSemester; // dành cho học sinh
public:
    Semester();
    Semester(Date startDate, Date endDate,string name);
    Semester(const string& name);
    bool operator!=(const Semester& other) const;
    Date getStartDate() const;
    Date getEndDate() const;
    string getNameSemester() const;
    LinkedList_Courses* getListCourses() const;
    LinkedList_Marks* getListMarks() const;
    void initListMarks(); // cấp phát ô nhớ cho danh sách điểm
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

