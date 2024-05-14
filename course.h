#ifndef COURSE_H
#define COURSE_H
#include"library.h"
class Course
{
    friend class Staff;
public:
    Course();
private:
    string idCourse, nameCourse, className, teacherName;
    int numCredits;
    string dayofWeek;
    string session;
    int maxStudents = 50;
    //		ListStudent listStudent;
};

#endif // COURSE_H
