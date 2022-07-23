#ifndef TILE_H
#define TILE_H

#include <QColor>
#include <QGraphicsItem>

class Tile : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    Tile(QColor color, int number, int x, int y, int w, int h);

    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    int width() const;
    void setWidth(int newWidth);

    int height() const;
    void setHeight(int newHeight);

    int y() const;
    void setY(int newY);

    int x() const;

    void setX(int newX);

    int number() const;
    void setNumber(int newNumber);

private:
    QColor color_;
    int number_;
    int x_;
    int y_;
    int width_;
    int height_;
};


#endif // TILE_H
