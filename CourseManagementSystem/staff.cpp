#include"staff.h"
#include"course.h"
#include"library.h"
#include"schoolyear.h"
#include"semester.h"
#include"student.h"
#include"class.h"

//khởi tạo giá trị biến static
LinkedList_Classes* Staff::listClassesOfSchool = nullptr;
LinkedList_SchoolYears* Staff::listSchoolYearsOfSchool = nullptr;

Staff::Staff() {
    if (listClassesOfSchool == nullptr) {
        listClassesOfSchool = new LinkedList_Classes();
    }
    if (listSchoolYearsOfSchool == nullptr) {
        listSchoolYearsOfSchool = new LinkedList_SchoolYears();
    }
}
LinkedList_Classes* Staff::getListClassesOfSchool() const {
    return listClassesOfSchool;
}

LinkedList_SchoolYears* Staff::getListSchoolYearsOfSchool() const {
    return listSchoolYearsOfSchool;
}

//
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
int Staff::countLines(const string& filename) {
    ifstream file;
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
        int isSTT = 1; // kiểm tra có phải là cột stt không (do không đọc số thứ tự)
        while (getline(ss, cell, ',')) {
            if(isSTT == 0){
            pString[row][col] = cell;
            ++col;
            }
            isSTT = 0;
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
// fileDirection ex : 23CTT5.csv
void Staff::loadStudentsInClass(Class* Class,const string& fileDirection){
    int numRows;
    string** data = processCsvFile(fileDirection,numRows);
    if(data == NULL) return;
    string nameClass = splitNameClassFromFile(fileDirection);
    for(int i = 0; i < numRows; i++){
        // gán từng data[i] vào các NodeStudent
        Student student(data[i],nameClass);
        addTailStudent(Class->listStudentsOfClass,student);
    }
    deletePointerData(data,numRows);
}

void Staff::loadStudentsInCourse(Course* course, const string& fileDirection,const string& nameYear, const string& nameSemester){
    int numRows;
    string** data = processCsvFile(fileDirection,numRows);
    if(data == NULL) return;
    for(int i = 0; i < numRows; i++){
        // gán từng data[i] vào các NodeStudent
        Student student(data[i]);
        addTailStudent(course->listStudentsOfCourse,student);
        Student* pStudent = &getNodeStudentPointer(course->listStudentsOfCourse,student)->data;
        Semester* pSemester = &findSemesterInYear(pStudent->getListSchoolYearsOfSchool(),nameYear,nameSemester)->data;
        addTailCourse(pSemester->listCoursesOfSemeter,*course);
    }
    deletePointerData(data,numRows);
}

// hàm cho Course

NodeCourse* Staff::getNodeCoursePointer(LinkedList_Courses* lCourses, const Course& course){
    if(lCourses->head == NULL) return NULL;
    NodeCourse* pNodeCourse = lCourses->head;
    while(pNodeCourse != NULL && (pNodeCourse->data != course)){
        pNodeCourse = pNodeCourse->next;
    }
    return pNodeCourse;
}

NodeCourse* Staff::getNodeCoursePointerByName(LinkedList_Courses* lCourses, const string& nameClass){
    if(lCourses->head == NULL) return NULL;
    NodeCourse* pNodeCourse = lCourses->head;
    while(pNodeCourse != NULL && (pNodeCourse->data.getClassName() != nameClass)){
        pNodeCourse = pNodeCourse->next;
    }
    return pNodeCourse;
}

NodeCourse* Staff::getNodeCoursePointer(LinkedList_Courses* lCourses, int index){
    NodeCourse* pNodeCourse = lCourses->head;
    int currentIndex = 0;
    while(pNodeCourse != NULL && currentIndex < index){
        pNodeCourse = pNodeCourse->next;
        currentIndex++;
    }
    return pNodeCourse;
}

int Staff::getNodeCourseIndex(LinkedList_Courses* lCourses, NodeCourse* pNodeCourse){
    if(lCourses->head == NULL) return -1;
    NodeCourse* p = lCourses->head;
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

NodeCourse* Staff::getPreviousNodeCoursePointer(LinkedList_Courses* lCourses, NodeCourse* pNodeCourse){
    NodeCourse* p = lCourses->head;
    NodeCourse* pPrev = NULL;
    while(p != NULL){
        if(p == pNodeCourse){
            return pPrev;
        }
        pPrev = p;
        p = p->next;
    }
    return NULL;
}

void Staff::addHeadCourse(LinkedList_Courses* lCourses, const Course& course){
    NodeCourse* pNodeCourse = new NodeCourse(course);
    if(pNodeCourse){
    pNodeCourse->next = lCourses->head;
    lCourses->head = pNodeCourse;
    if(lCourses->tail == NULL) lCourses->tail = lCourses->head;
    }
}

void Staff::addTailCourse(LinkedList_Courses* lCourses, const Course& course){
    NodeCourse* pNodeCourse = new NodeCourse(course);
    if(pNodeCourse){
    if(lCourses->tail == NULL){
        lCourses->head = lCourses->tail = pNodeCourse;
        return;
    }
    lCourses->tail->next = pNodeCourse;
    lCourses->tail = pNodeCourse;
    }
}

void Staff::addBeforeCourse(LinkedList_Courses* lCourses, NodeCourse* pNodeCourseBefore, const Course& course){
    if(pNodeCourseBefore == NULL) return;
    if(pNodeCourseBefore == lCourses->head){
        addHeadCourse(lCourses, course);
        return;
    }
    NodeCourse* pNodeCourse = new NodeCourse(course);
    NodeCourse* p = getPreviousNodeCoursePointer(lCourses, pNodeCourseBefore);
    if(p == NULL) return;
    p->next = pNodeCourse;
    pNodeCourse->next = pNodeCourseBefore;
}

void Staff::addAfterCourse(LinkedList_Courses* lCourses, NodeCourse* pNodeCourseAfter, const Course& course){
    NodeCourse* pNodeCourse = new NodeCourse(course);
    if(lCourses->head == NULL || pNodeCourseAfter == NULL) return;
    NodeCourse* p = lCourses->head;
    while(p != NULL){
        if(p == pNodeCourseAfter) break;
        p = p->next;
    }
    if(p == NULL) return;
    pNodeCourse->next = pNodeCourseAfter->next;
    pNodeCourseAfter->next = pNodeCourse;
    if(pNodeCourseAfter == lCourses->tail){
        lCourses->tail = pNodeCourse;
    }
}

void Staff::addCourseAtIndex(LinkedList_Courses* lCourses, const Course& course, int index){
    NodeCourse* p = getNodeCoursePointer(lCourses, index);
    addBeforeCourse(lCourses, p, course);
}

void Staff::deleteCourse(LinkedList_Courses* lCourses, NodeCourse* pNodeCourse) {
    if (lCourses->head == NULL) return; // Danh sách trống

    NodeCourse* temp = lCourses->head;
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
    if (temp == lCourses->head) {
        lCourses->head = temp->next;
        if (lCourses->head == NULL) {
            lCourses->tail = NULL; // Nếu danh sách trống sau khi xóa
        }
        delete temp;
        return;
    }

    // Nếu khóa học cần xóa là cuối danh sách
    if (temp == lCourses->tail) {
        lCourses->tail = prev;
        lCourses->tail->next = NULL;
        delete temp;
        return;
    }

    // Xóa khóa học ở giữa danh sách
    prev->next = temp->next;
    delete temp;
}

NodeStudent* Staff::getNodeStudentPointerByID(LinkedList_Students* lStudents, const string& mssv){
    if(lStudents == NULL || lStudents->head == NULL ) return NULL;
    NodeStudent* pNodeStudent = lStudents->head;
    while(pNodeStudent != NULL && (pNodeStudent->data.getStudentID() != mssv)){
        pNodeStudent = pNodeStudent->next;
    }
    return pNodeStudent;
}

NodeStudent* Staff::getNodeStudentPointer(LinkedList_Students* lStudents, const Student& student){
    if(lStudents == NULL || lStudents->head == NULL ) return NULL;
    NodeStudent* pNodeStudent = lStudents->head;
    while(pNodeStudent != NULL && (pNodeStudent->data != student)){
        pNodeStudent = pNodeStudent->next;
    }
    return pNodeStudent;
}

NodeStudent* Staff::getNodeStudentPointer(LinkedList_Students* lStudents, int index){
    NodeStudent* pNodeStudent = lStudents->head;
    int currentIndex = 0;
    while(pNodeStudent != NULL && currentIndex < index){
        pNodeStudent = pNodeStudent->next;
        currentIndex++;
    }
    return pNodeStudent;
}

int Staff::getNodeStudentIndex(LinkedList_Students* lStudents, NodeStudent* pNodeStudent){
    if(lStudents->head == NULL) return -1;
    NodeStudent* p = lStudents->head;
    int currentIndex = 0;
    while(p != NULL){
        if(p == pNodeStudent){
            return currentIndex;
        }
        p = p->next;
        currentIndex++;
    }
    return -1;
}

NodeStudent* Staff::getPreviousNodeStudentPointer(LinkedList_Students* lStudents, NodeStudent* pNodeStudent){
    NodeStudent* p = lStudents->head;
    NodeStudent* pPrev = NULL;
    while(p != NULL){
        if(p == pNodeStudent){
            return pPrev;
        }
        pPrev = p;
        p = p->next;
    }
    return NULL;
}

void Staff::addHeadStudent(LinkedList_Students* lStudents, const Student& student){
    NodeStudent* pNodeStudent = new NodeStudent(student);
    pNodeStudent->next = lStudents->head;
    lStudents->head = pNodeStudent;
    if(lStudents->tail == NULL) lStudents->tail = lStudents->head;
}

void Staff::addTailStudent(LinkedList_Students* lStudents, const Student& student){
    NodeStudent* pNodeStudent = new NodeStudent(student);
    if(lStudents->tail == NULL){
        lStudents->head = lStudents->tail = pNodeStudent;
        return;
    }
    lStudents->tail->next = pNodeStudent;
    lStudents->tail = pNodeStudent;
}

void Staff::addBeforeStudent(LinkedList_Students* lStudents, NodeStudent* pNodeStudentBefore, const Student& student){
    if(pNodeStudentBefore == NULL) return;
    if(pNodeStudentBefore == lStudents->head){
        addHeadStudent(lStudents, student);
        return;
    }
    NodeStudent* pNodeStudent = new NodeStudent(student);
    NodeStudent* p = getPreviousNodeStudentPointer(lStudents, pNodeStudentBefore);
    if(p == NULL) return;
    p->next = pNodeStudent;
    pNodeStudent->next = pNodeStudentBefore;
}

void Staff::addAfterStudent(LinkedList_Students* lStudents, NodeStudent* pNodeStudentAfter, const Student& student){
    NodeStudent* pNodeStudent = new NodeStudent(student);
    if(lStudents->head == NULL || pNodeStudentAfter == NULL) return;
    NodeStudent* p = lStudents->head;
    while(p != NULL){
        if(p == pNodeStudentAfter) break;
        p = p->next;
    }
    if(p == NULL) return;
    pNodeStudent->next = pNodeStudentAfter->next;
    pNodeStudentAfter->next = pNodeStudent;
    if(pNodeStudentAfter == lStudents->tail){
        lStudents->tail = pNodeStudent;
    }
}

void Staff::addStudentAtIndex(LinkedList_Students* lStudents, const Student& student, int index){
    NodeStudent* p = getNodeStudentPointer(lStudents, index);
    addBeforeStudent(lStudents, p, student);
}

void Staff::deleteStudent(LinkedList_Students* lStudents, NodeStudent* pNodeStudent) {
    if (lStudents->head == NULL) return; // Danh sách trống

    NodeStudent* temp = lStudents->head;
    NodeStudent* prev = NULL;

    while (temp != NULL) {
        if(temp == pNodeStudent) break;
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    if (temp == lStudents->head) {
        lStudents->head = temp->next;
        if (lStudents->head == NULL) {
            lStudents->tail = NULL;
        }
        delete temp;
        return;
    }

    // Nếu khóa học cần xóa là cuối danh sách
    if (temp == lStudents->tail) {
        lStudents->tail = prev;
        lStudents->tail->next = NULL;
        delete temp;
        return;
    }

    // Xóa khóa học ở giữa danh sách
    prev->next = temp->next;
    delete temp;
}
// ham cho Classes


NodeClass* Staff::getNodeClassPointer(LinkedList_Classes* lClasses, const Class& Class){
    if(lClasses == NULL || lClasses->head == NULL) return NULL;
    NodeClass* pNodeClass = lClasses->head;
    while(pNodeClass != NULL && (pNodeClass->data != Class)){
        pNodeClass = pNodeClass->next;
    }
    return pNodeClass;
}

NodeClass* Staff::getNodeClassPointerByName(LinkedList_Classes *lClasses, const string& nameClass){
    if(lClasses == NULL || lClasses->head == NULL) return NULL;
    NodeClass* pNodeClass = lClasses->head;
    while(pNodeClass != NULL && (pNodeClass->data.getNameClass() != nameClass)){
        pNodeClass = pNodeClass->next;
    }
    return pNodeClass;
}

NodeClass* Staff::getNodeClassPointer(LinkedList_Classes* lClasses, int index){
    NodeClass* pNodeClass = lClasses->head;
    int currentIndex = 0;
    while(pNodeClass != NULL && currentIndex < index){
        pNodeClass = pNodeClass->next;
        currentIndex++;
    }
    return pNodeClass;
}

int Staff::getNodeClassIndex(LinkedList_Classes* lClasses, NodeClass* pNodeClass){
    if(lClasses->head == NULL) return -1;
    NodeClass* p = lClasses->head;
    int currentIndex = 0;
    while(p != NULL){
        if(p == pNodeClass){
            return currentIndex;
        }
        p = p->next;
        currentIndex++;
    }
    return -1;
}

NodeClass* Staff::getPreviousNodeClassPointer(LinkedList_Classes* lClasses, NodeClass* pNodeClass){
    NodeClass* p = lClasses->head;
    NodeClass* pPrev = NULL;
    while(p != NULL){
        if(p == pNodeClass){
            return pPrev;
        }
        pPrev = p;
        p = p->next;
    }
    return NULL;
}

void Staff::addHeadClass(LinkedList_Classes* lClasses, const Class& Class){
    NodeClass* pNodeClass = new NodeClass(Class);
    pNodeClass->next = lClasses->head;
    lClasses->head = pNodeClass;
    if(lClasses->tail == NULL) lClasses->tail = lClasses->head;
}

void Staff::addTailClass(LinkedList_Classes* lClasses, const Class& Class){
    NodeClass* pNodeClass = new NodeClass(Class);
    if(lClasses->tail == NULL){
        lClasses->head = lClasses->tail = pNodeClass;
        return;
    }
    lClasses->tail->next = pNodeClass;
    lClasses->tail = pNodeClass;
}

void Staff::addBeforeClass(LinkedList_Classes* lClasses, NodeClass* pNodeClassBefore, const Class& Class){
    if(pNodeClassBefore == NULL) return;
    if(pNodeClassBefore == lClasses->head){
        addHeadClass(lClasses, Class);
        return;
    }
    NodeClass* pNodeClass = new NodeClass(Class);
    NodeClass* p = getPreviousNodeClassPointer(lClasses, pNodeClassBefore);
    if(p == NULL) return;
    p->next = pNodeClass;
    pNodeClass->next = pNodeClassBefore;
}

void Staff::addAfterClass(LinkedList_Classes* lClasses, NodeClass* pNodeClassAfter, const Class& Class){
    NodeClass* pNodeClass = new NodeClass(Class);
    if(lClasses->head == NULL || pNodeClassAfter == NULL) return;
    NodeClass* p = lClasses->head;
    while(p != NULL){
        if(p == pNodeClassAfter) break;
        p = p->next;
    }
    if(p == NULL) return;
    pNodeClass->next = pNodeClassAfter->next;
    pNodeClassAfter->next = pNodeClass;
    if(pNodeClassAfter == lClasses->tail){
        lClasses->tail = pNodeClass;
    }
}

void Staff::addClassAtIndex(LinkedList_Classes* lClasses, const Class& Class, int index){
    NodeClass* p = getNodeClassPointer(lClasses, index);
    addBeforeClass(lClasses, p, Class);
}

void Staff::deleteClass(LinkedList_Classes* lClasses, NodeClass* pNodeClass) {
    if (lClasses->head == NULL) return; // Danh sách trống

    NodeClass* temp = lClasses->head;
    NodeClass* prev = NULL;

    // Tìm nút chứa khóa học cần xóa
    while (temp != NULL) {
        if(temp == pNodeClass) break;
        prev = temp;
        temp = temp->next;
    }

    // Nếu không tìm thấy khóa học cần xóa
    if (temp == NULL) return;

    // Nếu khóa học cần xóa là đầu danh sách
    if (temp == lClasses->head) {
        lClasses->head = temp->next;
        if (lClasses->head == NULL) {
            lClasses->tail = NULL; // Nếu danh sách trống sau khi xóa
        }
        delete temp;
        return;
    }

    // Nếu khóa học cần xóa là cuối danh sách
    if (temp == lClasses->tail) {
        lClasses->tail = prev;
        lClasses->tail->next = NULL;
        delete temp;
        return;
    }

    // Xóa khóa học ở giữa danh sách
    prev->next = temp->next;
    delete temp;
}
// hàm cho Semester
// Các hàm cho Semester

NodeSemester* Staff::getNodeSemesterPointer(LinkedList_Semesters* lSemesters, const Semester& semester){
    if(lSemesters == NULL) return NULL;
    NodeSemester* pNodeSemester = lSemesters->head;
    while(pNodeSemester != NULL && (pNodeSemester->data != semester)){
        pNodeSemester = pNodeSemester->next;
    }
    return pNodeSemester;
}

NodeSemester* Staff::getNodeSemesterPointerByName(LinkedList_Semesters* lSemesters, const string& nameSemester){
    NodeSemester* pNodeSemester = lSemesters->head;
    while(pNodeSemester != NULL && (pNodeSemester->data.getNameSemester() != nameSemester)){
        pNodeSemester = pNodeSemester->next;
    }
    return pNodeSemester;
}

NodeSemester* Staff::getNodeSemesterPointer(LinkedList_Semesters* lSemesters, int index){
    NodeSemester* pNodeSemester = lSemesters->head;
    int currentIndex = 0;
    while(pNodeSemester != NULL && currentIndex < index){
        pNodeSemester = pNodeSemester->next;
        currentIndex++;
    }
    return pNodeSemester;
}

int Staff::getNodeSemesterIndex(LinkedList_Semesters* lSemesters, NodeSemester* pNodeSemester){
    if(lSemesters->head == NULL) return -1;
    NodeSemester* p = lSemesters->head;
    int currentIndex = 0;
    while(p != NULL){
        if(p == pNodeSemester){
            return currentIndex;
        }
        p = p->next;
        currentIndex++;
    }
    return -1;
}

NodeSemester* Staff::getPreviousNodeSemesterPointer(LinkedList_Semesters* lSemesters, NodeSemester* pNodeSemester){
    NodeSemester* p = lSemesters->head;
    NodeSemester* pPrev = NULL;
    while(p != NULL){
        if(p == pNodeSemester){
            return pPrev;
        }
        pPrev = p;
        p = p->next;
    }
    return NULL;
}

void Staff::addHeadSemester(LinkedList_Semesters* lSemesters, const Semester& semester){
    NodeSemester* pNodeSemester = new NodeSemester(semester);
    pNodeSemester->next = lSemesters->head;
    lSemesters->head = pNodeSemester;
    if(lSemesters->tail == NULL) lSemesters->tail = lSemesters->head;
}

void Staff::addTailSemester(LinkedList_Semesters* lSemesters, const Semester& semester){
    NodeSemester* pNodeSemester = new NodeSemester(semester);
    if(lSemesters->tail == NULL){
        lSemesters->head = lSemesters->tail = pNodeSemester;
        return;
    }
    lSemesters->tail->next = pNodeSemester;
    lSemesters->tail = pNodeSemester;
}

void Staff::addBeforeSemester(LinkedList_Semesters* lSemesters, NodeSemester* pNodeSemesterBefore, const Semester& semester){
    if(pNodeSemesterBefore == NULL) return;
    if(pNodeSemesterBefore == lSemesters->head){
        addHeadSemester(lSemesters, semester);
        return;
    }
    NodeSemester* pNodeSemester = new NodeSemester(semester);
    NodeSemester* p = getPreviousNodeSemesterPointer(lSemesters, pNodeSemesterBefore);
    if(p == NULL) return;
    p->next = pNodeSemester;
    pNodeSemester->next = pNodeSemesterBefore;
}

void Staff::addAfterSemester(LinkedList_Semesters* lSemesters, NodeSemester* pNodeSemesterAfter, const Semester& semester){
    NodeSemester* pNodeSemester = new NodeSemester(semester);
    if(lSemesters->head == NULL || pNodeSemesterAfter == NULL) return;
    NodeSemester* p = lSemesters->head;
    while(p != NULL){
        if(p == pNodeSemesterAfter) break;
        p = p->next;
    }
    if(p == NULL) return;
    pNodeSemester->next = pNodeSemesterAfter->next;
    pNodeSemesterAfter->next = pNodeSemester;
    if(pNodeSemesterAfter == lSemesters->tail){
        lSemesters->tail = pNodeSemester;
    }
}

void Staff::addSemesterAtIndex(LinkedList_Semesters* lSemesters, const Semester& semester, int index){
    NodeSemester* p = getNodeSemesterPointer(lSemesters, index);
    addBeforeSemester(lSemesters, p, semester);
}

void Staff::deleteSemester(LinkedList_Semesters* lSemesters, NodeSemester* pNodeSemester) {
    if (lSemesters->head == NULL) return; // Danh sách trống

    NodeSemester* temp = lSemesters->head;
    NodeSemester* prev = NULL;

    // Tìm nút chứa khóa học cần xóa
    while (temp != NULL) {
        if(temp == pNodeSemester) break;
        prev = temp;
        temp = temp->next;
    }

    // Nếu không tìm thấy khóa học cần xóa
    if (temp == NULL) return;

    // Nếu khóa học cần xóa là đầu danh sách
    if (temp == lSemesters->head) {
        lSemesters->head = temp->next;
        if (lSemesters->head == NULL) {
            lSemesters->tail = NULL; // Nếu danh sách trống sau khi xóa
        }
        delete temp;
        return;
    }

    // Nếu khóa học cần xóa là cuối danh sách
    if (temp == lSemesters->tail) {
        lSemesters->tail = prev;
        lSemesters->tail->next = NULL;
        delete temp;
        return;
    }

    // Xóa khóa học ở giữa danh sách
    prev->next = temp->next;
    delete temp;
}
// ham cho SchoolYears


NodeSchoolYear* Staff::getNodeSchoolYearPointer(LinkedList_SchoolYears* lSchoolYears, const SchoolYear& schoolyear){
    NodeSchoolYear* pNodeSchoolYear = lSchoolYears->head;
    while(pNodeSchoolYear != NULL && (pNodeSchoolYear->data != schoolyear)){
        pNodeSchoolYear = pNodeSchoolYear->next;
    }
    return pNodeSchoolYear;
}

NodeSchoolYear* Staff::getNodeSchoolYearPointerByName(LinkedList_SchoolYears* lSchoolYears, const string& nameSchoolYear){
    if(lSchoolYears == NULL) return NULL;
    NodeSchoolYear* pNodeSchoolYear = lSchoolYears->head;
    while(pNodeSchoolYear != NULL && (pNodeSchoolYear->data.getNameSchoolYear() != nameSchoolYear)){
        pNodeSchoolYear = pNodeSchoolYear->next;
    }
    return pNodeSchoolYear;
}

NodeSchoolYear* Staff::getNodeSchoolYearPointer(LinkedList_SchoolYears* lSchoolYears, int index){
    NodeSchoolYear* pNodeSchoolYear = lSchoolYears->head;
    int currentIndex = 0;
    while(pNodeSchoolYear != NULL && currentIndex < index){
        pNodeSchoolYear = pNodeSchoolYear->next;
        currentIndex++;
    }
    return pNodeSchoolYear;
}

int Staff::getNodeSchoolYearIndex(LinkedList_SchoolYears* lSchoolYears, NodeSchoolYear* pNodeSchoolYear){
    if(lSchoolYears->head == NULL) return -1;
    NodeSchoolYear* p = lSchoolYears->head;
    int currentIndex = 0;
    while(p != NULL){
        if(p == pNodeSchoolYear){
            return currentIndex;
        }
        p = p->next;
        currentIndex++;
    }
    return -1;
}

NodeSchoolYear* Staff::getPreviousNodeSchoolYearPointer(LinkedList_SchoolYears* lSchoolYears, NodeSchoolYear* pNodeSchoolYear){
    NodeSchoolYear* p = lSchoolYears->head;
    NodeSchoolYear* pPrev = NULL;
    while(p != NULL){
        if(p == pNodeSchoolYear){
            return pPrev;
        }
        pPrev = p;
        p = p->next;
    }
    return NULL;
}

void Staff::addHeadSchoolYear(LinkedList_SchoolYears* lSchoolYears, const SchoolYear& schoolyear){
    NodeSchoolYear* pNodeSchoolYear = new NodeSchoolYear(schoolyear);
    pNodeSchoolYear->next = lSchoolYears->head;
    lSchoolYears->head = pNodeSchoolYear;
    if(lSchoolYears->tail == NULL) lSchoolYears->tail = lSchoolYears->head;
}

void Staff::addTailSchoolYear(LinkedList_SchoolYears* lSchoolYears, const SchoolYear& schoolyear){
    NodeSchoolYear* pNodeSchoolYear = new NodeSchoolYear(schoolyear);
    if(lSchoolYears->tail == NULL){
        lSchoolYears->head = lSchoolYears->tail = pNodeSchoolYear;
        return;
    }
    lSchoolYears->tail->next = pNodeSchoolYear;
    lSchoolYears->tail = pNodeSchoolYear;
}

void Staff::addBeforeSchoolYear(LinkedList_SchoolYears* lSchoolYears, NodeSchoolYear* pNodeSchoolYearBefore, const SchoolYear& schoolyear){
    if(pNodeSchoolYearBefore == NULL) return;
    if(pNodeSchoolYearBefore == lSchoolYears->head){
        addHeadSchoolYear(lSchoolYears, schoolyear);
        return;
    }
    NodeSchoolYear* pNodeSchoolYear = new NodeSchoolYear(schoolyear);
    NodeSchoolYear* p = getPreviousNodeSchoolYearPointer(lSchoolYears, pNodeSchoolYearBefore);
    if(p == NULL) return;
    p->next = pNodeSchoolYear;
    pNodeSchoolYear->next = pNodeSchoolYearBefore;
}

void Staff::addAfterSchoolYear(LinkedList_SchoolYears* lSchoolYears, NodeSchoolYear* pNodeSchoolYearAfter, const SchoolYear& schoolyear){
    NodeSchoolYear* pNodeSchoolYear = new NodeSchoolYear(schoolyear);
    if(lSchoolYears->head == NULL || pNodeSchoolYearAfter == NULL) return;
    NodeSchoolYear* p = lSchoolYears->head;
    while(p != NULL){
        if(p == pNodeSchoolYearAfter) break;
        p = p->next;
    }
    if(p == NULL) return;
    pNodeSchoolYear->next = pNodeSchoolYearAfter->next;
    pNodeSchoolYearAfter->next = pNodeSchoolYear;
    if(pNodeSchoolYearAfter == lSchoolYears->tail){
        lSchoolYears->tail = pNodeSchoolYear;
    }
}

void Staff::addSchoolYearAtIndex(LinkedList_SchoolYears* lSchoolYears, const SchoolYear& schoolyear, int index){
    NodeSchoolYear* p = getNodeSchoolYearPointer(lSchoolYears, index);
    addBeforeSchoolYear(lSchoolYears, p, schoolyear);
}

void Staff::deleteSchoolYear(LinkedList_SchoolYears* lSchoolYears, NodeSchoolYear* pNodeSchoolYear) {
    if (lSchoolYears->head == NULL) return; // Danh sách trống

    NodeSchoolYear* temp = lSchoolYears->head;
    NodeSchoolYear* prev = NULL;

    // Tìm nút chứa khóa học cần xóa
    while (temp != NULL) {
        if(temp == pNodeSchoolYear) break;
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    if (temp == lSchoolYears->head) {
        lSchoolYears->head = temp->next;
        if (lSchoolYears->head == NULL) {
            lSchoolYears->tail = NULL;
        }
        delete temp;
        return;
    }


    if (temp == lSchoolYears->tail) {
        lSchoolYears->tail = prev;
        lSchoolYears->tail->next = NULL;
        delete temp;
        return;
    }

    prev->next = temp->next;
    delete temp;
}

//
LinkedList_Students* Staff::listStudentsOfCourse(const string& nameYear, const string& nameSemester, const string& nameClass){
    NodeSchoolYear* nodeSchoolYear = getNodeSchoolYearPointerByName(getListSchoolYearsOfSchool(), nameYear);
    if(nodeSchoolYear == NULL) return NULL;
    SchoolYear schoolYear = nodeSchoolYear->data;
    // delete nodeSchoolYear;
    NodeSemester* nodeSemester = getNodeSemesterPointerByName(schoolYear.getListSemesters(),nameSemester);
    if(nodeSemester == NULL) return NULL;
    Semester semester = nodeSemester->data;
    // delete nodeSemester;
    NodeCourse* nodeCourse= getNodeCoursePointerByName(semester.getListCourses(),nameClass);
    if(nodeCourse == NULL) return NULL;
    Course course = nodeCourse->data;
    // delete nodeCourse;
    return course.getListStudents();
}
LinkedList_Classes* Staff::listClassesInYear(const string& nameYear){
    // duyệt qua danh sách class lớp của trường
    LinkedList_Classes* listClasses = getListClassesOfSchool();
    if(listClasses == NULL || listClasses->head == NULL) return NULL;
    LinkedList_Classes* listClassesInYear = new LinkedList_Classes;
    NodeClass* tmp = listClasses->head;
    while(tmp != NULL){
        string nameClass = tmp->data.getNameClass();
        if(nameClass.substr(0,2)==nameYear.substr(2,2)){ // so khớp 23CTT5 vs 2023-2024
            addTailClass(listClassesInYear,tmp->data);
        }
        tmp = tmp->next;
    }
    return listClassesInYear;
}
LinkedList_Students* Staff::findListStudentsOfAClassInYear(const string& nameYear, const string nameClass){
    LinkedList_Classes* ClassesInYear = listClassesInYear(nameYear);
    if(ClassesInYear == NULL) return NULL;
    NodeClass* nodeClass = getNodeClassPointerByName(ClassesInYear,nameClass);
    if(nodeClass == NULL) return NULL;
    return nodeClass->data.getListStudents();
}
NodeStudent* Staff::findStudentByID(LinkedList_Classes* lClasses,const string& mssv){
    if(lClasses == NULL || lClasses->head == NULL) return NULL;
    NodeClass* tmp = lClasses->head;
    while(tmp != NULL){
        NodeStudent* pStudent = getNodeStudentPointerByID(tmp->data.getListStudents(),mssv);
        if(pStudent != NULL) return pStudent;
        tmp = tmp->next;
    }
    return NULL;
}
NodeSemester* Staff::findSemesterInYear(LinkedList_SchoolYears* lSchoolYears ,const string& nameYear, const string& nameSemester){
    NodeSchoolYear* pYear = getNodeSchoolYearPointerByName(lSchoolYears,nameYear);
    if(pYear == 0) return NULL;
    return getNodeSemesterPointerByName(pYear->data.getListSemesters(),nameSemester);
}

LinkedList_Courses* Staff::listCourseOfStudent(const string& mssv, const string& nameYear, const string& nameSemester){
    NodeStudent* pStudent = findStudentByID(getListClassesOfSchool(),mssv);
    if(pStudent == NULL) return NULL;
    NodeSemester* pSemester = findSemesterInYear(pStudent->data.getListSchoolYearsOfSchool(),nameYear,nameSemester);
    if(pSemester == NULL) return NULL;
    return pSemester->data.getListCourses();
}

LinkedList_Courses* Staff::listCourseOfSemester( LinkedList_SchoolYears* lSchoolYears ,const string& nameYear,const string& nameSemester){
    NodeSemester* pSemester = findSemesterInYear(lSchoolYears,nameYear,nameSemester);
    if(pSemester == NULL) return NULL;
    return pSemester->data.getListCourses();
}
