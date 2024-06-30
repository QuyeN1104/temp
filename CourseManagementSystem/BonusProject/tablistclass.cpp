#include "tablistclass.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>

// Hàm tạo cho lớp TabListClass
TabListClass::TabListClass(LinkedList_Classes* listClass, Staff* staff) : QWidget() {
    this->listClass = listClass;
    this->staff = staff;

    // Thiết lập mô hình với một cột cho tên lớp học
    model = new QStandardItemModel(0, 1);
    model->setHorizontalHeaderLabels({"Lớp học"});

    // Điền dữ liệu vào mô hình từ danh sách các lớp học hiện có
    if (listClass != NULL) {
        NodeClass* cur = this->listClass->head;
        while (cur != NULL) {
            QList<QStandardItem *> items;
            items.append(new QStandardItem(QString::fromStdString(cur->data.getNameClass())));
            model->appendRow(items);
            cur = cur->next;
        }
    }

    // Thiết lập bảng hiển thị
    tableView = new QTableView();
    tableView->setEditTriggers(QTableView::NoEditTriggers);
    tableView->setFixedSize(930, 500);
    tableView->setModel(model);
    tableView->setColumnWidth(0, 930);

    // Thiết lập layout chính và thêm bảng hiển thị vào layout
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(tableView);
    this->setLayout(mainLayout);
}

// Xử lý sự kiện menu ngữ cảnh
void TabListClass::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
    menu.addAction("Thêm lớp học mới", this, &TabListClass::addClass);
    // menu.addAction("Xóa lớp học", this, &TabListClass::removeClass);
    // menu.addAction("Chỉnh sửa lớp học", this, &TabListClass::editClass);
    menu.exec(event->globalPos());
}

// Thêm một lớp học mới
void TabListClass::addClass() {
    bool ok;
    QString className = QInputDialog::getText(
        NULL,
        "Nhập tên lớp học",
        "Vui lòng nhập tên lớp học:",
        QLineEdit::Normal,
        "",
        &ok
        );

    if (ok) {
        // Kiểm tra xem lớp học đã tồn tại chưa
        for (int row = 0; row < model->rowCount(); ++row) {
            QModelIndex index = model->index(row, 0);
            QVariant data = model->data(index);
            if (className == data.toString()) {
                QMessageBox::critical(NULL, "Thông báo", "Lớp học đã được khởi tạo từ trước", QMessageBox::Apply);
                return;
            }
        }
        // Thêm lớp học mới vào mô hình
        model->insertRow(model->rowCount());
        model->setItem(model->rowCount() - 1, 0, new QStandardItem(className));
        this->staff->addTailClass(this->listClass, className.toStdString());
    }
}

// Xóa một lớp học
void TabListClass::removeClass() {
    if(model->rowCount() > 0) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(NULL, "Thông báo", "Bạn chắc chắn muốn xóa lớp này?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            int rowIndex = tableView->currentIndex().row();
            tableView->model()->removeRow(rowIndex);
        }
    }
}

// Chỉnh sửa một lớp học
void TabListClass::editClass() {
    bool ok;
    QString className = QInputDialog::getText(
        NULL,
        "Chỉnh sửa lớp học",
        "Vui lòng nhập tên lớp học:",
        QLineEdit::Normal,
        "",
        &ok
        );

    if (ok) {
        // Kiểm tra xem lớp học đã tồn tại chưa
        for (int row = 0; row < model->rowCount(); ++row) {
            QModelIndex index = model->index(row, 0);
            QVariant data = model->data(index);
            if (className == data.toString()) {
                QMessageBox::critical(NULL, "Thông báo", "Lớp học đã được khởi tạo từ trước", QMessageBox::Apply);
                return;
            }
        }
        // Cập nhật tên lớp học trong mô hình
        tableView->model()->setData(tableView->currentIndex(), className, Qt::DisplayRole);
    }
}
