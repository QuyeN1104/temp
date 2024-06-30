#include "studentform.h"
#include <QFormLayout>


StudentForm::StudentForm(Student* st) : QLabel() {
    this->st = st;

    this->search = new QPushButton("Tìm kiếm");

    this->year = new QComboBox();
    this->year->setPlaceholderText(" Năm học ");
    if (st->getListSchoolYearsOfSchool()) {
        NodeSchoolYear* cur = st->getListSchoolYearsOfSchool()->head;
        while (cur) {
            this->year->addItem(QString::fromStdString(cur->data.getNameSchoolYear()));
            cur = cur->next;
        }
    }
    this->semester = new QComboBox();
    this->semester->setPlaceholderText(" Kì học ");
    this->semester->addItem("1");
    this->semester->addItem("2");
    this->semester->addItem("3");

    connect(this->search, &QPushButton::clicked, this, &StudentForm::searchListCourse);

    //         NHÃN XIN CHÀO         //
    QLabel *helloUser = new QLabel();
    helloUser->setAlignment(Qt::AlignCenter);
    // string nameString = "Chào " + st.getFirstName() + " " + st.getLastName();
    // QString name = QString::fromStdString(nameString);
    helloUser->setText(QString::fromStdString("Chào " + st->getFirstName() + " " + st->getLastName()));
    helloUser->setFont(QFont("Arial", 30, 10));

    //Menu kiểu nút
    QToolButton *setting = new QToolButton();
    setting->setCursor(Qt::PointingHandCursor);
    setting->setPopupMode(QToolButton::MenuButtonPopup);
    setting->setFixedSize(80, 40);
    setting->setIcon(QIcon(":\\/\\icon\\settingIcon.png"));
    QMenu *menu = new QMenu();
    menu->addAction("Trang cá nhân", this, &StudentForm::goToProfile);
    menu->addAction("Đổi mật khẩu", this, &StudentForm::goToChangePasswordForm);
    menu->addAction("Đăng xuất", this, &StudentForm::goToLoginForm);
    setting->setMenu(menu);

    //          LAYOUT CHÍNH        //
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *layoutLine1 = new QHBoxLayout();
    QHBoxLayout *layoutLine2 = new QHBoxLayout();
    QHBoxLayout *layoutline3 = new QHBoxLayout();

    layoutLine1->addWidget(helloUser);
    layoutLine1->addStretch(2);
    layoutLine1->addWidget(setting);

    QFormLayout layout21, layout22, layout23;
    layout21.addRow("Năm học", this->year);
    layout22.addRow("Kì học", this->semester);
    layout23.addRow("", this->search);
    layoutLine2->addLayout(&layout21);
    layoutLine2->addLayout(&layout22);
    layoutLine2->addStretch();
    layoutLine2->addLayout(&layout23);
    layoutLine2->addStretch(1);

    this->line = layoutline3;
    layoutline3->addStretch();
    tab = new QTabWidget();
    tab->addTab(NULL, "Danh sách môn");
    tab->addTab(NULL, "Bảng điểm");
    layoutline3->addWidget(tab);
    layoutline3->addStretch();

    mainLayout->addLayout(layoutLine1);
    mainLayout->addLayout(layoutLine2);
    mainLayout->addStretch();
    mainLayout->addLayout(layoutline3);
    mainLayout->addStretch();

    //          CỬA SỔ CHÍNH          //
    this->setAlignment(Qt::AlignCenter);
    this->setLayout(mainLayout);
    this->setWindowTitle("Sinh Viên");
    this->setWindowIcon(QIcon(":\\/\\icon\\Logo.png"));
    this->setPixmap(QPixmap(":\\/\\background\\hcmus_linh_trung.jpg"));
    this->showMaximized();
}

void StudentForm::searchListCourse() {
    this->tab->clear();
    // TabListCourseForStudent* tmp1 = this->listCourse;
    // ScoreBoard* tmp2 = this->scoreBoard;
    this->listCourse = new TabListCourseForStudent(this->st->getListCoursesOfASemester(this->year->currentText().toStdString(), this->semester->currentText().toStdString()));
    this->scoreBoard = new ScoreBoard(this->st, this->year->currentText().toStdString(), this->semester->currentText().toStdString());
    // delete tmp1;
    // delete tmp2;

    this->tab->addTab(this->listCourse, "Danh sách môn");
    this->tab->addTab(this->scoreBoard, "Bảng điểm");
}

