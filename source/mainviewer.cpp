#include "header/mainviewer.h"

#include "header/viewer.h"
#include "ui_mainviewer.h"
#include "ui_settings.h"

MainViewer::MainViewer(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainViewer) {
  ui->setupUi(this);
  this->setWindowTitle("3DViewer v1.0");
  settings = new Settings();
  init_obj(&objMain, 1, 1);
  get_settings();
  connect(settings->ui->set_apply, SIGNAL(clicked()), this, SLOT(settings_handler()));
  connect(settings->ui->set_default, SIGNAL(clicked()), this, SLOT(settings_handler()));
}

MainViewer::~MainViewer() {
  //settings->hide();
  delete settings;
  delete ui;
}

void MainViewer::get_settings()
{
    ui->glWindow->bkg_r = settings->ui->bg_color_r->value();
    ui->glWindow->bkg_g = settings->ui->bg_color_g->value();
    ui->glWindow->bkg_b = settings->ui->bg_color_b->value();
    ui->glWindow->vertex_r = settings->ui->vertex_color_r->value();
    ui->glWindow->vertex_g = settings->ui->vertex_color_g->value();
    ui->glWindow->vertex_b = settings->ui->vertex_color_b->value();
    ui->glWindow->edge_r = settings->ui->edge_color_r->value();
    ui->glWindow->edge_g = settings->ui->edge_color_g->value();
    ui->glWindow->edge_b = settings->ui->edge_color_b->value();
    ui->glWindow->vertex_size = settings->ui->vertex_size->value();
    ui->glWindow->edge_width = settings->ui->edge_width->value();
    ui->glWindow->vertex_shape = settings->ui->vertex_shape->currentIndex();
    ui->glWindow->edge_type = settings->ui->edge_type->currentIndex();
    ui->glWindow->grid_status = settings->ui->grid_on->isChecked() ? 1 : 0;
    ui->glWindow->proj_type = settings->ui->projection_type->currentIndex();
    ui->glWindow->update();
}

void MainViewer::settings_handler() {
    get_settings();
}

void MainViewer::on_load_file_clicked() {
  QString path = QFileDialog::getOpenFileName(this, ("Open .obj file"),
                                              QDir::currentPath(), "*.obj");
  if (objMain.edge_cnt > 1 && path.length() != 0) {
    init_obj(&objMain, 1, 1);
  }
  int error_code = open_file(qPrintable(path), &objMain);
  if (error_code != OK && path.length() > 0) {
    ui->label_file->setText("Incorrect File");
  } else if (path.length() > 0) {
    qsizetype idx = path.lastIndexOf('/') + 1;
    QString file_name = path.right(path.size() - idx);
    ui->label_file->setText(file_name);
    ui->label_file_back->setText(file_name);
    ui->cnt_vertices->setText(QString::number(objMain.vertex_cnt));
    ui->cnt_edges->setText(QString::number(objMain.edge_cnt));
    ui->glWindow->obj = &objMain;
    ui->glWindow->project = true;
    init_ui();
  }
}

void MainViewer::init_ui() {
  ui->spin_move_x->setValue(0);
  ui->spin_move_y->setValue(0);
  ui->spin_move_z->setValue(0);
  ui->spin_rot_x->setValue(0);
  ui->spin_rot_y->setValue(0);
  ui->spin_rot_z->setValue(0);
  ui->spin_scale->setValue(1);
  ui->slider_move_x->setValue(0);
  ui->slider_move_y->setValue(0);
  ui->slider_move_z->setValue(0);
  ui->slider_rot_x->setValue(0);
  ui->slider_rot_y->setValue(0);
  ui->slider_rot_z->setValue(0);
  ui->slider_scale->setValue(1);
}

void MainViewer::on_slider_move_x_valueChanged(int value) {
  if (ui->spin_move_x->value() != value) {
    move_x(&objMain, (ui->spin_move_x->value() - value) / -100.0);
    ui->spin_move_x->setValue(value);
  }
  if (value == 0) {
    ui->slider_move_x->setValue(0);
  }
  ui->glWindow->update();
}

void MainViewer::on_slider_move_y_valueChanged(int value) {
  if (ui->spin_move_y->value() != value) {
    move_y(&objMain, (ui->spin_move_y->value() - value) / -100.0);
    ui->spin_move_y->setValue(value);
  }
  if (value == 0) {
    ui->slider_move_y->setValue(0);
  }
  ui->glWindow->update();
}

void MainViewer::on_slider_move_z_valueChanged(int value) {
  if (ui->spin_move_z->value() != value) {
    move_z(&objMain, (ui->spin_move_z->value() - value) / -100.0);
    ui->spin_move_z->setValue(value);
  }
  if (value == 0) {
    ui->slider_move_z->setValue(0);
  }
  ui->glWindow->update();
}

