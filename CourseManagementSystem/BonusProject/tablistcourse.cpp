#include "tablistcourse.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QPushButton>
#include <QIcon>

// Hàm tạo cho lớp TabListCourse
TabListCourse::TabListCourse(LinkedList_Courses* listCourse, Staff* staff) : QWidget() {
    this->listCourse = listCourse;
    this->staff = staff;

    // Thiết lập mô hình với 7 cột
    model = new QStandardItemModel(0, 7);
    model->setHorizontalHeaderLabels({"Mã môn", "Tên môn", "Số tín", "Lớp học", "Tên GV", "Thứ", "Buổi"});

    // Điền dữ liệu vào mô hình từ danh sách các khóa học hiện có
    if (listCourse != NULL) {
        NodeCourse* cur = listCourse->head;
        while (cur != NULL) {
            QList<QStandardItem *> items;
            items.append(new QStandardItem(QString::fromStdString(cur->data.getIdCourse())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.getNameCourse())));
            QStandardItem *numCreditsItem = new QStandardItem();
            numCreditsItem->setData(cur->data.getNumCredits(), Qt::DisplayRole);
            items.append(numCreditsItem);
            items.append(new QStandardItem(QString::fromStdString(cur->data.getClassName())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.getTeacherName())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.getDayofWeek())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.getSession())));
            model->appendRow(items);
            cur = cur->next;
        }
    }

    // Thiết lập bảng hiển thị
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

// Xử lý sự kiện menu ngữ cảnh
void TabListCourse::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
    menu.addAction("Thêm khóa học", this, &TabListCourse::addCourse);
    menu.addAction("Xóa khóa học", this, &TabListCourse::removeCourse);
    menu.addAction("Chỉnh sửa khóa học", this, &TabListCourse::editCourse);
    menu.addAction("Xem bảng điểm", this, &TabListCourse::showScoreBoard);
    menu.exec(event->globalPos());
}

// Thêm một khóa học mới
void TabListCourse::addCourse() {
    QDialog dialog;
    QLineEdit *idEdit = new QLineEdit(&dialog);
    QLineEdit *nameEdit = new QLineEdit(&dialog);
    QLineEdit *creditsEdit = new QLineEdit(&dialog);
    QLineEdit *roomEdit = new QLineEdit(&dialog);
    QLineEdit *teacherEdit = new QLineEdit(&dialog);
    QLineEdit *dayEdit = new QLineEdit(&dialog);
    QLineEdit *sessionEdit = new QLineEdit(&dialog);
    QFormLayout *formLayout = new QFormLayout;

    // Thiết lập các gợi ý cho các trường thông tin
    idEdit->setPlaceholderText("VD: CSC10002");
    nameEdit->setPlaceholderText("VD: Kĩ thuật lập trình");
    creditsEdit->setPlaceholderText("VD: 4");
    roomEdit->setPlaceholderText("VD: 231KTLT_1");
    teacherEdit->setPlaceholderText("VD: Nguyễn Lê Hoàng Dũng");
    dayEdit->setPlaceholderText("THU");
    sessionEdit->setPlaceholderText("S3(13:30)");

    // Thêm các trường thông tin vào form layout
    formLayout->addRow("Mã môn:", idEdit);
    formLayout->addRow("Tên môn:", nameEdit);
    formLayout->addRow("Số tín chỉ:", creditsEdit);
    formLayout->addRow("Lớp học:", roomEdit);
    formLayout->addRow("Tên giáo viên:", teacherEdit);
    formLayout->addRow("Thứ:", dayEdit);
    formLayout->addRow("Buổi:", sessionEdit);

    // Thiết lập nút OK và kết nối với sự kiện accept của dialog
    QPushButton *okButton = new QPushButton("OK", &dialog);
    QObject::connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

    // Thiết lập layout chính của dialog và thêm form layout cùng nút OK vào đó
    QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(okButton);
    dialog.setLayout(mainLayout);
    dialog.setWindowTitle("Nhập thông tin môn học");
    dialog.setWindowIcon(QIcon(":\\/\\icon\\Logo.png"));

    // Xử lý khi người dùng chấp nhận dialog
    if (dialog.exec() == QDialog::Accepted) {
        if (idEdit->text().isEmpty() || nameEdit->text().isEmpty() || creditsEdit->text().isEmpty() || roomEdit->text().isEmpty() || teacherEdit->text().isEmpty() || dayEdit->text().isEmpty() || sessionEdit->text().isEmpty()) {
            QMessageBox::critical(NULL, "Lỗi", "Không được để trống!");
            return;
        }
        model->insertRow(model->rowCount());
        model->setItem(model->rowCount() - 1, 0, new QStandardItem(idEdit->text()));
        model->setItem(model->rowCount() - 1, 1, new QStandardItem(nameEdit->text()));
        model->setItem(model->rowCount() - 1, 2, new QStandardItem(creditsEdit->text()));
        model->setItem(model->rowCount() - 1, 3, new QStandardItem(roomEdit->text()));
        model->setItem(model->rowCount() - 1, 4, new QStandardItem(teacherEdit->text()));
        model->setItem(model->rowCount() - 1, 5, new QStandardItem(dayEdit->text()));
        model->setItem(model->rowCount() - 1, 6, new QStandardItem(sessionEdit->text()));

        // Tạo đối tượng Course tạm thời và thêm vào danh sách khóa học
        Course tmp(idEdit->text().toStdString(),
                   nameEdit->text().toStdString(),
                   roomEdit->text().toStdString(),
                   teacherEdit->text().toStdString(),
                   creditsEdit->text().toInt(),
                   dayEdit->text().toStdString(),
                   sessionEdit->text().toStdString());
        this->staff->addTailCourse(this->listCourse, tmp);
    }
}

