#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QWidget>

#include "view.h"

namespace Ui {
class mainmenu;
}
namespace s21 {
class mainmenu : public QWidget {
  Q_OBJECT

 public:
  explicit mainmenu(QWidget *parent = nullptr);
  ~mainmenu();

 private slots:
  void startSnakeGame();
  void startTetrisGame();

 private:
  Ui::mainmenu *ui;
  View *gameView;
};
}  // namespace s21
#endif  // MAINMENU_H
