#include "student.h"
#include "schoolyear.h"
#include"semester.h"
#include"course.h"
#include"class.h"
#include"mark.h"

LinkedList_Courses* Student::getListCoursesOfASemester(const string& nameYear, const string& nameSemester){
    Semester* semester = findSemesterInYear(nameYear,nameSemester);
    if(!semester) return NULL;
    return semester->getListCourses();
}
Student::Student() : User(),studentID(""),enrolledClass("") , dataOfStudents(new LinkedList_SchoolYears()), markOfCourse(NULL) {}

Student::Student(string* data) {
    int i = 0;
    this->studentID = data[i++];
    this->firstName = data[i++];
    this->lastName = data[i++];
    this->gender = data[i++];
    this->dateOfBirth = stringToDate(data[i++]);
    this->socialID = data[i++];
    this->userName = this->studentID;
    this->passWord = defaultPassWordStudent;
    dataOfStudents = new LinkedList_SchoolYears();
    markOfCourse = NULL;
}
Student::Student(string socialID, string studentID,string firstName,string lastName, string enrolledClass, string gender, string dob){
    this->studentID = studentID;
    this->lastName = lastName;
    this->firstName = firstName;
    this->gender = gender;
    this->dateOfBirth = stringToDate(dob);
    this->socialID = socialID;
    this->userName = studentID;
    this->passWord = defaultPassWordStudent;
    this->enrolledClass = enrolledClass;
    dataOfStudents = new LinkedList_SchoolYears();
    markOfCourse = NULL;
}
Student::Student(string* data,const string& nameClass) {
    int i = 0;
    this->studentID = data[i++];
    this-> firstName = data[i++];
    this->lastName = data[i++];
    this->gender = data[i++];
    this->dateOfBirth = stringToDate(data[i++]);
    this->socialID = data[i++];
    this->userName = this->studentID;
    this->passWord = defaultPassWordStudent;
    this->enrolledClass = nameClass;
    dataOfStudents = new LinkedList_SchoolYears();
    markOfCourse = NULL;
}

void Student::setEnrollClass(const string& newClass){
    enrolledClass = newClass;
}

void Student::setMark(){
    delete markOfCourse;
    markOfCourse = new Mark;
}

void Student::setMark(Mark* mark){
    delete markOfCourse;
    markOfCourse = mark;
}

Mark* Student::getMarks() const{
    return markOfCourse;
}

bool Student::operator !=(const Student& other) const{
    return this->studentID != other.studentID;
}
SchoolYear* Student::getSchoolYearByName(const string& nameSchoolYear){
    LinkedList_SchoolYears* lSchoolYears = getListSchoolYearsOfSchool();
    if(lSchoolYears == NULL||lSchoolYears->head == NULL) return NULL;
    NodeSchoolYear* pNodeSchoolYear = lSchoolYears->head;
    while(pNodeSchoolYear != NULL && (pNodeSchoolYear->data.getNameSchoolYear() != nameSchoolYear)){
        pNodeSchoolYear = pNodeSchoolYear->next;
    }
    if(pNodeSchoolYear == NULL) return NULL;
    return &pNodeSchoolYear->data;
}

Semester* Student::getSemesterByName(LinkedList_Semesters* lSemesters, const string& nameSemester){
    if(lSemesters == NULL || lSemesters->head == NULL) return NULL;
    NodeSemester* pNodeSemester = lSemesters->head;
    while(pNodeSemester != NULL && (pNodeSemester->data.getNameSemester() != nameSemester)){
        pNodeSemester = pNodeSemester->next;
    }
    if(pNodeSemester == NULL) return nullptr;
    return &pNodeSemester->data;
}
Semester* Student::findSemesterInYear(const string& nameYear, const string& nameSemester){
    SchoolYear* pYear = getSchoolYearByName(nameYear);
    if(pYear == NULL) return NULL;
    return getSemesterByName(pYear->getListSemesters(),nameSemester);
}

string Student::getStudentID() const{
    return studentID;
}

string Student::getEnrolledClass() const {
    return enrolledClass;
}

LinkedList_SchoolYears* Student::getListSchoolYearsOfSchool() const{
    return dataOfStudents;
}

NodeStudent::NodeStudent() {}

NodeStudent::NodeStudent(const Student& student) : data(student), next(nullptr) {}
LinkedList_Students::LinkedList_Students(): head(nullptr), tail(nullptr) {}
