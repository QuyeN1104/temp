#include "staff.h"
#include "course.h"
#include "library.h"
#include "schoolyear.h"
#include "semester.h"
#include "student.h"
#include "class.h"

int main() {
    Staff admin;
     Class cd("16ctt3");
     Class* c = admin.addTailClass(admin.getListClassesOfSchool(),cd);
     admin.loadStudentsInClass(c,"D:/16ctt3.csv");
    SchoolYear sc("2023-2024");
    SchoolYear* year = admin.addTailSchoolYear(admin.getListSchoolYearsOfSchool(),"2023-2024");
    Semester* semester = admin.addTailSemester(year->getListSemesters(),"1");
    Course course;
    Course* co = admin.addTailCourse(semester->getListCourses(), course);
    admin.loadStudentsInCourse(co,"D:/16ctt3.csv","2023-2024","1");
    NodeStudent* tmp = co->getListStudents()->head;
    int i = 0;
    while(tmp != NULL && i < 4){
        cout << tmp->data.getLastName() << " " ;
        tmp = tmp->next;
        i++;
    }
    cout << endl;
    tmp = c->getListStudents()->head;
    i = 0;
    while(tmp != NULL && i < 4){
        cout << tmp->data.getLastName() << endl;
        tmp = tmp->next;
        i++;
    }
    return 0;
}
