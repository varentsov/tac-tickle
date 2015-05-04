#ifndef TACTICKLE_H
#define TACTICKLE_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QDebug>
#include "cell.h"
#include "figure.h"

namespace Ui {
class TacTickle;
}

class TacTickle : public QWidget
{
    Q_OBJECT

public:
    explicit TacTickle(QWidget *parent = 0);
    ~TacTickle();
    void print_table();
    void paintEvent(QPaintEvent *);
    void print_this();
    void printCellsAry();
    static const int cage_size = 80;
    static const int start_x_pos = 30;
    static const int start_y_pos = 30;
    static Cell* cellsArray[4][5];
    static Cell *activeCell;
    static void gameOver();


protected:


private:
    Ui::TacTickle *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
};

#endif // TACTICKLE_H
