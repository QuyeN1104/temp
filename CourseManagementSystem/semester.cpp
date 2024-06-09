#include "semester.h"
#include"course.h"

    // Constructor mặc định của Semester
    Semester::Semester() : startDate({0, 0, 0}), endDate({0, 0, 0}) {}

    // Constructor của Semester với tham số
    Semester::Semester(Date start, Date end) : startDate(start), endDate(end) {}

    bool Semester::operator!=(const Semester& other) const {
        return (this->startDate != other.startDate || this->endDate != other.endDate /*|| this->listCourses != other.listCourses*/);
    }
    // Constructor của NodeSemester
    NodeSemester::NodeSemester(const Semester& semester) : data(semester), next(nullptr) {}

    // Constructor mặc định của LinkedList_Semesters
    LinkedList_Semesters::LinkedList_Semesters() : head(nullptr), tail(nullptr) {}

    Date Semester::getStartDate() const{
        return startDate;
    }
    Date Semester::getEndDate() const{
        return endDate;
    }
    LinkedList_Courses* Semester::getListCourses() const{
        return listCoursesOfSemeter;
    }


