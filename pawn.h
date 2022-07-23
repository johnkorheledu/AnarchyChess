#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

class Pawn : public Piece
{
public:
    Pawn(QString color, int x, int y, int w, int h) : Piece(color, x, y, w, h) {};
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    QString getType() override;
    bool getMoved();
    void setMoved();

private:
    bool moved_ = false;
};

#endif // PAWN_H
