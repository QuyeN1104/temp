#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QGroupBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QPixmap>
#include <QFont>
#include <QWidget>
#include <QHBoxLayout>
#include <QPalette>
#include <QObject>
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>
#include <staffform.h>
#include <studentform.h>
#include "struct_part\\user.h"
#include "struct_part\\student.h"
#include "struct_part\\staff.h"

class LoginForm : public QLabel {
    Q_OBJECT

    public:
        LoginForm();
        Staff* getAdmin();
        void setAdmin(Staff* staff);
    public slots:
        void showPassword();
        void goToNext();
    private:
        Staff* admin;
        QLabel *regionLogin;
        QVBoxLayout *regionLoginLayout;
        QLabel *title;
        QFormLayout *loginBox;
        QLabel *usernameIcon;
        QLineEdit *userName;
        QLabel *wrong;
        QLabel *passwordIcon;
        QLineEdit *passWord;
        QHBoxLayout *sup;
        QCheckBox *visiblePassword;
        QLabel* gif;
        QHBoxLayout *tmp;
        QPushButton *loginButton;
};


#endif // LOGINFORM_H
