#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QTimer>
#include <QWidget>

#include "../../brick_game/snake/controller.h"
#include "../../brick_game/snake/model.h"
#include "../../brick_game/tetris/s21_tetris.h"

namespace s21 {
class mainmenu;

enum GameType { SnakeGame, TetrisGame };

class View : public QMainWindow {
  Q_OBJECT
 public:
  explicit View(mainmenu *menu, QWidget *parent = nullptr);
  ~View();

  void startSnakeGame();
  void startTetrisGame();

 protected:
  void paintEvent(QPaintEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;
  void gameOver(QPainter &painter);
  void gameInfoPanel(QPainter &painter, int fieldWidth, int panelWidth,
                     int blockSize);
  void terminate();

 private slots:
  void updateGame();

 private:
  bool gameOverSnake;
  bool gameOverTetris;
  GameType gameType;
  QTimer *timer;
  GameInfo_t *gameInfo;

  controller *control;
  model *snakeModel;
  model::GameInfo_t SnakeGameInfo;
  model::Snake snake;

  GameInfo_t TetrisGameInfo;
  Block currentBlock;
  Block nextBlock;
  bool holdKey;

  mainmenu *menu;
};
}  // namespace s21
#endif  // VIEW_H
