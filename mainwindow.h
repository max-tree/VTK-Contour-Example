//-------------------------------------------------------
// Filename: mainwindow.cpp
//
// Description:  The cpp file for the qt5 bullet bouncy ball example.
//
// Creator:  Professor Corey McBride for MEEN 570 - Brigham Young University
//
// Creation Date: 11/8/2018
//
// Owner: Corey McBride
//-------------------------------------------------------
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QVTKOpenGLWidget.h>
#include <vtkSmartPointer.h>
#include <vtkContourFilter.h>
#include <vtkImageData.h>
#include "myvtkimagesource.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void save_data_to_file(vtkImageData* data);

protected slots:
    void setup();
    void on_contourSlider_valueChanged(int);

private:
    Ui::MainWindow *ui;
    QVTKOpenGLWidget* mQVtkWidget;

    vtkNew<vtkContourFilter> mContourFilter;
    vtkNew<MyVTKImageSource> mMyVTKImageSourceFilter;
    vtkNew<vtkRenderer> mRenderer;
};

#endif // MAINWINDOW_H
