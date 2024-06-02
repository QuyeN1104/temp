#include"staff.h"
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
        addTailStudent(lStudents,student);
    }
    deletePointerData(data,numRows);
}

NodeCourse* Staff::getNodeCoursePointer(LinkedList_Courses lCourses, Course course){
    NodeCourse* pNodeCourse = lCourses.head;
    if(pNodeCourse == NULL) return NULL;
    while(pNodeCourse != NULL && (pNodeCourse->data != course)){
        pNodeCourse = pNodeCourse->next;
    }
    return pNodeCourse;
}
NodeCourse* Staff::getNodeCoursePointer(LinkedList_Courses lCourses, int index){
    NodeCourse* pNodeCourse = lCourses.head;
    int currentIndex = 0;
    while(pNodeCourse != NULL && currentIndex < index){
        pNodeCourse = pNodeCourse->next;
        currentIndex++;
    }
    return pNodeCourse;
}
int Staff::getNodeCourseIndex(LinkedList_Courses lCourses, NodeCourse* pNodeCourse){
    if(lCourses.head == NULL) return -1;
    NodeCourse* p = lCourses.head;
    int currentIndex = 0;
    while(p != NULL){
        if(p == pNodeCourse){
            return currentIndex;
        }
        p = p->next;
        currentIndex++;
    }
    return -1;
}
NodeCourse* Staff::getPreviousNodeCoursePointer(LinkedList_Courses lCourses, NodeCourse* pNodeCourse){
    NodeCourse* p = lCourses.head;
    NodeCourse* pPrev = NULL;
    while(p != NULL){
        if(p==pNodeCourse){
            return pPrev;
        }
        pPrev = p;
        p = p->next;
    }
    return NULL;
}
void Staff::addHeadCourse(LinkedList_Courses& lCourses, Course course){
    NodeCourse* pNodeCourse = new NodeCourse(course);
    pNodeCourse->next = lCourses.head;
    lCourses.head = pNodeCourse;
    if(lCourses.tail == NULL) lCourses.tail = lCourses.head;
}
void Staff::addTailCourse(LinkedList_Courses& lCourses, Course course){

    NodeCourse* pNodeCourse = new NodeCourse(course);
    if(lCourses.tail == NULL){
        lCourses.head = lCourses.tail = pNodeCourse;
        return;
    }
    lCourses.tail->next = pNodeCourse;
    lCourses.tail = pNodeCourse;
}
void Staff::addBeforeCourse(LinkedList_Courses& lCourses, NodeCourse* pNodeCourseBefore,Course course){
    if(pNodeCourseBefore == NULL) return ;
    if(pNodeCourseBefore == lCourses.head){
        addHeadCourse(lCourses,course);
        return;
    }
    NodeCourse* pNodeCourse = new NodeCourse(course);
    NodeCourse* p = getPreviousNodeCoursePointer(lCourses,pNodeCourseBefore);
    if(p==NULL) return;
    p->next = pNodeCourse;
    pNodeCourse->next = pNodeCourseBefore;
}
void Staff::addAfterCourse(LinkedList_Courses& lCourses,NodeCourse* pNodeCourseAfter,Course course){
    NodeCourse* pNodeCourse = new NodeCourse(course);
    NodeCourse* p = lCourses.head;
    if(p == NULL || pNodeCourseAfter == NULL) return;
    while(p != NULL){
        if(p == pNodeCourseAfter) break;
        p = p->next;
    }
    if(p==NULL) return;
    p = pNodeCourseAfter->next;
    pNodeCourseAfter->next = pNodeCourse;
    pNodeCourse->next = p;
    if(p==NULL){
        lCourses.tail = pNodeCourse;
    }
}
void Staff::addCourseAtIndex(LinkedList_Courses& lCourses, Course course, int index){
    NodeCourse* p = getNodeCoursePointer(lCourses,index);
    addAfterCourse(lCourses,p,course);
}
void Staff::deleteCourse(LinkedList_Courses& lCourses, NodeCourse* pNodeCourse) {
    if (lCourses.head == NULL) return; // Danh sách trống

    NodeCourse* temp = lCourses.head;
    NodeCourse* prev = NULL;

    // Tìm nút chứa khóa học cần xóa
    while (temp != NULL) {
        if(temp == pNodeCourse) break;
        prev = temp;
        temp = temp->next;
    }

    // Nếu không tìm thấy khóa học cần xóa
    if (temp == NULL) return;

    // Nếu khóa học cần xóa là đầu danh sách
    if (temp == lCourses.head) {
        lCourses.head = temp->next;
        if (lCourses.head == NULL) {
            lCourses.tail = NULL; // Nếu danh sách trống sau khi xóa
        }
        delete temp;
        return;
    }

    // Nếu khóa học cần xóa là cuối danh sách
    if (temp == lCourses.tail) {
        lCourses.tail = prev;
        lCourses.tail->next = NULL;
        delete temp;
        return;
    }

    // Xóa khóa học ở giữa danh sách
    prev->next = temp->next;
    delete temp;
}

