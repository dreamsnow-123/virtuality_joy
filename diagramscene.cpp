/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "diagramscene.h"


#include <QGraphicsSceneMouseEvent>

DiagramScene::DiagramScene(qreal scale, QObject *parent)
    : QGraphicsScene(parent),_scale(scale)
{
    _bg_pic.load(":/resource/ui_joy_bg.png");
    _bg_pic = _bg_pic.scaled(_bg_pic.size()/_scale,Qt::KeepAspectRatio,Qt::FastTransformation);

    connect(&_timer, &QTimer::timeout, this, &DiagramScene::reset_btn);
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug()<<event->scenePos()<<endl;
//    QPointF mousePos(event->buttonDownScenePos(Qt::LeftButton).x(),
//                     event->buttonDownScenePos(Qt::LeftButton).y());
    QPointF mousePos = event->scenePos();
    const QList<QGraphicsItem *> itemList = items(mousePos);
    _current_item = itemList.isEmpty() ? nullptr : itemList.first();

//    if (movingItem != nullptr && event->button() == Qt::LeftButton)
//        qDebug()<< movingItem->pos()<<", "<< mousePos<<", "<<movingItem->mapFromScene(mousePos)<<endl;;

    clearSelection();
    QGraphicsScene::mousePressEvent(event);
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (_current_item != nullptr && event->button() == Qt::LeftButton) {
            _current_item->setPos(0,0);
    }

    QGraphicsScene::mouseReleaseEvent(event);
}


void DiagramScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if(views().count()==0)return;

    QGraphicsView* pView=views().first();
    QRect contentRect=pView->viewport()->contentsRect();
    QRectF sceneRect =pView->mapToScene(contentRect).boundingRect();

//    qDebug()<<"pView contentRect: "<<contentRect<<endl;;
//    qDebug()<<"pView->mapToScene(contentRect): "<<pView->mapToScene(contentRect)<<endl;;
//     qDebug()<<"sceneRect: "<<sceneRect<<endl;;

    painter->drawPixmap(sceneRect,_bg_pic,QRect());

    return;
}

void DiagramScene::reset_btn()
{
    _timer.stop();
    _current_item->setPos(0,0);
    return;
}

void DiagramScene::move(qreal dx, qreal dy)
{
    if(items().size()==0){
        return;
    }

//    qDebug()<<"oldPos: "<< items()[0]->scenePos() << " diff: "<<QPointF(dx, dy)<<endl;

//    _timer.stop();
    _current_item = items()[0];

    _current_item->setPos(_current_item->scenePos()+QPointF(dx, dy));
    return;
}

void DiagramScene::move_up()
{
    move(0, -1/_scale);
    return;
}

void DiagramScene::move_down()
{
    move(0, 1/_scale);
    return;
}

void DiagramScene::move_left()
{
    move(-1/_scale, 0);
    return;
}

void DiagramScene::move_right()
{
    move(1/_scale, 0);
    return;
}

void DiagramScene::keyPressEvent(QKeyEvent *event)
{

    if(_timer.isActive()){
        _timer.stop();
        _timer.start(700);
    }
    else{
        _timer.start(700);
    }
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


    QGraphicsScene::keyPressEvent(event);
    return;

}

void DiagramScene::keyReleaseEvent(QKeyEvent *event)
{
    if(items().size()==0){
        QGraphicsScene::keyReleaseEvent(event);
        return;
    }



    QGraphicsScene::keyReleaseEvent(event);
    return;
}



QSize DiagramScene::pixsize() { return _bg_pic.size(); }

