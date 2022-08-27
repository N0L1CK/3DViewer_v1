#include "header/settings.h"

#include "ui_settings.h"

Settings::Settings(QWidget *parent) : QDialog(parent), ui(new Ui::Settings) {
  ui->setupUi(this);
  config_file = QCoreApplication::applicationDirPath() + "/settings.conf";
  settings = new QSettings(config_file, QSettings::NativeFormat);
  load_settings();
  ui->vertex_color_r->setSuffix(" R");
  ui->vertex_color_g->setSuffix(" G");
  ui->vertex_color_b->setSuffix(" B");
  ui->edge_color_r->setSuffix(" R");
  ui->edge_color_g->setSuffix(" G");
  ui->edge_color_b->setSuffix(" B");
  ui->bg_color_r->setSuffix(" R");
  ui->bg_color_g->setSuffix(" G");
  ui->bg_color_b->setSuffix(" B");
}

Settings::~Settings() { delete ui; }

void Settings::load_settings() {
  ui->vertex_color_r->setValue(settings->value("vertex_color_r", 138).toInt());
  ui->vertex_color_g->setValue(settings->value("vertex_color_g", 183).toInt());
  ui->vertex_color_b->setValue(settings->value("vertex_color_b", 187).toInt());
  ui->vertex_size->setValue(settings->value("vertex_size", 1).toInt());
  ui->vertex_shape->setCurrentText(
      settings->value("vertex_shape", "None").toString());
  ui->edge_color_r->setValue(settings->value("edge_color_r", 138).toInt());
  ui->edge_color_g->setValue(settings->value("edge_color_g", 183).toInt());
  ui->edge_color_b->setValue(settings->value("edge_color_b", 187).toInt());
  ui->edge_width->setValue(settings->value("edge_width", 1).toInt());
  ui->edge_type->setCurrentText(
      settings->value("edge_type", "Solid").toString());
  ui->bg_color_r->setValue(settings->value("bg_color_r", 33).toInt());
  ui->bg_color_g->setValue(settings->value("bg_color_g", 33).toInt());
  ui->bg_color_b->setValue(settings->value("bg_color_b", 33).toInt());
  ui->projection_type->setCurrentText(
      settings->value("projection_type", "Central").toString());
}

void Settings::save_settings() {
  settings->setValue("vertex_color_r", QVariant::fromValue(ui->vertex_color_r));
  settings->setValue("vertex_color_g", QVariant::fromValue(ui->vertex_color_g));
  settings->setValue("vertex_color_b", QVariant::fromValue(ui->vertex_color_b));
  settings->setValue("vertex_size", QVariant::fromValue(ui->vertex_size));
  settings->setValue("vertex_shape", QVariant::fromValue(ui->vertex_shape));
  settings->setValue("edge_color_r", QVariant::fromValue(ui->edge_color_r));
  settings->setValue("edge_color_g", QVariant::fromValue(ui->edge_color_g));
  settings->setValue("edge_color_b", QVariant::fromValue(ui->edge_color_b));
  settings->setValue("edge_width", QVariant::fromValue(ui->edge_width));
  settings->setValue("edge_type", QVariant::fromValue(ui->edge_type));
  settings->setValue("bg_color_r", QVariant::fromValue(ui->bg_color_r));
  settings->setValue("bg_color_g", QVariant::fromValue(ui->bg_color_g));
  settings->setValue("bg_color_b", QVariant::fromValue(ui->bg_color_b));
  settings->setValue("projection_type",
                     QVariant::fromValue(ui->projection_type));
}

void Settings::set_default_settings() {
  settings->setValue("vertex_color_r", QVariant::fromValue(138));
  settings->setValue("vertex_color_g", QVariant::fromValue(183));
  settings->setValue("vertex_color_b", QVariant::fromValue(187));
  settings->setValue("vertex_size", QVariant::fromValue(1));
  settings->setValue("vertex_shape", QVariant::fromValue(0));
  settings->setValue("edge_color_r", QVariant::fromValue(138));
  settings->setValue("edge_color_g", QVariant::fromValue(183));
  settings->setValue("edge_color_b", QVariant::fromValue(187));
  settings->setValue("edge_width", QVariant::fromValue(1));
  settings->setValue("edge_type", QVariant::fromValue(0));
  settings->setValue("bg_color_r", QVariant::fromValue(33));
  settings->setValue("bg_color_g", QVariant::fromValue(33));
  settings->setValue("bg_color_b", QVariant::fromValue(33));
  settings->setValue("projection_type", QVariant::fromValue(0));
}

void Settings::on_vertex_size_decr_clicked() {
  if (ui->vertex_size->value() > 1) {
    ui->vertex_size->setValue(ui->vertex_size->value() - 1);
  }
}

void Settings::on_vertex_size_incr_clicked() {
  if (ui->vertex_size->value() < 10) {
    ui->vertex_size->setValue(ui->vertex_size->value() + 1);
  }
}

void Settings::on_edge_width_decr_clicked() {
  if (ui->edge_width->value() > 1) {
    ui->edge_width->setValue(ui->edge_width->value() - 1);
  }
}

void Settings::on_edge_width_incr_clicked() {
  if (ui->edge_width->value() < 10) {
    ui->edge_width->setValue(ui->edge_width->value() + 1);
  }
}

void Settings::on_set_cancel_clicked() { hide(); }

void Settings::on_set_default_clicked() {
  set_default_settings();
  load_settings();
}

void Settings::on_set_apply_clicked() { save_settings(); }