void MainViewer::on_slider_rot_x_valueChanged(int value) {
  if (ui->spin_rot_x->value() != value) {
    rotate_x(&objMain, (ui->spin_rot_x->value() - value) / -100.0);
    ui->spin_rot_x->setValue(value);
  }
  if (value == 0) {
    ui->slider_rot_x->setValue(0);
  }
  ui->glWindow->update();
}

void MainViewer::on_slider_rot_y_valueChanged(int value) {
  if (ui->spin_rot_y->value() != value) {
    rotate_y(&objMain, (ui->spin_rot_y->value() - value) / -100.0);
    ui->spin_rot_y->setValue(value);
  }
  if (value == 0) {
    ui->slider_rot_y->setValue(0);
  }
  ui->glWindow->update();
}

void MainViewer::on_slider_rot_z_valueChanged(int value) {
  if (ui->spin_rot_z->value() != value) {
    rotate_z(&objMain, (ui->spin_rot_z->value() - value) / -100.0);
    ui->spin_rot_z->setValue(value);
  }
  if (value == 0) {
    ui->slider_rot_z->setValue(0);
  }
  ui->glWindow->update();
}

void MainViewer::on_slider_scale_valueChanged(int value) {
  if (ui->spin_scale->value() != value && ui->spin_scale->value() < value) {
    ui->spin_scale->setValue(value);

    scale(&objMain, 1.1);
  }
  if (ui->spin_scale->value() != value && ui->spin_scale->value() > value) {
    ui->spin_scale->setValue(value);

    scale(&objMain, 0.9);
  }
  if (value == 0) {
    ui->slider_scale->setValue(0);
  }
  ui->glWindow->update();
}

void MainViewer::on_settings_clicked() {
  QPoint p = MainViewer::pos();
  settings->move(p.x() - 200, p.y() + 0);
  settings->show();
}

void MainViewer::on_translate_clicked() {
  ui->slider_move_x->setSliderPosition(ui->spin_move_x->value());
  move_x(&objMain, ui->spin_move_x->value() / 100.0);

  ui->slider_move_y->setSliderPosition(ui->spin_move_y->value());
  move_y(&objMain, ui->spin_move_y->value() / 100.0);

  ui->slider_move_z->setSliderPosition(ui->spin_move_z->value());
  move_z(&objMain, ui->spin_move_z->value() / 100.0);

  ui->glWindow->update();
}

void MainViewer::on_rotate_clicked() {
  ui->slider_rot_x->setSliderPosition(ui->spin_rot_x->value());
  rotate_x(&objMain, ui->spin_rot_x->value() / 100.0);

  ui->slider_rot_y->setSliderPosition(ui->spin_rot_y->value());
  rotate_y(&objMain, ui->spin_rot_y->value() / 100.0);

  ui->slider_rot_z->setSliderPosition(ui->spin_rot_z->value());
  rotate_z(&objMain, ui->spin_rot_z->value() / 100.0);

  ui->glWindow->update();
}

void MainViewer::on_scale_clicked() {
  ui->slider_scale->setSliderPosition(ui->spin_scale->value());
  if (ui->spin_scale->value() > 0)
    scale(&objMain, 1.1 * ui->spin_scale->value());
  if (ui->spin_scale->value() < 0)
    scale(&objMain, -0.9 / ui->spin_scale->value());
  ui->glWindow->update();
}

void MainViewer::on_screenshot_clicked() {
  QString savePath = NULL;
  savePath = QFileDialog::getSaveFileName(this, NULL, NULL,
                                          "JPEG (*.jpeg) ;; BMP (*.bmp)");
  if (!savePath.isNull())
    ui->glWindow->grabFramebuffer().save(savePath, NULL, 100);
}

void MainViewer::on_gif_clicked() {
  gif = new QGifImage(QSize(640, 480));
  gif->setDefaultDelay(100);
  frame = new QImage;
  timer = new QTimer(this);
  time = 0;
  connect(timer, SIGNAL(timeout()), this, SLOT(saveGifFrame()));
  timer->start(100);
}
void MainViewer::saveGifFrame() {
  time++;
  *frame = ui->glWindow->grabFramebuffer();
  gif->addFrame(*frame);
  if (time == 60) {
    timer->stop();
    gifSavePath = NULL;
    gifSavePath = QFileDialog::getSaveFileName(this, NULL, NULL, "GIF (*.gif)");
    if (!gifSavePath.isNull()) gif->save(gifSavePath);
  }
}
