#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <qmath.h>

#include "diagramscene.h"
#include "graphicspixmap.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
    void showEvent(QShowEvent *event) override;


private:
    Ui::MainWindow *ui;

private slots:
    void update_joy_slot(int x, int y);
};
#endif // MAINWINDOW_H
