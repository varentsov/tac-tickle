#include "tactickle.h"
#include "ui_tactickle.h"


TacTickle::TacTickle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TacTickle)
{
    ui->setupUi(this);
    view = new QGraphicsView(this);
    view->move(30, 30);
    //view->resize(300, 300);
    scene = new QGraphicsScene(view);
    view->setScene(scene);
}

TacTickle::~TacTickle()
{
    delete ui;
}

void TacTickle::print_this() {
    QWidget *table = new QWidget(this);
    QPalette *black = new QPalette;
    QPalette *white = new QPalette;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            QWidget *cage = new QWidget(table);
            black->setColor(cage->backgroundRole(), Qt::black);
            white->setColor(cage->backgroundRole(), Qt::white);
            cage->resize(cage_size, cage_size);
            cage->setAutoFillBackground(true);

            if ((i+j) % 2 == 0) {
                cage->setPalette(*black);
                cage->move(cage_size*i, cage_size*j);
            }
            else {
                cage->setPalette(*white);
                cage->move(cage_size*i, cage_size*j);
            }
        }
    }

    table->move(start_x_pos, start_y_pos);
}

void TacTickle::print_table() {
    QBrush *white = new QBrush(Qt::white);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            if ((i+j) % 2 == 0) {
                Cell *cell = new Cell(cage_size*i, cage_size*j, cage_size, white);
                scene->addItem(cell);
            }
            else {
                Cell *cell = new Cell(cage_size*i, cage_size*j, cage_size, white);
                scene->addItem(cell);
            }
        }
    }
}

void TacTickle::paintEvent(QPaintEvent *) {
    QPainter paint(this);
    paint.setPen(Qt::white);
    QBrush *brush = new QBrush;
    brush->setStyle(Qt::SolidPattern);
    brush->setColor(Qt::blue);
    paint.setBrush(*brush);

    //paint.drawEllipse(10, 10, 30, 30);
}
