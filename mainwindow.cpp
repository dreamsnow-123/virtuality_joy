#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->graphicsView, &JoyGraphicsView::update_joy_signal, this, &MainWindow::update_joy_slot);

    return;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *event)
{
     setGeometry(ui->graphicsView->geometry());

     QMainWindow::showEvent(event);
}

void MainWindow::update_joy_slot(int x, int y)
{
    ui->label_x->setText(QString::number(x));
    ui->label_y->setText(QString::number(y));
    return;
}


