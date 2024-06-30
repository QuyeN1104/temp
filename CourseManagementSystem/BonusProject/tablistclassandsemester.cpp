#include "tablistclassandsemester.h"
#include <QVBoxLayout>

// Hàm tạo cho lớp TabListClassAndSemester
TabListClassAndSemester::TabListClassAndSemester(LinkedList_Classes* listClass, LinkedList_Semesters* listSemester) {
    this->listClass = listClass;
    this->listSemester = listSemester;

    // Thiết lập mô hình với hai hàng và một cột
    model = new QStandardItemModel(2, 1);
    model->setData(model->index(0, 0), "Các lớp học");
    model->setData(model->index(1, 0), "Các kì học");

    // Thiết lập bảng hiển thị
    tableView = new QTableView();
    tableView->setEditTriggers(QTableView::NoEditTriggers);
    tableView->horizontalHeader()->setVisible(false);
    tableView->setFixedSize(930, 500);
    tableView->setModel(model);
    tableView->setColumnWidth(0, 780);

    // Thiết lập layout chính và thêm bảng hiển thị vào layout
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(tableView);
    this->setLayout(mainLayout);
}
