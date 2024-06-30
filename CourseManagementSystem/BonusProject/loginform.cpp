#include "loginform.h"
#include <QMovie>
#include <QDebug>

LoginForm::LoginForm() : QLabel(){
    admin = new Staff();
    admin->setUserName("");
    admin->setPassWord("");

    regionLogin = new QLabel(this);
    regionLoginLayout = new QVBoxLayout(this);
    title = new QLabel(this);
    loginBox = new QFormLayout(this);
    wrong = new QLabel(this);
    userName = new QLineEdit(this);
    passWord = new QLineEdit(this);
    loginButton = new QPushButton(this);

    //Cai dat phan title
    this->title->setAlignment(Qt::AlignCenter);
    this->title->setText("ĐĂNG NHẬP");
    this->title->setFont(QFont("Roboto", 30, 80));
    QPalette colorTitle;
    this->title->setAutoFillBackground(true);
    colorTitle.setColor(QPalette::WindowText, Qt::blue);
    // colorTitle.setColor(QPalette::Window, QColor(165,0,255));
    this->title->setPalette(colorTitle);

    //Cai dat phan username va password
    visiblePassword = new QCheckBox("Hiện mật khẩu", this);
    this->wrong->setAlignment(Qt::AlignCenter);
    this->userName->setFixedSize(300, 30);
    this->passWord->setFixedSize(300, 30);
    this->userName->setPlaceholderText("Tên đăng nhập");
    this->passWord->setPlaceholderText("Mật khẩu");
    usernameIcon = new QLabel(this);
    usernameIcon->setPixmap(QPixmap(":\\/\\icon\\usernameIcon.png"));
    usernameIcon->setFixedSize(20, 20);
    this->loginBox->addRow(usernameIcon, this->userName);
    passwordIcon = new QLabel(this);
    passwordIcon->setPixmap(QPixmap(":\\/\\icon\\passwordIcon.png"));
    this->loginBox->addRow(passwordIcon, this->passWord);
    this->passWord->setEchoMode(QLineEdit::Password);
    this->loginBox->addWidget(visiblePassword);

    //Tao su kien khi click vao hien thi mat khau
    connect(this->visiblePassword, SIGNAL(clicked()), this, SLOT(showPassword()));
    //Tao su kien khi click vao dang nhap
    connect(this->loginButton, SIGNAL(clicked()), this, SLOT(goToNext()));

    //Cai dat nut login
    this->loginButton->setText("Đăng nhập");
    this->loginButton->setToolTip("Nhấn để đăng nhập!");
    this->loginButton->setCursor(Qt::PointingHandCursor);
    this->loginButton->setAutoFillBackground(true);
    QPalette colorButtonLogin = this->loginButton->palette();
    colorButtonLogin.setColor(QPalette::Button, QColor(49, 95, 248));
    colorButtonLogin.setColor(QPalette::ButtonText, Qt::white);
    this->loginButton->setPalette(colorButtonLogin);
    this->loginButton->setFlat(true);

    this->loginButton->setFixedSize(140, 60);
    connect(this->loginButton, SIGNAL(pressed()), this, SLOT(goToNext()));


    //Trang tri cho cac thanh phan
    QPalette palette;
    this->regionLogin->setAutoFillBackground(true);
    palette.setColor(QPalette::Window, QColor(165,250,254));
    this->regionLogin->setPalette(palette);

    //Ghep cac thanh phan lai
    this->regionLoginLayout->addStretch();
    this->regionLoginLayout->addWidget(this->title);
    this->regionLoginLayout->addStretch();
    this->regionLoginLayout->addStretch();
    this->regionLoginLayout->addWidget(this->wrong);
    this->regionLoginLayout->addLayout(this->loginBox);
    this->regionLoginLayout->addStretch();
    sup = new QHBoxLayout(this);
    this->regionLoginLayout->addLayout(sup);
    sup->addStretch();
    sup->addWidget(this->loginButton);
    sup->addStretch();
    gif = new QLabel(this);
    QMovie *movie = new QMovie(":\\/\\background\\UWU.gif");
    gif->setMovie(movie);
    movie->start();
    this->regionLoginLayout->addStretch();
    this->regionLoginLayout->addWidget(gif);
    // this->regionLoginLayout->addStretch();
    this->regionLogin->setLayout(this->regionLoginLayout);
    this->regionLogin->setFixedSize(370, 600);
    this->regionLoginLayout->setAlignment(Qt::AlignCenter);

    //Trung gian
    tmp = new QHBoxLayout(this);
    tmp->addWidget(this->regionLogin);

    //Cua so login
    this->regionLogin->setFrameShape(QFrame::Panel);
    this->regionLogin->setFrameShadow(QFrame::Shadow::Raised);
    this->regionLogin->setLineWidth(3);
    this->regionLogin->setMidLineWidth(3);
    this->setLayout(tmp);
    this->setAlignment(Qt::AlignCenter);

    //Cua so chinh
    this->setWindowTitle("Đăng nhập");
    this->setPixmap(QPixmap(":\\/\\background\\KHTN (2).jpg"));
    this->setWindowIcon(QIcon(":\\/\\icon\\Logo.png"));
    this->showMaximized();
}

//Dinh nghia cho su kien click vao hien thi mat khau
void LoginForm::showPassword() {
    if (visiblePassword->isChecked()) {
        passWord->setEchoMode(QLineEdit::Normal);
    }
    else {
        passWord->setEchoMode(QLineEdit::Password);
    }
}

Staff* LoginForm::getAdmin() {
    return this->admin;
}

void LoginForm::setAdmin(Staff* staff) {
    this->admin = staff;
}
