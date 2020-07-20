#include "mainwindow.h"
#include <QApplication>
#include <QTime>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    qDebug() << QTime::currentTime().toString();
    return a.exec();
}
