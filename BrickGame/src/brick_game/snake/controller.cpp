#include "controller.h"
namespace s21 {
controller::controller(){};
controller::~controller() {}

void controller::userInput(UserAction_t action, bool *hold) {
  if (action == Left) {
    if (direction == Left)
      *hold = true;
    else if (direction != Right) {
      direction = Left;
    }
  }
  if (action == Right) {
    if (direction == Right)
      *hold = true;
    else if (direction != Left) {
      direction = Right;
    }
  }
  if (action == Up) {
    if (direction == Up)
      *hold = true;
    else if (direction != Down) {
      direction = Up;
    }
  }
  if (action == Down) {
    if (direction == Down)
      *hold = true;
    else if (direction != Up) {
      direction = Down;
    }
  }
  if (action == Pause) {
    if (pause == 0)
      pause = 1;
    else
      pause = 0;
  }
}
}  // namespace s21
