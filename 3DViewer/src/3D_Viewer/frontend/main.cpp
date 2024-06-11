#include <QApplication>

#include "mainwindow.h"

/**
 * @mainpage
 * @brief Главная страница документации.
 *
 * Этот проект представляет собой приложение на C++ с использованием Qt для
 * визуализации и управления 3D моделями. Включает классы для обработки 3D
 * моделей, их отображения в OpenGL и взаимодействия с пользователем через
 * графический интерфейс.
 *
 * @section Установка
 * Для установки нужно собрать src/Makefile с целью install
 *
 * @section usage_sec Использование
 * Для запуска используйте "open build/3D_Viewer.app"
 * Исходные модели хранятся в директории
 *
 */

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  setlocale(LC_NUMERIC, "C");
  s21::MainWindow w;
  w.show();
  return a.exec();
}
