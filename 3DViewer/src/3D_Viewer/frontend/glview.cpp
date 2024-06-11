#include "glview.h"

void glView::initializeGL() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glScalef(0.29f, 0.305f, 0.29f);
  type_project();
}

glView::~glView() {
  controller->free_memory();
  delete controller;
}

void glView::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void glView::paintGL() {
  if (toRemove) return;

  initializeGL();
  glClearColor(setting.value("Color_back_r").toDouble(),
               setting.value("Color_back_g").toDouble(),
               setting.value("Color_back_b").toDouble(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnableClientState(GL_VERTEX_ARRAY);
  type_line();
  type_vertices();
  glDisableClientState(GL_VERTEX_ARRAY);
}

void glView::updateGL() {
  if (toRemove) {
    clear_window();
    return;
  }

  load_obj_file(setting.value("Path").toString());
}

void glView::load_obj_file(const QString& filename) {
  model = Model::parse_obj_file(filename.toStdString());
  controller = new Controller(model);
  if (controller->getVertices().empty() || controller->getPolygons().empty()) {
    toRemove = true;
    return;
  }
  update();
}

void glView::clear_window() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void glView::init_default() { load_obj_file(setting.value("Path").toString()); }

void glView::type_project() {
  if (setting.value("isCentral") == false) {
    glOrtho(-1, 1, -1, 1, -5, 5);
    glTranslatef(0, 0.2, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  } else {
    glFrustum(-0.5, 0.5, -0.5, 0.5, 0.2, 1000);
    glTranslatef(0, 0, -0.9);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }
}

void glView::type_line() {
  glLineWidth(setting.value("Size_Edge").toDouble());
  glColor3f(setting.value("Color_edge_r").toDouble(),
            setting.value("Color_edge_g").toDouble(),
            setting.value("Color_edge_b").toDouble());

  if (setting.value("isDash").toBool()) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x00FF);
  } else {
    glDisable(GL_LINE_STIPPLE);
  }

  std::vector<float> vertices = controller->get_obj_vertices_to_1D_array();
  std::vector<int> indices = controller->get_obj_polygons_to_1D_array();

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3, GL_FLOAT, 0, vertices.data());
  glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, indices.data());
  glDisableClientState(GL_VERTEX_ARRAY);
}

void glView::type_vertices() {
  glPointSize(setting.value("Size_Vertices").toDouble());
  glColor3f(setting.value("Color_ver_r").toDouble(),
            setting.value("Color_ver_g").toDouble(),
            setting.value("Color_ver_b").toDouble());

  std::vector<float> vertices = controller->get_obj_vertices_to_1D_array();
  int num_vertices = vertices.size() / 3;

  if (setting.value("Vertices") == "Circle") {
    glEnable(GL_POINT_SMOOTH);
    glBegin(GL_POINTS);
    for (int i = 0; i < num_vertices; ++i) {
      glVertex3f(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]);
    }
    glEnd();
    glDisable(GL_POINT_SMOOTH);
  } else if (setting.value("Vertices") == "Square") {
    glBegin(GL_POINTS);
    for (int i = 0; i < num_vertices; ++i) {
      glVertex3f(vertices[i * 3], vertices[i * 3 + 1], vertices[i * 3 + 2]);
    }
    glEnd();
  }
}

void glView::move(int axis, float value) {
  if (axis == 1) {
    if (controller) controller->moveX(value);
  }
  if (axis == 2) {
    if (controller) controller->moveY(value);
  }
  if (axis == 3) {
    if (controller) controller->moveZ(value);
  }
  update();
}

void glView::rotate(int axis, float value) {
  if (axis == 1) {
    if (controller) controller->rotateX(value);
  }
  if (axis == 2) {
    if (controller) controller->rotateY(value);
  }
  if (axis == 3) {
    if (controller) controller->rotateZ(value);
  }
  update();
}

void glView::scale(float value) {
  controller->scale(value);
  update();
}
