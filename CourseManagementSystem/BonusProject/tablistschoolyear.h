#ifndef TABLISTSCHOOLYEAR_H
#define TABLISTSCHOOLYEAR_H

#include <QWidget>
#include <QTableView>
#include <QMenu>
#include <QContextMenuEvent>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QInputDialog>
#include "tablistclassandsemester.h"
#include "struct_part\\user.h"
#include "struct_part\\student.h"
#include "struct_part\\staff.h"
#include "struct_part\\schoolyear.h"

class TabListSchoolYear : public QWidget
{
public:
    Staff* staff;
    LinkedList_SchoolYears* listSchoolYear;
    QStandardItemModel* model;
    QTableView* tableView;
    TabListSchoolYear(LinkedList_SchoolYears* listSchoolYear, Staff* staff);
public slots:
    void addSchoolYear();
    void removeSchoolYear();
    void editSchoolYear();
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
};

#endif // TABLISTSCHOOLYEAR_H
