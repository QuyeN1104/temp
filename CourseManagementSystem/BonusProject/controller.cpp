#include "controller.h"
#include <QMessageBox>

controller::controller(View *view) {
    this->view = view;
}

void LoginForm::goToNext() {
    bool ok;
    int num = this->userName->text().toInt(&ok);
    if ((this->userName->text() ==  QString::fromStdString(admin->getUserName())) && (this->passWord->text() == QString::fromStdString(admin->getPassWord()))) {
        StaffForm *staffForm = new StaffForm(this->admin);
        delete this;
    }
    else if (ok == false) {
        this->wrong->setText("Sai tên đăng nhập hoặc mật khẩu");
    }
    else if (this->admin->IsStudent(userName->text().toStdString(), passWord->text().toStdString()) != NULL){
        Student* st = this->admin->IsStudent(userName->text().toStdString(), passWord->text().toStdString());
        StudentForm* studentForm = new StudentForm(st);
        delete this;
    }
    else {
        this->wrong->setText("Sai tên đăng nhập hoặc mật khẩu");
    }
}

//Dinh nghia ham di toi cua so dang nhap (dang xuat) doi voi sinh vien
void StudentForm::goToLoginForm() {
    LoginForm* loginForm = new LoginForm();
    loginForm->show();
    delete this;
}

//Dinh nghia ham di toi cua so dang nhap (dang xuat) doi voi giao vu
void StaffForm::goToLoginForm() {
    LoginForm* loginForm = new LoginForm();
    loginForm->show();
    delete this;
}

//Dinh nghia ham di toi cua so trang ca nhan doi voi sinh vien
void StudentForm::goToProfile() {
    new ProfileForm(this->st);
}

//Dinh nghia ham di toi cua so trang ca nhan doi voi giao vu
void StaffForm::goToProfile() {
    new ProfileForm(this->staff);
}

//Dinh nghia ham di toi cua so doi mat khau doi voi sinh vien
void StudentForm::goToChangePasswordForm() {
    new ChangePasswordForm(this->st);
}

//Dinh nghia ham di toi cua so doi mat khau doi voi giao vu
void StaffForm::goToChangePasswordForm() {
    new ChangePasswordForm(this->staff);
}

void StaffForm::goToStudentForm(Student* st) {
    StudentForm* tmp = new StudentForm(st);
}
