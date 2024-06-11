#ifndef CONTROLLER_H
#define CONTROLLER_H

/**
 * @file controller.h
 * @brief Заголовочный файл класса Controller.
 */

#include "model.h"
namespace s21 {
/**
 * @brief Класс контроллера.
 */
class Controller {
 public:
  Controller(Model& model) : model_(model) {}
  /**
   * @brief движение по Х.
   */
  void moveX(float value) { model_.move_obj(X, value); }
  /**
   * @brief движение по Y.
   */
  void moveY(float value) { model_.move_obj(Y, value); }
  /**
   * @brief движение по Z.
   */
  void moveZ(float value) { model_.move_obj(Z, value); }
  /**
   * @brief Приблежение.
   */
  void scale(float value) { model_.scale(value); }
  /**
   * @brief Поворот и вращение Х.
   */
  void rotateX(float value) { model_.rotate(value, X); }
  /**
   * @brief Поворот и вращение Y.
   */
  void rotateY(float value) { model_.rotate(value, Y); }
  /**
   * @brief Поворот и вращение Z.
   */
  void rotateZ(float value) { model_.rotate(value, Z); }
  /**
   * @brief Значение вершин.
   */
  const std::vector<Model::Vertex>& getVertices() const {
    return model_.getVertices();
  }
  /**
   * @brief Значение полигонов.
   */
  const std::vector<Model::Polygon>& getPolygons() const {
    return model_.getPolygons();
  }
  /**
   * @brief Массив полигонов.
   */
  const std::vector<int> get_obj_polygons_to_1D_array() const {
    return model_.obj_polygons_to_1D_array();
  }
  /**
   * @brief Массив вершин.
   */
  const std::vector<float> get_obj_vertices_to_1D_array() const {
    return model_.obj_vertices_to_1D_array();
  }
  /**
   * @brief Количество полигонов.
   */
  int get_count_indices_for_polygon() const {
    return model_.count_indices_for_polygon();
  }
  /**
   * @brief Освобождение памяти.
   */
  void free_memory() { model_.free_memory(); }

 private:
  Model& model_;
};
}  // namespace s21
#endif  // CONTROLLER_H
