#include "staff.h"
#include "course.h"
#include "library.h"
#include "schoolyear.h"
#include "semester.h"
#include "student.h"
#include "class.h"

int main() {
    Class s;
    Staff a;
    a.loadStudentsInClass(&s,"D:/16CTT3.csv");
    a.addTailClass(a.getListClassesOfSchool(),s);
    NodeStudent* sdd = a.findStudentByID(a.getListClassesOfSchool(),"20120278");
    cout << sdd->data.getEnrolledClass();
    return 0;
}
