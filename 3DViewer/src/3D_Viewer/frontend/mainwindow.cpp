#include "mainwindow.h"

#include "glview.h"
#include "ui_mainwindow.h"
namespace s21 {
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  const Controller *controller = ui->openGLWidget->getController();
  last_setting();
  ui->error->setVisible(false);

  isGeometry = false;
  isColor = false;
  isVertices = false;
  isEdges = false;
  isProject = false;
  isSave = false;
  isRotate = false;

  QFileInfo fileInfo(ui->path->text());
  ui->label_count_vert->setText(
      QString::number(controller->getVertices().size()));
  ui->label_name->setText(fileInfo.fileName());
  ui->label_count_edge->setText(
      QString::number(controller->get_count_indices_for_polygon()));

  connect(&tmr, SIGNAL(timeout()), this, SLOT(rotate_x()));
  connect(&tmr, SIGNAL(timeout()), this, SLOT(rotate_y()));
  connect(&tmr, SIGNAL(timeout()), this, SLOT(rotate_z()));

  connect(ui->auto_rotate, SIGNAL(clicked()), this, SLOT(auto_rotate()));
  connect(ui->open_file, SIGNAL(clicked()), this, SLOT(fileopen()));
  connect(ui->download, SIGNAL(clicked()), this, SLOT(load_model()));
  connect(ui->remove, SIGNAL(clicked()), this, SLOT(remove()));
  connect(ui->x_rorate_slider, &QSlider::valueChanged, ui->x_rorate_spin,
          &QDoubleSpinBox::setValue);
  connect(ui->x_rorate_spin,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          ui->x_rorate_slider, &QSlider::setValue);
  connect(ui->y_rorate_slider, &QSlider::valueChanged, ui->y_rorate_spin,
          &QDoubleSpinBox::setValue);
  connect(ui->y_rorate_spin,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          ui->y_rorate_slider, &QSlider::setValue);
  connect(ui->z_rorate_slider, &QSlider::valueChanged, ui->z_rorate_spin,
          &QDoubleSpinBox::setValue);
  connect(ui->z_rorate_spin,
          QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          ui->z_rorate_slider, &QSlider::setValue);
  connect(ui->x_pos_slider, &QSlider::valueChanged, ui->x_pos_spin,
          &QDoubleSpinBox::setValue);
  connect(ui->x_pos_spin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          ui->x_pos_slider, &QSlider::setValue);
  connect(ui->y_pos_slider, &QSlider::valueChanged, ui->y_pos_spin,
          &QDoubleSpinBox::setValue);
  connect(ui->y_pos_spin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          ui->y_pos_slider, &QSlider::setValue);
  connect(ui->z_pos_slider, &QSlider::valueChanged, ui->z_pos_spin,
          &QDoubleSpinBox::setValue);
  connect(ui->z_pos_spin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          ui->z_pos_slider, &QSlider::setValue);
  connect(ui->scale_slider, &QSlider::valueChanged, ui->scale_spin,
          &QDoubleSpinBox::setValue);
  connect(ui->scale_spin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          ui->scale_slider, &QSlider::setValue);
  connect(ui->ver_slider, &QSlider::valueChanged, ui->ver_spin,
          &QDoubleSpinBox::setValue);
  connect(ui->ver_spin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          ui->ver_slider, &QSlider::setValue);
  connect(ui->ed_slider, &QSlider::valueChanged, ui->ed_spin,
          &QDoubleSpinBox::setValue);
  connect(ui->ed_spin, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          ui->ed_slider, &QSlider::setValue);

  connect(ui->radioButton_dashes, SIGNAL(toggled(bool)), this,
          SLOT(type_line()));
  connect(ui->radioButton_central, SIGNAL(toggled(bool)), this,
          SLOT(type_project()));
  connect(ui->radioButton_circle, SIGNAL(toggled(bool)), this,
          SLOT(type_vertices()));
  connect(ui->radioButton_square, SIGNAL(toggled(bool)), this,
          SLOT(type_vertices()));

