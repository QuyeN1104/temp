#ifndef STUDENTFORM_H
#define STUDENTFORM_H

#include <QLabel>
#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>
#include <QHeaderView>
#include <QObject>
#include <QToolButton>
#include <QMenu>
#include <QIcon>
#include <QPixmap>
#include <QComboBox>
#include <QTabWidget>
#include "scoreboard.h"
#include "tablistcourseforstudent.h"
#include "struct_part\\schoolyear.h"
#include "struct_part\\user.h"
#include "struct_part\\student.h"
#include "struct_part\\staff.h"


class StudentForm : public QLabel
{

    public:
        StudentForm(Student* st);
    public slots:
        void goToLoginForm();
        void goToChangePasswordForm();
        void goToProfile();
        void searchListCourse();
    private:
        QHBoxLayout* line;
        QComboBox* year, *semester;
        QPushButton* search;
        Student* st;
        ScoreBoard *scoreBoard;
        TabListCourseForStudent *listCourse;
        QTabWidget* tab;
};

#endif // STUDENTFORM_H
