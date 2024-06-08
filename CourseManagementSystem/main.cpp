#include"staff.h"
#include"course.h"
#include"student.h"
int main() {
    cout << "hello";
    Staff a;
    LinkedList_Students* s = new LinkedList_Students;
    Student d;
    a.addHeadStudent(*s,d);
    return 0;
}
