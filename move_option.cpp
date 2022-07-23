#include "move_option.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <QColor>
#include <QGraphicsItem>
#include <QString>


QRectF MoveOption::boundingRect() const
{
    return QRectF(x_, y_, width_, height_);
}

QPainterPath MoveOption::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, height_);
    return path;
}

void MoveOption::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(is_occupied_){
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(QPen(Qt::black,8));
        painter->setOpacity(0.2);
        painter->drawEllipse(this->x_ + 4, this->y_ + 4, 87, 87);
    }
    else{
        painter->setRenderHint(QPainter::Antialiasing);
        Q_UNUSED(widget);
        QRect tile = QRect(this->x_ + 28, this->y_ + 28, this->width_/2.5, this->height_/2.5);
        QPainterPath path;
        path.addEllipse(tile);
        painter->setOpacity(0.2);
        painter->fillPath (path, QBrush (QColor ("black")));
    }
}

int MoveOption::width() const
{
    return width_;
}

void MoveOption::setWidth(int newWidth)
{
    width_ = newWidth;
}

int MoveOption::height() const
{
    return height_;
}

void MoveOption::setHeight(int newHeight)
{
    height_ = newHeight;
}

int MoveOption::y() const
{
    return y_;
}

void MoveOption::setY(int newY)
{
    y_ = newY;
}

void MoveOption::setX(int newX)
{
    x_ = newX;
}

bool MoveOption::is_occupied() const
{
    return is_occupied_;
}

void MoveOption::setIs_occupied(bool newIs_occupied)
{
    is_occupied_ = newIs_occupied;
}


int MoveOption::x() const
{
    return x_;
}

MoveOption::MoveOption(int x, int y, int w, int h, bool o){
    this->x_ = x;
    this->y_ = y;
    this->width_ = w;
    this->height_ = h;
    this->is_occupied_ = o;
};

//Emit the signal that our MainWindow can grab for moving a piece
void MoveOption::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    emit(MoveOptionSelected(this));
}
