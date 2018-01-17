#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "NativeEventFilterZ.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setHook();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    unHook();
    delete ui;
}
