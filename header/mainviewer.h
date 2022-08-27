#ifndef MAINVIEWER_H
#define MAINVIEWER_H

#include <QMainWindow>
#include <QFileDialog>
#include "header/glview.h"
#include "header/settings.h"
#include "qgifimage.h"


extern "C"{
    #include "header/viewer.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainViewer; }
QT_END_NAMESPACE

class MainViewer : public QMainWindow
{
    Q_OBJECT

public:
    MainViewer(QWidget *parent = nullptr);
    ~MainViewer();
    obj_t obj;


private slots:

    void on_load_file_clicked();
    void on_slider_move_x_valueChanged(int value);
    void on_slider_move_y_valueChanged(int value);
    void on_slider_move_z_valueChanged(int value);
    void on_slider_rot_x_valueChanged(int value);
    void on_slider_rot_y_valueChanged(int value);
    void on_slider_rot_z_valueChanged(int value);
    void on_slider_scale_valueChanged(int value);
    void on_settings_clicked();

    void on_translate_clicked();

    void on_rotate_clicked();

    void on_scale_clicked();

    void on_screenshot_clicked();

    void on_gif_clicked();

    void saveGifFrame();

signals:

    void valueChanged(int value);
    void sig_Data(obj_t obj);
    void set_scale(int value);
    void set_move_x(int value);
    void set_move_y(int value);
    void set_move_z(int value);
    void set_rot_x(int value);
    void set_rot_y(int value);
    void set_rot_z(int value);


private:
    Ui::MainViewer *ui;
    Settings *settings;
    glView *gl;
    void init_ui();
    QGifImage *gif;
    QImage *frame;
    QTimer *timer;
    int time;
    QString gifSavePath;
};
#endif // MAINVIEWER_H
