#ifndef TACTICKLE_H
#define TACTICKLE_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "cell.h"

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
    static const int cage_size = 80;
    static const int start_x_pos = 30;
    static const int start_y_pos = 30;

private:
    Ui::TacTickle *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
};

#endif // TACTICKLE_H