// NodeStudent* Staff::getNodeStudentPointer(LinkedList_Students lStudents, Student student) {
//     NodeStudent* pNodeStudent = lStudents.head;
//     if (pNodeStudent == NULL) return NULL;
//     while (pNodeStudent != NULL && (pNodeStudent->data != student)) {
//         pNodeStudent = pNodeStudent->next;
//     }
//     return pNodeStudent;
// }
NodeStudent* Staff::getNodeStudentPointer(LinkedList_Students lStudents, int index) {
    NodeStudent* pNodeStudent = lStudents.head;
    int currentIndex = 0;
    while (pNodeStudent != NULL && currentIndex < index) {
        pNodeStudent = pNodeStudent->next;
        currentIndex++;
    }
    return pNodeStudent;
}
int Staff::getNodeStudentIndex(LinkedList_Students lStudents, NodeStudent* pNodeStudent) {
    if (lStudents.head == NULL) return -1;
    NodeStudent* p = lStudents.head;
    int currentIndex = 0;
    while (p != NULL) {
        if (p == pNodeStudent) {
            return currentIndex;
        }
        p = p->next;
        currentIndex++;
    }
    return -1;
}
NodeStudent* Staff::getPreviousNodeStudentPointer(LinkedList_Students lStudents, NodeStudent* pNodeStudent) {
    NodeStudent* p = lStudents.head;
    NodeStudent* pPrev = NULL;
    while (p != NULL) {
        if (p == pNodeStudent) {
            return pPrev;
        }
        pPrev = p;
        p = p->next;
    }
    return NULL;
}
void Staff::addHeadStudent(LinkedList_Students& lStudents, Student student) {
    NodeStudent* pNodeStudent = new NodeStudent(student);
    pNodeStudent->next = lStudents.head;
    lStudents.head = pNodeStudent;
    if (lStudents.tail == NULL) lStudents.tail = lStudents.head;
}
void Staff::addTailStudent(LinkedList_Students& lStudents, Student student) {

    NodeStudent* pNodeStudent = new NodeStudent(student);
    if (lStudents.tail == NULL) {
        lStudents.head = lStudents.tail = pNodeStudent;
        return;
    }
    lStudents.tail->next = pNodeStudent;
    lStudents.tail = pNodeStudent;
}
void Staff::addBeforeStudent(LinkedList_Students& lStudents, NodeStudent* pNodeStudentBefore, Student student) {
    if (pNodeStudentBefore == NULL) return;
    if (pNodeStudentBefore == lStudents.head) {
        addHeadStudent(lStudents, student);
        return;
    }
    NodeStudent* pNodeStudent = new NodeStudent(student);
    NodeStudent* p = getPreviousNodeStudentPointer(lStudents, pNodeStudentBefore);
    if (p == NULL) return;
    p->next = pNodeStudent;
    pNodeStudent->next = pNodeStudentBefore;
}
void Staff::addAfterStudent(LinkedList_Students& lStudents, NodeStudent* pNodeStudentAfter, Student student) {
    NodeStudent* pNodeStudent = new NodeStudent(student);
    NodeStudent* p = lStudents.head;
    if (p == NULL || pNodeStudentAfter == NULL) return;
    while (p != NULL) {
        if (p == pNodeStudentAfter) break;
        p = p->next;
    }
    if (p == NULL) return;
    p = pNodeStudentAfter->next;
    pNodeStudentAfter->next = pNodeStudent;
    pNodeStudent->next = p;
    if (p == NULL) {
        lStudents.tail = pNodeStudent;
    }
}
void Staff::addStudentAtIndex(LinkedList_Students& lStudents, Student student, int index) {
    if(index == 0){
        addHeadStudent(lStudents,student);
        return;
    }
    NodeStudent* p = getNodeStudentPointer(lStudents, index - 1);
    addAfterStudent(lStudents, p, student);
}
void Staff::deleteStudent(LinkedList_Students& lStudents, NodeStudent* pNodeStudent) {
    if (lStudents.head == NULL) return; // Danh sách trống

    NodeStudent* temp = lStudents.head;
    NodeStudent* prev = NULL;

    // Tìm nút chứa khóa học cần xóa
    while (temp != NULL) {
        if (temp == pNodeStudent) break;
        prev = temp;
        temp = temp->next;
    }

    // Nếu không tìm thấy khóa học cần xóa
    if (temp == NULL) return;

    // Nếu khóa học cần xóa là đầu danh sách
    if (temp == lStudents.head) {
        lStudents.head = temp->next;
        if (lStudents.head == NULL) {
            lStudents.tail = NULL; // Nếu danh sách trống sau khi xóa
        }
        delete temp;
        return;
    }

    // Nếu khóa học cần xóa là cuối danh sách
    if (temp == lStudents.tail) {
        lStudents.tail = prev;
        lStudents.tail->next = NULL;
        delete temp;
        return;
    }

    // Xóa khóa học ở giữa danh sách
    prev->next = temp->next;
    delete temp;
}

