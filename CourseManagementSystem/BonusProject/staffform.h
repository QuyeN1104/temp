#ifndef STAFFFORM_H
#define STAFFFORM_H

#include <QObject>
#include <QLabel>
#include <QVBoxLayout>
#include <QTableView>
#include <QToolButton>
#include <QMenu>
#include <QTabWidget>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QComboBox>
#include <QPushButton>
#include <QTabBar>
#include <QFont>
#include <QHBoxLayout>
#include <QListView>
#include <QStringListModel>
#include <QFormLayout>
#include <QDebug>
#include "scoreboard.h"
#include "struct_part\\user.h"
#include "struct_part\\student.h"
#include "struct_part\\staff.h"
#include "struct_part\\schoolyear.h"
#include "struct_part\\class.h"
#include "struct_part\\semester.h"
#include "struct_part\\course.h"
#include "tabliststudent.h"
#include "tablistclass.h"
#include "tablistcourse.h"
#include "tablistschoolyear.h"
#include "tablistsemester.h"
#include "tablistclassandsemester.h"

class StaffForm : public QLabel
{
public slots:
    void goToLoginForm();
    void goToChangePasswordForm();
    void goToProfile();
    void doubleClickOnSchoolYear(const QModelIndex &index);
    void doubleClickOnClass(const QModelIndex &index);
    void doubleClickOnSemester(const QModelIndex &index);
    void doubleClickOnCourse(const QModelIndex &index);
    void doubleClickINSchoolYear(const QModelIndex &index);
    void doubleClickOnStudent (const QModelIndex &index);
    void goToStudentForm(Student* st);
public:
    StaffForm(Staff* staff);
private:
    TabListClassAndSemester* listClassAndSemester;
    TabListSchoolYear* listSchoolYear;
    TabListSemester* listSemester;
    TabListCourse* listCourse;
    TabListClass* listClass;
    TabListStudent* listStudent;
    QTabWidget* tab;
    Staff* staff;
    QLabel* helloStaff;
    QToolButton* setting;
    string curSchoolYear;
    string curSemester;
};

#endif // STAFFFORM_H
