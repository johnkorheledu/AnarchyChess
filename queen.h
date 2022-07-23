#ifndef QUEEN_H
#define QUEEN_H


#include "piece.h"

class Queen : public Piece
{
public:
    Queen(QString color, int x, int y, int w, int h) : Piece(color, x, y, w, h) {};
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    QString getType() override;
};

#endif // QUEEN_H
