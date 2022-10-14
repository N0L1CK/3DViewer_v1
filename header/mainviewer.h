#ifndef MAINVIEWER_H
#define MAINVIEWER_H

#include <QFileDialog>
#include <QMainWindow>
#include <QTimer>

#include "glview.h"
#include "qgifimage.h"
#include "settings.h"

extern "C" {
#include "header/viewer.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainViewer;
}
QT_END_NAMESPACE

class MainViewer : public QMainWindow {
  Q_OBJECT

 public:
  MainViewer(QWidget *parent = nullptr);
  ~MainViewer();
  void get_settings();

 private slots:
  void on_translate_clicked();
  void on_rotate_clicked();
  void on_scale_clicked();
  void on_load_file_clicked();
  void on_slider_move_x_valueChanged(int value);
  void on_slider_move_y_valueChanged(int value);
  void on_slider_move_z_valueChanged(int value);
  void on_slider_rot_x_valueChanged(int value);
  void on_slider_rot_y_valueChanged(int value);
  void on_slider_rot_z_valueChanged(int value);
  void on_slider_scale_valueChanged(int value);
  void on_settings_clicked();
  void on_screenshot_clicked();
  void on_gif_clicked();
  void saveGifFrame();
  void settings_handler();

 private:
  Ui::MainViewer *ui;
  Settings *settings;
  glView *gl;
  obj_t objMain;
  void init_ui();
  QGifImage *gif;
  QImage *frame;
  QTimer *timer;
  int time;
  QString gifSavePath;
};
#endif  // MAINVIEWER_H
