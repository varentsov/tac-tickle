#ifndef TACTICKLE_H
#define TACTICKLE_H

#include <QWidget>
#include <QPainter>
#include <QGraphicsView>
#include <QGraphicsItem>
#include "cell.h"
#include "figure.h"
#include "movies.h"
#include <QStack>
#include <QMessageBox>


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
    void print_this();
    static const int cage_size = 80;
    static const int start_x_pos = 30;
    static const int start_y_pos = 30;
    static Cell* cellsArray[4][5];
    static Cell *activeCell;
    void gameOver(QString player);
    static QString bot;
    static TacTickle *game;
    int aiLevel;
    static QStack<Movies*> moves;
    void closeEvents();
    void openEvents();

protected:
    void resetGame();
    void printPureTable();
    void backMove();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::TacTickle *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
};

#endif // TACTICKLE_H
