#pragma once
#include"library.h"
#include"user.h"

// khai báo chuyển tiếp
class Course;
class SchoolYear;
class Class;
class Student;
class Semester;

struct LinkedList_Classes;
struct LinkedList_SchoolYears;
struct LinkedList_Courses;
struct LinkedList_Students;
struct LinkedList_Semesters;

struct NodeStudent;
struct NodeSchoolYear;
struct NodeSemester;
struct NodeClass;
struct NodeCourse;

class Staff : public User {
private:
     static LinkedList_SchoolYears* listSchoolYearsOfSchool;
public:
    // các hàm getter
    Staff();
    LinkedList_SchoolYears* getListSchoolYearsOfSchool() const;

    // các hàm truy xuất trực tiếp cần sử dụng ( cho UI )

    // hàm kiểm tra sinh viên khi đăng nhập
    Student* IsStudent(const string& userName,const string& passWord);
    // Tìm 1 kì học trong danh sách năm
    Semester* findSemesterInYear( LinkedList_SchoolYears* lSchoolYears ,const string& nameYear,const string& nameSemester);

    // trả về danh sách sinh viên của 1 môn học bằng mã lớp
    // ex : 23_s2 23_s1 cùng thuộc mã MATH001 môn VI TÍCH PHÂN
    LinkedList_Students* listStudentsOfCourse(const string& nameYear, const string& nameSemester, const string& nameClass);

    // trả về năm nhập học của 1 học sinh theo mssv
    // ví dụ 23120349 -> k23 -> 2023-2024
    SchoolYear* findEnrolledYearOfAStudent(const string& mssv);

    // trả về danh sách các lớp của 1 năm học (k23,k24,..)
    LinkedList_Classes* listClassesInYear(const string& nameYear);

    //Tìm 1 học sinh trong danh sách các lớp
    Student* findStudentByID(const string& mssv);

    //Tìm một khóa học dựa theo năm kì và mã lớp
    Course* findCourseByClassName(const string& nameYear,const string& nameSemester,const string& nameClass);

    // Tìm Danh Sách khóa học của 1 học sinh trong 1 kì
    LinkedList_Courses* listCourseOfStudent(const string& mssv, const string& nameYear, const string& nameSemester);

    // Hàm trả về danh sách lớp của năm học

    // Trả về danh sách các môn học của 1 học kì
    LinkedList_Courses* listCourseOfSemester( LinkedList_SchoolYears* lSchoolYears ,const string& nameYear,const string& nameSemester);

    // hàm load sinh viên vào một class
    bool loadStudentsInClass(LinkedList_Students* lStudents ,const string& fileDirection);

    // hàm load sinh viên cho 1 lớp học
    bool loadStudentsInCourse(LinkedList_Students* lStudents, const string& fileDirection);

    //trả về một khó học theo tên lớp khóa học
    Course* getCourseByName(LinkedList_Courses* lCourses, const string& nameClass);

    // Tìm danh sách sinh viên trong 1 lớp học
    Student* getStudentByID(LinkedList_Students* lStudents, const string& mssv);

    //Tìm kì học trong danh sách kì
    Semester* getSemesterByName(LinkedList_Semesters* lSemesters, const string& nameSemester);

    //Tìm năm học trong danh sách năm
    SchoolYear* getSchoolYearByName(LinkedList_SchoolYears* lSchoolYears, const string& nameSchoolYear);

    // các hàm thay đổi thông tin khóa học, lớp, ...
    void change_idCourse(Course& course,string newIdCourse);
    void change_nameCourse(Course& course,string newNameCourse);
    void change_className(Course& course,string newClassName);
    void change_teacherName(Course& course,string newTeacherName);
    void change_numCredits(Course& course, int newNumCredits);
    void change_session(Course& course,string newSession);
    void change_dayofWeek(Course& course,string newDayofWeek);
    void change_maxStudents(Course& course,int newMaxStudens);

