#ifndef MOVEOPTION_H
#define MOVEOPTION_H

#include <QColor>
#include <QGraphicsItem>

class MoveOption : public QObject, public QGraphicsItem {
    Q_OBJECT

public:
    MoveOption(int x, int y, int w, int h, bool o);

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

    bool is_occupied() const;
    void setIs_occupied(bool newIs_occupied);

private:

    int x_;
    int y_;
    int width_;
    int height_;
    bool is_occupied_;

protected:
    //Handle Click
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

signals:
    void MoveOptionSelected(MoveOption *mo);
};


#endif // MOVEOPTION_H
