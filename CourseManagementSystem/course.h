#ifndef COURSE_H
#define COURSE_H

#include <library.h>

class Course {
    friend class Staff;
public:
    Course();
    Course(std::string id, std::string name, std::string className, std::string teacherName, int numCredits, std::string dayofWeek, std::string session);

    bool operator!=(const Course& other) const;

 private:
    std::string idCourse, nameCourse, className, teacherName;
    int numCredits;
    std::string dayofWeek;
    std::string session;
    int maxStudents = 50;
};

struct NodeCourse {
    Course data;
    NodeCourse* next;
    NodeCourse(Course course);
};

struct LinkedList_Courses {
    NodeCourse *head, *tail;
    LinkedList_Courses();
};

#endif // COURSE_H
