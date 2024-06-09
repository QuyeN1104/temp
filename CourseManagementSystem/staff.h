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
struct LinkedList_Users;
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
    LinkedList_Classes*  listClassesOfSchool;
    LinkedList_SchoolYears* listSchoolYearsOfSchool;
    LinkedList_Users* listUsersOfSchool;
public:
    // các hàm getter
    Staff();
    LinkedList_Classes* getListClassesOfSchool() const;

    LinkedList_SchoolYears* getListSchoolYearsOfSchool() const;

    LinkedList_Users* getListUsersOfSchool() const;

    // SchoolYear getSchoolYear()

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
    // int countLines(const string& filename);
    // string** processCsvFile(const string& fileDirection, int& numRows);
    // void deletePointerData(string** s, int numRows);
    // void loadStudentsFromCsvfile(LinkedList_Students& lStudents,const string& fileDirection);

    // hàm Course
    NodeCourse* getNodeCoursePointerByName(LinkedList_Courses* lCourses, const string& nameClass);
    NodeCourse* getNodeCoursePointer(LinkedList_Courses* lCourses, const Course& course);
    NodeCourse* getNodeCoursePointer(LinkedList_Courses* lCourses, int index);
    int getNodeCourseIndex(LinkedList_Courses* lCourses, NodeCourse* pNodeCourse);
    NodeCourse* getPreviousNodeCoursePointer(LinkedList_Courses* lCourses, NodeCourse* pNodeCourse);
    void addHeadCourse(LinkedList_Courses* lCourses, const Course& course);
    void addTailCourse(LinkedList_Courses* lCourses, const Course& course);
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
    void addTailStudent(LinkedList_Students* lStudents, const Student& student);
    void addBeforeStudent(LinkedList_Students* lStudents, NodeStudent* pNodeStudentBefore, const Student& student);
    void addAfterStudent(LinkedList_Students* lStudents, NodeStudent* pNodeStudentAfter, const Student& student);
    void addStudentAtIndex(LinkedList_Students* lStudents, const Student& student, int index);
    void deleteStudent(LinkedList_Students* lStudents, NodeStudent* pNodeStudent);
    // hàm cho Class
    NodeClass* getNodeClassPointerByName(LinkedList_Classes *lClasses, const string& nameClass); // ex : 23CTT5
    NodeClass* getNodeClassPointer(LinkedList_Classes* lClasses, const Class& Class);
    NodeClass* getNodeClassPointer(LinkedList_Classes* lClasses, int index);
    int getNodeClassIndex(LinkedList_Classes* lClasses, NodeClass* pNodeClass);
    NodeClass* getPreviousNodeClassPointer(LinkedList_Classes* lClasses, NodeClass* pNodeClass);
    void addHeadClass(LinkedList_Classes* lClasses, const Class& Class);
    void addTailClass(LinkedList_Classes* lClasses, const Class& Class);
    void addBeforeClass(LinkedList_Classes* lClasses, NodeClass* pNodeClassBefore, const Class& Class);
    void addAfterClass(LinkedList_Classes* lClasses, NodeClass* pNodeClassAfter, const Class& Class);
    void addClassAtIndex(LinkedList_Classes* lClasses, const Class& Class, int index);
    void deleteClass(LinkedList_Classes* lClasses, NodeClass* pNodeClass);
    // hàm cho Semester
    NodeSemester* getNodeSemesterPointerByName(LinkedList_Semesters* lSemesters, const string& nameSemester);
    NodeSemester* getNodeSemesterPointer(LinkedList_Semesters* lSemesters, const Semester& semester);
    NodeSemester* getNodeSemesterPointer(LinkedList_Semesters* lSemesters, int index);
    int getNodeSemesterIndex(LinkedList_Semesters* lSemesters, NodeSemester* pNodeSemester);
    NodeSemester* getPreviousNodeSemesterPointer(LinkedList_Semesters* lSemesters, NodeSemester* pNodeSemester);
    void addHeadSemester(LinkedList_Semesters* lSemesters, const Semester& semester);
    void addTailSemester(LinkedList_Semesters* lSemesters, const Semester& semester);
    void addBeforeSemester(LinkedList_Semesters* lSemesters, NodeSemester* pNodeSemesterBefore, const Semester& semester);
    void addAfterSemester(LinkedList_Semesters* lSemesters, NodeSemester* pNodeSemesterAfter, const Semester& semester);
    void addSemesterAtIndex(LinkedList_Semesters* lSemesters, const Semester& semester, int index);
    void deleteSemester(LinkedList_Semesters* lSemesters, NodeSemester* pNodeSemester);
    // hàm cho SchoolYear
    NodeSchoolYear* getNodeSchoolYearPointerByName(LinkedList_SchoolYears* lSchoolYears, const string& nameSchoolYear);
    NodeSchoolYear* getNodeSchoolYearPointer(LinkedList_SchoolYears* lSchoolYears, const SchoolYear& schoolyear);
    NodeSchoolYear* getNodeSchoolYearPointer(LinkedList_SchoolYears* lSchoolYears, int index);
    int getNodeSchoolYearIndex(LinkedList_SchoolYears* lSchoolYears, NodeSchoolYear* pNodeSchoolYear);
    NodeSchoolYear* getPreviousNodeSchoolYearPointer(LinkedList_SchoolYears* lSchoolYears, NodeSchoolYear* pNodeSchoolYear);
    void addHeadSchoolYear(LinkedList_SchoolYears* lSchoolYears, const SchoolYear& schoolyear);
    void addTailSchoolYear(LinkedList_SchoolYears* lSchoolYears, const SchoolYear& schoolyear);
    void addBeforeSchoolYear(LinkedList_SchoolYears* lSchoolYears, NodeSchoolYear* pNodeSchoolYearBefore, const SchoolYear& schoolyear);
    void addAfterSchoolYear(LinkedList_SchoolYears* lSchoolYears, NodeSchoolYear* pNodeSchoolYearAfter, const SchoolYear& schoolyear);
    void addSchoolYearAtIndex(LinkedList_SchoolYears* lSchoolYears, const SchoolYear& schoolyear, int index);
    void deleteSchoolYear(LinkedList_SchoolYears* lSchoolYears, NodeSchoolYear* pNodeSchoolYear);

    // các hàm truy xuất trực tiếp cần sử dụng ( cho UI )

    LinkedList_Students* listStudentsOfCourse(const string& nameYear, const string& nameSemester, const string& nameClass);
    // ex : 23_s2 23_s1 cùng thuộc mã MATH001 môn VI TÍCH PHÂN
    LinkedList_Classes* listClassesInYear(const string& nameYear);
    LinkedList_Students* findListStudentsOfACourseInYear(const string& nameYear, const string nameClass);

};
