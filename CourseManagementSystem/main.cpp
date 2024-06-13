#include "staff.h"
#include "course.h"
#include "library.h"
#include "schoolyear.h"
#include "semester.h"
#include "student.h"
#include "class.h"

int main() {
    Staff admin;
    Class a("16CTT3.csv");
    admin.addTailClass(admin.getListClassesOfSchool(),a);
    cout << &a << endl;
    Class* b =  &admin.getListClassesOfSchool()->head->data;
    admin.loadStudentsInClass(b,"D:/16CTT3.csv");
    cout << admin.getListClassesOfSchool()->head->data.getListStudents()->head->data.getLastName();
    // delete admin;
    return 0;
}
