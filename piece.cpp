#include "piece.h"
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>
#include <QColor>
#include <QGraphicsItem>
#include <QString>
#include "pawn.h"
#include "bishop.h"
#include "knight.h"
#include "queen.h"
#include "king.h"
#include "rook.h"

Piece::Piece(QString color, int x, int y, int w, int h){
    this->color_ = color;
    this->x_ = x;
    this->y_ = y;
    this->width_ = w;
    this->height_ = h;
}

Piece::Piece(){}

//Emit the signal that our MainWindow can grab for selecting a piece
void Piece::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
    emit(PieceSelected(this));
}

int Piece::getX() {
    return x_;
}

int Piece::getY() {
    return y_;
}

QString Piece::getType()  {
    return "";
}


QString Piece::getColor() {
    return color_;
}

Piece * Piece::PieceFactory(QString type, QString color){

    if (type == "pawn"){
        return new Pawn(color, 0, 0, 95, 95);
    }
    if (type == "bishop"){
        return new Bishop(color, 0, 0, 95, 95);
    }
    if (type == "knight"){
        return new Knight(color, 0, 0, 95, 95);
    }
    if (type == "queen"){
        return new Queen(color, 0, 0, 95, 95);
    }
    if (type == "rook"){
        return new Rook(color, 0, 0, 95, 95);
    }
    if (type == "king"){
        return new King(color, 0, 0, 95, 95);
    }
}


