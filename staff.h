#ifndef STAFF_H
#define STAFF_H
#include"course.h"
  class Staff{
    private:
        void change_idCourse(Course &x,string newIdCourse){
            x.idCourse = newIdCourse;
        }
        void change_nameCourse(Course &x,string newNameCourse){
            x.nameCourse = newNameCourse;
        }
        void change_className(Course &x,string newClassName){
            x.className = newClassName;
        }
        void change_teacherName(Course &x,string newTeacherName){
            x.teacherName = newTeacherName;
        }
        void change_numCredits(Course &x, int newNumCredits){
            x.numCredits = newNumCredits;
        }
        void chang_session(Course &x,string newSession){
            x.session = newSession;
        }
    };

#endif // STAFF_H
