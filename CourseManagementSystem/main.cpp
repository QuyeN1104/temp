#include "staff.h"
#include "course.h"
#include "library.h"
#include "schoolyear.h"
#include "semester.h"
#include "student.h"
#include "class.h"

int main() {
    Staff admin;
    // thêm 1 year năm dô ds năm của trường -> trả về cái điạ chỉ năm đó lun cho dễ dùng
    SchoolYear* year = admin.addTailSchoolYear(admin.getListSchoolYearsOfSchool(),"2016-2017");
    // thêm 1 kì tương tự
    Semester* semester = admin.addTailSemester(year->getListSemesters(),"1");
    // thêm khóa học
    Class* ncl = admin.addTailClass(year->getListClassesOfYear(),"16ctt3");
    // load khóa học
    admin.loadStudentsInClass(ncl,"D:/16ctt3.csv");
    Course course;
    Course* co = admin.addTailCourse(semester->getListCourses(), course);
    // load danh sách học sinh dô khóa học -> load khóa học đó vào kì của năm đó (2016-2017/1)
    cout << admin.loadStudentsInCourse(co,"D:/16ctt3.csv","2016-2017","1") << endl;
    Student s;
    Student* sdd = admin.addTailStudent(co->getListStudents(),s);
    cout << sdd->getLastName() << endl;
    NodeStudent* tmp = co->getListStudents()->head;
    int i = 0;
    while(tmp != NULL && i < 4){
        cout << tmp->data.getLastName() << " " ;
        tmp = tmp->next;
        i++;
    }
    cout << endl;
    tmp = ncl->getListStudents()->head;
    i = 0;
    while(tmp != NULL && i < 4){
        cout << tmp->data.getLastName() << endl;
        tmp = tmp->next;
        i++;
    }
    cout << "hello";
    return 0;
}
