#ifndef TACTICKLE_H
#define TACTICKLE_H

#include <QWidget>
#include <QPainter>

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
    static const int cage_size = 80;
    static const int start_x_pos = 30;
    static const int start_y_pos = 30;

private:
    Ui::TacTickle *ui;

};

#endif // TACTICKLE_H