    // các hàm làm việc vơí file
    int countLines(const string& filename);
    string** processCsvFile(const string& fileDirection, int& numRows);
    void deletePointerData(string** s, int numRows);
    // hàm Course
    NodeCourse* getNodeCoursePointer(LinkedList_Courses* lCourses, const Course& course);
    NodeCourse* getNodeCoursePointer(LinkedList_Courses* lCourses, int index);
    int getNodeCourseIndex(LinkedList_Courses* lCourses, NodeCourse* pNodeCourse);
    NodeCourse* getPreviousNodeCoursePointer(LinkedList_Courses* lCourses, NodeCourse* pNodeCourse);
    void addHeadCourse(LinkedList_Courses* lCourses, const Course& course);
    Course* addTailCourse(LinkedList_Courses* lCourses, const Course& course);
    void addBeforeCourse(LinkedList_Courses* lCourses, NodeCourse* pNodeCourseBefore, const Course& course);
    void addAfterCourse(LinkedList_Courses* lCourses, NodeCourse* pNodeCourseAfter, const Course& course);
    void addCourseAtIndex(LinkedList_Courses* lCourses, const Course& course, int index);
    void deleteCourse(LinkedList_Courses* lCourses, NodeCourse* pNodeCourse);
    // hàm cho Student
    NodeStudent* getNodeStudentPointer(LinkedList_Students* lStudents, const Student& student);
    NodeStudent* getNodeStudentPointer(LinkedList_Students* lStudents, int index);
    int getNodeStudentIndex(LinkedList_Students* lStudents, NodeStudent* pNodeStudent);
    NodeStudent* getPreviousNodeStudentPointer(LinkedList_Students* lStudents, NodeStudent* pNodeStudent);
    void addHeadStudent(LinkedList_Students* lStudents, const Student& student);
    Student* addTailStudent(LinkedList_Students* lStudents, const Student& student);
    void addBeforeStudent(LinkedList_Students* lStudents, NodeStudent* pNodeStudentBefore, const Student& student);
    void addAfterStudent(LinkedList_Students* lStudents, NodeStudent* pNodeStudentAfter, const Student& student);
    void addStudentAtIndex(LinkedList_Students* lStudents, const Student& student, int index);
    void deleteStudent(LinkedList_Students* lStudents, NodeStudent* pNodeStudent);
    // hàm cho Class
    Class* getClassByName(LinkedList_Classes *lClasses, const string& nameClass); // ex : 23CTT5
    NodeClass* getNodeClassPointer(LinkedList_Classes* lClasses, const Class& Class);
    NodeClass* getNodeClassPointer(LinkedList_Classes* lClasses, int index);
    int getNodeClassIndex(LinkedList_Classes* lClasses, NodeClass* pNodeClass);
    NodeClass* getPreviousNodeClassPointer(LinkedList_Classes* lClasses, NodeClass* pNodeClass);
    void addHeadClass(LinkedList_Classes* lClasses, const Class& Class);
    Class* addTailClass(LinkedList_Classes* lClasses, const Class& Class);
    Class* addTailClass(LinkedList_Classes* lClasses, const string& nameClass);
    void addBeforeClass(LinkedList_Classes* lClasses, NodeClass* pNodeClassBefore, const Class& Class);
    void addAfterClass(LinkedList_Classes* lClasses, NodeClass* pNodeClassAfter, const Class& Class);
    void addClassAtIndex(LinkedList_Classes* lClasses, const Class& Class, int index);
    void deleteClass(LinkedList_Classes* lClasses, NodeClass* pNodeClass);
    // hàm cho Semester
    NodeSemester* getNodeSemesterPointer(LinkedList_Semesters* lSemesters, const Semester& semester);
    NodeSemester* getNodeSemesterPointer(LinkedList_Semesters* lSemesters, int index);
    int getNodeSemesterIndex(LinkedList_Semesters* lSemesters, NodeSemester* pNodeSemester);
    NodeSemester* getPreviousNodeSemesterPointer(LinkedList_Semesters* lSemesters, NodeSemester* pNodeSemester);
    void addHeadSemester(LinkedList_Semesters* lSemesters, const Semester& semester);
    Semester* addTailSemester(LinkedList_Semesters* lSemesters, const Semester& semester);
    Semester* addTailSemester(LinkedList_Semesters* lSemesters, const string& nameSemester);
    void addBeforeSemester(LinkedList_Semesters* lSemesters, NodeSemester* pNodeSemesterBefore, const Semester& semester);
    void addAfterSemester(LinkedList_Semesters* lSemesters, NodeSemester* pNodeSemesterAfter, const Semester& semester);
    void addSemesterAtIndex(LinkedList_Semesters* lSemesters, const Semester& semester, int index);
    void deleteSemester(LinkedList_Semesters* lSemesters, NodeSemester* pNodeSemester);
    // hàm cho SchoolYear
    NodeSchoolYear* getNodeSchoolYearPointer(LinkedList_SchoolYears* lSchoolYears, const SchoolYear& schoolyear);
    NodeSchoolYear* getNodeSchoolYearPointer(LinkedList_SchoolYears* lSchoolYears, int index);
    int getNodeSchoolYearIndex(LinkedList_SchoolYears* lSchoolYears, NodeSchoolYear* pNodeSchoolYear);
    NodeSchoolYear* getPreviousNodeSchoolYearPointer(LinkedList_SchoolYears* lSchoolYears, NodeSchoolYear* pNodeSchoolYear);
    void addHeadSchoolYear(LinkedList_SchoolYears* lSchoolYears, const SchoolYear& schoolyear);
    SchoolYear* addTailSchoolYear(LinkedList_SchoolYears* lSchoolYears, const SchoolYear& schoolyear);
    SchoolYear* addTailSchoolYear(LinkedList_SchoolYears* lSchoolYears, const string& nameSchoolyear);
    void addBeforeSchoolYear(LinkedList_SchoolYears* lSchoolYears, NodeSchoolYear* pNodeSchoolYearBefore, const SchoolYear& schoolyear);
    void addAfterSchoolYear(LinkedList_SchoolYears* lSchoolYears, NodeSchoolYear* pNodeSchoolYearAfter, const SchoolYear& schoolyear);
    void addSchoolYearAtIndex(LinkedList_SchoolYears* lSchoolYears, const SchoolYear& schoolyear, int index);
    void deleteSchoolYear(LinkedList_SchoolYears* lSchoolYears, NodeSchoolYear* pNodeSchoolYear);
};