  connect(ui->x_rorate_slider, SIGNAL(valueChanged(int)), this,
          SLOT(rotate_x()));
  connect(ui->y_rorate_slider, SIGNAL(valueChanged(int)), this,
          SLOT(rotate_y()));
  connect(ui->z_rorate_slider, SIGNAL(valueChanged(int)), this,
          SLOT(rotate_z()));

  connect(ui->ver_slider, SIGNAL(valueChanged(int)), this, SLOT(size_ver()));
  connect(ui->ed_slider, SIGNAL(valueChanged(int)), this, SLOT(size_edge()));

  connect(ui->x_pos_slider, SIGNAL(valueChanged(int)), this, SLOT(move_x()));
  connect(ui->y_pos_slider, SIGNAL(valueChanged(int)), this, SLOT(move_y()));
  connect(ui->z_pos_slider, SIGNAL(valueChanged(int)), this, SLOT(move_z()));

  connect(ui->scale_slider, SIGNAL(valueChanged(int)), this, SLOT(scale_obj()));

  connect(ui->ver_slider, SIGNAL(valueChanged(int)), this, SLOT(size_ver()));
  connect(ui->ed_slider, SIGNAL(valueChanged(int)), this, SLOT(size_edge()));

  connect(ui->pushButton_geometry, SIGNAL(clicked()), this, SLOT(geometry()));
  connect(ui->pushButton_color, SIGNAL(clicked()), this, SLOT(color()));
  connect(ui->pushButton_vertices, SIGNAL(clicked()), this, SLOT(vertices()));
  connect(ui->pushButton_edges, SIGNAL(clicked()), this, SLOT(edges()));
  connect(ui->pushButton_project, SIGNAL(clicked()), this, SLOT(projection()));
  connect(ui->pushButton_save, SIGNAL(clicked()), this, SLOT(save()));
  connect(ui->make_jpeg, SIGNAL(clicked()), this, SLOT(make_scr()));
  connect(ui->make_bmp, SIGNAL(clicked()), this, SLOT(make_scr()));
  connect(ui->make_gif, SIGNAL(clicked()), this, SLOT(make_gif()));

