#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/**
 * @file mainwindow.h
 * @brief Заголовочный файл для класса MainWindow.
 *
 * Этот файл содержит определения класса MainWindow, который является главным
 * окном графического интерфейса приложения.
 */

#include <QColorDialog>
#include <QDate>
#include <QDebug>
#include <QFileDialog>
#include <QGroupBox>
#include <QMainWindow>
#include <QOpenGLWidget>
#include <QPixmap>
#include <QPoint>
#include <QPropertyAnimation>
#include <QScreen>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>

#include "../backend/controller.h"
#include "glview.h"
#include "qgifimage.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
namespace s21 {
/**
 * @brief Класс мэйнвиндоу.
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();
  bool isGeometry;
  bool isColor;
  bool isVertices;
  bool isEdges;
  bool isProject;
  bool isSave;
  bool isRotate;
  bool recording;
  int ms;
  QGifImage *gif;
  QTimer *time_gif;
  QTimer tmr;
  QString filePath_gif;
  int length;

 private:
  Ui::MainWindow *ui;
  float previousX = 0.0f;
  float previousY = 0.0f;
  float previousZ = 0.0f;
  double prevAngleX = 0.0f;
  double prevAngleY = 0.0f;
  double prevAngleZ = 0.0f;
  float previousScale = 1.0f;

 private slots:
  /**
   * @brief Открытие файла.
   */
  void fileopen();

  /**
   * @brief Загрузка модели.
   */
  void load_model();

  /**
   * @brief Удаление модели.
   */
  void remove();

  /**
   * @brief Настройка геометрии.
   */
  void geometry();

  /**
   * @brief Настройка цвета.
   */
  void color();

  /**
   * @brief Настройка вершин.
   */
  void vertices();

  /**
   * @brief Настройка ребер.
   */
  void edges();

  /**
   * @brief Настройка проекции.
   */
  void projection();

  /**
   * @brief Сохранение модели.
   */
  void save();

  /**
   * @brief Перемещение модели.
   */
  void move();

  /**
   * @brief Выбор цвета.
   */
  void but_color();

  /**
   * @brief Создание снимка экрана.
   */
  void make_scr();

  /**
   * @brief Создание GIF.
   */
  void make_gif();

  /**
   * @brief Сохранение GIF.
   */
  void save_gif();

  /**
   * @brief Вращение модели по оси X.
   */
  void rotate_x();

  /**
   * @brief Вращение модели по оси Y.
   */
  void rotate_y();

  /**
   * @brief Вращение модели по оси Z.
   */
  void rotate_z();

  /**
   * @brief Перемещение модели по оси X.
   */
  void move_x();

  /**
   * @brief Перемещение модели по оси Y.
   */
  void move_y();

  /**
   * @brief Перемещение модели по оси Z.
   */
  void move_z();

  /**
   * @brief Масштабирование модели.
   */
  void scale_obj();

  /**
   * @brief Настройка типа линии.
   */
  void type_line();

  /**
   * @brief Настройка типа проекции.
   */
  void type_project();

  /**
   * @brief Настройка типа вершин.
   */
  void type_vertices();

  /**
   * @brief Применение последней настройки.
   */
  void last_setting();

  /**
   * @brief Настройка размера вершин.
   */
  void size_ver();

  /**
   * @brief Настройка размера ребер.
   */
  void size_edge();

  /**
   * @brief Автоматическое вращение модели.
   */
  void auto_rotate();

  /**
   * @brief Переключение меню.
   * @param off Логическое значение для включения/выключения меню.
   */
  void switch_menu(bool off);
};
}  // namespace s21
#endif  // MAINWINDOW_H
