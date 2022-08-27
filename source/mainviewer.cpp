#include "header/mainviewer.h"
#include "ui_mainviewer.h"
#include "header/viewer.h"

MainViewer::MainViewer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainViewer)
{
    ui->setupUi(this);
    this->setWindowTitle("3DViewer v1.0");
    gl = new glView();
    connect(this, &MainViewer::sig_Data, gl, &glView::slot_Data);

    connect(this, SIGNAL(on_translate_clicked()), gl, SLOT(set_move_x(int);set_move_y(int);set_move_z(int)));
    connect(this, SIGNAL(on_rotate_clicked()), gl, SLOT(set_rot_x(int);set_rot_y(int);set_rot_z(int)));
    connect(this, SIGNAL(on_scale_clicked()), gl, SLOT(set_scale(int)));
    connect(this, SIGNAL(set_move_x(int)), gl, SLOT(get_move_x(int)));
    connect(this, SIGNAL(set_move_y(int)), gl, SLOT(get_move_y(int)));
    connect(this, SIGNAL(set_move_z(int)), gl, SLOT(get_move_z(int)));
    connect(this, SIGNAL(set_rot_x(int)), gl, SLOT(get_rot_x(int)));
    connect(this, SIGNAL(set_rot_y(int)), gl, SLOT(get_rot_y(int)));
    connect(this, SIGNAL(set_rot_z(int)), gl, SLOT(get_rot_z(int)));
    connect(this, SIGNAL(set_scale(int)), gl, SLOT(get_scale(int)));

}

MainViewer::~MainViewer()
{
    delete gl;
    delete ui;
}

void MainViewer::on_load_file_clicked()
{
    init_obj(&obj,1,1);
    QString path = QFileDialog::getOpenFileName(this, ("Open .obj file"),  QDir::currentPath(), "*.obj");
    int error_code = open_file(qPrintable(path), &obj);
    if (error_code != OK && path.length() > 0) {
        ui->label_file->setText("Incorrect File");
    } else if (obj.vertices != NULL && path.length() > 0) {
        qsizetype idx = path.lastIndexOf('/') + 1;
        QString file_name = path.right(path.size() - idx);
        ui->label_file->setText(file_name);
        ui->label_file_back->setText(file_name);
        ui->cnt_vertices->setText(QString::number(obj.vertex_cnt));
        ui->cnt_edges->setText(QString::number(obj.edge_cnt));
        init_ui();
        emit sig_Data(obj);
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
        emit set_move_x(ui->spin_move_x->value()-value);
        ui->spin_move_x->setValue(value);
    }
    if (value == 0)
    {
        ui->slider_move_x->setValue(0);

    }
}

void MainViewer::on_slider_move_y_valueChanged(int value) {
    if (ui->spin_move_y->value() != value) {
        emit set_move_y(ui->spin_move_y->value()-value);
        ui->spin_move_y->setValue(value);
    }
    if (value == 0)
    {
        ui->slider_move_y->setValue(0);
    }
}

void MainViewer::on_slider_move_z_valueChanged(int value) {
    if (ui->spin_move_z->value() != value) {
        emit set_move_z(ui->spin_move_z->value()-value);
        ui->spin_move_z->setValue(value);
    }
    if (value == 0)
    {
        ui->slider_move_z->setValue(0);
    }
}

void MainViewer::on_slider_rot_x_valueChanged(int value) {
    if (ui->spin_rot_x->value() != value) {
        emit set_rot_x(ui->spin_rot_x->value()-value);
        ui->spin_rot_x->setValue(value);
    }
    if (value == 0)
    {
        ui->slider_rot_x->setValue(0);
    }
}

void MainViewer::on_slider_rot_y_valueChanged(int value) {
    if (ui->spin_rot_y->value() != value) {
        emit set_rot_y(ui->spin_rot_y->value()-value);
        ui->spin_rot_y->setValue(value);
    }
    if (value == 0)
    {
        ui->slider_rot_y->setValue(0);
    }
}

void MainViewer::on_slider_rot_z_valueChanged(int value) {
    if (ui->spin_rot_z->value() != value) {
        emit set_rot_z(ui->spin_rot_z->value()-value);
        ui->spin_rot_z->setValue(value);
    }
    if (value == 0)
    {
        ui->slider_rot_z->setValue(0);
    }
}

void MainViewer::on_slider_scale_valueChanged(int value) {
    if (ui->spin_scale->value() != value && ui->spin_scale->value() < value) {
        emit set_scale(1);
        ui->spin_scale->setValue(value);
    }
    if (ui->spin_scale->value() != value && ui->spin_scale->value() > value) {
        emit set_scale(-1);
        ui->spin_scale->setValue(value);
    }
    if (value == 0)
    {
        ui->slider_scale->setValue(0);
    }
}

void MainViewer::on_settings_clicked()
{
    settings = new Settings(this);
    QPoint p = MainViewer::pos();
    settings->move(p.x() - 200, p.y() + 0);
    settings->show();
}


void MainViewer::on_translate_clicked()
{

    ui->slider_move_x->setSliderPosition(ui->spin_move_x->value());
    ui->slider_move_y->setSliderPosition(ui->spin_move_y->value());
    ui->slider_move_z->setSliderPosition(ui->spin_move_z->value());

    emit set_move_x(ui->spin_move_x->value());
    emit set_move_y(ui->spin_move_y->value());
    emit set_move_z(ui->spin_move_z->value());

}


void MainViewer::on_rotate_clicked()
{

    ui->slider_rot_x->setSliderPosition(ui->spin_rot_x->value());
    ui->slider_rot_y->setSliderPosition(ui->spin_rot_y->value());
    ui->slider_rot_z->setSliderPosition(ui->spin_rot_z->value());

    emit set_rot_x(ui->spin_rot_x->value());
    emit set_rot_y(ui->spin_rot_y->value());
    emit set_rot_z(ui->spin_rot_z->value());

}


void MainViewer::on_scale_clicked()
{
    ui->slider_scale->setSliderPosition(ui->spin_scale->value());

    emit set_scale(ui->spin_scale->value());
}


void MainViewer::on_screenshot_clicked()
{
    QString savePath = NULL;
    savePath = QFileDialog::getSaveFileName(this, NULL, NULL, "JPEG (*.jpeg) ;; BMP (*.bmp)");
    if (!savePath.isNull()) ui->glWindow->grabFramebuffer().save(savePath, NULL, 100);

}


void MainViewer::on_gif_clicked()
{
    gif = new QGifImage;
    frame = new QImage;
    timer = new QTimer(this);
    time = 0;
    connect(timer, SIGNAL(timeout()), this, SLOT(saveGifFrame()));
    timer->start(100);
}
void MainViewer::saveGifFrame()
{
    time++;
    *frame = ui->glWindow->grabFramebuffer();
    gif->addFrame(*frame);
    if (time == 60) {
        timer->stop();
        gifSavePath = NULL;
        gifSavePath = QFileDialog::getSaveFileName(this, NULL, NULL, "GIF (*.gif)");
        if (!gifSavePath.isNull())
            gif->save(gifSavePath);
    }
}
