#ifndef BISHOP_H
#define BISHOP_H


#include "piece.h"

class Bishop : public Piece
{
public:
    Bishop(QString color, int x, int y, int w, int h) : Piece(color, x, y, w, h) {};
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    QString getType() override;
};

#endif // BISHOP_H
