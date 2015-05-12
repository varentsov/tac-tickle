#include "tactickle.h"
#include "ui_tactickle.h"


TacTickle::TacTickle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TacTickle)
{
    ui->setupUi(this);
    view = ui->graphicsView;
    scene = new QGraphicsScene(view);
    view->setScene(scene);
    game = this;
    this->setFixedSize(this->width()+70, this->height()+100);
    printPureTable();
}

TacTickle::~TacTickle()
{
    delete ui;
}

TacTickle* TacTickle::game;

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

void TacTickle::gameOver(QString player)
{
    ui->graphicsView->setInteractive(false);
    QString str = QString("Gameis over and winner is %1").arg(player);
    QMessageBox msg;
    msg.addButton(QMessageBox::Ok);
    msg.setText(str);

    msg.exec();
}

void TacTickle::closeEvents()
{
    ui->graphicsView->setInteractive(false);
}

void TacTickle::openEvents()
{
    ui->graphicsView->setInteractive(true);
}

void TacTickle::resetGame()
{
    this->print_table();
    ui->graphicsView->setInteractive(true);
    Cell::whoMove = "Blue";
    aiLevel = ui->spinBox->value();
    cellsArray[0][0]->botMove();
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

void TacTickle::backMove()
{
    if (moves.isEmpty())
        return;
    else if (bot == "Blue" && moves.size() == 1)
        return;

    if (bot != "") {
        for (int i = 0; i < 2; i++) {
            if (moves.isEmpty())
                break;

            Movies *move = moves.pop();
            Cell::whoMove = TacTickle::cellsArray[move->to_x][move->to_y]->figure->player;
            TacTickle::cellsArray[move->to_x][move->to_y]->whereCanMove();
            TacTickle::cellsArray[move->to_x][move->to_y]->moveFigure(TacTickle::cellsArray[move->from_x][move->from_y], true);
            delete move;
        }
    }
    else {
        Movies *move = moves.pop();
        Cell::whoMove = TacTickle::cellsArray[move->to_x][move->to_y]->figure->player;
        TacTickle::cellsArray[move->to_x][move->to_y]->whereCanMove();
        TacTickle::cellsArray[move->to_x][move->to_y]->moveFigure(TacTickle::cellsArray[move->from_x][move->from_y], true);
        delete move;
        Cell::whoMove = (Cell::whoMove == "Red") ? "Blue" : "Red";
    }
    if (!ui->graphicsView->isInteractive())
        ui->graphicsView->setInteractive(true);
}

QString TacTickle::bot = "";

QStack<Movies*> TacTickle::moves;

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

void TacTickle::on_pushButton_clicked()
{
    backMove();
}

void TacTickle::concurrentBotMove()
{
    qDebug() << Cell::tempBotMove.from_x << Cell::tempBotMove.from_y << Cell::tempBotMove.to_x << Cell::tempBotMove.to_y;
    cellsArray[Cell::tempBotMove.from_x][Cell::tempBotMove.from_y]->whereCanMove();
    cellsArray[Cell::tempBotMove.from_x][Cell::tempBotMove.from_y]->moveFigure(cellsArray[Cell::tempBotMove.to_x][Cell::tempBotMove.to_y]);
}

