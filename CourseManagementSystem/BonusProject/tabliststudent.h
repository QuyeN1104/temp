#ifndef TABLISTSTUDENT_H
#define TABLISTSTUDENT_H

#include <QWidget>
#include <QMenu>
#include <QContextMenuEvent>
#include <QObject>
#include <QTableView>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QDialog>
#include <QMessageBox>
#include <QComboBox>
#include <QLineEdit>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QFont>
#include <QHeaderView>
#include "struct_part\\course.h"
#include "struct_part\\class.h"
#include "struct_part\\user.h"
#include "struct_part\\student.h"
#include "struct_part\\staff.h"

class TabListStudent : public QWidget
{
public:
    Class* clas;
    Course* course;
    Staff* staff;
    LinkedList_Students* listStudent;
    QString type;
    QStandardItemModel* model;
    QTableView* tableView;
    TabListStudent(Course* course, Staff* staff, QString type);
    TabListStudent(Class* clas, Staff* staff, QString type);
public slots:
    void addStudent();
    void addStudentFromFile();
    void removeStudent();
    void editStudent();
    void exportListStudent();
    void getScoreFromFile();
protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
};

#endif // TABLISTSTUDENT_H
