#include "mainmenu.h"

#include "ui_mainmenu.h"

namespace s21 {
mainmenu::mainmenu(QWidget *parent) : QWidget(parent), ui(new Ui::mainmenu) {
  ui->setupUi(this);
  this->setWindowTitle("BrickGame by cedricho");
  gameView = new View(this);
  connect(ui->snake, SIGNAL(clicked()), this, SLOT(startSnakeGame()));
  connect(ui->tetris, SIGNAL(clicked()), this, SLOT(startTetrisGame()));
}

mainmenu::~mainmenu() {
  delete gameView;
  delete ui;
}

void mainmenu::startSnakeGame() {
  gameView->startSnakeGame();
  gameView->show();
  this->hide();
}

void mainmenu::startTetrisGame() {
  gameView->startTetrisGame();
  gameView->show();
  this->hide();
}
}  // namespace s21