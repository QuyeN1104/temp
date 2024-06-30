#ifndef TABLISTSEMESTER_H
#define TABLISTSEMESTER_H

#include <QWidget>
#include <QTableView>
#include <QMenu>
#include <QContextMenuEvent>
#include <QStandardItemModel>
#include <QDialog>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include "struct_part\\user.h"
#include "struct_part\\student.h"
#include "struct_part\\staff.h"
#include "struct_part\\semester.h"

class TabListSemester : public QWidget
{
public:
    Staff* staff;
    LinkedList_Semesters* listSemester;
    QStandardItemModel* model;
    QTableView* tableView;
    TabListSemester(LinkedList_Semesters* listSemester, Staff* staff);
public slots:
    void addSemester();
    void removeSemester();
    void editSemester();
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
};

#endif // TABLISTSEMESTER_H
