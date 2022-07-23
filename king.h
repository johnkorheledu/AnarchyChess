#ifndef KING_H
#define KING_H


#include "piece.h"

class King : public Piece
{
public:
    King(QString color, int x, int y, int w, int h) : Piece(color, x, y, w, h) {};
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    QString getType() override;
};


#endif // KING_H
