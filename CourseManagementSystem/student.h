#pragma once
#include"library.h"
#include "user.h"
struct LinkedList_SchoolYears;
struct LinkedList_Semesters;
struct LinkedList_Courses;
struct LinkedList_Classes;
struct Mark;
class SchoolYear;
class Semester;
class Course;
class Class;
class Student : public User {
    friend class Staff;
private:
    string studentID;
    string enrolledClass;
    LinkedList_SchoolYears* dataOfStudents;
    Mark* markOfCourse; // dành cho học sinh trong khóa học
public:
    // hàm lấy 1 danh sách môn học của 1 kì thuộc 1 năm học
    LinkedList_Courses* getListCoursesOfASemester(const string& nameYear, const string& nameSemester);
    Student();
    Student(string socialID, string studentID,string firstName,string lastName, string enrolledClass, string gender, string dob);
    Student(string* data);
    Student(string* data,const string& nameClass);
    Mark* getMarks() const;
    void setEnrollClass(const string& newClass);
    void setMark();
    void setMark(Mark* mark);
    string getStudentID() const;
    string getEnrolledClass() const;
    LinkedList_SchoolYears* getListSchoolYearsOfSchool() const;
    bool operator !=(const Student& other) const;
    SchoolYear* getSchoolYearByName(const string& nameSchoolYear);
    Semester* getSemesterByName(LinkedList_Semesters* lSemesters, const string& nameSemester);
    Semester* findSemesterInYear(const string& nameYear, const string& nameSemester);
};
struct NodeStudent{
    Student data;
    NodeStudent* next;
    NodeStudent();
    NodeStudent(const Student& student);
};

struct LinkedList_Students {
    NodeStudent *head, *tail;
    LinkedList_Students();
};

