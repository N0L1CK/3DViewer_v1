#include "header/mainwindow.h"
#include "header/viewer.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    gl = new glView();

    ui->setupUi(this);
    connect(ui->glWindow, &glView::mouseRotTrigger, this, &MainWindow::setRotFieldsValues);
    connect(this, &MainWindow::sig_Data, gl, &glView::slot_Data);


}

MainWindow::~MainWindow()
{ 
    delete gl;
    delete ui;
}




void MainWindow::setRotFieldsValues(double x, double y, double z, double xR, double yR, double zR)
{
    ui->posX->setValue(x);
    ui->posY->setValue(y);
    ui->posZ->setValue(z);
    ui->rotateX->setValue(xR);
    ui->rotateY->setValue(yR);
    ui->rotateZ->setValue(zR);
}



void MainWindow::on_actionOpen_File_triggered()
{
    obj = {NULL, 0, NULL, 0};
    QString str = QFileDialog::getOpenFileName();
    if (open_file(qPrintable(str), &obj) && str.length() > 0) {
        statusBar()->showMessage("Incorrect File");
        ui->statusBar->setStyleSheet("color: red");

    } else if (obj.vertices != NULL && str.length() > 0){
        //statusBar()->showMessage("Correct File");

        ui->label_9->setText(" " + str);
        ui->statusBar->setStyleSheet("color: white");
        ui->label_10->setText(" Vertex: " + QString::number(obj.vertex_cnt) + " Edges: " + QString::number(obj.edge_cnt));
        emit sig_Data(obj);


    }
    else
    {
        statusBar()->showMessage("");
        ui->label_10->setText("");
        ui->label_9->setText("");
    }
}

