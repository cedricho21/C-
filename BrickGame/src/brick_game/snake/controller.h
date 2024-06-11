#ifndef CONTROLLER_H
#define CONTROLLER_H
namespace s21 {
class controller {
 public:
  controller();
  ~controller();

  typedef enum {
    Start,
    Pause,
    Terminate,
    Left,
    Right,
    Up,
    Down,
    Action,
    None
  } UserAction_t;

  UserAction_t direction;
  int pause = 0;
  void userInput(UserAction_t action, bool *hold);
};
}  // namespace s21
#endif  // CONTROLLER_H
