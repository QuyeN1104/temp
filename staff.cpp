#include "staff.h"
void Staff::change_idCourse(Course &x,string newIdCourse){
    x.idCourse = newIdCourse;
}
void Staff::change_nameCourse(Course &x,string newNameCourse){
    x.nameCourse = newNameCourse;
}
void Staff::change_className(Course &x,string newClassName){
    x.className = newClassName;
}
void Staff::change_teacherName(Course &x,string newTeacherName){
    x.teacherName = newTeacherName;
}
void Staff::change_numCredits(Course &x, int newNumCredits){
    x.numCredits = newNumCredits;
}
void Staff::change_session(Course &x,string newSession){
    x.session = newSession;
}
void Staff::change_dayofWeek(Course &x,string newDayofWeek){
    x.dayofWeek = newDayofWeek;
}
void Staff::change_maxStudents(Course &x,int newMaxStudens){
    x.maxStudents = newMaxStudens;
}
