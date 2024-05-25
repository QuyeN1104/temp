#include"staff.h"
int main(){
    Staff s;
    LinkedList_Students stt;
    string st = "D:/20CLC1.csv";
    s.loadStudentsFromCsvfile(stt,st);
    NodeStudent* tmp = stt.head;
    s.deleteStudent(stt,stt.head->data);
    while(tmp != NULL){
        cout << tmp->data.no << " " << tmp->data.firstName << " " << tmp->data.lastName << endl;
        tmp = tmp->next;
    }
    return 0;
}
