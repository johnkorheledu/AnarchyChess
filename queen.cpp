#include "queen.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <QColor>
#include <QGraphicsItem>
#include <QString>
#include <QSvgRenderer>


QRectF Queen::boundingRect() const
{
    return QRectF(x_, y_, width_, height_);
}

QPainterPath Queen::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, height_);
    return path;
}

void Queen::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    QRect tile = QRect(this->x_, this->y_, this->width_, this->height_);

    if(color_ == "white"){
        painter->drawImage(tile, QImage(":/assets/queen_w.svg"));
    }
    else{
        painter->drawImage(tile, QImage(":/assets/queen_b.svg"));
    }
}

QString Queen::getType() {
    return "queen";
}
