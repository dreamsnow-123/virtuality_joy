#include "joygraphicsview.h"

JoyGraphicsView::JoyGraphicsView(QWidget *parent):QGraphicsView(parent),_scale(2),_r(167/_scale)
{
    _scene = new DiagramScene(_scale, this);
    _scene->setBackgroundBrush(QColor(0, 0, 18));

    QPixmap joy_btn(":/resource/ui_joy_btn.png");
    _joy_btn = new GraphicsPixmap(_scale, _r);
    _joy_btn->setPixmap(joy_btn);
    _joy_btn->setItemOffset(QPointF(_scene->pixsize().width()/2.0-34/_scale,_scene->pixsize().height()/2.0-46/_scale));
    _joy_btn->setFlags(QGraphicsItem::ItemIsMovable|
                    QGraphicsItem::ItemSendsGeometryChanges|
                       QGraphicsItem::ItemIsFocusable);

    setScene(_scene);
    _scene->setBackgroundBrush(QColor(0, 0, 18));
    _scene->addItem(_joy_btn);


    connect(&_timer, &QTimer::timeout, this, &JoyGraphicsView::update_joy_slot);

//    qDebug() << "_joy_btn->scenePos(): "<<_joy_btn <<endl;


    return;
}

void JoyGraphicsView::set_x_limit(int min, int max)
{
    _x_min = min;
    _x_max = max;
    return;
}

void JoyGraphicsView::set_y_limit(int min, int max)
{
    _y_min = -max;
    _y_max = -min;
    return;
}

void JoyGraphicsView::showEvent(QShowEvent *event)
{
    setGeometry(0,0,_scene->pixsize().width(),_scene->pixsize().height());
    setMinimumSize(_scene->pixsize()/_scale);

    QRectF rect = QRectF(QPointF(0, 0), _scene->pixsize());
    _scene->setSceneRect(rect);

    QGraphicsView::showEvent(event);

    _timer.start(10);


    return;
}

void JoyGraphicsView::resizeEvent(QResizeEvent *event) {
  QGraphicsView::resizeEvent(event);
  fitInView(sceneRect(), Qt::KeepAspectRatio);
  return;
}

void JoyGraphicsView::update_joy_slot()
{
//    qDebug() << "_joy_btn->pos(): " <<_joy_btn->pos()<<endl;
//    qDebug() << "_joy_btn->scenePos(): " <<_joy_btn->scenePos()<<endl;
    qreal x = (_joy_btn->scenePos().x()/_r + 1)/2;
    qreal y = (_joy_btn->scenePos().y()/_r + 1)/2;

    qreal x_output_tmp = (_x_max-_x_min) * x+_x_min;
    qreal y_output_tmp = (_y_max-_y_min) * y+_y_min;

    int x_output = x_output_tmp;
    int y_output = y_output_tmp;
    x_output = qMax(_x_min,qMin(x_output,_x_max));
    y_output = qMax(_y_min,qMin(y_output,_y_max));

    emit update_joy_signal(x_output, -y_output);
    return;
}



