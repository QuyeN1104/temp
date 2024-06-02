#ifndef _SEMESTER_H_
#define _SEMESTER_H_
#include "user.h"
#include "course.h"
#include "schoolyear.h"
struct Semester {
	Date startDate;
	Date endDate;
	SchoolYear schoolYear;
	LinkedList_Courses listCourse;
};
#endif // !_SEMESTER_H_
