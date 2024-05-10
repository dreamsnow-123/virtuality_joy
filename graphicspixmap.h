#ifndef GRAPHICSPIXMAP_H
#define GRAPHICSPIXMAP_H

#include <QGraphicsObject>
#include <QObject>
#include <QPixmap>
#include <QtWidgets>
#include <QtMath>

class GraphicsPixmap : public QGraphicsObject {
  Q_OBJECT
  Q_PROPERTY(QPointF itemoffset READ itemoffset WRITE setItemOffset)
  Q_PROPERTY(QSize itemsize READ pixsize WRITE setPixmapSize)

public:
  GraphicsPixmap(qreal scale, qreal r=167);

public:
  QRectF boundingRect() const Q_DECL_OVERRIDE;
  void setItemOffset(QPointF ponit);
  QPointF itemoffset();
  QSize pixsize();
  void setPixmap(const QPixmap &pixmap);
  QPixmap pixmap();
  void setPixmapSize(QSize size);

protected:
  QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;

  void keyPressEvent(QKeyEvent *event) override;
  void keyReleaseEvent(QKeyEvent *event) override;

signals:
  void clicked();

private:
  void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
  void paint(QPainter *, const QStyleOptionGraphicsItem *,
             QWidget *) Q_DECL_OVERRIDE;

  void move(qreal dx, qreal dy);
  void move_up();
  void move_down();
  void move_right();
  void move_left();

private:
  QPixmap pix;
  QPointF offset;
  QSize pixSize;
  qreal _scale;

  const qreal _r;
};

#endif // GRAPHICSPIXMAP_H