// NodeClass* Staff::getNodeClassPointer(LinkedList_Classes lClasses, Class Class) {
//     NodeClass* pNodeClass = lClasses.head;
//     if (pNodeClass == NULL) return NULL;
//     while (pNodeClass != NULL && (pNodeClass->data != Class)) {
//         pNodeClass = pNodeClass->next;
//     }
//     return pNodeClass;
// }
NodeClass* Staff::getNodeClassPointer(LinkedList_Classes lClasses, int index) {
    NodeClass* pNodeClass = lClasses.head;
    int currentIndex = 0;
    while (pNodeClass != NULL && currentIndex < index) {
        pNodeClass = pNodeClass->next;
        currentIndex++;
    }
    return pNodeClass;
}
int Staff::getNodeClassIndex(LinkedList_Classes lClasses, NodeClass* pNodeClass) {
    if (lClasses.head == NULL) return -1;
    NodeClass* p = lClasses.head;
    int currentIndex = 0;
    while (p != NULL) {
        if (p == pNodeClass) {
            return currentIndex;
        }
        p = p->next;
        currentIndex++;
    }
    return -1;
}
NodeClass* Staff::getPreviousNodeClassPointer(LinkedList_Classes lClasses, NodeClass* pNodeClass) {
    NodeClass* p = lClasses.head;
    NodeClass* pPrev = NULL;
    while (p != NULL) {
        if (p == pNodeClass) {
            return pPrev;
        }
        pPrev = p;
        p = p->next;
    }
    return NULL;
}
void Staff::addHeadClass(LinkedList_Classes& lClasses, Class Class) {
    NodeClass* pNodeClass = new NodeClass(Class);
    pNodeClass->next = lClasses.head;
    lClasses.head = pNodeClass;
    if (lClasses.tail == NULL) lClasses.tail = lClasses.head;
}
void Staff::addTailClass(LinkedList_Classes& lClasses, Class Class) {

    NodeClass* pNodeClass = new NodeClass(Class);
    if (lClasses.tail == NULL) {
        lClasses.head = lClasses.tail = pNodeClass;
        return;
    }
    lClasses.tail->next = pNodeClass;
    lClasses.tail = pNodeClass;
}
void Staff::addBeforeClass(LinkedList_Classes& lClasses, NodeClass* pNodeClassBefore, Class Class) {
    if (pNodeClassBefore == NULL) return;
    if (pNodeClassBefore == lClasses.head) {
        addHeadClass(lClasses, Class);
        return;
    }
    NodeClass* pNodeClass = new NodeClass(Class);
    NodeClass* p = getPreviousNodeClassPointer(lClasses, pNodeClassBefore);
    if (p == NULL) return;
    p->next = pNodeClass;
    pNodeClass->next = pNodeClassBefore;
}
void Staff::addAfterClass(LinkedList_Classes& lClasses, NodeClass* pNodeClassAfter, Class Class) {
    NodeClass* pNodeClass = new NodeClass(Class);
    NodeClass* p = lClasses.head;
    if (p == NULL || pNodeClassAfter == NULL) return;
    while (p != NULL) {
        if (p == pNodeClassAfter) break;
        p = p->next;
    }
    if (p == NULL) return;
    p = pNodeClassAfter->next;
    pNodeClassAfter->next = pNodeClass;
    pNodeClass->next = p;
    if (p == NULL) {
        lClasses.tail = pNodeClass;
    }
}
void Staff::addClassAtIndex(LinkedList_Classes& lClasses, Class Class, int index) {
    NodeClass* p = getNodeClassPointer(lClasses, index);
    addAfterClass(lClasses, p, Class);
}
void Staff::deleteClass(LinkedList_Classes& lClasses, NodeClass* pNodeClass) {
    if (lClasses.head == NULL) return; // Danh sách trống

    NodeClass* temp = lClasses.head;
    NodeClass* prev = NULL;

    // Tìm nút chứa khóa học cần xóa
    while (temp != NULL) {
        if (temp == pNodeClass) break;
        prev = temp;
        temp = temp->next;
    }

    // Nếu không tìm thấy khóa học cần xóa
    if (temp == NULL) return;

    // Nếu khóa học cần xóa là đầu danh sách
    if (temp == lClasses.head) {
        lClasses.head = temp->next;
        if (lClasses.head == NULL) {
            lClasses.tail = NULL; // Nếu danh sách trống sau khi xóa
        }
        delete temp;
        return;
    }

    // Nếu khóa học cần xóa là cuối danh sách
    if (temp == lClasses.tail) {
        lClasses.tail = prev;
        lClasses.tail->next = NULL;
        delete temp;
        return;
    }

    // Xóa khóa học ở giữa danh sách
    prev->next = temp->next;
    delete temp;
}




