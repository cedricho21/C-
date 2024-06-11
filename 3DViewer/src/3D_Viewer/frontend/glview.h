#ifndef GLVIEW_H
#define GLVIEW_H

/**
 * @file glview.h
 * @brief Заголовочный файл для класса glView.
 *
 * Этот файл содержит определения класса glView, который отвечает за отображение
 * графических данных с использованием OpenGL в приложении на основе Qt.
 */

#include <QDebug>
#include <QOpenGLWidget>
#include <QSettings>
#include <QTimer>
#include <QWidget>
#include <QtOpenGL>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../backend/controller.h"
#include "../backend/model.h"

using namespace s21;

/**
 * @class glView
 * @brief Класс для отображения графических данных с использованием OpenGL.
 *
 * Этот класс наследуется от QOpenGLWidget и используется для рендеринга
 * 3D-объектов с использованием OpenGL в приложении на основе Qt.
 */
class glView : public QOpenGLWidget {
  Q_OBJECT

 public:
  /**
   * @brief Конструктор класса glView.
   * @param parent Указатель на родительский виджет.
   */
  glView(QWidget* parent = nullptr)
      : QOpenGLWidget(parent), controller(nullptr) {
    init_default();
  };

  /**
   * @brief Деструктор класса glView.
   */
  ~glView();

  /**
   * @brief Инициализация OpenGL.
   *
   * Этот метод вызывается один раз до выполнения первого вызова paintGL()
   * или resizeGL().
   */
  void initializeGL() override;

  /**
   * @brief Изменение размеров окна OpenGL.
   * @param w Новая ширина окна.
   * @param h Новая высота окна.
   */
  void resizeGL(int w, int h) override;

  /**
   * @brief Отрисовка содержимого окна OpenGL.
   */
  void paintGL() override;

  /**
   * @brief Обновление содержимого окна OpenGL.
   */
  void updateGL();

  /**
   * @brief Перемещение объекта.
   * @param axis Ось перемещения (0 - x, 1 - y, 2 - z).
   * @param value Величина перемещения.
   */
  void move(int axis, float value);

  /**
   * @brief Вращение объекта.
   * @param axis Ось вращения (0 - x, 1 - y, 2 - z).
   * @param value Величина вращения.
   */
  void rotate(int axis, float value);

  /**
   * @brief Масштабирование объекта.
   * @param value Коэффициент масштабирования.
   */
  void scale(float value);

  /**
   * @brief Загрузка объекта из файла .obj.
   * @param filename Имя файла для загрузки.
   */
  void load_obj_file(const QString& filename);

  /**
   * @brief Очистка окна.
   */
  void clear_window();

  /**
   * @brief Получение модели.
   * @return Константная ссылка на объект модели.
   */
  const Model& getModel() const { return model; }

  /**
   * @brief Получение указателя на модель.
   * @return Указатель на объект модели.
   */
  Model* getModelPointer() { return &model; }

  /**
   * @brief Проверка, нужно ли удалить объект.
   * @return Логическое значение, указывающее, нужно ли удалить объект.
   */
  bool getToRemove() const { return toRemove; }

  /**
   * @brief Установка флага удаления объекта.
   * @param value Новое значение флага удаления.
   */
  void setToRemove(bool value) { toRemove = value; }
  QSettings setting;
  /**
   * @brief Получение контроллера.
   * @return Константный указатель на объект контроллера.
   */
  const Controller* getController() const { return controller; }

 private:
  Model model;  ///< Объект модели.
  Controller* controller;  ///< Указатель на объект контроллера.
  bool toRemove = false;  ///< Флаг удаления объекта.

  /**
   * @brief Инициализация параметров по умолчанию.
   */
  void init_default();

  /**
   * @brief Установка типа проекции.
   */
  void type_project();

  /**
   * @brief Установка типа линии.
   */
  void type_line();

  /**
   * @brief Установка типа вершин.
   */
  void type_vertices();
};

#endif  // GLVIEW_H
