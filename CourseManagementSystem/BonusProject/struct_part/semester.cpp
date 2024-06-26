#include "semester.h"
#include"course.h"
#include"mark.h"

    // Constructor mặc định của Semester
Semester::Semester() : startDate({0, 0, 0}), endDate({0, 0, 0}), nameSemester("") , listCoursesOfSemeter(new LinkedList_Courses()), marksOfSemester(NULL) {}
Semester::Semester(const string& name) : startDate({0, 0, 0}), endDate({0, 0, 0}), nameSemester(name), listCoursesOfSemeter(new LinkedList_Courses()),marksOfSemester(NULL) {}

    // Constructor của Semester với tham số
Semester::Semester(Date start, Date end,string name) : startDate(start), endDate(end), nameSemester(name),listCoursesOfSemeter(new LinkedList_Courses), marksOfSemester(NULL) {}

    bool Semester::operator!=(const Semester& other) const {
        return (this->startDate != other.startDate || this->endDate != other.endDate || this->nameSemester != other.nameSemester);
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
    string Semester::getNameSemester() const{
        return nameSemester;
    }
    LinkedList_Courses* Semester::getListCourses() const{
        return listCoursesOfSemeter;
    }
    LinkedList_Marks* Semester::getListMarks() const{
        return marksOfSemester;
    }
    void Semester::initListMarks(){
        marksOfSemester = new LinkedList_Marks();
    }


