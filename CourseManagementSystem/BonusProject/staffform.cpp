#include "staffform.h"

StaffForm::StaffForm(Staff* staff) : QLabel(){
    this->staff = staff;
    helloStaff = new QLabel("Chào Admin");
    helloStaff->setFont(QFont("Arial", 30, 10));
    // helloStaff->setFixedSize(200, 300);

    setting = new QToolButton();
    setting->setCursor(Qt::PointingHandCursor);
    setting->setPopupMode(QToolButton::MenuButtonPopup);
    setting->setFixedSize(80, 40);
    setting->setIcon(QIcon(":\\/\\icon\\settingIcon.png"));
    QMenu *menu = new QMenu();
    menu->addAction("Trang cá nhân", this, &StaffForm::goToProfile);
    menu->addAction("Đổi mật khẩu", this, &StaffForm::goToChangePasswordForm);
    menu->addAction("Đăng xuất", this, &StaffForm::goToLoginForm);
    setting->setMenu(menu);

    tab = new QTabWidget();
    this->listSchoolYear = new TabListSchoolYear(staff->getListSchoolYearsOfSchool(), this->staff);
    tab->addTab(this->listSchoolYear, "Các năm học");
    tab->setTabsClosable(true);
    tab->setFixedSize(950, 500);

    connect(this->listSchoolYear->tableView, &QTableView::doubleClicked, this, &StaffForm::doubleClickOnSchoolYear);

    //Xoa tab
    QTabWidget* tabTmp = this->tab;
    connect(tabTmp, &QTabWidget::tabCloseRequested, this, [tabTmp](int index) {
        QWidget *widget = tabTmp->widget(index);
        if (widget) {
            tabTmp->removeTab(index);
            delete widget;
        }
    });

    QHBoxLayout* line1 = new QHBoxLayout();
    line1->addWidget(helloStaff, Qt::AlignCenter);
    line1->addStretch();
    line1->addWidget(setting, Qt::AlignCenter);

    QHBoxLayout* line3 = new QHBoxLayout();
    line3->addStretch();
    line3->addWidget(tab);
    line3->addStretch();

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(line1);
    mainLayout->addStretch();
    // mainLayout->addLayout(line2);
    // mainLayout->addStretch();
    mainLayout->addLayout(line3);
    mainLayout->addStretch();
    this->setLayout(mainLayout);
    this->setWindowTitle("Giáo viên");
    this->setWindowIcon(QIcon(":\\/\\icon\\Logo.png"));
    this->setPixmap(QPixmap(":\\/\\background\\hcmus_linh_trung.jpg"));
    this->showMaximized();
}

void StaffForm::doubleClickOnSchoolYear(const QModelIndex &index) {
    if (index.isValid()) {
        QModelIndex i = listSchoolYear->model->index(index.row(), 0, QModelIndex());
        QVariant data = listSchoolYear->model->data(i);
        QString nameYearSchoolQString = data.toString();
        std::string nameYearSchoolString = nameYearSchoolQString.toStdString();
        this->curSchoolYear = nameYearSchoolString;
        for (int i = 0; i < this->tab->count(); i++) {
            if (this->tab->tabText(i) == nameYearSchoolQString) {
                this->tab->setCurrentIndex(i);
                return;
            }
        }
        this->listClassAndSemester = new TabListClassAndSemester(
            this->staff->listClassesInYear(nameYearSchoolString),
            this->staff->getSchoolYearByName(this->staff->getListSchoolYearsOfSchool(), nameYearSchoolString)->getListSemesters()
        );
        connect(this->listClassAndSemester->tableView, &QTableView::doubleClicked, this, &StaffForm::doubleClickINSchoolYear);
        this->tab->addTab(this->listClassAndSemester, nameYearSchoolQString);
        this->tab->setCurrentIndex(this->tab->count() - 1);
    }
}

void StaffForm::doubleClickINSchoolYear(const QModelIndex &index) {
    if (index.isValid()) {
        QModelIndex i = listClassAndSemester->model->index(index.row(), 0);
        QVariant data = listClassAndSemester->model->data(i);
        QString choose = data.toString();

        if (choose.startsWith("Các kì học")) {
            // QWidget* tmp = this->listSemester;
            for (int i = 0; i < this->tab->count(); i++) {
                if (this->tab->tabText(i) == QString::fromStdString("Các kì học (" + this->curSchoolYear + ")")) {
                    this->tab->setCurrentIndex(i);
                    return;
                }
            }
            this->listSemester = new TabListSemester(this->listClassAndSemester->listSemester, this->staff);
            connect(this->listSemester->tableView, &QTableView::doubleClicked, this, &StaffForm::doubleClickOnSemester);
            this->tab->addTab(this->listSemester, QString::fromStdString("Các kì học (" + this->curSchoolYear + ")"));
            this->tab->setCurrentIndex(this->tab->count() - 1);
            // delete tmp;
        }
        else if (choose.startsWith("Các lớp học")) {
            for (int i = 0; i < this->tab->count(); i++) {
                if (this->tab->tabText(i) == QString::fromStdString("Các lớp học (" + this->curSchoolYear + ")")) {
                    this->tab->setCurrentIndex(i);
                    return;
                }
            }
            this->listClass = new TabListClass(this->listClassAndSemester->listClass, this->staff);
            connect(this->listClass->tableView, &QTableView::doubleClicked, this, &StaffForm::doubleClickOnClass);
            this->tab->addTab(this->listClass, QString::fromStdString("Các lớp học (" + this->curSchoolYear + ")"));
            this->tab->setCurrentIndex(this->tab->count() - 1);
        }
    }
}

