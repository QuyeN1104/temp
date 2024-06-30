#ifndef TABLISTCOURSEFORSTUDENT_H
#define TABLISTCOURSEFORSTUDENT_H

#include <QWidget>
#include <QTableView>
#include <QMenu>
#include <QContextMenuEvent>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QScrollArea>
#include "struct_part\\user.h"
#include "struct_part\\student.h"
#include "struct_part\\staff.h"
#include "struct_part\\course.h"

class TabListCourseForStudent : public QWidget
{
private:
    QStandardItemModel* model;
    QTableView* tableView;
public:
    TabListCourseForStudent(LinkedList_Courses* listCourse);
};

#endif // TABLISTCOURSEFORSTUDENT_H
