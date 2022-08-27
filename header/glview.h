#ifndef GLVIEW_H
#define GLVIEW_H

#define GL_SILENCE_DEPRECATION

#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QTimer>
#include <QTime>
#include <QKeyEvent>
#include <GL/glu.h>
#include <QFileDialog>

extern "C" {
    #include "header/viewer.h"
}
static bool project;
static obj_t objx;



class glView : public QOpenGLWidget
{
    Q_OBJECT


private:
    QTimer *timer;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void DrawGrid(float cx, float cy, float step);
    void paintGL(bool project);
    void paintGL() override;
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    //void keyPressEvent(QKeyEvent *e) override;
    void wheelEvent(QWheelEvent* pe) override;
    void drawAxis();
    QPoint mPos;
    GLfloat ratio;
    void DrawPoint(double x, double y, double z);
    void DrawObject(obj_t objx);

public:
    glView(QWidget *parent = nullptr);
    double xRot, yRot, zRot, nSca, xPos, yPos, zPos;
    double xR, yR, zR, x, y, z;
    void updateFrame();

private slots:
    void Updater();

public slots:
        void slot_Data(obj_t obj);
        void get_rot_x(int value);
        void get_rot_y(int value);
        void get_rot_z(int value);
        void get_scale(int value);
        void get_move_x(int value);
        void get_move_y(int value);
        void get_move_z(int value);

signals:
    void mouseRotTrigger(double x, double y, double z, double xR, double yR, double zR);
    void pressKey(bool x);

};

#endif // GLVIEW_H

