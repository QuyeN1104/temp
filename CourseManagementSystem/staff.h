#ifndef STAFF_H
#define STAFF_H
#include"class.h"

class Staff{
private:
    LinkedList_Courses semeterCourses;
public:
    void change_idCourse(Course& course,string newIdCourse);
    void change_nameCourse(Course& course,string newNameCourse);
    void change_className(Course& course,string newClassName);
    void change_teacherName(Course& course,string newTeacherName);
    void change_numCredits(Course& course, int newNumCredits);
    void change_session(Course& course,string newSession);
    void change_dayofWeek(Course& course,string newDayofWeek);
    void change_maxStudents(Course& course,int newMaxStudens);
    int countLines(const std::string& filename);
    string** processCsvFile(const string& fileDirection, int& numRows);
    void deletePointerData(string** s, int numRows);
    void loadStudentsFromCsvfile(LinkedList_Students& lStudents,const string& fileDirection);
    NodeCourse* getNodeCoursePointer(LinkedList_Courses lCourses, Course course);
    NodeCourse* getNodeCoursePointer(LinkedList_Courses lCourses, int index);
    int getNodeCourseIndex(LinkedList_Courses lCourses, NodeCourse* pNodeCourse);
    NodeCourse* getPreviousNodeCoursePointer(LinkedList_Courses lCourses, NodeCourse* pNodeCourse);
    void addHeadCourse(LinkedList_Courses& lCourses, Course course);
    void addTailCourse(LinkedList_Courses& lCourses, Course course);
    void addBeforeCourse(LinkedList_Courses& lCourses, NodeCourse* pNodeCourseBefore, Course course);
    void addAfterCourse(LinkedList_Courses& lCourses, NodeCourse* pNodeCourseAfter, Course course);
    void addCourseAtIndex(LinkedList_Courses& lCourses, Course course, int index);
    void deleteCourse(LinkedList_Courses& lCourses, NodeCourse* pNodeCourse);
    // NodeStudent* getNodeStudentPointer(LinkedList_Students lStudents, Student student);
    NodeStudent* getNodeStudentPointer(LinkedList_Students lStudents, int index);
    int getNodeStudentIndex(LinkedList_Students lStudents, NodeStudent* pNodeStudent);
    NodeStudent* getPreviousNodeStudentPointer(LinkedList_Students lStudents, NodeStudent* pNodeStudent);
    void addHeadStudent(LinkedList_Students& lStudents, Student student);
    void addTailStudent(LinkedList_Students& lStudents, Student student);
    void addBeforeStudent(LinkedList_Students& lStudents, NodeStudent* pNodeStudentBefore, Student student);
    void addAfterStudent(LinkedList_Students& lStudents, NodeStudent* pNodeStudentAfter, Student student);
    void addStudentAtIndex(LinkedList_Students& lStudents, Student student, int index);
    void deleteStudent(LinkedList_Students& lStudents, NodeStudent* pNodeStudent);
    //NodeClass* getNodeClassPointer(LinkedList_Classes lClasses, Class Class);
    NodeClass* getNodeClassPointer(LinkedList_Classes lClasses, int index);
    int getNodeClassIndex(LinkedList_Classes lClasses, NodeClass* pNodeClass);
    NodeClass* getPreviousNodeClassPointer(LinkedList_Classes lClasses, NodeClass* pNodeClass);
    void addHeadClass(LinkedList_Classes& lClasses, Class Class);
    void addTailClass(LinkedList_Classes& lClasses, Class Class);
    void addBeforeClass(LinkedList_Classes& lClasses, NodeClass* pNodeClassBefore, Class Class);
    void addAfterClass(LinkedList_Classes& lClasses, NodeClass* pNodeClassAfter, Class Class);
    void addClassAtIndex(LinkedList_Classes& lClasses, Class Class, int index);
    void deleteClass(LinkedList_Classes& lClasses, NodeClass* pNodeClass);
};
#endif // STAFF_H
