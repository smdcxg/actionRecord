#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QAbstractNativeEventFilter>
#include <windows.h>
#pragma comment(lib, "user32.lib")

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public QAbstractNativeEventFilter
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


    virtual bool nativeEventFilter(const QByteArray &eventType, void *message, long *) Q_DECL_OVERRIDE
    {
        qDebug() << eventType;
        if(eventType == "windows_generic_MSG" || eventType == "windows_dispatcher_MSG")
        {
            MSG* pMsg = reinterpret_cast<MSG*>(message);
            if(pMsg->message == WM_COPYDATA)
            {
                qDebug()<<"MainWindow windows system message WM_COPYDATA";
            }
        }
        return false;
    }


private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
