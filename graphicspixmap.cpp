#include "graphicspixmap.h"

#include <QCursor>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>

GraphicsPixmap::GraphicsPixmap(qreal scale, qreal r) : QGraphicsObject(),_scale(scale), _r(r) {
  setCacheMode(DeviceCoordinateCache);



}

void GraphicsPixmap::mousePressEvent(QGraphicsSceneMouseEvent *event) {
  QGraphicsObject::mousePressEvent(event);
  if (event->button() == Qt::LeftButton) {
    emit clicked();
  }
}

void GraphicsPixmap::setItemOffset(QPointF ponit) {
  prepareGeometryChange();
  offset = ponit;
  update();
}

QPointF GraphicsPixmap::itemoffset() { return offset; }

QPixmap GraphicsPixmap::pixmap() { return pix; }

void GraphicsPixmap::setPixmap(const QPixmap &pixmap) {
  pixSize = pixmap.size()/_scale;
  pix = pixmap;
}

void GraphicsPixmap::setPixmapSize(QSize size) { pixSize = size; }

QSize GraphicsPixmap::pixsize() { return pixSize; }

QRectF GraphicsPixmap::boundingRect() const {
  return QRectF(offset, pix.size() / pix.devicePixelRatio());
}

void GraphicsPixmap::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
                           QWidget *) {

  painter->setRenderHint(QPainter::SmoothPixmapTransform, true);
  painter->drawPixmap(offset, pix.scaled(pixSize, Qt::KeepAspectRatio,
                                         Qt::SmoothTransformation));
}



void GraphicsPixmap::move(qreal dx, qreal dy)
{
    setPos(scenePos()+QPointF(dx, dy));
    return;
}

void GraphicsPixmap::move_up()
{
    move(0, -1/_scale);
    return;
}

void GraphicsPixmap::move_down()
{
    move(0, 1/_scale);
    return;
}

void GraphicsPixmap::move_left()
{
    move(-1/_scale, 0);
    return;
}

void GraphicsPixmap::move_right()
{
    move(1/_scale, 0);
    return;
}

QVariant GraphicsPixmap::itemChange(GraphicsItemChange change, const QVariant &value)
{
    bool item_change_cond = (change == ItemPositionChange || change == ItemPositionHasChanged) && scene();
    if(!item_change_cond){
        return QGraphicsObject::itemChange(change, value);
    }

    QPointF newPos = value.toPointF();
    QLineF tmp(newPos, QPointF(0,0));
    qreal dist = tmp.length();
//    qDebug()<<"newPos: "<<newPos<<", newPos.dist(): " << dist<<", _r: "<<_r <<endl;
    if(dist> _r){
        qreal angle = qAtan2(newPos.y(),newPos.x());
        newPos.setX(_r*qCos(angle));
        newPos.setY(_r*qSin(angle));
//        qDebug()<<"modify newPos: "<<_r*qCos(angle)<<", "<<_r*qSin(angle)<<endl;
        return newPos;
    }

    return QGraphicsObject::itemChange(change, value);
}


void GraphicsPixmap::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Up){
        move_up();
    }
    else if(event->key()==Qt::Key_Down){
        move_down();
    }
    else if(event->key()==Qt::Key_Right){
        move_right();
    }
    else if(event->key()==Qt::Key_Left){
        move_left();
    }

    qDebug()<<"keyPressEvent "<<event->key()<<endl;

    QGraphicsObject::keyPressEvent(event);
    return;

}

void GraphicsPixmap::keyReleaseEvent(QKeyEvent *event)
{
    QGraphicsObject::keyReleaseEvent(event);
    return;
}
