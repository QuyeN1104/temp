#include"staff.h"
#include"course.h"
#include"library.h"
#include"schoolyear.h"
#include"semester.h"
#include"student.h"
#include"class.h"
#include"mark.h"

//khởi tạo giá trị biến static
LinkedList_SchoolYears* Staff::listSchoolYearsOfSchool = nullptr;

Staff::Staff() {
    if (listSchoolYearsOfSchool == nullptr) {
        listSchoolYearsOfSchool = new LinkedList_SchoolYears();
    }
}

LinkedList_SchoolYears* Staff::getListSchoolYearsOfSchool() const {
    return listSchoolYearsOfSchool;
}

//

void Staff::setCourse(Course* course,string id, string name, string className, string teacherName, int numCredits,
                      string dayofWeek, string session){
    if(course){
        Course* newCourse = new Course(id,name,className,teacherName,numCredits,dayofWeek,session);
        string nameClass = course->getClassName();
        string nameYear, nameSemester;
        splitYearandSemester(nameClass,nameYear,nameSemester);
        // thay đổi khoa học trong ds khóa học của hs
        NodeStudent* tmp = course->getListStudents()->head;
        while(tmp){
            Student* st = &(tmp->data);
            Course* pCourse = st->findCourseByClassName(nameYear,nameSemester,nameClass);
            if(pCourse){
                pCourse->className = newCourse->getClassName();
                pCourse->dayofWeek = newCourse->getDayofWeek();
                pCourse->idCourse = newCourse->getIdCourse();
                pCourse->nameCourse = newCourse->getNameCourse();
                pCourse->numCredits = newCourse->getNumCredits();
                pCourse->session = newCourse->getSession();
                pCourse->teacherName = newCourse->getTeacherName();
            }
            tmp = tmp->next;
        }
        // thay doi khóa học
        course->className = newCourse->getClassName();
        course->dayofWeek = newCourse->getDayofWeek();
        course->idCourse = newCourse->getIdCourse();
        course->nameCourse = newCourse->getNameCourse();
        course->numCredits = newCourse->getNumCredits();
        course->session = newCourse->getSession();
        course->teacherName = newCourse->getTeacherName();
        delete newCourse;
    }
}

void Staff::change_idCourse(Course* course, string newIdCourse) {
    if (course) {
        course->idCourse = newIdCourse;
        updateCourseforStudent(course);
    }
}

void Staff::change_nameCourse(Course* course, string newNameCourse) {
    if (course) {
        course->nameCourse = newNameCourse;
        updateCourseforStudent(course);
    }
}

void Staff::change_className(Course* course, string newClassName) {
    if (course) {
        string nameClass = course->getClassName();
        string nameYear, nameSemester;
        splitYearandSemester(nameClass,nameYear,nameSemester);
        NodeStudent* tmp = course->getListStudents()->head;
        while(tmp){
            Student* st = &(tmp->data);
            Course* pCourse = st->findCourseByClassName(nameYear,nameSemester,nameClass);
            if(pCourse){
                pCourse->className = newClassName;
            }
            tmp = tmp->next;
        }
        course->className = newClassName;
    }
}

void Staff::change_teacherName(Course* course, string newTeacherName) {
    if (course) {
        course->teacherName = newTeacherName;
        updateCourseforStudent(course);
    }
}

void Staff::change_numCredits(Course* course, int newNumCredits) {
    if (course) {
        course->numCredits = newNumCredits;
        updateCourseforStudent(course);
    }
}

void Staff::change_session(Course* course, string newSession) {
    if (course) {
        course->session = newSession;
        updateCourseforStudent(course);
    }
}

void Staff::change_dayofWeek(Course* course, string newDayofWeek) {
    if (course) {
        course->dayofWeek = newDayofWeek;
        updateCourseforStudent(course);
    }
}

