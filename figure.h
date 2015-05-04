#ifndef FIGURE_H
#define FIGURE_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsItemAnimation>
#include <QTimeLine>

class Figure :public QGraphicsItem
{
public:

    Figure(int x, int y, int radius, QBrush *brush, QString player);

    QRectF boundingRect() const;
    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    void moveDown();
    void moveUp();
    void moveLeft();
    void moveRight();
    QString player;

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    int x_pos;
    int y_pos;
    int radius;
    QBrush *brush;
};

#endif // FIGURE_H
