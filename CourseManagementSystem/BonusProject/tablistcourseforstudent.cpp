#include "tablistcourseforstudent.h"
#include <QVBoxLayout>
#include <QScrollArea>

// Hàm tạo cho lớp TabListCourseForStudent
TabListCourseForStudent::TabListCourseForStudent(LinkedList_Courses* listCourse) : QWidget() {
    model = new QStandardItemModel(0, 7);
    model->setHorizontalHeaderLabels({"Mã môn", "Tên môn", "Số tín", "Lớp học", "Tên GV", "Thứ", "Buổi"});

    // Điền dữ liệu vào mô hình từ danh sách các khóa học hiện có
    if (listCourse != NULL) {
        NodeCourse* cur = listCourse->head;
        while(cur != NULL) {
            QList<QStandardItem *> items;
            items.append(new QStandardItem(QString::fromStdString(cur->data.getIdCourse())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.getNameCourse())));
            items.append(new QStandardItem(QString::number(cur->data.getNumCredits())));
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
    tableView->setModel(model);
    // tableView->setFixedSize(1050, 700);
    tableView->setColumnWidth(0, 130);
    tableView->setColumnWidth(1, 130);
    tableView->setColumnWidth(2, 150);
    tableView->setColumnWidth(3, 150);
    tableView->setColumnWidth(4, 120);
    tableView->setColumnWidth(5, 100);
    tableView->setColumnWidth(6, 150);

    // Thiết lập khu vực cuộn
    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidget(tableView);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Thiết lập layout chính và thêm khu vực cuộn vào layout
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(scrollArea);
    this->setLayout(mainLayout);
    this->setFixedSize(970, 500);
}
