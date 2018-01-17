#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    qDebug() << "MainWindow.winId : " << w.winId() << " , " << GetCurrentThreadId();

    return a.exec();
}
