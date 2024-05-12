#ifndef COURSE_H
#define COURSE_H

class Course
{
public:
    Course();
private:
    string idCourse,nameCourse,className,teacherName;
    int numCredit;
    string dayOfWeek;
    string Session;
    int maxStudent=50;
    //ListStudent listStudent;
};

#endif // COURSE_H
