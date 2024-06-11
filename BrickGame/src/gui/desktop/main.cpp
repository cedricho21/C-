#include <QApplication>

#include "mainmenu.h"
// #include "snakeview.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  s21::mainmenu w;
  w.show();
  return a.exec();
}
