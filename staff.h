#ifndef STAFF_H
#define STAFF_H
#include"course.h"
#include"linkedlist_courses.h"
#include"linkedlist_students.h"

  class Staff{
  private:
      LinkedList_Courses semeterCourses;
  public:
        void change_idCourse(Course course,string newIdCourse);
        void change_nameCourse(Course course,string newNameCourse);
        void change_className(Course course,string newClassName);
        void change_teacherName(Course course,string newTeacherName);
        void change_numCredits(Course course, int newNumCredits);
        void change_session(Course course,string newSession);
        void change_dayofWeek(Course course,string newDayofWeek);
        void change_maxStudents(Course course,int newMaxStudens);
        void addCourse(LinkedList_Courses& lCourses, Course course);
        void deleteCourse(LinkedList_Courses& lCourses, Course course);
        void addStudent(LinkedList_Students& lStudents, Student student);
        void deleteStudent(LinkedList_Students& lStudents, Student student);
    };

#endif // STAFF_H
