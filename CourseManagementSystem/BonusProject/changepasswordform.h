#ifndef CHANGEPASSWORDFORM_H
#define CHANGEPASSWORDFORM_H

#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include <QFormLayout>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QIcon>
#include <QObject>
#include "struct_part\\user.h"
#include "struct_part\\student.h"
#include "struct_part\\staff.h"

class ChangePasswordForm : public QLabel
{
public:
    ChangePasswordForm(User* user);
public slots:
    void showPassword();
    void changePassword();
private:
    User* user;
    QLabel* wrong;
    QLineEdit *passWord;
    QLineEdit *newPassword;
    QLineEdit *reNewPassword;
    QPushButton *enter;
    QCheckBox *visiblePassword;
    QFormLayout *changePasswordLayout;
    QVBoxLayout *mainLayout;
    QHBoxLayout* lineEnter;

};

#endif // CHANGEPASSWORDFORM_H
