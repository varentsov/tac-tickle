#include "figure.h"

Figure::Figure(int x, int y, int radius, QBrush *brush, QString player)
{
    this->x_pos = x;
    this->y_pos = y;
    this->radius = radius;
    this->brush = brush;
    setZValue(1);
    this->player = player;
}

QRectF Figure::boundingRect() const
{
    return QRectF(x_pos, y_pos, radius, radius);
}

void Figure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::black);
    painter->setPen(pen);
    painter->setBrush(*brush);

    painter->drawEllipse(x_pos, y_pos, radius, radius);
}

void Figure::moveDown() {
    moveBy(0, 80);
}

void Figure::moveUp() {
    moveBy(0, -80);
}

void Figure::moveLeft() {
    moveBy(-80, 0);
}

void Figure::moveRight() {
    moveBy(80, 0);
}

void Figure::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event);
}
