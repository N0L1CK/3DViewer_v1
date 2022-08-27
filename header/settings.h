#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class Settings;
}  // namespace Ui

class Settings : public QDialog {
  Q_OBJECT

 public:
  explicit Settings(QWidget *parent = nullptr);
  ~Settings();

 private slots:
  void on_vertex_size_decr_clicked();
  void on_vertex_size_incr_clicked();
  void on_edge_width_decr_clicked();
  void on_edge_width_incr_clicked();
  void on_set_cancel_clicked();
  void on_set_default_clicked();
  void on_set_apply_clicked();

 private:
  Ui::Settings *ui;
  QString config_file;
  QSettings *settings;
  void load_settings();
  void save_settings();
  void set_default_settings();
};

#endif  // SETTINGS_H
