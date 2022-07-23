#include "knight.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <QColor>
#include <QGraphicsItem>
#include <QString>
#include <QSvgRenderer>


QRectF Knight::boundingRect() const
{
    return QRectF(x_, y_, width_, height_);
}

QPainterPath Knight::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, height_);
    return path;
}

void Knight::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    QRect tile = QRect(this->x_, this->y_, this->width_, this->height_);

    if(color_ == "white"){
       painter->drawImage(tile, QImage(":/assets/knight_w.svg"));
    }
    else{
        painter->drawImage(tile, QImage(":/assets/knight_b.svg"));
    }
}

QString Knight::getType() {
    return "knight";
}
