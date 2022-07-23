#include "pawn.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <QColor>
#include <QGraphicsItem>
#include <QString>
#include <QSvgRenderer>

//Pawn::Pawn(){}

QRectF Pawn::boundingRect() const
{
    return QRectF(x_, y_, width_, height_);
}

QPainterPath Pawn::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, height_);
    return path;
}

void Pawn::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    QRect tile = QRect(this->x_, this->y_, this->width_, this->height_);

    if(color_ == "white"){
        painter->drawImage(tile, QImage(":/assets/pawn_w.svg"));
    }
    else{
        painter->drawImage(tile, QImage(":/assets/pawn_b.svg"));
    }
}

QString Pawn::getType() {
    return "pawn";
}

void Pawn::setMoved() {
    moved_ = true;
}

bool Pawn::getMoved() {
    return moved_;
}
