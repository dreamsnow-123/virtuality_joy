#ifndef JOYGRAPHICSVIEW_H
#define JOYGRAPHICSVIEW_H

#include <QtWidgets>

#include "diagramscene.h"
#include "graphicspixmap.h"


class JoyGraphicsView : public QGraphicsView
{
Q_OBJECT
public:
    JoyGraphicsView(QWidget *parent = nullptr);

    void set_x_limit(int min, int max);
    void set_y_limit(int min, int max);
protected:
    void showEvent(QShowEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;


private:
    DiagramScene *_scene;
    GraphicsPixmap *_joy_btn;

    qreal _scale;

        int _x_max = 127;
    int _x_min = -128;

    //向下zheng
    int _y_min = -127;
    int _y_max = 128;

    QTimer _timer;

    int _r;

signals:
    void update_joy_signal(int x, int y);

private slots:
    void update_joy_slot();



};

#endif // JOYGRAPHICSVIEW_H
