#include "view.h"

#include <QKeyEvent>
#include <QPainter>

#include "../../brick_game/tetris/s21_tetris.h"
#include "mainmenu.h"
namespace s21 {
View::View(mainmenu *menu, QWidget *parent) : QMainWindow(parent), menu(menu) {
  setFixedSize(500, 600);
  timer = new QTimer(this);
  // holdKey = false;
  connect(timer, &QTimer::timeout, this, &View::updateGame);
}

View::~View() {
  delete timer;
  delete control;
  delete snakeModel;
  delete gameInfo;
  snakeModel->free_memory(reinterpret_cast<model::GameInfo_t *>(&SnakeGameInfo),
                          &snake);
  free_memory(&TetrisGameInfo);
}

void View::startSnakeGame() {
  gameOverSnake = false;
  gameType = SnakeGame;
  control = new controller();
  snakeModel = new model(control);
  snakeModel->initGame(&SnakeGameInfo, &snake);
  gameInfo = reinterpret_cast<GameInfo_t *>(&SnakeGameInfo);
  holdKey = true;
  timer->start(gameInfo->speed / 500);
}

void View::startTetrisGame() {
  gameOverTetris = false;
  gameType = TetrisGame;
  initGame(&TetrisGameInfo);
  newBlock(&currentBlock);
  newBlock(&nextBlock);
  gameInfo = &TetrisGameInfo;
  for (int i = 0; i < BLOCK_SIZE; i++) {
    for (int j = 0; j < BLOCK_SIZE; j++) {
      gameInfo->next[i][j] = nextBlock.block[i][j];
    }
  }
  holdKey = true;
  timer->start(gameInfo->speed / 525000);
}

void View::paintEvent(QPaintEvent *event) {
  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, true);
  int panelWidth = 200;
  int fieldWidth = width() - panelWidth;
  int blockSize = fieldWidth / WIDTH;
  painter.setBrush(Qt::gray);
  painter.drawRect(0, 0, fieldWidth, height());
  gameOverSnake = snakeModel->gameOverCheck(&snake);
  gameOverTetris = gameOverCheck(gameInfo);
  if ((gameOverSnake && gameType == SnakeGame) ||
      (gameOverTetris && gameType == TetrisGame) || snakeModel->winGame(snake))
    gameOver(painter);
  else {
    for (int i = 0; i < HEIGHT; ++i) {
      for (int j = 0; j < WIDTH; ++j) {
        if (gameInfo->field[i][j] == 1) {
          painter.fillRect(j * blockSize, i * blockSize - 1, blockSize - 1,
                           blockSize - 1, Qt::green);
        } else if (gameInfo->field[i][j] == 2) {
          painter.fillRect(j * blockSize, i * blockSize - 1, blockSize - 1,
                           blockSize - 1, Qt::red);
        }
      }
    }
    if (gameType == SnakeGame) {
      painter.setBrush(Qt::red);
      painter.fillRect(snake.xHead * blockSize, snake.yHead * blockSize - 1,
                       blockSize - 1, blockSize - 1, Qt::blue);
      for (int i = 1; i < snake.length; ++i) {
        painter.fillRect(snake.snake[i][0] * blockSize,
                         snake.snake[i][1] * blockSize - 1, blockSize - 1,
                         blockSize - 1, Qt::green);
      }
    } else if (gameType == TetrisGame) {
      painter.setBrush(Qt::red);
      for (int i = 0; i < BLOCK_SIZE; ++i) {
        for (int j = 0; j < BLOCK_SIZE; ++j) {
          if (currentBlock.block[i][j] == 1) {
            painter.fillRect((currentBlock.x + j) * blockSize,
                             (currentBlock.y + i) * blockSize, blockSize - 1,
                             blockSize - 1, Qt::red);
          }
        }
      }
    }
  }
  gameInfoPanel(painter, fieldWidth, panelWidth, blockSize);
}

