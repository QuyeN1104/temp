#include "profileform.h"

ProfileForm::ProfileForm(Student* student) : QLabel() {

    QLabel* socialID = new QLabel(QString::fromStdString(student->getSocialID()));
    QLabel* studentID = new QLabel(QString::fromStdString(student->getStudentID()));
    QLabel* firstName = new QLabel(QString::fromStdString(student->getFirstName()));
    QLabel* lastName = new QLabel(QString::fromStdString(student->getLastName()));
    QLabel* enrolledClass = new QLabel(QString::fromStdString(student->getEnrolledClass()));
    QLabel* gender = new QLabel(QString::fromStdString(student->getGender()));
    QLabel*  dob= new QLabel(QString::fromStdString(dateToString(student->getDateOfBirth())));

    // Tạo layout cho profile
    QFormLayout* profileLayout = new QFormLayout();
    profileLayout->addRow("CCCD: ", socialID);
    profileLayout->addRow("MSSV: ", studentID);
    profileLayout->addRow("Họ đệm", firstName);
    profileLayout->addRow("Tên: ", lastName);
    profileLayout->addRow("Lớp: ", enrolledClass);
    profileLayout->addRow("Giới tính: ", gender);
    profileLayout->addRow("Ngày sinh: ", dob);

    // Tạo widget để hiển thị profile
    QWidget* profileWidget = new QWidget();
    profileWidget->setLayout(profileLayout);
    profileWidget->setFixedSize(550, 330);
    profileWidget->setStyleSheet("background-color: #f0f0f0; border: 1px solid #ddd; border-radius: 5px; padding: 10px;");

    // Tạo layout chính
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(profileLayout);
    mainLayout->addWidget(profileWidget, 0, Qt::AlignCenter); // Đặt profile ở giữa
    mainLayout->setContentsMargins(20, 20, 20, 20); // Khoảng cách từ viền của cửa sổ
    mainLayout->setSpacing(10); // Khoảng cách giữa các phần tử

    // Thiết lập layout cho cửa sổ
    this->setLayout(mainLayout);
    this->setWindowTitle("Trang cá nhân");
    this->setWindowIcon(QIcon(":/icon/Logo.png")); // Đường dẫn icon
    this->setFixedSize(700, 450); // Kích thước cố định cho cửa sổ
    this->setPixmap(QPixmap(":\\/\\background\\hcmusthumb().jpg"));
    this->show();
}

ProfileForm::ProfileForm(Staff* staff) : QLabel() {

    QLabel* socialID = new QLabel(QString::fromStdString(staff->getSocialID()));
    // QLabel* studentID = new QLabel(QString::fromStdString(staff->getStudentID()));
    QLabel* firstName = new QLabel(QString::fromStdString(staff->getFirstName()));
    QLabel* lastName = new QLabel(QString::fromStdString(staff->getLastName()));
    // QLabel* enrolledClass = new QLabel(QString::fromStdString(staff->getEnrolledClass()));
    QLabel* gender = new QLabel(QString::fromStdString(staff->getGender()));
    QLabel*  dob= new QLabel(QString::fromStdString(dateToString(staff->getDateOfBirth())));

    // Tạo layout cho profile
    QFormLayout* profileLayout = new QFormLayout();
    profileLayout->addRow("CCCD: ", socialID);
    // profileLayout->addRow("MSSV: ", studentID);
    profileLayout->addRow("Họ đệm", firstName);
    profileLayout->addRow("Tên: ", lastName);
    // profileLayout->addRow("Lớp: ", enrolledClass);
    profileLayout->addRow("Giới tính: ", gender);
    profileLayout->addRow("Ngày sinh: ", dob);

    // Tạo widget để hiển thị profile
    QWidget* profileWidget = new QWidget();
    profileWidget->setLayout(profileLayout);
    profileWidget->setFixedSize(550, 240);
    profileWidget->setStyleSheet("background-color: #f0f0f0; border: 1px solid #ddd; border-radius: 5px; padding: 10px;");

    // Tạo layout chính
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(profileLayout);
    mainLayout->addWidget(profileWidget, 0, Qt::AlignCenter); // Đặt profile ở giữa
    mainLayout->setContentsMargins(20, 20, 20, 20); // Khoảng cách từ viền của cửa sổ
    mainLayout->setSpacing(10); // Khoảng cách giữa các phần tử

    // Thiết lập layout cho cửa sổ
    this->setLayout(mainLayout);
    this->setWindowTitle("Trang cá nhân");
    this->setWindowIcon(QIcon(":/icon/Logo.png")); // Đường dẫn icon
    this->setFixedSize(700, 450); // Kích thước cố định cho cửa sổ
    this->setPixmap(QPixmap(":\\/\\background\\hcmusthumb().jpg"));
    this->show();
}

