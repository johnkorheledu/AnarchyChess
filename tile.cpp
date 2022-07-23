#include "tile.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <QColor>
#include <QGraphicsItem>
#include <QString>


QRectF Tile::boundingRect() const
{
    return QRectF(x_, y_, width_, height_);
}

QPainterPath Tile::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, height_);
    return path;
}

void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    QRect tile = QRect(this->x_, this->y_, this->width_, this->height_);
    painter->fillRect(tile, QBrush(this->color_, Qt::SolidPattern));
    //    painter->drawText(this->x_ + 5,this->y_ + 55, QString(QString::fromStdString(std::to_string(this->number_))));
}

int Tile::width() const
{
    return width_;
}

void Tile::setWidth(int newWidth)
{
    width_ = newWidth;
}

int Tile::height() const
{
    return height_;
}

void Tile::setHeight(int newHeight)
{
    height_ = newHeight;
}

int Tile::y() const
{
    return y_;
}

void Tile::setY(int newY)
{
    y_ = newY;
}

void Tile::setX(int newX)
{
    x_ = newX;
}

int Tile::number() const
{
    return number_;
}

void Tile::setNumber(int newNumber)
{
    number_ = newNumber;
}
int Tile::x() const
{
    return x_;
}

Tile::Tile(QColor color, int number, int x, int y, int w, int h){
    this->color_ = color;
    this->number_ = number;
    this->x_ = x;
    this->y_ = y;
    this->width_ = w;
    this->height_ = h;
};
