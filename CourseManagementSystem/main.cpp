#include "staff.h"
#include "course.h"
#include "library.h"
#include "schoolyear.h"
#include "semester.h"
#include "student.h"
#include "class.h"

int main() {
    Course s;
    LinkedList_Students* l = s.getListStudents();
    Staff a;
    a.loadStudentsFromCsvfile(l,"D:/16CTT3.csv");
    NodeStudent* p = l->head;
    if(!p) cout << "hello";
    while(p != NULL){
        cout << p->data.getFirstName() << " " << dateToString(p->data.getDateOfBirth())   <<  endl;
        p = p->next;
    }
    Staff sd;
    cout << sd.getDateOfBirth().day;
    return 0;
}
