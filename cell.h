#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>
#include <QPainter>
#include "figure.h"
#include <QVector>
#include "movies.h"
#include <QtConcurrent>
#include <QFutureWatcher>
#include <QFuture>

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
    void moveFigure(Cell *to_cell, bool backMove = false);
    void whereCanMove();
    static Movies tempBotMove;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void clearMovement();
    void moveFigureDown();
    void moveFigureUp();
    void moveFigureLeft();
    void moveFigureRight();
    bool isWinner(Cell *cell);
    void changeWhoMove();
    double miniMax(int recLevel, QString player, double alpha, double beta);
    double heuristicAnalysis();
    bool isGameOverBoard();
    QVector<QPoint> whereCanTempMove();
    void tempMoveFigure(Cell *to_cell);
    void addMove(Cell *from_cell, Cell *to_cell);
    QFutureWatcher<double> watcher;

private:
    int start_x_pos;
    int start_y_pos;
    int size;
    QBrush *color;
};

#endif // CELL_H
