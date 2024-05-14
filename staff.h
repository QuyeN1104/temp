#ifndef STAFF_H
#define STAFF_H
#include"course.h"
  class Staff{
    private:
        void change_idCourse(Course &x,string newIdCourse);
        void change_nameCourse(Course &x,string newNameCourse);
        void change_className(Course &x,string newClassName);
        void change_teacherName(Course &x,string newTeacherName);
        void change_numCredits(Course &x, int newNumCredits);
        void change_session(Course &x,string newSession);
        void change_dayofWeek(Course &x,string newDayofWeek);
        void change_maxStudents(Course &x,int newMaxStudens);
    };

#endif // STAFF_H
