#include "staff.h"
void Staff::change_idCourse(Course course,string newIdCourse){
    course.idCourse = newIdCourse;
}
void Staff::change_nameCourse(Course course,string newNameCourse){
    course.nameCourse = newNameCourse;
}
void Staff::change_className(Course course,string newClassName){
    course.className = newClassName;
}
void Staff::change_teacherName(Course course,string newTeacherName){
    course.teacherName = newTeacherName;
}
void Staff::change_numCredits(Course course, int newNumCredits){
    course.numCredits = newNumCredits;
}
void Staff::change_session(Course course,string newSession){
    course.session = newSession;
}
void Staff::change_dayofWeek(Course course,string newDayofWeek){
    course.dayofWeek = newDayofWeek;
}
void Staff::change_maxStudents(Course course,int newMaxStudens){
    course.maxStudents = newMaxStudens;
}
