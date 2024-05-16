#ifndef STAFF_H
#define STAFF_H
#include"course.h"
  class Staff{
    private:
        void change_idCourse(Course course,string newIdCourse);
        void change_nameCourse(Course course,string newNameCourse);
        void change_className(Course course,string newClassName);
        void change_teacherName(Course course,string newTeacherName);
        void change_numCredits(Course course, int newNumCredits);
        void change_session(Course course,string newSession);
        void change_dayofWeek(Course course,string newDayofWeek);
        void change_maxStudents(Course course,int newMaxStudens);
    };

#endif // STAFF_H
