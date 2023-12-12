#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<QVector<int>>("QVector<int>");          //注册QVector容器否则可能无法进行信号槽传递
    MainWindow w;
    w.show();
    return a.exec();
}
