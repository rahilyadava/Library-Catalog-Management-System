#include <QApplication>
#include <QDebug>
#include "BTree.h"
#include "mainwindow.h"
#include <QTextStream>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
