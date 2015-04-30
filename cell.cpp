#include "cell.h"
#include <QDebug>


Cell::Cell(int start_x_pos, int start_y_pos, int size, QBrush *color)
{
    this->start_x_pos = start_x_pos;
    this->start_y_pos = start_y_pos;
    this->size = size;
    this->color = color;
    pressed = false;
}

QRectF Cell::boundingRect() const
{
    return QRectF(start_x_pos, start_y_pos, size, size);
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::black, 2);
    painter->setPen(pen);
    if (!pressed) {
        painter->setBrush(*color);
        painter->drawRect(start_x_pos, start_y_pos, size, size);
    }
    else {
        QBrush brush(Qt::yellow);
        painter->setBrush(brush);
        painter->drawRect(start_x_pos, start_y_pos, size, size);
    }

}

void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}

void Cell::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    pressed = true;
    update();
    QGraphicsItem::mousePressEvent(event);
}


void Cell::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void Cell::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    pressed = false;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
