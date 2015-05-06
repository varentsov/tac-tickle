#include "cell.h"
#include <QDebug>
#include "tactickle.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define MAX_REC_LEVEL 1


Cell::Cell(int start_x_pos, int start_y_pos, int size, QBrush *color)
{
    this->start_x_pos = start_x_pos;
    this->start_y_pos = start_y_pos;
    this->size = size;
    this->color = color;
    pressed = false;
    figure = NULL;
    canMoveHere = false;
}

QString Cell::whoMove = "Blue";

QRectF Cell::boundingRect() const
{
    return QRectF(start_x_pos, start_y_pos, size, size);
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen(Qt::black, 2);
    painter->setPen(pen);
    if (!canMoveHere) {
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
    if (this->canMoveHere) {
        moveFigure(this);
    }
    else {
        clearMovement();
        whereCanMove();
    }
    //qDebug() << this->figure->player;
    QGraphicsItem::mousePressEvent(event);
}

void Cell::whereCanMove() {
    if (this->figure && this->figure->player == whoMove) {
        TacTickle::activeCell = this;
        for (int i = -1; i < 2; i = i + 1) {
            for (int j = -1; j < 2; j = j + 1) {
                if ((abs(i) == abs(j)) || (this->x_cord + i < 0) || (this->x_cord + i >= 4) || (this->y_cord + j < 0) || (this->y_cord + j >= 5))
                    continue;
                else {
                    Cell *cell = TacTickle::cellsArray[this->x_cord + i][this->y_cord + j];
                    if (!cell->figure) {
                        cell->canMoveHere = true;
                        cell->update();
                    }
                }
            }
        }
    }
}

void Cell::clearMovement() {
    TacTickle::activeCell = NULL;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            Cell *cell = TacTickle::cellsArray[i][j];
            if (cell->canMoveHere) {
                cell->canMoveHere = false;
                cell->update();
            }
        }
    }
}

void Cell::moveFigure(Cell *to_cell) {
    if (to_cell->canMoveHere) {
        Cell *cell = TacTickle::activeCell;
        if (to_cell->x_cord < cell->x_cord)
            moveFigureLeft();
        else if (to_cell->x_cord > cell->x_cord)
            moveFigureRight();
        else if (to_cell->y_cord > cell->y_cord)
            moveFigureDown();
        else
            moveFigureUp();
    }
    clearMovement();
    isGameOver(to_cell);
    changeWhoMove();
}

void Cell::moveFigureDown()
{
    Cell *cell = TacTickle::activeCell;
    Figure *fig = cell->figure;
    fig->moveDown();
    Cell *to_cell = TacTickle::cellsArray[cell->x_cord][cell->y_cord + 1];
    cell->figure = NULL;
    to_cell->figure = fig;
}

void Cell::moveFigureUp()
{
    Cell *cell = TacTickle::activeCell;
    Figure *fig = cell->figure;
    fig->moveUp();
    Cell *to_cell = TacTickle::cellsArray[cell->x_cord][cell->y_cord - 1];
    cell->figure = NULL;
    to_cell->figure = fig;
}

void Cell::moveFigureLeft()
{
    Cell *cell = TacTickle::activeCell;
    Figure *fig = cell->figure;
    fig->moveLeft();
    Cell *to_cell = TacTickle::cellsArray[cell->x_cord - 1][cell->y_cord];
    cell->figure = NULL;
    to_cell->figure = fig;
}

void Cell::moveFigureRight()
{
    Cell *cell = TacTickle::activeCell;
    Figure *fig = cell->figure;
    fig->moveRight();
    Cell *to_cell = TacTickle::cellsArray[cell->x_cord + 1][cell->y_cord];
    cell->figure = NULL;
    to_cell->figure = fig;
}

void Cell::isGameOver(Cell *cell)
{
    if (isWinner(cell)) {
        qDebug() << "Winner is " << cell->figure->player;
        TacTickle::gameOver();
    }
}

bool Cell::isWinner(Cell *cell)
{
    QString name = cell->figure->player;

    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
            if ((cell->x_cord + i < 0) || (cell->x_cord + i >= 4) || (cell->y_cord + j < 0) || (cell->y_cord + j >= 5) || ((i == j) && (i == 0)))
                continue;
            else {
                Cell *next_cell = TacTickle::cellsArray[cell->x_cord + i][cell->y_cord + j];
                if (next_cell->figure && next_cell->figure->player == name) {
                    if ((next_cell->x_cord + i < 0) || (next_cell->x_cord + i >= 4) || (next_cell->y_cord + j < 0) || (next_cell->y_cord + j >= 5)) {
                    }
                    else {
                        Cell *next_next_cell = TacTickle::cellsArray[next_cell->x_cord + i][next_cell->y_cord + j];
                        if (next_next_cell->figure && next_next_cell->figure->player == name)
                            return true;
                    }
                    if ((cell->x_cord - i < 0) || (cell->x_cord - i >= 4) || (cell->y_cord - j < 0) || (cell->y_cord - j >= 5)) {
                    }
                    else {
                        Cell *next_next_cell = TacTickle::cellsArray[cell->x_cord - i][cell->y_cord - j];
                        if (next_next_cell->figure && next_next_cell->figure->player == name)
                            return true;
                    }
                }
            }
        }
    }
    return false;
}

