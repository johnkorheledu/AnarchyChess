#ifndef KNIGHT_H
#define KNIGHT_H


#include "piece.h"

class Knight : public Piece
{
public:
    Knight(QString color, int x, int y, int w, int h) : Piece(color, x, y, w, h) {};
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    QString getType() override;
};

#endif // KNIGHT_H
