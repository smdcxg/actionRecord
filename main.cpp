#include "mainwindow.h"
#include <QApplication>

#include "NativeEventFilterZ.h"
#include <QDebug>
#include <Windows.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    qDebug() << "MainWindow.winId : " << w.winId() << " , " << GetCurrentThreadId();

    setHook();
    return a.exec();
}
