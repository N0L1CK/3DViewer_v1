#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "header/glview.h"
#include <QMainWindow>
#include <QFileDialog>


extern "C"{
    #include "viewer.h"
}

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void vectorInit(obj_t obj);

    obj_t obj;
    QVector<double> vector;



public slots:

    void setRotFieldsValues(double x, double y, double z, double xR, double yR, double zR);




private:
    Ui::MainWindow *ui;
    glView *gl;


signals:

    void sig_Data(obj_t obj);


private slots:
    void on_actionOpen_File_triggered();
};
#endif // MAINWINDOW_H
