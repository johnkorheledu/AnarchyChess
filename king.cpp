#include "king.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <QColor>
#include <QGraphicsItem>
#include <QString>
#include <QSvgRenderer>


QRectF King::boundingRect() const
{
    return QRectF(x_, y_, width_, height_);
}

QPainterPath King::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, height_);
    return path;
}

void King::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    QRect tile = QRect(this->x_, this->y_, this->width_, this->height_);

    if(color_ == "white"){
       painter->drawImage(tile, QImage(":/assets/king_b.svg"));
    }
    else{
        painter->drawImage(tile, QImage(":/assets/king_w.svg"));
    }
}

QString King::getType() {
    return "king";
}
