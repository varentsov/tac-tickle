#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>
#include <QPainter>

class Cell :public QGraphicsItem
{
public:

    Cell(int start_x_pos, int start_y_pos, int size, QBrush *color);

    QRectF boundingRect() const;

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

    bool pressed;
protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
private:
    int start_x_pos;
    int start_y_pos;
    int size;
    QBrush *color;
};

#endif // CELL_H
