#include "tabliststudent.h"


TabListStudent::TabListStudent(Course* course, Staff* staff, QString type) : QWidget() {
    this->course = course;
    this->listStudent = course->getListStudents();
    this->staff = staff;
    this->type = type;

    model = new QStandardItemModel(0, 7);
    model->setHorizontalHeaderLabels({"CCCD", "MSSV", "Họ đệm", "Tên", "Lớp học", "Giới tính", "Ngày sinh"});

    if (listStudent != NULL) {
        NodeStudent* cur = listStudent->head;
        while (cur != NULL) {
            QList<QStandardItem *> items;
            items.append(new QStandardItem(QString::fromStdString(cur->data.getSocialID())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.getStudentID())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.getFirstName())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.getLastName())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.getEnrolledClass())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.getGender())));
            items.append(new QStandardItem(QString::fromStdString(dateToString(cur->data.getDateOfBirth()))));
            model->appendRow(items);
            cur = cur->next;
        }
    }
    tableView = new QTableView();
    tableView->setEditTriggers(QTableView::NoEditTriggers);
    tableView->setFixedSize(970, 500);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidget(tableView);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    tableView->setModel(model);
    tableView->setColumnWidth(0, 130);
    tableView->setColumnWidth(1, 130);
    tableView->setColumnWidth(2, 150);
    tableView->setColumnWidth(3, 150);
    tableView->setColumnWidth(5, 100);
    tableView->setColumnWidth(6, 150);
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(scrollArea);
    this->setLayout(mainLayout);
}

TabListStudent::TabListStudent(Class* clas, Staff* staff, QString type) : QWidget() {
    this->clas = clas;
    this->listStudent = clas->getListStudents();
    this->staff = staff;
    this->type = type;

    model = new QStandardItemModel(0, 7);
    model->setHorizontalHeaderLabels({"CCCD", "MSSV", "Họ đệm", "Tên", "Lớp học", "Giới tính", "Ngày sinh"});

    if (listStudent != NULL) {
        NodeStudent* cur = listStudent->head;
        while (cur != NULL) {
            QList<QStandardItem *> items;
            items.append(new QStandardItem(QString::fromStdString(cur->data.getSocialID())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.getStudentID())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.getFirstName())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.getLastName())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.getEnrolledClass())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.getGender())));
            items.append(new QStandardItem(QString::fromStdString(dateToString(cur->data.getDateOfBirth()))));
            model->appendRow(items);
            cur = cur->next;
        }
    }
    tableView = new QTableView();
    tableView->setEditTriggers(QTableView::NoEditTriggers);
    tableView->setFixedSize(970, 500);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidget(tableView);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    tableView->setModel(model);
    tableView->setColumnWidth(0, 130);
    tableView->setColumnWidth(1, 130);
    tableView->setColumnWidth(2, 150);
    tableView->setColumnWidth(3, 150);
    tableView->setColumnWidth(5, 100);
    tableView->setColumnWidth(6, 150);
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(scrollArea);
    this->setLayout(mainLayout);
    // this->show();
}

void TabListStudent::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction("Thêm học sinh",this, &TabListStudent::addStudent);
    menu.addAction("Thêm học sinh từ file", this, &TabListStudent::addStudentFromFile);
    if (this->type == "Course") {
        menu.addAction("Xóa học sinh", this, &TabListStudent::removeStudent);
        menu.addAction("Xuất danh sách điểm", this, &TabListStudent::exportListStudent);
        menu.addAction("Cập nhật điểm", this, &TabListStudent::getScoreFromFile);
    }
    menu.exec(event->globalPos());
}

