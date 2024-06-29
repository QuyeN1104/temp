#include "staff.h"
#include "course.h"
#include "library.h"
#include "schoolyear.h"
#include "semester.h"
#include "student.h"
#include "class.h"
#include"mark.h"

int main() {
    Staff admin;
    // thêm 1 year năm dô ds năm của trường -> trả về cái điạ chỉ năm đó lun cho dễ dùng
    SchoolYear* year = admin.addTailSchoolYear(admin.getListSchoolYearsOfSchool(),"2021-2022");
    // thêm 1 kì tương tự
    Semester* semester = admin.addTailSemester(year->getListSemesters(),"1");
    // thêm khóa học
    Class* ncl = admin.addTailClass(year->getListClassesOfYear(),"21ctt3");
    // load khóa học
    cout << admin.loadStudentsInClass(ncl->getListStudents(),"D:/211vtp2b.csv") << endl;
    Course myCourse("CS101", "Introduction to Computer Science", "211vtp2b", "Dr. Smith", 3, "Monday", "Morning");
    Course* course = admin.addTailCourse(semester->getListCourses(),myCourse);
    cout << admin.loadStudentsInCourse(course->getListStudents(),"D:/211vtp2b.csv") << endl;
    admin.importCourseCsvFile(course,"D:/211vtp2b_scores.csv");
    Student* id = admin.findStudentByID("21000352");
    Semester* pSemester = admin.findSemesterInYear(id->getListSchoolYearsOfSchool(),"2021-2022","1");
    if(pSemester){
        cout << pSemester->getListMarks()->head->data.totalMark << endl;
    }

    return 0;
}
