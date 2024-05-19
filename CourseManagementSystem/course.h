#ifndef COURSE_H
#define COURSE_H
#include"library.h"
class Course
{
    friend class Staff;
public:
    Course();
private:
    string idCourse,nameCourse,className,teacherName;
    int numCredits;
    string dayofWeek;
    string session;
    int maxStudents=50;
};
struct NodeCourse{
    Course data;
    NodeCourse* next;
    NodeCourse(Course course);
};
struct LinkedList_Courses{
    NodeCourse *head, *tail;
    LinkedList_Courses();
};

#endif // COURSE_H
