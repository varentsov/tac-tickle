#include "tactickle.h"
#include "ui_tactickle.h"


TacTickle::TacTickle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TacTickle)
{
    ui->setupUi(this);
    //view = new QGraphicsView(this);
    //view->move(30, 30);
    //view->resize(300, 300);
    view = ui->graphicsView;
    scene = new QGraphicsScene(view);
    view->setScene(scene);

    printPureTable();
}

TacTickle::~TacTickle()
{
    delete ui;
}

Cell* TacTickle::activeCell;

Cell* TacTickle::cellsArray[4][5];

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
    QBrush *red = new QBrush(Qt::red);
    QBrush *blue = new QBrush(Qt::blue);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            if ((i+j) % 2 == 0) {
                Cell *cell = new Cell(cage_size*i, cage_size*j, cage_size, white);
                cell->x_cord = i;
                cell->y_cord = j;
                cellsArray[i][j] = cell;
                scene->addItem(cell);
                if (j == 0) {
                    Figure *fig = new Figure(cage_size*i + 5, cage_size*j + 5, cage_size - 10, red, "Red");
                    scene->addItem(fig);
                    cell->figure = fig;
                }
                else if (j == 4) {
                    Figure *fig = new Figure(cage_size*i + 5, cage_size*j + 5, cage_size - 10, blue, "Blue");
                    scene->addItem(fig);
                    cell->figure = fig;
                }
            }
            else {
                Cell *cell = new Cell(cage_size*i, cage_size*j, cage_size, white);
                cell->x_cord = i;
                cell->y_cord = j;
                cellsArray[i][j] = cell;
                scene->addItem(cell);
                if (j == 0) {
                    Figure *fig = new Figure(cage_size*i + 5, cage_size*j + 5, cage_size - 10, blue, "Blue");
                    scene->addItem(fig);
                    cell->figure = fig;
                }
                else if (j == 4) {
                    Figure *fig = new Figure(cage_size*i + 5, cage_size*j + 5, cage_size - 10, red, "Red");
                    scene->addItem(fig);
                    cell->figure = fig;
                }
            }
        }
    }
}

void TacTickle::printCellsAry() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            qDebug() << cellsArray[i][j];
        }
    }
}

void TacTickle::gameOver()
{
    qDebug() << "GAME OVER!";
}

void TacTickle::resetGame()
{
    this->print_table();
    Cell::whoMove = "Blue";
    Cell::botMove();
}

void TacTickle::printPureTable()
{
    QBrush *white = new QBrush(Qt::white);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            if ((i+j) % 2 == 0) {
                Cell *cell = new Cell(cage_size*i, cage_size*j, cage_size, white);
                cell->x_cord = i;
                cell->y_cord = j;
                scene->addItem(cell);
                cellsArray[i][j] = cell;
            }
            else {
                Cell *cell = new Cell(cage_size*i, cage_size*j, cage_size, white);
                cell->x_cord = i;
                cell->y_cord = j;
                scene->addItem(cell);
                cellsArray[i][j] = cell;
            }
        }
    }
}

void TacTickle::paintEvent(QPaintEvent *) {
    /*QPainter paint(this);
    paint.setPen(Qt::white);
    QBrush *brush = new QBrush;
    brush->setStyle(Qt::SolidPattern);
    brush->setColor(Qt::blue);
    paint.setBrush(*brush);

    //paint.drawEllipse(10, 10, 30, 30);
    */
}

QString TacTickle::bot;

void TacTickle::on_pushButton_2_clicked()
{
    scene->clear();
    if (ui->radioButton_2->isChecked()) {
        bot = "Blue";
    }
    else if (ui->radioButton_3->isChecked()) {
        bot = "Red";
    }
    else {
        bot = "";
    }
    resetGame();
}
