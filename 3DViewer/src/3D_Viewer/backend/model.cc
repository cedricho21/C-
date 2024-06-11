#include "model.h"
namespace s21 {
void Model::handle_polygon(const std::string& line) {
  std::istringstream iss(line);
  std::string prefix;
  std::vector<int> vertex_indices;

  iss >> prefix;
  while (!iss.eof()) {
    std::string vertex_info;
    iss >> vertex_info;
    std::istringstream vertex_stream(vertex_info);
    std::string index_str;
    std::getline(vertex_stream, index_str, '/');
    int vertex_index = std::stoi(index_str);
    vertex_indices.push_back(vertex_index - 1);

    for (int i = 0; i < 2; ++i) {
      std::getline(vertex_stream, index_str, '/');
    }
  }

  polygons.emplace_back(vertex_indices);
}

void Model::handle_vertex(const std::string& line) {
  std::istringstream iss(line);
  std::string prefix;
  float x, y, z;

  iss >> prefix >> x >> y >> z;
  vertices.emplace_back(x, y, z);
}

Model Model::parse_obj_file(const std::string& filename) {
  Model obj;
  std::ifstream infile(filename);

  if (!infile.is_open()) {
    std::cerr << "Unable to open file: " << filename << std::endl;
    return obj;
  }

  std::string line;
  while (std::getline(infile, line)) {
    if (line.substr(0, 2) == "v ") {
      obj.handle_vertex(line);
    } else if (line.substr(0, 2) == "f ") {
      obj.handle_polygon(line);
    }
  }

  infile.close();
  return obj;
}

void Model::free_memory() const {
  const_cast<Model*>(this)->vertices.clear();
  const_cast<Model*>(this)->polygons.clear();
}

float Model::max(float val1, float val2) { return std::max(val1, val2); }

float Model::min(float val1, float val2) { return std::min(val1, val2); }

int Model::count_indices_for_polygon() const {
  int count = 0;
  for (const auto& polygon : polygons) {
    count += polygon.count_of_vertices();
  }
  return count;
}

std::vector<float> Model::obj_vertices_to_1D_array() const {
  std::vector<float> arr;
  for (const auto& vertex : vertices) {
    arr.push_back(vertex.x);
    arr.push_back(vertex.y);
    arr.push_back(vertex.z);
  }
  return arr;
}

std::vector<int> Model::obj_polygons_to_1D_array() const {
  std::vector<int> arr;
  for (const auto& polygon : polygons) {
    for (size_t i = 0; i < polygon.points_indices.size() - 1; ++i) {
      arr.push_back(polygon.points_indices[i]);
      arr.push_back(polygon.points_indices[i + 1]);
    }
    arr.push_back(polygon.points_indices.back());
    arr.push_back(polygon.points_indices.front());
  }
  return arr;
}

std::vector<float> Model::normalize_array(const std::vector<float>& arr) const {
  if (arr.empty()) return arr;

  float max_val = *std::max_element(arr.begin(), arr.end());
  float min_val = *std::min_element(arr.begin(), arr.end());
  std::vector<float> normalized_arr;

  for (float val : arr) {
    normalized_arr.push_back((val - min_val) / (max_val - min_val));
  }

  return normalized_arr;
}

void Model::scale(float scaling_factor) {
  for (auto& vertex : vertices) {
    vertex.x *= scaling_factor;
    vertex.y *= scaling_factor;
    vertex.z *= scaling_factor;
  }
}

void Model::move_obj(int axis, float pos) {
  for (auto& vertex : vertices) {
    if (axis == X)
      vertex.x += pos;
    else if (axis == Y)
      vertex.y += pos;
    else if (axis == Z)
      vertex.z += pos;
  }
}

void Model::rotate(float angle, int axis) {
  angle = angle * M_PI / 180;
  for (auto& vertex : vertices) {
    float x = vertex.x;
    float y = vertex.y;
    float z = vertex.z;
    if (axis == X) {
      vertex.y = y * cos(angle) + z * sin(angle);
      vertex.z = -y * sin(angle) + z * cos(angle);
    } else if (axis == Y) {
      vertex.x = x * cos(angle) + z * sin(angle);
      vertex.z = -x * sin(angle) + z * cos(angle);
    } else if (axis == Z) {
      vertex.x = x * cos(angle) + y * sin(angle);
      vertex.y = -x * sin(angle) + y * cos(angle);
    }
  }
}
}  // namespace s21