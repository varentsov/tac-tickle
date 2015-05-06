#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>
#include <QPainter>
#include "figure.h"
#include <QVector>

class Cell :public QGraphicsItem
{
public:

    Cell(int start_x_pos, int start_y_pos, int size, QBrush *color);

    QRectF boundingRect() const;

    void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);

    bool pressed;
    bool canMoveHere;
    Figure *figure;
    int x_cord;
    int y_cord;
    void isGameOver(Cell *cell);
    static QString whoMove;
    void botMove();

protected:

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void whereCanMove();
    void clearMovement();
    void moveFigure(Cell *to_cell);
    void moveFigureDown();
    void moveFigureUp();
    void moveFigureLeft();
    void moveFigureRight();
    bool isWinner(Cell *cell);
    void changeWhoMove();
    double miniMax(int recLevel, QString player);
    double heuristicAnalysis();
    QVector<QPoint> whereCanTempMove();
    void tempMoveFigure(Cell *to_cell);

private:
    int start_x_pos;
    int start_y_pos;
    int size;
    QBrush *color;
};

#endif // CELL_H
