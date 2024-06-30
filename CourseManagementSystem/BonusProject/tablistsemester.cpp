#include "tablistsemester.h"
#include <QMessageBox>
#include <QVBoxLayout>

TabListSemester::TabListSemester(LinkedList_Semesters* listSemester, Staff* staff) : QWidget() {
    // Khởi tạo danh sách kì học và nhân viên
    this->listSemester = listSemester;
    this->staff = staff;

    // Tạo model cho TableView và đặt tiêu đề cột
    model = new QStandardItemModel(0, 3);
    model->setHorizontalHeaderLabels({"Kì học", "Ngày bắt đầu", "Ngày kết thúc"});

    // Nếu danh sách kì học không rỗng, thêm dữ liệu vào model
    if (listSemester != NULL) {
        NodeSemester* cur = listSemester->head;
        while(cur != NULL) {
            QList<QStandardItem *> items;
            items.append(new QStandardItem(QString::fromStdString(cur->data.getNameSemester())));
            items.append(new QStandardItem(QString::fromStdString(dateToString(cur->data.getStartDate()))));
            items.append(new QStandardItem(QString::fromStdString(dateToString(cur->data.getEndDate()))));
            model->appendRow(items);
            cur = cur->next;
        }
    }

    // Tạo TableView để hiển thị dữ liệu
    tableView = new QTableView();
    tableView->setEditTriggers(QTableView::NoEditTriggers);
    tableView->setFixedSize(930, 500);
    tableView->setModel(model);
    tableView->setColumnWidth(0, 330);
    tableView->setColumnWidth(1, 300);
    tableView->setColumnWidth(2, 300);

    // Đặt layout chính của widget
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(tableView);
    this->setLayout(mainLayout);
}

void TabListSemester::contextMenuEvent(QContextMenuEvent *event)
{
    // Tạo menu ngữ cảnh cho TableView
    QMenu menu(this);
    menu.addAction("Thêm kì học", this, &TabListSemester::addSemester);
    // menu.addAction("Xóa kì học", this, &TabListSemester::removeSemester);
    // menu.addAction("Chỉnh sửa kì học", this, &TabListSemester::editSemester);
    menu.exec(event->globalPos());
}

void TabListSemester::addSemester() {
    // Kiểm tra số lượng hàng trong model, nếu vượt quá 3 thì thông báo lỗi
    if (model->rowCount() + 1 > 3) {
        QMessageBox::critical(nullptr, "Thông báo", "Số lượng kì học quá giới hạn !", QMessageBox::Ok);
    }
    else {
        // Tạo dialog để nhập thông tin kì học mới
        QDialog dialog;
        QLineEdit *semesterNameEdit = new QLineEdit(&dialog);
        QLineEdit *startDateEdit = new QLineEdit(&dialog);
        QLineEdit *endDateEdit = new QLineEdit(&dialog);
        semesterNameEdit->setPlaceholderText("VD: 1");
        startDateEdit->setPlaceholderText("dd/mm/yyyy");
        endDateEdit->setPlaceholderText("dd/mm/yyyy");

        // Tạo layout cho dialog và thêm các trường nhập liệu
        QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow("Tên kì:", semesterNameEdit);
        formLayout->addRow("Ngày bắt đầu:", startDateEdit);
        formLayout->addRow("Ngày kết thúc:", endDateEdit);

        // Tạo nút OK để chấp nhận nhập liệu
        QPushButton *okButton = new QPushButton("OK", &dialog);
        QObject::connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

        // Đặt layout chính cho dialog và thiết lập tiêu đề cửa sổ
        QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(okButton);
        dialog.setLayout(mainLayout);
        dialog.setWindowTitle("Nhập thông tin kì học");
        dialog.setWindowIcon(QIcon(":\\/\\icon\\Logo.png"));

        // Nếu người dùng chấp nhận nhập liệu, thêm dữ liệu vào model và danh sách kì học
        if (dialog.exec() == QDialog::Accepted) {
            if (semesterNameEdit->text().isEmpty() || startDateEdit->text().isEmpty() || endDateEdit->text().isEmpty()) {
                QMessageBox::critical(nullptr, "Lỗi", "Không được để trống !");
                return;
            }
            model->insertRow(model->rowCount());
            model->setItem(model->rowCount() - 1, 0, new QStandardItem(semesterNameEdit->text()));
            model->setItem(model->rowCount() - 1, 1, new QStandardItem(startDateEdit->text()));
            model->setItem(model->rowCount() - 1, 2, new QStandardItem(endDateEdit->text()));

            // Tạo đối tượng Semester từ dữ liệu nhập và thêm vào danh sách kì học của nhân viên
            Semester tmp(stringToDate(startDateEdit->text().toStdString()),
                         stringToDate(endDateEdit->text().toStdString()),
                         semesterNameEdit->text().toStdString()
                         );
            this->staff->addTailSemester(this->listSemester, tmp);
        }
    }
}

void TabListSemester::removeSemester() {
    // Kiểm tra nếu có hàng được chọn trong TableView
    if (model->rowCount() > 0) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(nullptr, "Thông báo", "Bạn chắc chắn muốn xóa kì học này ?", QMessageBox::Yes | QMessageBox::No);

        // Nếu người dùng chọn Yes, xóa hàng tại vị trí được chọn
        if (reply == QMessageBox::Yes) {
            int rowIndex = tableView->currentIndex().row();
            tableView->model()->removeRow(rowIndex);
        }
    }
}

void TabListSemester::editSemester() {
    QModelIndex currentIndex = tableView->currentIndex();
    // Kiểm tra hàng hiện tại có hợp lệ không
    if (currentIndex.isValid()) {
        // Tạo dialog để chỉnh sửa thông tin kì học
        QDialog dialog;
        QLineEdit *semesterNameEdit = new QLineEdit(&dialog);
        QLineEdit *startDateEdit = new QLineEdit(&dialog);
        QLineEdit *endDateEdit = new QLineEdit(&dialog);
        semesterNameEdit->setPlaceholderText("VD: 1");
        startDateEdit->setPlaceholderText("dd/mm/yyyy");
        endDateEdit->setPlaceholderText("dd/mm/yyyy");

        // Tạo layout cho dialog và thêm các trường nhập liệu
        QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow("Tên kì:", semesterNameEdit);
        formLayout->addRow("Ngày bắt đầu:", startDateEdit);
        formLayout->addRow("Ngày kết thúc:", endDateEdit);

        // Tạo nút OK để chấp nhận chỉnh sửa
        QPushButton *okButton = new QPushButton("OK", &dialog);
        QObject::connect(okButton, &QPushButton::clicked, &dialog, &QDialog::accept);

        // Đặt layout chính cho dialog và thiết lập tiêu đề cửa sổ
        QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
        mainLayout->addLayout(formLayout);
        mainLayout->addWidget(okButton);
        dialog.setLayout(mainLayout);
        dialog.setWindowTitle("Chỉnh sửa thông tin kì học");
        dialog.setWindowIcon(QIcon(":\\/\\icon\\Logo.png"));

        // Nếu người dùng chấp nhận chỉnh sửa, cập nhật dữ liệu vào model
        if (dialog.exec() == QDialog::Accepted) {
            model->setItem(currentIndex.row(), 0, new QStandardItem(semesterNameEdit->text()));
            model->setItem(currentIndex.row(), 1, new QStandardItem(startDateEdit->text()));
            model->setItem(currentIndex.row(), 2, new QStandardItem(endDateEdit->text()));
        }
    }
}
