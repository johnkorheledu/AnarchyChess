#ifndef PIECE_H
#define PIECE_H


#include <QColor>
#include <QGraphicsItem>

class Piece : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    Piece();
    Piece(QString color, int x, int y, int w, int h);
    static Piece *PieceFactory(QString type, QString color);

    virtual QString getType();
    QString getColor();

    int getX();
    int getY();

protected:
    int x_;
    int y_;
    int width_;
    int height_;
    QString color_;

    //Handle Click
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void PieceSelected(Piece *p);
};

#endif // PIECE_H
