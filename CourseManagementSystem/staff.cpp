#include "staff.h"
void Staff::change_idCourse(Course& course,string newIdCourse){
    course.idCourse = newIdCourse;
}
void Staff::change_nameCourse(Course& course,string newNameCourse){
    course.nameCourse = newNameCourse;
}
void Staff::change_className(Course& course,string newClassName){
    course.className = newClassName;
}
void Staff::change_teacherName(Course& course,string newTeacherName){
    course.teacherName = newTeacherName;
}
void Staff::change_numCredits(Course& course, int newNumCredits){
    course.numCredits = newNumCredits;
}
void Staff::change_session(Course& course,string newSession){
    course.session = newSession;
}

void Staff::change_dayofWeek(Course& course,string newDayofWeek){
    course.dayofWeek = newDayofWeek;
}

void Staff::change_maxStudents(Course& course,int newMaxStudens){
    course.maxStudents = newMaxStudens;
}
void Staff::addCourse(LinkedList_Courses& lCourses, Course course){

    NodeCourse* pNodeCourse = new NodeCourse(course);
    if(lCourses.tail == NULL){
        lCourses.head = lCourses.tail = pNodeCourse;
        return;
    }
    lCourses.tail->next = pNodeCourse;
    lCourses.tail = pNodeCourse;
}
void Staff::deleteCourse(LinkedList_Courses& lCourses,Course course){
    NodeCourse* pCourse = new NodeCourse(course);
    NodeCourse* pTemp = lCourses.head;
    while(pTemp != NULL){
        if(pTemp == pCourse){
            break;
        }
        pTemp = pTemp->next;
    }
    if(pTemp == NULL) return;
    NodeCourse* pPrev = NULL;
    while(pPrev->next != pTemp){
        pPrev = pPrev->next;
    }
    if(pPrev == NULL){
        lCourses.head = pTemp->next;
        delete pTemp;
        if(lCourses.head == NULL){
            lCourses.tail = NULL;
        }
        return;
    }
    pPrev->next = pTemp->next;
    delete pTemp;
    if(pPrev->next == NULL){
        lCourses.tail = pPrev;
    }
}
void Staff::addStudent(LinkedList_Students& lStudents, Student student){
    NodeStudent* pNodeStudent = new NodeStudent(student);
    if(lStudents.tail == NULL){
        lStudents.head = lStudents.tail = pNodeStudent;
        return;
    }
    lStudents.tail->next = pNodeStudent;
    lStudents.tail = pNodeStudent;
}
void Staff::deleteStudent(LinkedList_Students& lStudents,Student student){
//     NodeStudent* pTemp = lStudents.head;
//     while(pTemp != NULL){
//         if(pTemp->data == student){
//             break;
//         }
//         pTemp = pTemp->next;
//     }
//     if(pTemp == NULL) return;
//     if(pTemp == lStudents.head){

//     }
//     NodeStudent* pPrev = lStudents.head;
//     while(pPrev->next != pTemp){
//         pPrev = pPrev->next;
//     }
//     if(pPrev == NULL){
//         lStudents.head = pTemp->next;
//         delete pTemp;
//         if(lStudents.head == NULL){
//             lStudents.tail = NULL;
//         }
//         return;
//     }
//     pPrev->next = pTemp->next;
//     delete pTemp;
//     if(pPrev->next == NULL){
//         lStudents.tail = pPrev;
//     }
}
void Staff::addClass(LinkedList_Classes& lClasses, Class Class){
    NodeClass* pNodeClass = new NodeClass(Class);
    if(lClasses.tail == NULL){
        lClasses.head = lClasses.tail = pNodeClass;
        return;
    }
    lClasses.tail->next = pNodeClass;
    lClasses.tail = pNodeClass;
}
void Staff::deleteClass(LinkedList_Classes& lClasses,Class Class){
    NodeClass* pClass = new NodeClass(Class);
    NodeClass* pTemp = lClasses.head;
    while(pTemp != NULL){
        if(pTemp == pClass){
            break;
        }
        pTemp = pTemp->next;
    }
    if(pTemp == NULL) return;
    NodeClass* pPrev = NULL;
    while(pPrev->next != pTemp){
        pPrev = pPrev->next;
    }
    if(pPrev == NULL){
        lClasses.head = pTemp->next;
        delete pTemp;
        if(lClasses.head == NULL){
            lClasses.tail = NULL;
        }
        return;
    }
    pPrev->next = pTemp->next;
    delete pTemp;
    if(pPrev->next == NULL){
        lClasses.tail = pPrev;
    }
}
int Staff::countLines(const std::string& filename) {
    std::ifstream file;
    file.open(filename,ios::in);
    if (!file.is_open()) {
        return -1;
    }

    int lineCount = 0;
    string line;
    while (getline(file,line)) {
        ++lineCount;
    }
    lineCount--; // trừ hàng đầu tiên chứa các trường dữ liệu
    file.close();
    return lineCount;
}
string** Staff::processCsvFile(const string& fileDirection, int& numRows){
    ifstream file(fileDirection,ios::in);
    if(!file.is_open()){
        return nullptr;
    }
    // cap phat o nho
    numRows = countLines(fileDirection);
    string** pString = new string* [numRows];
    for(int i = 0; i < numRows; i++){
        pString[i] = new string [numCsvCols];
    }
    // bỏ qua hàng tiêu đề đầu tiên
    string header;
    getline(file,header);
    // bắt đầu đọc dữ liệu
    string line;
    int row = 0;
    while(getline(file,line)){
        stringstream ss(line);
        int col = 0;
        string cell;
        while (getline(ss, cell, ',')) {
            pString[row][col] = cell;
            ++col;
        }
        ++row;
    }
    file.close();
    return pString;
}
void Staff::deletePointerData(string** s, int numRows){
    for(int i = 0; i < numRows; i++){
        delete [] s[i];
        s[i] = nullptr;
    }
    delete [] s;
}
void Staff::loadStudentsFromCsvfile(LinkedList_Students& lStudents,const string& fileDirection){
    int numRows;
    string** data = processCsvFile(fileDirection,numRows);
    for(int i = 0; i < numRows; i++){
        // gán từng data[i] vào các NodeStudent
        Student student(data[i]);
        addStudent(lStudents,student);
    }
    deletePointerData(data,numRows);
}
