#include "staff.h"


int main() {
    Staff s;
    string des = "D:/20CLC1.csv";
    LinkedList_Students ssd;
    s.loadStudentsFromCsvfile(ssd,des);
    NodeStudent* a;
    a = s.getNodeStudentPointer(ssd,0);
    NodeStudent* b= s.getPreviousNodeStudentPointer(ssd,a->next->next);
    Student newst;
    s.addStudentAtIndex(ssd,newst,1);
    s.deleteStudent(ssd,b);
    // cout << a->data.no;
    NodeStudent* tmp = ssd.head;
    while(tmp != NULL){
        cout << tmp->data.no << " " << tmp->data.dateOfBirth << endl;
        tmp = tmp->next;
    }
    return 0;
}
