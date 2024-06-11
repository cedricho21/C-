#ifndef VIEW_H
#define VIEW_H

#include <locale.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

#include <cstdlib>
#include <cstring>

#include "../../brick_game/snake/controller.h"
#include "../../brick_game/snake/model.h"
#include "../../brick_game/tetris/s21_tetris.h"

namespace s21 {

class View {
  enum GameType { SnakeGame, TetrisGame, None };
  UserAction_t action = Start;

 public:
  View();
  ~View();
  void initScreen();
  void closeScreen();
  void preview();
  void startSnakeGame();
  void startTetrisGame();
  void updateGame();
  void handleInput(int key);
  void drawGame();
  void drawFrame();
  void gameOver();
  void terminate();
  void setTerminalSize(int rows, int cols);
  void decor_s();
  void decor_t();
  GameInfo_t *getGameInfo() const;
  bool checkGameOver();

 private:
  GameType gameType;
  GameInfo_t *gameInfo;
  GameInfo_t TetrisGameInfo;
  model::GameInfo_t SnakeGameInfo;
  model::Snake snake;
  Block currentBlock, nextBlock;
  bool holdKey;
  controller *control;
  model *snakeModel;
};
}  // namespace s21
#endif  // VIEW_H
