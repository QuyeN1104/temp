#include "course.h"

Course::Course() {}
NodeCourse::NodeCourse(Course course) : data(course), next(nullptr) {}
LinkedList_Courses::LinkedList_Courses() : head(nullptr), tail(nullptr){}