void TabListStudent::addStudent() {
    QDialog dialog;
    QLineEdit *socialIDEdit = new QLineEdit(&dialog);
    QLineEdit *studentIDEdit = new QLineEdit(&dialog);
    QLineEdit *firstNameEdit = new QLineEdit(&dialog);
    QLineEdit *lastNameEdit = new QLineEdit(&dialog);
    QLineEdit *enrolledClassEdit = new QLineEdit(&dialog);
    QComboBox *genderComboBox = new QComboBox(&dialog);
    QLineEdit *dobEdit = new QLineEdit(&dialog);
    genderComboBox->addItem("Nam");
    genderComboBox->addItem("Nữ");
    socialIDEdit->setPlaceholderText("VD: 011111111111");
    studentIDEdit->setPlaceholderText("VD: 23121111");
    firstNameEdit->setPlaceholderText("VD: Nguyen Van");
    lastNameEdit->setPlaceholderText("VD: A");
    enrolledClassEdit->setPlaceholderText("VD: 23CTT5");
    dobEdit->setPlaceholderText("dd/mm/yyyy");
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("CCCD:", socialIDEdit);
    formLayout->addRow("MSSV:", studentIDEdit);
    formLayout->addRow("Họ đệm:", firstNameEdit);
    formLayout->addRow("Tên:", lastNameEdit);
    formLayout->addRow("Lớp:", enrolledClassEdit);
    formLayout->addRow("Giới tính:", genderComboBox);
    formLayout->addRow("Ngày sinh:", dobEdit);
    QPushButton *okButton = new QPushButton("OK", &dialog);
    QObject::connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(okButton);
    dialog.setLayout(mainLayout);
    dialog.setWindowTitle("Nhập thông tin sinh viên");
    dialog.setWindowIcon(QIcon(":\\/\\icon\\Logo.png"));
    if (dialog.exec() == QDialog::Accepted) {
        if(socialIDEdit->text().isEmpty() || studentIDEdit->text().isEmpty() || firstNameEdit->text().isEmpty() || lastNameEdit->text().isEmpty() || enrolledClassEdit->text().isEmpty() || dobEdit->text().isEmpty()) {
            QMessageBox::critical(NULL, "Lỗi", "Không được để trống !");
            return;
        }
        model->insertRow(model->rowCount());
        model->setItem(model->rowCount() - 1, 0, new QStandardItem(socialIDEdit->text()));
        model->setItem(model->rowCount() - 1, 1, new QStandardItem(studentIDEdit->text()));
        model->setItem(model->rowCount() - 1, 2, new QStandardItem(firstNameEdit->text()));
        model->setItem(model->rowCount() - 1, 3, new QStandardItem(lastNameEdit->text()));
        model->setItem(model->rowCount() - 1, 4, new QStandardItem(enrolledClassEdit->text()));
        model->setItem(model->rowCount() - 1, 5, new QStandardItem(genderComboBox->currentText()));
        model->setItem(model->rowCount() - 1, 6, new QStandardItem(dobEdit->text()));
        Student tmp(socialIDEdit->text().toStdString(),
                    studentIDEdit->text().toStdString(),
                    firstNameEdit->text().toStdString(),
                    lastNameEdit->text().toStdString(),
                    enrolledClassEdit->text().toStdString(),
                    genderComboBox->currentText().toStdString(),
                    dobEdit->text().toStdString());
        this->staff->addTailStudent(this->listStudent, tmp);
        if (this->type == "Class") {
            this->staff->addStudentInClass(this->clas, &tmp);
        }
        if (this->type == "Course") {
            this->staff->addStudentInCourse(this->course, &tmp);
        }
    }
}

void TabListStudent::addStudentFromFile() {
    QString fileName = QFileDialog::getOpenFileName(NULL, "Chọn tệp", QDir::currentPath(), "Tất cả các tệp (*.*)");
    if(fileName.isEmpty()) {
        return;
    }
    if (!fileName.endsWith(".csv")) {
        QMessageBox::critical(NULL, "Lỗi", "Định dạng file không hợp lệ, yêu cầu là file csv");
        return;
    }
    if (this->type == "Class") {
        qDebug() << "Class1";
        this->staff->loadStudentsInClass(this->listStudent, fileName.toStdString());
        qDebug() << "Class 2";
    }
    else if (this->type == "Course") {
        this->staff->loadStudentsInCourse(this->listStudent, fileName.toStdString());
    }

    model->removeRows(0, model->rowCount());
    if (listStudent != NULL) {
        NodeStudent* cur = listStudent->head;

        while (cur != NULL) {
            QList<QStandardItem *> items;
            items.append(new QStandardItem(QString::fromStdString(cur->data.getSocialID())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.getStudentID())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.getFirstName())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.getLastName())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.getEnrolledClass())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.getGender())));
            items.append(new QStandardItem(QString::fromStdString(dateToString(cur->data.getDateOfBirth()))));
            model->appendRow(items);
            cur = cur->next;
        }
    }
}

