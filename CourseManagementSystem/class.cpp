#include "class.h"
Class::Class() {}
Class::Class(string name) : nameClass(name) {};
NodeClass::NodeClass(Class Class) : data(Class) , next(nullptr) {};
LinkedList_Classes::LinkedList_Classes() : head(nullptr) , tail(nullptr) {};