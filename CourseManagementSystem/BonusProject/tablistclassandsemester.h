#ifndef TABLISTCLASSANDSEMESTER_H
#define TABLISTCLASSANDSEMESTER_H

#include <QWidget>
#include <QTableView>
#include <QMenu>
#include <QContextMenuEvent>
#include <QStandardItemModel>
#include <QHeaderView>
#include "struct_part\\user.h"
#include "struct_part\\student.h"
#include "struct_part\\staff.h"

class TabListClassAndSemester : public QWidget
{
public:
    LinkedList_Classes* listClass;
    LinkedList_Semesters* listSemester;
    QStandardItemModel* model;
    QTableView* tableView;
    TabListClassAndSemester(LinkedList_Classes* listClass, LinkedList_Semesters* listSemester);
};

#endif // TABLISTCLASSANDSEMESTER_H
