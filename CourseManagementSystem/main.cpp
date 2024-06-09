#include "staff.h"
#include "course.h"
#include "library.h"
#include "schoolyear.h"
#include "semester.h"
#include "student.h"
#include "class.h"

int main() {
    Staff a;
    Course s;
    LinkedList_Students* list = s.getListStudents();
    Student d;
    d.studentID = "1313";
    a.addHeadStudent(list,d);
    delete list;
    return 0;
}
