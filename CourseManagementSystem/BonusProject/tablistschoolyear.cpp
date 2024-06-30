#include "tablistschoolyear.h"
#include <QVBoxLayout>
#include <QInputDialog>
#include <QMessageBox>

TabListSchoolYear::TabListSchoolYear(LinkedList_SchoolYears* listSchoolYear, Staff* staff) : QWidget() {
    this->listSchoolYear = listSchoolYear;
    this->staff = staff;

    model = new QStandardItemModel(0, 1);
    model->setHorizontalHeaderLabels({"Niên khóa"});

    if (listSchoolYear != NULL) {
        NodeSchoolYear* cur = this->listSchoolYear->head;
        while(cur != NULL) {
            QList<QStandardItem *> items;
            items.append(new QStandardItem(QString::fromStdString(cur->data.getNameSchoolYear())));
            model->appendRow(items);
            cur = cur->next;
        }
    }

    tableView = new QTableView();
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    tableView->horizontalHeader()->setFont(QFont("Arial", 14));
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setFont(QFont("Arial", 12));
    tableView->setShowGrid(true);
    tableView->setGridStyle(Qt::DotLine);
    tableView->setFrameShape(QFrame::NoFrame);

    tableView->setEditTriggers(QTableView::NoEditTriggers);
    tableView->setFixedSize(930, 500);
    tableView->setModel(model);
    tableView->setColumnWidth(0, 930);

    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(tableView);
    this->setLayout(mainLayout);
}

void TabListSchoolYear::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction("Thêm niên khóa",this, &TabListSchoolYear::addSchoolYear);
    // menu.addAction("Xóa niên khóa", this, &TabListSchoolYear::removeSchoolYear);
    // menu.addAction("Chỉnh sửa niên khóa", this, &TabListSchoolYear::editSchoolYear);
    menu.exec(event->globalPos());
}

void TabListSchoolYear::addSchoolYear() {
    bool ok;
    QString academicYear = QInputDialog::getText(
        NULL,
        "Nhập tên năm học",
        "Vui lòng nhập tên năm học:",
        QLineEdit::Normal,
        "",
        &ok
        );
    if (ok) {
        if (academicYear == "") {
            QMessageBox::critical(nullptr, "Lỗi", "Không được để trống !");
            return;
        }
        for (int row = 0; row < model->rowCount(); ++row) {
            QModelIndex index = model->index(row, 0);
            QVariant data = model->data(index);
            if (academicYear == data.toString()) {
                QMessageBox::critical(NULL, "Thông báo", "Năm học đã được khởi tạo từ trước", QMessageBox::Apply);
                return;
            }
        }
        model->insertRow(model->rowCount());
        model->setItem(model->rowCount() - 1, 0, new QStandardItem(academicYear));
        this->staff->addTailSchoolYear(this->staff->getListSchoolYearsOfSchool(), academicYear.toStdString());
    }
}

void TabListSchoolYear::removeSchoolYear() {
    if(model->rowCount() > 0) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(NULL, "Thông báo", "Bạn chắc chắn muốn xóa năm học này ?", QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            int rowIndex = tableView->currentIndex().row();
            tableView->model()->removeRow(rowIndex);
        }
    }
}

void TabListSchoolYear::editSchoolYear() {
    bool ok;
    QString academicYear = QInputDialog::getText(
        NULL,
        "Chỉnh sửa tên năm học",
        "Vui lòng nhập tên năm học:",
        QLineEdit::Normal,
        "",
        &ok
        );
    if (ok) {
        for (int row = 0; row < model->rowCount(); ++row) {
            QModelIndex index = model->index(row, 0);
            QVariant data = model->data(index);
            if (academicYear == data.toString()) {
                QMessageBox::critical(NULL, "Thông báo", "Năm học đã được khởi tạo từ trước", QMessageBox::Apply);
                return;
            }
        }
        tableView->model()->setData(tableView->currentIndex(), academicYear, Qt::DisplayRole);
    }
}

