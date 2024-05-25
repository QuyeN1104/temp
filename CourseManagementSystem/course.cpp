#include "course.h"

Course::Course() : idCourse(""), nameCourse(""), className(""), teacherName(""), numCredits(0), dayofWeek(""), session(""), maxStudents(50) {}

Course::Course(std::string id, std::string name, std::string className, std::string teacherName, int numCredits, std::string dayofWeek, std::string session)
    : idCourse(id), nameCourse(name), className(className), teacherName(teacherName), numCredits(numCredits), dayofWeek(dayofWeek), session(session), maxStudents(50) {}

bool Course::operator!=(const Course& other) const {
    return this->idCourse != other.idCourse || this->nameCourse != other.nameCourse || this->className != other.className ||
           this->teacherName != other.teacherName || this->numCredits != other.numCredits || this->dayofWeek != other.dayofWeek || this->session != other.session;
}

NodeCourse::NodeCourse(Course course) : data(course), next(nullptr) {}

LinkedList_Courses::LinkedList_Courses() : head(nullptr), tail(nullptr) {}
