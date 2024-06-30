#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QWidget>
#include <QTableView>
#include <QMenu>
#include <QContextMenuEvent>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QFormLayout>
#include "struct_part\\mark.h"
#include "struct_part\\user.h"
#include "struct_part\\semester.h"
#include "struct_part\\student.h"
#include "struct_part\\staff.h"
#include "struct_part\\course.h"

class ScoreBoard : public QWidget
{
private:
    QStandardItemModel* model;
    QTableView* tableView;
public:
    ScoreBoard(Student* st, string year, string semester);
    ScoreBoard(Course* course);
};

#endif // SCOREBOARD_H