void TabListStudent::removeStudent() {
    if (this->type == "Course") {
        if(model->rowCount() > 0) {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(NULL, "Thông báo", "Bạn chắc chắn muốn xóa khóa học này ?", QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                int rowIndex = tableView->currentIndex().row();
                QModelIndex index = model->index(rowIndex, 1);
                QVariant data = model->data(index);
                this->staff->deleteStudentFromCourse(this->course, data.toString().toStdString());
                tableView->model()->removeRow(rowIndex);
            }
        }
    }
}

void TabListStudent::editStudent() {
    QModelIndex currentIndex = tableView->currentIndex();
    if (currentIndex.isValid()) {
        QDialog dialog;
        QLineEdit *socialIDEdit = new QLineEdit(&dialog);
        QLineEdit *studentIDEdit = new QLineEdit(&dialog);
        QLineEdit *firstNameEdit = new QLineEdit(&dialog);
        QLineEdit *lastNameEdit = new QLineEdit(&dialog);
        QLineEdit *enrolledClassEdit = new QLineEdit(&dialog);
        QComboBox *genderComboBox = new QComboBox(&dialog);
        QLineEdit *dobEdit = new QLineEdit(&dialog);
        genderComboBox->addItem("Nam");
        genderComboBox->addItem("Nữ");
        socialIDEdit->setPlaceholderText("VD: 011111111111");
        studentIDEdit->setPlaceholderText("VD: 23121111");
        firstNameEdit->setPlaceholderText("VD: Nguyen Van");
        lastNameEdit->setPlaceholderText("VD: A");
        enrolledClassEdit->setPlaceholderText("VD: 23CTT5");
        dobEdit->setPlaceholderText("dd/mm/yyyy");
        QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow("CCCD:", socialIDEdit);
        formLayout->addRow("MSSV:", studentIDEdit);
        formLayout->addRow("Họ đệm:", firstNameEdit);
        formLayout->addRow("Tên:", lastNameEdit);
        formLayout->addRow("Lớp:", enrolledClassEdit);
        formLayout->addRow("Giới tính:", genderComboBox);
        formLayout->addRow("Ngày sinh:", dobEdit);
        QPushButton *okButton = new QPushButton("OK", &dialog);
        QObject::connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
        QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(okButton);
        dialog.setLayout(mainLayout);
        dialog.setWindowTitle("Chỉnh sửa thông tin sinh viên");
        dialog.setWindowIcon(QIcon(":\\/\\icon\\Logo.png"));
        if (dialog.exec() == QDialog::Accepted) {
            model->setItem(currentIndex.row(), 0, new QStandardItem(socialIDEdit->text()));
            model->setItem(currentIndex.row(), 1, new QStandardItem(studentIDEdit->text()));
            model->setItem(currentIndex.row(), 2, new QStandardItem(firstNameEdit->text()));
            model->setItem(currentIndex.row(), 3, new QStandardItem(lastNameEdit->text()));
            model->setItem(currentIndex.row(), 4, new QStandardItem(enrolledClassEdit->text()));
            model->setItem(currentIndex.row(), 5, new QStandardItem(genderComboBox->currentText()));
            model->setItem(currentIndex.row(), 6, new QStandardItem(dobEdit->text()));
        }
    }
}

void TabListStudent::exportListStudent() {
    if (this->type == "Course") {
        QString dir = QFileDialog::getExistingDirectory(NULL, QObject::tr("Chọn thư mục"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
        if(dir.isEmpty()) {
            return;
        }
        this->staff->exportCourseCsvFile(course, dir.toStdString());
    }

}

void TabListStudent::getScoreFromFile() {
    if (this->type == "Course") {
        QString fileName = QFileDialog::getOpenFileName(NULL, "Chọn tệp", QDir::currentPath(), "Tất cả các tệp (*.*)");
        if(fileName.isEmpty()) {
            return;
        }
        if (!fileName.endsWith(".csv")) {
            QMessageBox::critical(NULL, "Lỗi", "Định dạng file không hợp lệ, yêu cầu là file csv");
            return;
        }
        this->staff->importCourseCsvFile(this->course, fileName.toStdString());
    }
}
