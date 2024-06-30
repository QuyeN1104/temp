#ifndef TABLISTCLASS_H
#define TABLISTCLASS_H

#include <QWidget>
#include <QTableView>
#include <QMenu>
#include <QContextMenuEvent>
#include <QStandardItemModel>
#include "struct_part\\user.h"
#include "struct_part\\student.h"
#include "struct_part\\staff.h"
#include "struct_part\\class.h"

class TabListClass : public QWidget
{
public:
    Staff* staff;
    LinkedList_Classes* listClass;
    QStandardItemModel* model;
    QTableView* tableView;
    TabListClass(LinkedList_Classes* listClass, Staff* staff);
public slots:
    void addClass();
    void removeClass();
    void editClass();
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
};

#endif // TABLISTCLASS_H
