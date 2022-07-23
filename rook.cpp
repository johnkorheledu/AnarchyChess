#include "rook.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <QColor>
#include <QGraphicsItem>
#include <QString>
#include <QSvgRenderer>


QRectF Rook::boundingRect() const
{
    return QRectF(x_, y_, width_, height_);
}

QPainterPath Rook::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, height_);
    return path;
}

void Rook::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    QRect tile = QRect(this->x_, this->y_, this->width_, this->height_);

    if(color_ == "white"){
        painter->drawImage(tile, QImage(":/assets/rook_w.svg"));
    }
    else{
        painter->drawImage(tile, QImage(":/assets/rook_b.svg"));
    }
}


QString Rook::getType() {
    return "rook";
}