void StaffForm::doubleClickOnClass(const QModelIndex &index) {
    if(index.isValid()) {
        QModelIndex i = listClass->model->index(index.row(), 0, QModelIndex());
        QVariant data = listClass->model->data(i);
        QString nameClassQString = data.toString();
        std::string nameClassString = nameClassQString.toStdString();
        // TabListStudent* tmp  = this->listStudent;
        for (int i = 0; i < this->tab->count(); i++) {
            if (this->tab->tabText(i) == nameClassQString) {
                this->tab->setCurrentIndex(i);
                return;
            }
        }
        this->listStudent = new TabListStudent(this->staff->getClassByName(this->staff->listClassesInYear(curSchoolYear), nameClassString), this->staff, "Class");
        connect(this->listStudent->tableView, &QTableView::doubleClicked, this, &StaffForm::doubleClickOnStudent);
        this->tab->addTab(this->listStudent, nameClassQString);
        this->tab->setCurrentIndex(this->tab->count() - 1);
        // delete tmp;
    }
}

void StaffForm::doubleClickOnSemester(const QModelIndex &index) {
    if(index.isValid()) {
        QModelIndex i = listSemester->model->index(index.row(), 0, QModelIndex());
        QVariant data = listSemester->model->data(i);
        QString nameSemesterQString = data.toString();
        std::string nameSemesterString = nameSemesterQString.toStdString();
        this->curSemester = nameSemesterString;
        // TabListCourse* tmp = this->listCourse;
        for (int i = 0; i < this->tab->count(); i++) {
            if (this->tab->tabText(i) == nameSemesterQString) {
                this->tab->setCurrentIndex(i);
                return;
            }
        }
        this->listCourse = new TabListCourse(this->staff->listCourseOfSemester(this->staff->getListSchoolYearsOfSchool(), curSchoolYear, nameSemesterString), this->staff);
        connect(this->listCourse->tableView, &QTableView::doubleClicked, this, &StaffForm::doubleClickOnCourse);
        this->tab->addTab(this->listCourse, "Kì " + nameSemesterQString + QString::fromStdString("(" + this->curSchoolYear + ")"));
        this->tab->setCurrentIndex(this->tab->count() - 1);
        // delete tmp;
    }
}

void StaffForm::doubleClickOnCourse(const QModelIndex &index) {
    if(index.isValid()) {
        QModelIndex i = listCourse->model->index(index.row(), 3, QModelIndex());
        QVariant data = listCourse->model->data(i);
        QString nameCourseQString = data.toString();
        std::string nameCourseString = nameCourseQString.toStdString();
        for (int i = 0; i < this->tab->count(); i++) {
            if (this->tab->tabText(i) == nameCourseQString) {
                this->tab->setCurrentIndex(i);
                return;
            }
        }
        this->listStudent = new TabListStudent(this->staff->getCourseByName(this->staff->listCourseOfSemester(this->staff->getListSchoolYearsOfSchool(),this->curSchoolYear, this->curSemester), nameCourseString), this->staff, "Course");
        connect(this->listStudent->tableView, &QTableView::doubleClicked, this, &StaffForm::doubleClickOnStudent);
        this->tab->addTab(this->listStudent, nameCourseQString);
        this->tab->setCurrentIndex(this->tab->count() - 1);
    }
}

void StaffForm::doubleClickOnStudent(const QModelIndex &index) {
    if (index.isValid()) {
        QModelIndex i = listStudent->model->index(index.row(), 1, QModelIndex());
        QVariant data = listStudent->model->data(i);

        QTabWidget *tabWidget = new QTabWidget;

        // Tab 1
        QWidget *tab1 = new QWidget;
        QVBoxLayout *layout1 = new QVBoxLayout;
        ScoreBoard *sb1 = new ScoreBoard(this->staff->findStudentByID(data.toString().toStdString()), this->curSchoolYear, "1");
        layout1->addWidget(sb1);
        tab1->setLayout(layout1);
        tabWidget->addTab(tab1, "Kì 1");

        // Tab 2
        QWidget *tab2 = new QWidget;
        QVBoxLayout *layout2 = new QVBoxLayout;
        ScoreBoard *sb2 = new ScoreBoard(this->staff->findStudentByID(data.toString().toStdString()), this->curSchoolYear, "2");
        layout2->addWidget(sb2);
        tab2->setLayout(layout2);
        tabWidget->addTab(tab2, "Kì 2");

        // Tab 3
        QWidget *tab3 = new QWidget;
        QVBoxLayout *layout3 = new QVBoxLayout;
        ScoreBoard *sb3 = new ScoreBoard(this->staff->findStudentByID(data.toString().toStdString()), this->curSchoolYear, "3");
        layout3->addWidget(sb3);
        tab3->setLayout(layout3);
        tabWidget->addTab(tab3, "Kì 3");

        tabWidget->setWindowTitle(QString::fromStdString(this->staff->findStudentByID(data.toString().toStdString())->getStudentID()) + "-" + QString::fromStdString(this->staff->findStudentByID(data.toString().toStdString())->getFirstName() + " " + this->staff->findStudentByID(data.toString().toStdString())->getLastName()));
        tabWidget->setWindowIcon(QIcon(":\\/\\icon\\Logo.png"));
        tabWidget->setFixedSize(950, 530);
        tabWidget->setVisible(true);

    }
}