void Staff::change_maxStudents(Course* course, int newMaxStudents) {
    if (course) {
        course->maxStudents = newMaxStudents;
        updateCourseforStudent(course);
    }
}
void Staff::updateCourseforStudent(Course* course){
    if(!course) return;
    string nameClass = course->getClassName();
    string nameYear, nameSemester;
    splitYearandSemester(nameClass,nameYear,nameSemester);
    NodeStudent* tmp = course->getListStudents()->head;
    while(tmp){
        Student* st = &(tmp->data);
        Course* pCourse = st->findCourseByClassName(nameYear,nameSemester,nameClass);
        if(pCourse){
            *pCourse = *course;
        }
        tmp = tmp->next;
    }
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

bool Staff::exportCourseCsvFile(Course* course,const string& fileDirect){
    string filePath;
    if(fileDirect.find(".csv") != string::npos) filePath = fileDirect;
    else filePath = fileDirect + "/" + course->getClassName() + "_scores.csv"; // đã tạo file
    ofstream f;
    f.open(filePath);
    if(!f.is_open()){
        return false;
    }
    // đọc header
    f << "No,StudentID,Student Full Name,Other Mark,Midterm Mark,Final Mark,Total Mark" << endl;
    int no = 1;
    if(course == NULL || course->getListStudents() == NULL ) return false;
    NodeStudent* tmp = course->getListStudents()->head;
    while(tmp){
        f<< no << "," << tmp->data.getStudentID() << "," << tmp->data.getFirstName() << " " << tmp->data.getLastName() << ",";
        if(tmp->data.markOfCourse->otherMark != -1) f << tmp->data.markOfCourse->otherMark;
        f << ",";
        if(tmp->data.markOfCourse->midtermMark != -1) f << tmp->data.markOfCourse->otherMark;
        f << ",";
        if(tmp->data.markOfCourse->finalMark != -1) f << tmp->data.markOfCourse->otherMark;
        f << ",";
        if(tmp->data.markOfCourse->totalMark != -1) f << tmp->data.markOfCourse->otherMark;
        f<<'\n';
        no++;
        tmp = tmp->next;
    }
    f.close();
    return true;
}
bool Staff::importCourseCsvFile(Course* course, const string& fileName) {
    if (course == NULL) return false;

    string nameClass = course->getClassName();
    string nameYear, nameSemester;
    splitYearandSemester(nameClass,nameYear,nameSemester);
    int numRows;
    string** data = processCsvFile(fileName, numRows);

    if (!data) return false;

    NodeStudent* tmp = course->getListStudents()->head;
    for (int i = 0; i < numRows; i++) {
        if (!tmp) break;  // Kiểm tra nếu danh sách rỗng hoặc đã hết sinh viên

        double other = stod(data[i][2]);
        double mid = stod(data[i][3]);
        double final = stod(data[i][4]);
        double total = stod(data[i][5]);
        Mark* mark = new Mark(course,other, mid, final, total);

        // Xóa đối tượng Mark cũ nếu có để tránh rò rỉ bộ nhớ
        delete tmp->data.markOfCourse;
        tmp->data.markOfCourse = mark;
        tmp = tmp->next;
    }
    tmp = course->getListStudents()->head;
    for (int i = 0; i < numRows; i++) {
        if (!tmp) break;  // Kiểm tra nếu danh sách rỗng hoặc đã hết sinh viên
        Student* pStudent = findStudentByID(data[i][0]);
        if(!pStudent) continue;
        Semester* semester = findSemesterInYear(pStudent->getListSchoolYearsOfSchool(),nameYear,nameSemester);
        if(!semester) continue;
        double other = stod(data[i][2]);
        double mid = stod(data[i][3]);
        double final = stod(data[i][4]);
        double total = stod(data[i][5]);
        Mark* mark = new Mark(course,other, mid, final, total);
        addTailMark(semester->getListMarks(),*mark);
        // Xóa đối tượng Mark cũ nếu có để tránh rò rỉ bộ nhớ
        tmp = tmp->next;
    }

    deletePointerData(data, numRows);
    return true;
}



// fileDirection ex : 23CTT5.csv
bool Staff::loadStudentsInClass(LinkedList_Students* lStudents ,const string& fileDirection){
    bool loaded = false;
    int numRows;
    string** data = processCsvFile(fileDirection,numRows);
    if(data == NULL) return false;
    string nameClass = splitNameClassFromFile(fileDirection);
    for(int i = 0; i < numRows; i++){
        // gán từng data[i] vào các NodeStudent
        Student student(data[i],nameClass);
        addTailStudent(lStudents,student);
        loaded = true;
    }
    deletePointerData(data,numRows);
    return loaded;
}

void Staff::deleteStudentFromCourse(Course* course, const string& mssv){
    NodeStudent* pStudent = getNodeStudentPointer(course->getListStudents(),mssv);
    if(pStudent == NULL) return;
    delete pStudent->data.markOfCourse;
    // pStudent->data.markOfCourse = NULL;
    deleteStudent(course->getListStudents(),pStudent);
    // xóa khóa học khỏi ds của hs
    string nameYear,nameSemester;
    splitYearandSemester(course->getClassName(),nameYear,nameSemester);
    Student* st = findStudentByID(mssv);
    if(!st) return;
    Semester* semester = findSemesterInYear(st->getListSchoolYearsOfSchool(),nameYear,nameSemester);
    if(!semester) return;
    LinkedList_Courses* lCourses = semester->getListCourses();
    if(lCourses == NULL) return;
    // Course* pCourse = getCourseByName(lCourses,course->getClassName());
    NodeCourse* pCourse = getNodeCoursePointer(lCourses,*course);
    if(pCourse == NULL) return;
    deleteCourse(lCourses,pCourse);
    // xóa ds điểm của khóa học đó
    LinkedList_Marks* lMarks = semester->getListMarks();
    NodeMark* pMark = getNodeMarkPointer(lMarks,course);
    if(!pMark) return;
    deleteMark(lMarks,pMark);
}

void Staff::deleteCourse(LinkedList_Courses* lCourses, Course* course){
    if(course == NULL || lCourses == NULL) return;
    if(course->listStudentsOfCourse){
        NodeStudent* pStudent = course->getListStudents()->head;
        // xóa khóa học ra khỏi ds của học sinh
        while(pStudent){
            string nameYear,nameSemester;
            splitYearandSemester(course->getClassName(),nameYear,nameSemester);
            Student* st = findStudentByID(pStudent->data.getStudentID());
            if(!st) return;
            Semester* semester = findSemesterInYear(st->getListSchoolYearsOfSchool(),nameYear,nameSemester);
            if(!semester) return;
            LinkedList_Courses* lCourses = semester->getListCourses();
            if(lCourses == NULL) return;
            // Course* pCourse = getCourseByName(lCourses,course->getClassName());
            NodeCourse* pCourse = getNodeCoursePointer(lCourses,*course);
            if(pCourse == NULL) return;
            deleteCourse(lCourses,pCourse);
            // xóa ds điểm của khóa học đó
            LinkedList_Marks* lMarks = semester->getListMarks();
            NodeMark* pMark = getNodeMarkPointer(lMarks,course);
            if(!pMark) return;
            deleteMark(lMarks,pMark);
            pStudent = pStudent->next;
        }
        pStudent = course->getListStudents()->head;
        while(pStudent){
            NodeStudent* tmp = pStudent;
            pStudent = pStudent->next;
            delete tmp;
        }
        delete course->getListStudents();
    }
    // delete course;
    // xóa course ra khỏi danh sách
    NodeCourse* pCourse = getNodeCoursePointer(lCourses,*course);
    if(pCourse == NULL) return;
    deleteCourse(lCourses,pCourse);

}

Student* Staff::addStudentInClass(Class* Class, Student* newStudent){
    if(Class == NULL || newStudent == NULL) return NULL;
    // lấy enrolledClass từ Class cho học sinh
    newStudent->setEnrollClass(Class->getNameClass());
    // thêm học sinh đó vào lớp
    Student* student = addTailStudent(Class->getListStudents(),*newStudent);
    return student;
}

bool Staff::loadStudentsInCourse(LinkedList_Students* lStudents, const string& fileDirection){
    string nameYear = "", nameSemester = "";
    string nameClass = splitYearandSemesterfromFile(fileDirection,nameYear,nameSemester);
    Course* course = findCourseByClassName(nameYear,nameSemester,nameClass);
    if(course == NULL) return false;
    int numRows;
    bool loaded = false;
    string** data = processCsvFile(fileDirection,numRows);
    if(data == NULL) return false;
    for(int i = 0; i < numRows; i++){
        Student* student = findStudentByID(data[i][0]); // mssv được lưu trường đầu tiên trong data
        if(student == NULL) continue; // không có học sinh này trong trường
        // thêm học sinh đó vào danh sách học sinh của khóa học (sau có thể thêm điều kiện ràng buộc vào)
        Student* studentInCourse = addTailStudent(lStudents,*student);
        studentInCourse->setMark(); // tạo ô nhớ cho điểm của môn học đó
        // thêm khóa học đó vào danh sách của học sinh
        // kiểm tra năm học đó có tồn tại không
        SchoolYear* year = getSchoolYearByName(student->getListSchoolYearsOfSchool(),nameYear);
        // nếu chưa tồn tại năm học đó
        if(year == NULL) {
            year = addTailSchoolYear(student->getListSchoolYearsOfSchool(),nameYear);
            year->deletelistClasses();
        }
        Semester* semester = getSemesterByName(year->getListSemesters(),nameSemester);
        if(semester == NULL){
            semester = addTailSemester(year->getListSemesters(),nameSemester);
            semester->initListMarks(); // cấp phát ô nhớ
        }
        // Thêm khóa học vào đúng năm học và kì học đó cho sinh viên
        addTailCourse(semester->getListCourses(),*course);
        loaded = true;
    }
    deletePointerData(data,numRows);
    return loaded;
}
Student* Staff::addStudentInCourse(Course* course, Student* newStudent){
    Student* student = findStudentByID(newStudent->getStudentID());
    if(student == NULL) return NULL;
    if(course == NULL || newStudent == NULL) return NULL;
    string nameClass = course->getClassName();
    string nameYear = fullNameSchoolYear(nameClass.substr(0,2));
    string nameSemester = nameClass.substr(2,1);
        // thêm học sinh đó vào danh sách học sinh của khóa học (sau có thể thêm điều kiện ràng buộc vào)
    Student* studentInCourse = addTailStudent(course->getListStudents(),*newStudent);
    if(!studentInCourse) return NULL;
    studentInCourse->setMark(); // tạo ô nhớ cho điểm của môn học đó
    // thêm khóa học đó vào danh sách của học sinh
    // kiểm tra năm học đó có tồn tại không
    SchoolYear* year = getSchoolYearByName(student->getListSchoolYearsOfSchool(),nameYear);
    // nếu chưa tồn tại năm học đó
    if(year == NULL) {
        year = addTailSchoolYear(student->getListSchoolYearsOfSchool(),nameYear);
        year->deletelistClasses();
    }
    Semester* semester = getSemesterByName(year->getListSemesters(),nameSemester);
    if(semester == NULL){
        semester = addTailSemester(year->getListSemesters(),nameSemester);
        semester->initListMarks(); // cấp phát ô nhớ
    }
    // Thêm khóa học vào đúng năm học và kì học đó cho sinh viên
    addTailCourse(semester->getListCourses(),*course);
    return studentInCourse;
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

Course* Staff::getCourseByName(LinkedList_Courses* lCourses, const string& nameClass){
    if(lCourses == NULL || lCourses->head == NULL) return NULL;
    NodeCourse* pNodeCourse = lCourses->head;
    while(pNodeCourse != NULL && (pNodeCourse->data.getClassName() != nameClass)){
        pNodeCourse = pNodeCourse->next;
    }
    if(pNodeCourse == NULL) return NULL;
    return &pNodeCourse->data;
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

Course* Staff::addTailCourse(LinkedList_Courses* lCourses, const Course& course){
    NodeCourse* pNodeCourse = new NodeCourse(course);
    if(pNodeCourse == NULL || lCourses == NULL) return NULL;
    if(lCourses->head == NULL){
        lCourses->head = lCourses->tail =  pNodeCourse;
        return &(pNodeCourse->data);
    }
    lCourses->tail->next = pNodeCourse;
    lCourses->tail = pNodeCourse;
    return &(pNodeCourse->data);
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

Student* Staff::getStudentByID(LinkedList_Students* lStudents, const string& mssv){
    if(lStudents == NULL || lStudents->head == NULL ) return NULL;
    NodeStudent* pNodeStudent = lStudents->head;
    while(pNodeStudent != NULL && (pNodeStudent->data.getStudentID() != mssv)){
        pNodeStudent = pNodeStudent->next;
    }
    if(pNodeStudent == NULL) return NULL;
    return &pNodeStudent->data;
}

NodeStudent* Staff::getNodeStudentPointer(LinkedList_Students* lStudents, const Student& student){
    if(lStudents == NULL || lStudents->head == NULL ) return NULL;
    NodeStudent* pNodeStudent = lStudents->head;
    while(pNodeStudent != NULL && (pNodeStudent->data != student)){
        pNodeStudent = pNodeStudent->next;
    }
    return pNodeStudent;
}

NodeStudent* Staff::getNodeStudentPointer(LinkedList_Students* lStudents, const string& mssv){
    if(lStudents == NULL || lStudents->head == NULL ) return NULL;
    NodeStudent* pNodeStudent = lStudents->head;
    while(pNodeStudent != NULL && (pNodeStudent->data.getStudentID() != mssv)){
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

Student* Staff::addTailStudent(LinkedList_Students* lStudents, const Student& student){
    NodeStudent* pNodeStudent = new NodeStudent(student);
    if(pNodeStudent == NULL || lStudents == NULL) return NULL;
    if(lStudents->tail == NULL){
        lStudents->head = pNodeStudent;
    }
    else lStudents->tail->next = pNodeStudent;
    lStudents->tail = pNodeStudent;
    return &(pNodeStudent->data);
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

    // Nếu học sinh cần xóa là cuối danh sách
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

Class* Staff::getClassByName(LinkedList_Classes *lClasses, const string& nameClass){
    if(lClasses == NULL || lClasses->head == NULL) return NULL;
    NodeClass* pNodeClass = lClasses->head;
    while(pNodeClass != NULL && (pNodeClass->data.getNameClass() != nameClass)){
        pNodeClass = pNodeClass->next;
    }
    if(pNodeClass == NULL) return NULL;
    return &pNodeClass->data;
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

Class* Staff::addTailClass(LinkedList_Classes* lClasses, const Class& Class){
    NodeClass* pNodeClass = new NodeClass(Class);
    if(lClasses == NULL || pNodeClass == NULL) return NULL;
    if(lClasses->tail == NULL){
        lClasses->head = pNodeClass;
    }
    else lClasses->tail->next = pNodeClass;
    lClasses->tail = pNodeClass;
    return &pNodeClass->data;
}

Class* Staff::addTailClass(LinkedList_Classes* lClasses, const string& nameClass){
    Class newClass(nameClass);
    return addTailClass(lClasses,newClass);
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

Semester* Staff::getSemesterByName(LinkedList_Semesters* lSemesters, const string& nameSemester){
    if(lSemesters == NULL || lSemesters->head == NULL) return NULL;
    NodeSemester* pNodeSemester = lSemesters->head;
    while(pNodeSemester != NULL && (pNodeSemester->data.getNameSemester() != nameSemester)){
        pNodeSemester = pNodeSemester->next;
    }
    if(pNodeSemester == NULL) return nullptr;
    return &pNodeSemester->data;
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

Semester* Staff::addTailSemester(LinkedList_Semesters* lSemesters, const Semester& semester){
    NodeSemester* pNodeSemester = new NodeSemester(semester);
    if(pNodeSemester == NULL || lSemesters == NULL) return NULL;
    if(lSemesters->tail == NULL){
        lSemesters->head = pNodeSemester;
    }
    else lSemesters->tail->next = pNodeSemester;
    lSemesters->tail = pNodeSemester;
    return &pNodeSemester->data;
}

Semester* Staff::addTailSemester(LinkedList_Semesters* lSemesters, const string& nameSemester){
    Semester semester(nameSemester);
    return addTailSemester(lSemesters,semester);
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

SchoolYear* Staff::getSchoolYearByName(LinkedList_SchoolYears* lSchoolYears, const string& nameSchoolYear){
    if(lSchoolYears == NULL||lSchoolYears->head == NULL) return NULL;
    NodeSchoolYear* pNodeSchoolYear = lSchoolYears->head;
    while(pNodeSchoolYear != NULL && (pNodeSchoolYear->data.getNameSchoolYear() != nameSchoolYear)){
        pNodeSchoolYear = pNodeSchoolYear->next;
    }
    if(pNodeSchoolYear == NULL) return NULL;
    return &pNodeSchoolYear->data;
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

SchoolYear* Staff::addTailSchoolYear(LinkedList_SchoolYears* lSchoolYears, const SchoolYear& schoolyear){
    NodeSchoolYear* pNodeSchoolYear = new NodeSchoolYear(schoolyear);
    if(pNodeSchoolYear == NULL || lSchoolYears == NULL) return NULL;
    if(lSchoolYears->tail == NULL){
        lSchoolYears->head = pNodeSchoolYear;
    }
    else lSchoolYears->tail->next = pNodeSchoolYear;
    lSchoolYears->tail = pNodeSchoolYear;
    return &pNodeSchoolYear->data;
}
SchoolYear* Staff::addTailSchoolYear(LinkedList_SchoolYears* lSchoolYears, const string& nameSchoolyear){
    SchoolYear newSchoolyear(nameSchoolyear);
    return addTailSchoolYear(lSchoolYears,newSchoolyear);
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
    Semester* semester = findSemesterInYear(getListSchoolYearsOfSchool(),nameYear,nameSemester);
    if(semester == NULL) return NULL;
    Course* course= getCourseByName(semester->getListCourses(),nameClass);
    if(course == NULL) return NULL;
    return course->getListStudents();
}
LinkedList_Classes* Staff::listClassesInYear(const string& nameYear){
    SchoolYear* year = getSchoolYearByName(getListSchoolYearsOfSchool(),nameYear);
    if(year == NULL) return NULL;
    return year->getListClassesOfYear();
}

Student* Staff::findStudentByID(const string& mssv){
    SchoolYear* year = findEnrolledYearOfAStudent(mssv);
    if(year == NULL) return NULL;
    LinkedList_Classes* lClasses = year->getListClassesOfYear();
    if(lClasses == NULL || lClasses->head == NULL) return NULL;
    NodeClass* tmp = lClasses->head;
    while(tmp != NULL){
        Student* pStudent = getStudentByID(tmp->data.getListStudents(),mssv);
        if(pStudent != NULL) return pStudent;
        tmp = tmp->next;
    }
    return NULL;
}

Course* Staff::findCourseByClassName(const string& nameYear,const string& nameSemester,const string& nameClass){
    LinkedList_Courses* lCourses = listCourseOfSemester(getListSchoolYearsOfSchool(),nameYear,nameSemester);
    if(lCourses == nullptr) return NULL;
    Course* course = getCourseByName(lCourses,nameClass);
    return course;
}

Semester* Staff::findSemesterInYear(LinkedList_SchoolYears* lSchoolYears ,const string& nameYear, const string& nameSemester){
    SchoolYear* pYear = getSchoolYearByName(lSchoolYears,nameYear);
    if(pYear == NULL) return NULL;
    return getSemesterByName(pYear->getListSemesters(),nameSemester);
}

LinkedList_Courses* Staff::listCourseOfStudent(const string& mssv, const string& nameYear, const string& nameSemester){
    Student* pStudent = findStudentByID(mssv);
    if(pStudent == NULL) return NULL;
    Semester* pSemester = findSemesterInYear(pStudent->getListSchoolYearsOfSchool(),nameYear,nameSemester);
    if(pSemester == NULL) return NULL;
    return pSemester->getListCourses();
}

LinkedList_Courses* Staff::listCourseOfSemester( LinkedList_SchoolYears* lSchoolYears ,const string& nameYear,const string& nameSemester){
    Semester* pSemester = findSemesterInYear(lSchoolYears,nameYear,nameSemester);
    if(pSemester == NULL) return NULL;
    return pSemester->getListCourses();
}
SchoolYear* Staff::findEnrolledYearOfAStudent(const string& mssv){
    string year = fullNameSchoolYear(mssv);
    return getSchoolYearByName(getListSchoolYearsOfSchool(),year);
}
Student* Staff::IsStudent(const string& userName,const string& passWord){
    Student* student = findStudentByID(userName); // userName is mssv
    if(student == NULL) return NULL;
    if(student->getPassWord() == passWord) return student;
    return NULL;
}

Mark* Staff::addTailMark(LinkedList_Marks* lMarks, const Mark& Mark) {
    NodeMark* pNodeMark = new NodeMark(Mark);
    if (pNodeMark == NULL || lMarks == NULL) return NULL;
    if (lMarks->tail == NULL) {
        lMarks->head = pNodeMark;
    }
    else lMarks->tail->next = pNodeMark;
    lMarks->tail = pNodeMark;
    return &pNodeMark->data;
}
NodeMark* Staff::getNodeMarkPointer(LinkedList_Marks* lMarks,Course* course){
    if (lMarks->head == NULL) return NULL;
    NodeMark* pNodeMark = lMarks->head;
    while (pNodeMark != NULL && (pNodeMark->data.course->getClassName() != course->getClassName())) {
        pNodeMark = pNodeMark->next;
    }
    return pNodeMark;
}
void Staff::deleteMark(LinkedList_Marks* lMarks, NodeMark* pNodeMark) {
    if (lMarks->head == NULL) return; // Danh sách trống

    NodeMark* temp = lMarks->head;
    NodeMark* prev = NULL;

    // Tìm nút chứa khóa học cần xóa
    while (temp != NULL) {
        if (temp == pNodeMark) break;
        prev = temp;
        temp = temp->next;
    }

    // Nếu không tìm thấy khóa học cần xóa
    if (temp == NULL) return;

    // Nếu khóa học cần xóa là đầu danh sách
    if (temp == lMarks->head) {
        lMarks->head = temp->next;
        if (lMarks->head == NULL) {
            lMarks->tail = NULL; // Nếu danh sách trống sau khi xóa
        }
        delete temp;
        return;
    }

    // Nếu khóa học cần xóa là cuối danh sách
    if (temp == lMarks->tail) {
        lMarks->tail = prev;
        lMarks->tail->next = NULL;
        delete temp;
        return;
    }

    // Xóa khóa học ở giữa danh sách
    prev->next = temp->next;
    delete temp;
}
