#include "scoreboard.h"

ScoreBoard::ScoreBoard(Student* st, string year, string semester) : QWidget() {
    model = new QStandardItemModel(0, 7);
    model->setHorizontalHeaderLabels({"Mã môn", "Tên môn", "Số tín", "Điểm khác", "Điểm giữa kì", "Điểm cuối kì", "Điểm trung bình"});
    model->removeRows(0, model->rowCount());
    if (st->findSemesterInYear(year, semester)) {
        NodeMark* cur = st->findSemesterInYear(year, semester)->getListMarks()->head;
        while (cur) {
            QList<QStandardItem *> items;
            items.append(new QStandardItem(QString::fromStdString(cur->data.course->getIdCourse())));
            items.append(new QStandardItem(QString::fromStdString(cur->data.course->getNameCourse())));
            QStandardItem *numCreditsItem = new QStandardItem();
            numCreditsItem->setData(cur->data.course->getNumCredits(), Qt::DisplayRole);
            items.append(numCreditsItem);
            QStandardItem *otherMarkItem = new QStandardItem();
            otherMarkItem->setData(cur->data.otherMark, Qt::DisplayRole);
            items.append(otherMarkItem);

            QStandardItem *midtermMarkItem = new QStandardItem();
            midtermMarkItem->setData(cur->data.midtermMark, Qt::DisplayRole);
            items.append(midtermMarkItem);

            QStandardItem *finalMarkItem = new QStandardItem();
            finalMarkItem->setData(cur->data.finalMark, Qt::DisplayRole);
            items.append(finalMarkItem);

            QStandardItem *totalMarkItem = new QStandardItem();
            totalMarkItem->setData(cur->data.totalMark, Qt::DisplayRole);
            items.append(totalMarkItem);

            model->appendRow(items);
            cur = cur->next;
        }
    }

    tableView = new QTableView();
    tableView->setEditTriggers(QTableView::NoEditTriggers);
    tableView->setModel(model);
    tableView->setColumnWidth(0, 130);
    tableView->setColumnWidth(1, 130);
    tableView->setColumnWidth(2, 150);
    tableView->setColumnWidth(3, 150);
    tableView->setColumnWidth(4, 120);
    tableView->setColumnWidth(5, 100);
    tableView->setColumnWidth(6, 150);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidget(tableView);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QHBoxLayout* line = new QHBoxLayout();
    double allGpa, allcredit;
    QLabel* label1 = new QLabel(QString::number(st->getGPAOfSemester(allGpa, allcredit, st->findSemesterInYear(year, semester))));
    QLabel* label2 = new QLabel(QString::number(st->getAllGPA()));
    QFormLayout* form = new QFormLayout();
    form->addRow("Điểm trung bình kì: " , label1);
    form->addRow("Điểm trung bình: ", label2);
    line->addStretch(1);
    line->addLayout(form);
    line->addStretch(1);


    // Thiết lập layout chính và thêm khu vực cuộn vào layout
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(scrollArea);
    mainLayout->addLayout(line);
    this->setLayout(mainLayout);
    this->setFixedSize(970, 500);
}

ScoreBoard::ScoreBoard(Course* course) {
    model = new QStandardItemModel(0, 6);
    model->setHorizontalHeaderLabels({"MSSV", "Họ và tên", "Điểm khác", "Điểm giữa kì", "Điểm cuối kì", "Điểm trung bình"});

    if (course->getListStudents()) {
        NodeStudent* student = course->getListStudents()->head;
        while (student) {
            QList<QStandardItem *> items;
            items.append(new QStandardItem(QString::fromStdString(student->data.getStudentID())));
            items.append(new QStandardItem(QString::fromStdString(student->data.getFirstName() + " " + student->data.getLastName())));

            QStandardItem *otherMarkItem = new QStandardItem();
            otherMarkItem->setData(student->data.getMarks()->otherMark, Qt::DisplayRole);
            items.append(otherMarkItem);

            QStandardItem *midtermMarkItem = new QStandardItem();
            midtermMarkItem->setData(student->data.getMarks()->midtermMark, Qt::DisplayRole);
            items.append(midtermMarkItem);

            QStandardItem *finalMarkItem = new QStandardItem();
            finalMarkItem->setData(student->data.getMarks()->finalMark, Qt::DisplayRole);
            items.append(finalMarkItem);

            QStandardItem *totalMarkItem = new QStandardItem();
            totalMarkItem->setData(student->data.getMarks()->totalMark, Qt::DisplayRole);
            items.append(totalMarkItem);

            model->appendRow(items);
            student = student->next;
        }
    }

    tableView = new QTableView();
    tableView->setEditTriggers(QTableView::NoEditTriggers);
    tableView->setModel(model);
    tableView->setColumnWidth(0, 130);
    tableView->setColumnWidth(1, 130);
    tableView->setColumnWidth(2, 150);
    tableView->setColumnWidth(3, 150);
    tableView->setColumnWidth(4, 120);
    tableView->setColumnWidth(5, 100);

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidget(tableView);
    scrollArea->setWidgetResizable(true);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Thiết lập layout chính và thêm khu vực cuộn vào layout
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(scrollArea);
    this->setWindowTitle(QString::fromStdString(course->getNameCourse() + "-" + course->getClassName()));
    this->setLayout(mainLayout);
    this->setFixedSize(940, 500);
    this->setWindowIcon(QIcon(":\\/\\icon\\Logo.png"));
    this->show();
}