void View::keyPressEvent(QKeyEvent *event) {
  controller::UserAction_t action = controller::None;
  UserAction_t t_action;
  switch (event->key()) {
    case Qt::Key_Left:
      action = controller::Left;
      t_action = Left;
      break;
    case Qt::Key_Right:
      action = controller::Right;
      t_action = Right;
      break;
    case Qt::Key_Up:
      action = controller::Up;
      t_action = Up;
      break;
    case Qt::Key_Down:
      action = controller::Down;
      t_action = Down;
      break;
    case Qt::Key_Escape:
      action = controller::Terminate;
      t_action = Terminate;
      terminate();
      break;
    case Qt::Key_Space:
      action = controller::Pause;
      t_action = Pause;
      break;
    default:
      break;
  }

  if (gameType == SnakeGame) {
    control->userInput(action, &holdKey);
  } else if (gameType == TetrisGame) {
    userInput(t_action, gameInfo, &currentBlock, holdKey);
  }
  update();
}

void View::updateGame() {
  if (gameType == SnakeGame) {
    if (!gameInfo->pause && !snakeModel->gameOverCheck(&snake)) {
      snakeModel->moveSnake(&snake);
      snakeModel->eatFood(reinterpret_cast<model::GameInfo_t *>(gameInfo),
                          &snake);
      timer->setInterval(gameInfo->speed / 500);
      if (holdKey) {
        timer->setInterval(gameInfo->speed / 1000);
        holdKey = false;
      }
    }
    gameInfo->pause = control->pause;
  } else if (gameType == TetrisGame) {
    if (!gameInfo->pause && !gameOverCheck(gameInfo)) {
      if (checkCollision(gameInfo, &currentBlock, currentBlock.y + 1,
                         currentBlock.x)) {
        mergeBlock(gameInfo, &currentBlock);
        clearLines(gameInfo);
        timer->setInterval(gameInfo->speed / 525000);
        currentBlock = nextBlock;
        newBlock(&nextBlock);
        for (int i = 0; i < BLOCK_SIZE; i++) {
          for (int j = 0; j < BLOCK_SIZE; j++) {
            gameInfo->next[i][j] = nextBlock.block[i][j];
          }
        }
      } else {
        currentBlock.y++;
      }
    }
  }
  update();
}

void View::gameOver(QPainter &painter) {
  timer->stop();
  painter.eraseRect(0, 0, 300, height());
  painter.setPen(Qt::red);
  painter.setFont(QFont("Arial", 24));
  if (snakeModel->winGame(snake))
    painter.drawText(90, height() / 2, "YOU WIN");
  else
    painter.drawText(90, height() / 2, "Game Over");
}

void View::gameInfoPanel(QPainter &painter, int fieldWidth, int panelWidth,
                         int blockSize) {
  painter.setBrush(Qt::green);
  painter.setPen(Qt::black);
  painter.setFont(QFont("Chalkboard", 20));
  painter.drawRect(fieldWidth, 0, panelWidth, 600);

  painter.translate(fieldWidth + 10, 20);
  painter.drawText(0, 40, "Score: " + QString::number(gameInfo->score));
  painter.drawText(0, 80,
                   "High Score: " + QString::number(gameInfo->high_score));
  painter.drawText(0, 120, "Level: " + QString::number(gameInfo->level));
  if (gameType == TetrisGame) painter.drawText(0, 170, "Next: ");
  if (gameInfo->pause) painter.drawText(50, 300, "PAUSE");
  if (gameType == TetrisGame) {
    painter.setBrush(Qt::red);
    for (int i = 0; i < BLOCK_SIZE; ++i) {
      for (int j = 0; j < BLOCK_SIZE; ++j) {
        if (gameInfo->next[i][j] == 1) {
          int nextBlockX = 60 + j * blockSize;
          int nextBlockY = 150 + i * blockSize;
          painter.fillRect(nextBlockX, nextBlockY, blockSize - 1, blockSize - 1,
                           Qt::red);
        }
      }
    }
  }
}

void View::terminate() {
  this->hide();
  menu->show();
}

}  // namespace s21