void Cell::changeWhoMove()
{
    if (whoMove == "Blue")
        whoMove = "Red";
    else
        whoMove = "Blue";

    botMove();
}

double Cell::heuristicAnalysis()
{

    QVector<QPoint> points;
    double minAreaForWin = 1000;
    double tempArea, a, b, c, per;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            if (TacTickle::cellsArray[i][j]->figure && TacTickle::cellsArray[i][j]->figure->player == TacTickle::bot) {
                points.append(QPoint(i, j));
            }
        }
    }

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j)
                continue;
            for (int k = 0; k < 4; k++) {
                if (k == j || k == i)
                    continue;
                a = sqrt(pow(points[i].x() - points[j].x(), 2) + pow(points[i].y() - points[j].y(), 2));
                b = sqrt(pow(points[i].x() - points[k].x(), 2) + pow(points[i].y() - points[k].y(), 2));
                c = sqrt(pow(points[k].x() - points[j].x(), 2) + pow(points[k].y() - points[j].y(), 2));
                per = (a + b + c)/2;
                tempArea = sqrt(per*(per - a)*(per - b)*(per - c));
                if (tempArea < minAreaForWin)
                    minAreaForWin = tempArea;
            }
        }
    }

    //return minAreaForWin;

    return rand()%100;
}

QVector<QPoint> Cell::whereCanTempMove()
{
    QVector<QPoint> points;

    TacTickle::activeCell = this;
    for (int i = -1; i < 2; i = i + 1) {
        for (int j = -1; j < 2; j = j + 1) {
            if ((abs(i) == abs(j)) || (this->x_cord + i < 0) || (this->x_cord + i >= 4) || (this->y_cord + j < 0) || (this->y_cord + j >= 5))
                continue;
            else {
                Cell *cell = TacTickle::cellsArray[this->x_cord + i][this->y_cord + j];
                if (!cell->figure) {
                    points.append(QPoint(cell->x_cord, cell->y_cord));
                }
            }
        }
    }

    return points;
}

void Cell::tempMoveFigure(Cell *to_cell)
{

    Cell *cell = TacTickle::activeCell;
    if (to_cell->x_cord < cell->x_cord)
        moveFigureLeft();
    else if (to_cell->x_cord > cell->x_cord)
        moveFigureRight();
    else if (to_cell->y_cord > cell->y_cord)
        moveFigureDown();
    else
        moveFigureUp();

    //changeWhoMove();
}

void Cell::botMove()
{
    if (TacTickle::bot == whoMove) {
        miniMax(0, TacTickle::bot);
    }
}


double Cell::miniMax(int recLevel, QString player)
{
    if (recLevel >= MAX_REC_LEVEL) {
        return heuristicAnalysis();
    }

    int from_x, from_y, to_x, to_y;

    double score = 1000, temp;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            if (TacTickle::cellsArray[i][j]->figure && TacTickle::cellsArray[i][j]->figure->player == player) {
                QVector<QPoint> points = TacTickle::cellsArray[i][j]->whereCanTempMove();
                //TacTickle::cellsArray[i][j]->moveFigure(TacTickle::cellsArray[i][j-1]);
                for (int p = 0; p < points.size(); p++) {
                    TacTickle::activeCell = TacTickle::cellsArray[i][j];
                    TacTickle::cellsArray[i][j]->tempMoveFigure(TacTickle::cellsArray[points[p].x()][points[p].y()]);

                    temp = miniMax(recLevel + 1, (player == "Red") ? "Blue" : "Red");

                    if (temp < score) {
                        score = temp;
                        from_x = i;
                        from_y = j;
                        to_x = points[p].x();
                        to_y = points[p].y();
                    }

                    qDebug() << temp;

                    TacTickle::activeCell = TacTickle::cellsArray[points[p].x()][points[p].y()];
                    TacTickle::cellsArray[points[p].x()][points[p].y()]->tempMoveFigure(TacTickle::cellsArray[i][j]);
                }
            }
        }
    }

    if (recLevel == 0) {
        TacTickle::cellsArray[from_x][from_y]->whereCanMove();
        TacTickle::cellsArray[from_x][from_y]->moveFigure(TacTickle::cellsArray[to_x][to_y]);
    }

    return score;
}


