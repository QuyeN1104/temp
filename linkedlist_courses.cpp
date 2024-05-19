#include "linkedlist_courses.h"

NodeCourse::NodeCourse(Course course) : data(course), next(nullptr) {}

// Implementation of LinkedList_Courses methods
LinkedList_Courses::LinkedList_Courses() : head(nullptr), tail(nullptr){}

// void LinkedList_Courses::DeleteLinkedList_Courses() {
//     NodeCourse* current = head;
//     NodeCourse* next;
//     while (current != nullptr) {
//         next = current->next;
//         delete current;
//         current = next;
//     }
// }

