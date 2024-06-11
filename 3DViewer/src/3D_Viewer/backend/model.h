#ifndef MODEL_H
#define MODEL_H

/**
 * @file model.h
 * @brief Заголовочный файл для класса Model.
 *
 * Этот файл содержит определения класса Model, который используется для
 * представления 3D моделей и обработки их данных.
 */

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace s21 {
enum AXES { X, Y, Z };
/**
 * @brief Класс модели.
 */
class Model {
 public:
  /**
   * @class Vertex
   * @brief Класс для представления вершин модели.
   */
  class Vertex {
   public:
    float x;
    float y;
    float z;

    Vertex(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}
  };
  /**
   * @brief Класс полигонов.
   */
  class Polygon {
   public:
    std::vector<int> points_indices;
    Polygon(const std::vector<int>& indices = {}) : points_indices(indices) {}
    int count_of_vertices() const { return points_indices.size(); }
  };

  Model() = default;
  /**
   * @brief Обработка строки полигона.
   * @param line Строка, содержащая данные полигона.
   */
  void handle_polygon(const std::string& line);

  /**
   * @brief Обработка строки вершины.
   * @param line Строка, содержащая данные вершины.
   */
  void handle_vertex(const std::string& line);

  /**
   * @brief Парсинг файла OBJ и создание модели.
   * @param filename Имя файла.
   * @return Модель, созданная из файла.
   */
  static Model parse_obj_file(const std::string& filename);

  /**
   * @brief Освобождение памяти.
   */
  void free_memory() const;

  /**
   * @brief Максимальное значение из двух.
   * @param val1 Первое значение.
   * @param val2 Второе значение.
   * @return Максимальное значение.
   */
  static float max(float val1, float val2);

  /**
   * @brief Минимальное значение из двух.
   * @param val1 Первое значение.
   * @param val2 Второе значение.
   * @return Минимальное значение.
   */
  static float min(float val1, float val2);

  /**
   * @brief Возвращает количество индексов для полигона.
   * @return Количество индексов.
   */
  int count_indices_for_polygon() const;

  /**
   * @brief Преобразует вершины объекта в 1D массив.
   * @return Вектор, содержащий координаты вершин в 1D массиве.
   */
  std::vector<float> obj_vertices_to_1D_array() const;

  /**
   * @brief Преобразует полигоны объекта в 1D массив.
   * @return Вектор, содержащий индексы полигонов в 1D массиве.
   */
  std::vector<int> obj_polygons_to_1D_array() const;

  /**
   * @brief Нормализация массива координат.
   * @param arr Вектор, содержащий координаты.
   * @return Нормализованный вектор координат.
   */
  std::vector<float> normalize_array(const std::vector<float>& arr) const;

  /**
   * @brief Вращение модели.
   * @param angle Угол вращения.
   * @param axis Ось вращения.
   */
  void rotate(float angle, int axis);

  /**
   * @brief Масштабирование модели.
   * @param scaling_factor Коэффициент масштабирования.
   */
  void scale(float scaling_factor);

  /**
   * @brief Перемещение модели.
   * @param axis Ось перемещения.
   * @param pos Позиция.
   */
  void move_obj(int axis, float pos);

  /**
   * @brief Возвращает константную ссылку на вектор вершин.
   * @return Константная ссылка на вектор вершин.
   */
  const std::vector<Vertex>& getVertices() const { return vertices; }

  /**
   * @brief Возвращает константную ссылку на вектор полигонов.
   * @return Константная ссылка на вектор полигонов.
   */
  const std::vector<Polygon>& getPolygons() const { return polygons; }

  /**
   * @brief Возвращает ссылку на вектор вершин.
   * @return Ссылка на вектор вершин.
   */
  std::vector<Vertex>& getVertices() { return vertices; }

  /**
   * @brief Возвращает ссылку на вектор полигонов.
   * @return Ссылка на вектор полигонов.
   */
  std::vector<Polygon>& getPolygons() { return polygons; }

 private:
  std::vector<Vertex> vertices;  ///< Вектор вершин модели.
  std::vector<Polygon> polygons;  ///< Вектор полигонов модели.
};

}  // namespace s21

#endif  // MODEL_H