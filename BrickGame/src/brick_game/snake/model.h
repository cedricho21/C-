#ifndef MODEL_H
#define MODEL_H

#include <fstream>
#include <iostream>

#include "controller.h"

#define WIDTH 10
#define HEIGHT 20
namespace s21 {
class model {
 public:
  model(controller *ctrl);
  ~model();

  typedef struct {
    int **field;
    int **next;
    int score;
    int high_score;
    int level;
    int speed;
    int pause;
  } GameInfo_t;

  typedef struct {
    int **snake;
    int xHead;
    int yHead;
    int length;
  } Snake;

  void initGame(GameInfo_t *game, Snake *snake);
  void moveSnake(Snake *snake);
  void eatFood(GameInfo_t *game, Snake *snake);
  int gameOverCheck(Snake *snake);
  void writeHighScore(int high_score);
  int readHighScore();
  void newFood(GameInfo_t *game, Snake *snake);
  void addBody(Snake *snake);
  void updateInfo(GameInfo_t *game);
  bool isSnakeCell(Snake *snake, int x, int y);
  bool winGame(Snake snake);
  void free_memory(GameInfo_t *game, Snake *snake);

 private:
  controller *control;
};
}  // namespace s21
#endif  // MODEL_H
