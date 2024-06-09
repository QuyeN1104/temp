#include "course.h"
#include"student.h"
Course::Course() : idCourse(""), nameCourse(""), className(""), teacherName(""), numCredits(0), dayofWeek(""),
    session(""), maxStudents(50), listStudentsOfCourse(new LinkedList_Students()) {}

Course::Course(string id, string name, string className, string teacherName, int numCredits, string dayofWeek, string session)
    : idCourse(id), nameCourse(name), className(className), teacherName(teacherName), numCredits(numCredits), dayofWeek(dayofWeek),
    session(session), maxStudents(50), listStudentsOfCourse(new LinkedList_Students()) {}

bool Course::operator!=(const Course& other) const {
    return this->idCourse != other.idCourse || this->nameCourse != other.nameCourse || this->className != other.className ||
           this->teacherName != other.teacherName || this->numCredits != other.numCredits || this->dayofWeek != other.dayofWeek || this->session != other.session;
}
// Getter functions for Course
string Course::getIdCourse() const {
    return idCourse;
}

string Course::getNameCourse() const {
    return nameCourse;
}

string Course::getClassName() const {
    return className;
}

string Course::getTeacherName() const {
    return teacherName;
}

int Course::getNumCredits() const {
    return numCredits;
}

string Course::getDayofWeek() const {
    return dayofWeek;
}

string Course::getSession() const {
    return session;
}

int Course::getMaxStudents() const {
    return maxStudents;
}

LinkedList_Students* Course::getListStudents() const {
    return listStudentsOfCourse;
}
NodeCourse::NodeCourse(const Course& course) : data(course), next(nullptr) {}

LinkedList_Courses::LinkedList_Courses() : head(nullptr), tail(nullptr) {}

