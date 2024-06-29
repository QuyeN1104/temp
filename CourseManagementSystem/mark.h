#ifndef MARK_H
#define MARK_H
#include"library.h"
#include"course.h"
struct Mark{
    Course* course; // điểm của môn nào
    double totalMark, finalMark, midtermMark, otherMark;
    Mark();
    Mark(double other, double mid, double final, double total);
};
struct NodeMark{
    Mark data;
    NodeMark* next;
    NodeMark(const Mark& mark);
};

struct LinkedList_Marks{
    NodeMark *head, *tail;
    LinkedList_Marks();
};

#endif // MARK_H
