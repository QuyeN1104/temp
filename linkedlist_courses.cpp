#include "linkedlist_courses.h"

NodeCourse::NodeCourse(Course course) : data(course), next(nullptr) {}

// Implementation of LinkedList_Courses methods
LinkedList_Courses::LinkedList_Courses() : head(nullptr) {}

LinkedList_Courses::~LinkedList_Courses() {
    NodeCourse* current = head;
    NodeCourse* next;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
}

// void LinkedList_Courses::insert(Course course) {
//     NodeCourse* newNodeCourse = new NodeCourse(course);
//     newNodeCourse->next = head;
//     head = newNodeCourse;
// }

// void LinkedList_Courses::display() const {
//     NodeCourse* current = head;
//     while (current != nullptr) {
//         current->data.display();
//         current = current->next;
//     }
// }