  connect(ui->but_color, SIGNAL(clicked()), this, SLOT(but_color()));
  connect(ui->but_color_back, SIGNAL(clicked()), this, SLOT(but_color()));
  connect(ui->but_color_ver, SIGNAL(clicked()), this, SLOT(but_color()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::fileopen() {
  QString filename = QFileDialog::getOpenFileName(
      this, "Select file", QDir::currentPath() + "../obj_images");
  ui->path->setText(filename);
}

void MainWindow::load_model() {
  QFileInfo fileInfo(ui->path->text());
  if (fileInfo.exists()) {
    switch_menu(true);
    ui->openGLWidget->load_obj_file(ui->path->text());
    ui->openGLWidget->setting.setValue("Path", ui->path->text());
    ui->openGLWidget->setToRemove(false);
    ui->openGLWidget->update();
    ui->label_count_vert->setText(QString::number(
        ui->openGLWidget->getModel().obj_vertices_to_1D_array().size() / 3));
    ui->label_name->setText(fileInfo.fileName());
    ui->label_count_edge->setText(QString::number(
        ui->openGLWidget->getModel().count_indices_for_polygon() / 4));
    ui->openGLWidget->setting.setValue("Menu", true);
  } else {
    switch_menu(false);
    ui->openGLWidget->setToRemove(true);
    ui->openGLWidget->update();
    ui->openGLWidget->setting.setValue("Menu", false);
  }
}

void MainWindow::remove() {
  if (!ui->openGLWidget->getToRemove()) {
    ui->openGLWidget->getModel().free_memory();
    ui->openGLWidget->clear_window();
    ui->path->setText("");
    ui->openGLWidget->setToRemove(true);
    ui->openGLWidget->update();
    switch_menu(false);
    ui->openGLWidget->setting.setValue("Menu", false);
    ui->openGLWidget->setting.setValue("Path", "");
    ui->error->setVisible(false);
  }
}

void MainWindow::geometry() {
  QPropertyAnimation *animation =
      new QPropertyAnimation(ui->groupBox_geometry, "geometry");
  animation->setDuration(100);
  connect(animation, &QPropertyAnimation::valueChanged, this,
          &MainWindow::move);

  if (!isGeometry) {
    animation->setStartValue(ui->groupBox_geometry->geometry());
    animation->setEndValue(QRect(0, 130, 321, 302));
    ui->pushButton_geometry->setText("▼ Geometry");
    isGeometry = true;
  } else {
    animation->setStartValue(ui->groupBox_geometry->geometry());
    animation->setEndValue(QRect(0, 130, 321, 32));
    ui->pushButton_geometry->setText("▶ Geometry");
    isGeometry = false;
  }
  animation->start();
}

void MainWindow::color() {
  QPropertyAnimation *animation =
      new QPropertyAnimation(ui->groupBox_color, "geometry");
  animation->setDuration(100);
  connect(animation, &QPropertyAnimation::valueChanged, this,
          &MainWindow::move);
  if (!isColor) {
    animation->setStartValue(ui->groupBox_color->geometry());
    animation->setEndValue(
        QRect(ui->groupBox_color->x(), ui->groupBox_color->y(), 321, 151));
    ui->pushButton_color->setText("▼ Color");
    isColor = true;
  } else {
    animation->setStartValue(ui->groupBox_color->geometry());
    animation->setEndValue(
        QRect(ui->groupBox_color->x(), ui->groupBox_color->y(), 321, 32));
    ui->pushButton_color->setText("▶ Color");
    isColor = false;
  }
  animation->start();
}

void MainWindow::vertices() {
  QPropertyAnimation *animation =
      new QPropertyAnimation(ui->groupBox_vertices, "geometry");
  animation->setDuration(100);
  connect(animation, &QPropertyAnimation::valueChanged, this,
          &MainWindow::move);
  if (!isVertices) {
    animation->setStartValue(ui->groupBox_vertices->geometry());
    animation->setEndValue(QRect(ui->groupBox_vertices->x(),
                                 ui->groupBox_vertices->y(), 321, 111));
    ui->pushButton_vertices->setText("▼ Vertices");
    isVertices = true;
  } else {
    animation->setStartValue(ui->groupBox_vertices->geometry());
    animation->setEndValue(
        QRect(ui->groupBox_vertices->x(), ui->groupBox_vertices->y(), 321, 32));
    ui->pushButton_vertices->setText("▶ Vertices");
    isVertices = false;
  }
  animation->start();
}

void MainWindow::edges() {
  QPropertyAnimation *animation =
      new QPropertyAnimation(ui->groupBox_edges, "geometry");
  animation->setDuration(100);
  connect(animation, &QPropertyAnimation::valueChanged, this,
          &MainWindow::move);
  if (!isEdges) {
    animation->setStartValue(ui->groupBox_edges->geometry());
    animation->setEndValue(
        QRect(ui->groupBox_edges->x(), ui->groupBox_edges->y(), 321, 105));
    ui->pushButton_edges->setText("▼ Edges");
    isEdges = true;
  } else {
    animation->setStartValue(ui->groupBox_edges->geometry());
    animation->setEndValue(
        QRect(ui->groupBox_edges->x(), ui->groupBox_edges->y(), 321, 32));
    ui->pushButton_edges->setText("▶ Edges");
    isEdges = false;
  }
  animation->start();
}

void MainWindow::projection() {
  QPropertyAnimation *animation =
      new QPropertyAnimation(ui->groupBox_project, "geometry");
  animation->setDuration(100);
  connect(animation, &QPropertyAnimation::valueChanged, this,
          &MainWindow::move);
  if (!isProject) {
    animation->setStartValue(ui->groupBox_project->geometry());
    animation->setEndValue(
        QRect(ui->groupBox_project->x(), ui->groupBox_project->y(), 321, 72));
    ui->pushButton_project->setText("▼ Projection");
    isProject = true;
  } else {
    animation->setStartValue(ui->groupBox_project->geometry());
    animation->setEndValue(
        QRect(ui->groupBox_project->x(), ui->groupBox_project->y(), 321, 32));
    ui->pushButton_project->setText("▶ Projection");
    isProject = false;
  }
  animation->start();
}

void MainWindow::save() {
  QPropertyAnimation *animation =
      new QPropertyAnimation(ui->groupBox_save, "geometry");
  animation->setDuration(100);
  connect(animation, &QPropertyAnimation::valueChanged, this,
          &MainWindow::move);
  if (!isSave) {
    animation->setStartValue(ui->groupBox_save->geometry());
    animation->setEndValue(
        QRect(ui->groupBox_save->x(), ui->groupBox_save->y(), 321, 83));
    ui->pushButton_save->setText("▼ Save");
    isSave = true;
  } else {
    animation->setStartValue(ui->groupBox_save->geometry());
    animation->setEndValue(
        QRect(ui->groupBox_save->x(), ui->groupBox_save->y(), 321, 32));
    ui->pushButton_save->setText("▶ Save");
    isSave = false;
  }
  animation->start();
}

void MainWindow::but_color() {
  QPushButton *button = (QPushButton *)sender();
  QColorDialog dialog(this);
  QColor color = dialog.getColor(Qt::white, this, "Choose Color");
  if (color.isValid()) {
    QString styleSheet = QString("background-color: %1;").arg(color.name());
    button->setStyleSheet(styleSheet);
    if (button == ui->but_color_back) {
      ui->openGLWidget->setting.setValue("Color_back_r", color.redF());
      ui->openGLWidget->setting.setValue("Color_back_g", color.greenF());
      ui->openGLWidget->setting.setValue("Color_back_b", color.blueF());
    } else if (button == ui->but_color) {
      ui->openGLWidget->setting.setValue("Color_edge_r", color.redF());
      ui->openGLWidget->setting.setValue("Color_edge_g", color.greenF());
      ui->openGLWidget->setting.setValue("Color_edge_b", color.blueF());
    } else {
      ui->openGLWidget->setting.setValue("Color_ver_r", color.redF());
      ui->openGLWidget->setting.setValue("Color_ver_g", color.greenF());
      ui->openGLWidget->setting.setValue("Color_ver_b", color.blueF());
    }
  }
}

void MainWindow::move() {
  ui->groupBox_color->move(
      0, ui->groupBox_geometry->y() + ui->groupBox_geometry->height());
  ui->groupBox_vertices->move(
      0, ui->groupBox_color->y() + ui->groupBox_color->height());
  ui->groupBox_edges->move(
      0, ui->groupBox_vertices->y() + ui->groupBox_vertices->height());
  ui->groupBox_project->move(
      0, ui->groupBox_edges->y() + ui->groupBox_edges->height());
  ui->groupBox_save->move(
      0, ui->groupBox_project->y() + ui->groupBox_project->height());
}

void MainWindow::make_scr() {
  QPushButton *button = (QPushButton *)sender();
  QPixmap screenshot =
      qApp->primaryScreen()->grabWindow(ui->openGLWidget->winId());
  QString filePath = QFileDialog::getSaveFileName(nullptr, "Сохранитьскриншот",
                                                  "", "Images (*.jpeg*.bmp) ");
  if (!filePath.isEmpty()) {
    if (!filePath.endsWith("." + button->text().toLower(),
                           Qt::CaseInsensitive)) {
      filePath += "." + button->text().toLower();
    }
    if (button->text() == "JPEG")
      screenshot.save(filePath, "JPEG");
    else
      screenshot.save(filePath, "BMP");
  }
}

void MainWindow::make_gif() {
  ms = 0;
  gif = new QGifImage();
  time_gif = new QTimer();
  filePath_gif = QFileDialog::getSaveFileName(nullptr, "Сохранить GIF", "",
                                              "GIFs (*.gif)");
  if (!recording) {
    recording = true;
    tmr.start(5);
    ui->auto_rotate->setText("❚❚");
    connect(time_gif, SIGNAL(timeout()), this, SLOT(save_gif()));
    time_gif->start(100);
  }
}

void MainWindow::save_gif() {
  QImage frame = ui->openGLWidget->grabFramebuffer();
  gif->addFrame(frame, 100);
  ms += 100;
  if (ms >= 5000) {
    time_gif->stop();
    gif->save(filePath_gif + ".gif");
    recording = false;
    tmr.stop();
    ui->auto_rotate->setText("▶");
  }
}

void MainWindow::type_line() {
  if (ui->radioButton_dashes->isChecked() == true) {
    ui->openGLWidget->setting.setValue("isDash", true);
  } else
    ui->openGLWidget->setting.setValue("isDash", false);
  ui->openGLWidget->update();
}

void MainWindow::type_project() {
  if (ui->radioButton_central->isChecked() == true) {
    ui->openGLWidget->setting.setValue("isCentral", true);
  } else
    ui->openGLWidget->setting.setValue("isCentral", false);
  ui->openGLWidget->update();
}

void MainWindow::type_vertices() {
  if (ui->radioButton_circle->isChecked() == true)
    ui->openGLWidget->setting.setValue("Vertices", "Circle");
  else if (ui->radioButton_square->isChecked() == true)
    ui->openGLWidget->setting.setValue("Vertices", "Square");
  else
    ui->openGLWidget->setting.setValue("Vertices", "No");
  ui->openGLWidget->update();
}

void MainWindow::last_setting() {
  ui->but_color->setStyleSheet(
      "background-color: rgb(" +
      QString::number(
          ui->openGLWidget->setting.value("Color_edge_r").toDouble() * 255) +
      "," +
      QString::number(
          ui->openGLWidget->setting.value("Color_edge_g").toDouble() * 255) +
      "," +
      QString::number(
          ui->openGLWidget->setting.value("Color_edge_b").toDouble() * 255) +
      ")");
  ui->but_color_back->setStyleSheet(
      "background-color: rgb(" +
      QString::number(
          ui->openGLWidget->setting.value("Color_back_r").toDouble() * 255) +
      "," +
      QString::number(
          ui->openGLWidget->setting.value("Color_back_g").toDouble() * 255) +
      "," +
      QString::number(
          ui->openGLWidget->setting.value("Color_back_b").toDouble() * 255) +
      ")");
  ui->but_color_ver->setStyleSheet(
      "background-color: rgb(" +
      QString::number(
          ui->openGLWidget->setting.value("Color_ver_r").toDouble() * 255) +
      "," +
      QString::number(
          ui->openGLWidget->setting.value("Color_ver_g").toDouble() * 255) +
      "," +
      QString::number(
          ui->openGLWidget->setting.value("Color_ver_b").toDouble() * 255) +
      ")");

  if (ui->openGLWidget->setting.value("Vertices") == "Circle")
    ui->radioButton_circle->setChecked(true);
  else if (ui->openGLWidget->setting.value("Vertices") == "Square")
    ui->radioButton_square->setChecked(true);
  else
    ui->radioButton_no->setChecked(true);

  if (ui->openGLWidget->setting.value("isDash") == true)
    ui->radioButton_dashes->setChecked(true);
  else
    ui->radioButton_solid->setChecked(true);

  if (ui->openGLWidget->setting.value("isCentral") == true)
    ui->radioButton_central->setChecked(true);
  else
    ui->radioButton_ortho->setChecked(true);

  ui->ed_slider->setValue(
      ui->openGLWidget->setting.value("Size_Edge").toDouble());
  ui->ed_spin->setValue(
      ui->openGLWidget->setting.value("Size_Edge").toDouble());
  ui->ver_slider->setValue(
      ui->openGLWidget->setting.value("Size_Vertices").toDouble());
  ui->ver_spin->setValue(
      ui->openGLWidget->setting.value("Size_Vertices").toDouble());
  ui->path->setText(ui->openGLWidget->setting.value("Path").toString());
  switch_menu(ui->openGLWidget->setting.value("Menu").toBool());
}

void MainWindow::rotate_x() {
  QTimer *sender_ptr = qobject_cast<QTimer *>(sender());
  if (sender_ptr) {
    ui->x_rorate_slider->setValue(
        static_cast<int>(ui->x_rorate_spin->value() + 1) % 360);
  }

  double angle = ui->x_rorate_spin->value();
  ui->openGLWidget->rotate(1, angle - prevAngleX);
  prevAngleX = angle;
}

void MainWindow::rotate_y() {
  QTimer *sender_ptr = qobject_cast<QTimer *>(sender());
  if (sender_ptr) {
    ui->y_rorate_slider->setValue(
        static_cast<int>(ui->y_rorate_spin->value() + 1) % 360);
  }

  double angle = ui->y_rorate_spin->value();
  ui->openGLWidget->rotate(2, angle - prevAngleY);
  prevAngleY = angle;
}

void MainWindow::rotate_z() {
  QTimer *sender_ptr = qobject_cast<QTimer *>(sender());
  if (sender_ptr) {
    ui->z_rorate_slider->setValue(
        static_cast<int>(ui->z_rorate_spin->value() + 1) % 360);
  }

  double angle = ui->z_rorate_spin->value();
  ui->openGLWidget->rotate(3, angle - prevAngleZ);
  prevAngleZ = angle;
}

void MainWindow::size_ver() {
  ui->openGLWidget->setting.setValue("Size_Vertices", ui->ver_spin->value());
  ui->openGLWidget->update();
}

void MainWindow::size_edge() {
  ui->openGLWidget->setting.setValue("Size_Edge", ui->ed_spin->value());
  ui->openGLWidget->update();
}

void MainWindow::move_x() {
  float currentX = ui->x_pos_slider->value() / 100.0f;
  float moveValue = currentX - previousX;
  ui->openGLWidget->move(1, moveValue);
  previousX = currentX;
}

void MainWindow::move_y() {
  float currentY = ui->y_pos_slider->value() / 100.0f;
  float moveValue = currentY - previousY;
  ui->openGLWidget->move(2, moveValue);
  previousY = currentY;
}

void MainWindow::move_z() {
  float currentZ = ui->z_pos_slider->value() / 100.0f;
  float moveValue = currentZ - previousZ;
  ui->openGLWidget->move(3, moveValue);
  previousZ = currentZ;
}

void MainWindow::scale_obj() {
  float currentScale = ui->scale_spin->value() / 100.0f;
  float scaleValue = currentScale / previousScale;
  ui->openGLWidget->scale(scaleValue);
  previousScale = currentScale;
}

void MainWindow::auto_rotate() {
  if (!isRotate) {
    tmr.start(5);
    ui->auto_rotate->setText("❚❚");
    isRotate = true;
  } else {
    tmr.stop();
    ui->auto_rotate->setText("▶");
    isRotate = false;
  }
}

void MainWindow::switch_menu(bool off) {
  ui->groupBox_info->setVisible(off);
  ui->groupBox_geometry->setVisible(off);
  ui->groupBox_color->setVisible(off);
  ui->groupBox_vertices->setVisible(off);
  ui->groupBox_edges->setVisible(off);
  ui->groupBox_save->setVisible(off);
  ui->groupBox_project->setVisible(off);
  ui->auto_rotate->setVisible(off);
  ui->error->setVisible(!off);
}
}  // namespace s21