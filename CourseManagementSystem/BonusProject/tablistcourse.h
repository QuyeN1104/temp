#ifndef TABLISTCOURSE_H
#define TABLISTCOURSE_H

#include <QWidget>
#include <QTableView>
#include <QMenu>
#include <QContextMenuEvent>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDialog>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QScrollArea>
#include "scoreboard.h"
#include "struct_part\\user.h"
#include "struct_part\\student.h"
#include "struct_part\\staff.h"
#include "struct_part\\course.h"

class TabListCourse : public QWidget
{
public:
    Staff* staff;
    LinkedList_Courses* listCourse;
    QStandardItemModel* model;
    QTableView* tableView;
    TabListCourse(LinkedList_Courses* listCourse, Staff* staff);
public slots:
    void addCourse();
    void removeCourse();
    void editCourse();
    void showScoreBoard();
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
};

#endif // TABLISTCOURSE_H
