#include "changepasswordform.h"
#include <QHBoxLayout>

ChangePasswordForm::ChangePasswordForm(User* user) : QLabel() {
    this->user = user;

    changePasswordLayout = new QFormLayout();
    mainLayout = new QVBoxLayout(this);
    wrong = new QLabel();
    passWord = new QLineEdit();
    newPassword = new QLineEdit();
    reNewPassword = new QLineEdit();
    passWord->setMaximumSize(250, 20);
    enter = new QPushButton("Đổi mật khẩu");
    visiblePassword = new QCheckBox("Hiển thị mật khẩu");

    //Cai dat phan nhap mat khau cu, mat khau moi, nhap lai mat khau moi
    passWord->setPlaceholderText("Mật khẩu cũ");
    passWord->setEchoMode(QLineEdit::Password);
    newPassword->setPlaceholderText("Mật khẩu mới");
    newPassword->setEchoMode(QLineEdit::Password);
    reNewPassword->setPlaceholderText("Nhập lại mật khẩu mới");
    reNewPassword->setEchoMode(QLineEdit::Password);
    enter->setCursor(Qt::PointingHandCursor);
    enter->setFixedSize(100, 60);

    //Tao su kien khi click vao nut doi mat khau
    connect(enter, &QPushButton::pressed, this, &ChangePasswordForm::changePassword);

    //Tao su kien khi click vao hien thi mat khau
    connect(visiblePassword, &QCheckBox::clicked, this, &ChangePasswordForm::showPassword);

    //Them cac thanh phan vao layout
    changePasswordLayout->addRow("", wrong);
    changePasswordLayout->addRow("Mật khẩu cũ", passWord);
    changePasswordLayout->addRow("Mật khẩu mới", newPassword);
    changePasswordLayout->addRow("Nhập lại mật khẩu mới", reNewPassword);
    changePasswordLayout->addWidget(visiblePassword);

    //Tao layout phu de chua nut doi mat khau
    lineEnter = new QHBoxLayout();
    lineEnter->addStretch();
    lineEnter->addWidget(enter);
    lineEnter->addStretch();

    //Cai dat layout cho cua so chinh
    mainLayout->addStretch();
    mainLayout->addLayout(changePasswordLayout);
    mainLayout->addStretch(); // Đưa nút "Đổi mật khẩu" xuống dưới cùng
    mainLayout->addLayout(lineEnter);
    mainLayout->addStretch(); // Đưa nút "Đổi mật khẩu" xuống dưới cùng

    //Cai dat title, icon, background cho cua so chinh
    setWindowTitle("Đổi mật khẩu");
    setWindowIcon(QIcon(":/icon/Logo.png"));
    setPixmap(QPixmap(":/background/hcmusthumb.jpg"));
    setFixedSize(456, 250);
    this->show();
}



//Dinh nghia cho phan hien thi mat khau
void ChangePasswordForm::showPassword() {
    if (visiblePassword->isChecked()) {
        passWord->setEchoMode(QLineEdit::Normal);
        newPassword->setEchoMode(QLineEdit::Normal);
        reNewPassword->setEchoMode(QLineEdit::Normal);
    }
    else {
        passWord->setEchoMode(QLineEdit::Password);
        newPassword->setEchoMode(QLineEdit::Password);
        reNewPassword->setEchoMode(QLineEdit::Password);

    }
}

//Dinh nghia su kien khi nhan vao doi mat khau
void ChangePasswordForm::changePassword() {
    int check = this->user->changePassWord(this->passWord->text().toStdString(), this->newPassword->text().toStdString(), this->reNewPassword->text().toStdString());
    if (check == 0) {
        this->wrong->setText("Mật khẩu cũ không đúng");
    }
    else if (check == 1) {
        this->wrong->setText("Mật khẩu mới và nhập lại mật khẩu mới không khớp");
    }
    else if (check == 2) {
        this->wrong->setText("Đổi mật khẩu thành công");
    }
}


