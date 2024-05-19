#include "staff.h"
void Staff::change_idCourse(Course course,string newIdCourse){
    course.idCourse = newIdCourse;
}
void Staff::change_nameCourse(Course course,string newNameCourse){
    course.nameCourse = newNameCourse;
}
void Staff::change_className(Course course,string newClassName){
    course.className = newClassName;
}
void Staff::change_teacherName(Course course,string newTeacherName){
    course.teacherName = newTeacherName;
}
void Staff::change_numCredits(Course course, int newNumCredits){
    course.numCredits = newNumCredits;
}
void Staff::change_session(Course course,string newSession){
    course.session = newSession;
}
void Staff::change_dayofWeek(Course course,string newDayofWeek){
    course.dayofWeek = newDayofWeek;
}
void Staff::change_maxStudents(Course course,int newMaxStudens){
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
    NodeStudent* pStudent = new NodeStudent(student);
    NodeStudent* pTemp = lStudents.head;
    while(pTemp != NULL){
        if(pTemp == pStudent){
            break;
        }
        pTemp = pTemp->next;
    }
    if(pTemp == NULL) return;
    NodeStudent* pPrev = NULL;
    while(pPrev->next != pTemp){
        pPrev = pPrev->next;
    }
    if(pPrev == NULL){
        lStudents.head = pTemp->next;
        delete pTemp;
        if(lStudents.head == NULL){
            lStudents.tail = NULL;
        }
        return;
    }
    pPrev->next = pTemp->next;
    delete pTemp;
    if(pPrev->next == NULL){
        lStudents.tail = pPrev;
    }
}

