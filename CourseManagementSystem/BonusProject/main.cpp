#include "view.h"
#include <QApplication>
#include <QFileDialog>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    View();
    return app.exec();
}

