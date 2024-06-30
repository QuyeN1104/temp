#pragma once
#include"library.h"
struct LinkedList_Students;
struct LinkedList_Marks;
class Course  {
    friend class Staff;
private:
    string idCourse, nameCourse, className, teacherName; // className là đặc điểm riêng biệt của mỗi object
    int numCredits;
    string dayofWeek;
    string session;
    int maxStudents = 50;
    LinkedList_Students* listStudentsOfCourse;
public:
    Course();
    Course(string id, string name, string className, string teacherName, int numCredits, string dayofWeek, string session);
    bool operator!=(const Course& other) const;
    string getIdCourse() const;
    string getNameCourse() const;
    string getClassName() const;
    string getTeacherName() const;
    int getNumCredits() const;
    string getDayofWeek() const;
    string getSession() const;
    int getMaxStudents() const;
    LinkedList_Students* getListStudents() const;
};

struct NodeCourse {
    Course data;
    NodeCourse* next;
    NodeCourse(const Course& course);
};
struct LinkedList_Courses {
    NodeCourse *head, *tail;
    LinkedList_Courses();
};