// Xóa một khóa học
void TabListCourse::removeCourse() {
    if (model->rowCount() > 0) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(NULL, "Thông báo", "Bạn chắc chắn muốn xóa khóa học này?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            int rowIndex = tableView->currentIndex().row();
            QModelIndex i = model->index(rowIndex, 3);
            this->staff->deleteCourse(this->listCourse, this->staff->getCourseByName(this->listCourse, model->data(i).toString().toStdString()));
            tableView->model()->removeRow(rowIndex);
        }
    }
}

// Chỉnh sửa một khóa học
void TabListCourse::editCourse() {
    QModelIndex currentIndex = tableView->currentIndex();
    if (currentIndex.isValid()) {
        QDialog dialog;
        QLineEdit *idEdit = new QLineEdit(&dialog);
        QLineEdit *nameEdit = new QLineEdit(&dialog);
        QLineEdit *creditsEdit = new QLineEdit(&dialog);
        QLineEdit *roomEdit = new QLineEdit(&dialog);
        QLineEdit *teacherEdit = new QLineEdit(&dialog);
        QLineEdit *dayEdit = new QLineEdit(&dialog);
        QLineEdit *sessionEdit = new QLineEdit(&dialog);
        QFormLayout *formLayout = new QFormLayout;

        // Thiết lập các gợi ý cho các trường thông tin
        idEdit->setPlaceholderText("VD: CSC10002");
        nameEdit->setPlaceholderText("VD: Kĩ thuật lập trình");
        creditsEdit->setPlaceholderText("VD: 4");
        roomEdit->setPlaceholderText("VD: 231KTLT_1");
        teacherEdit->setPlaceholderText("VD: Nguyễn Lê Hoàng Dũng");
        dayEdit->setPlaceholderText("THU");
        sessionEdit->setPlaceholderText("S3(13:30)");

        // Thêm các trường thông tin vào form layout
        formLayout->addRow("Mã môn:", idEdit);
        formLayout->addRow("Tên môn:", nameEdit);
        formLayout->addRow("Số tín chỉ:", creditsEdit);
        formLayout->addRow("Lớp học:", roomEdit);
        formLayout->addRow("Tên giáo viên:", teacherEdit);
        formLayout->addRow("Thứ:", dayEdit);
        formLayout->addRow("Buổi:", sessionEdit);

        // Thiết lập nút OK và kết nối với sự kiện accept của dialog
        QPushButton *okButton = new QPushButton("OK", &dialog);
        QObject::connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

        // Thiết lập layout chính của dialog và thêm form layout cùng nút OK vào đó
        QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(okButton);
        dialog.setLayout(mainLayout);
        dialog.setWindowTitle("Chỉnh sửa thông tin môn học");
        dialog.setWindowIcon(QIcon(":\\/\\icon\\Logo.png"));

        // Xử lý khi người dùng chấp nhận dialog
        if (dialog.exec() == QDialog::Accepted) {
            QModelIndex index = model->index(currentIndex.row(), 3);
            QVariant data = model->data(index);
            this->staff->setCourse(this->staff->getCourseByName(this->listCourse, data.toString().toStdString()), idEdit->text().toStdString(), nameEdit->text().toStdString(), roomEdit->text().toStdString(), teacherEdit->text().toStdString(), creditsEdit->text().toInt(), dayEdit->text().toStdString(), sessionEdit->text().toStdString());
            model->setItem(currentIndex.row(), 0, new QStandardItem(idEdit->text()));
            model->setItem(currentIndex.row(), 1, new QStandardItem(nameEdit->text()));
            model->setItem(currentIndex.row(), 2, new QStandardItem(creditsEdit->text()));
            model->setItem(currentIndex.row(), 3, new QStandardItem(roomEdit->text()));
            model->setItem(currentIndex.row(), 4, new QStandardItem(teacherEdit->text()));
            model->setItem(currentIndex.row(), 5, new QStandardItem(dayEdit->text()));
            model->setItem(currentIndex.row(), 6, new QStandardItem(sessionEdit->text()));
        }
    }
}

void TabListCourse::showScoreBoard() {
    QModelIndex i = model->index(tableView->currentIndex().row(), 3, QModelIndex());
    QVariant data = model->data(i);
    ScoreBoard* scoreboard = new ScoreBoard(this->staff->getCourseByName(listCourse, data.toString().toStdString()));
}
