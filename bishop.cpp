#include "bishop.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <QColor>
#include <QGraphicsItem>
#include <QString>
#include <QSvgRenderer>


QRectF Bishop::boundingRect() const
{
    return QRectF(x_, y_, width_, height_);
}

QPainterPath Bishop::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, height_);
    return path;
}

void Bishop::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    QRect tile = QRect(this->x_, this->y_, this->width_, this->height_);

    if(color_ == "white"){
       painter->drawImage(tile, QImage(":/assets/bishop_w.svg"));
    }
    else{
        painter->drawImage(tile, QImage(":/assets/bishop_b.svg"));
    }
}

QString Bishop::getType() {
    return "bishop";
}
