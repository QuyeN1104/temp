#include"mark.h"
Mark::Mark() : course(NULL),totalMark(-1), finalMark(-1), midtermMark(-1), otherMark(-1) {}
Mark::Mark(double other, double mid, double final, double total) : totalMark(total), finalMark(final), midtermMark(mid), otherMark(other) {}
Mark::Mark(Course* newCoure,double other, double mid, double final, double total) : course(newCoure) , totalMark(total), finalMark(final), midtermMark(mid), otherMark(other) {}
NodeMark::NodeMark(const Mark& mark) : data(mark) , next(NULL) {}
LinkedList_Marks::LinkedList_Marks() : head(nullptr) , tail(nullptr) {}
