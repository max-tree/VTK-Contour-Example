//-------------------------------------------------------
// Filename: mainwindow.cpp
//
// Description:  The cpp file for the qt5 bullet bouncy ball example.
//
// Creator:  Professor Corey McBride for MEEN 570 - Brigham Young University
//
// Creation Date: 11/22/16
//
// Owner: Corey McBride
//-------------------------------------------------------
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include "QVTKWidget.h"
#include <vtkSmartPointer.h>
#include <vtkContourFilter.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

protected slots:
        void setup();
        void on_contourSlider_valueChanged(int);

protected:
    void CreateData(vtkImageData *data);


private:
  Ui::MainWindow *ui;
  QVTKWidget* vtkwidget;

  vtkSmartPointer<vtkContourFilter> mContourFilter;
  vtkSmartPointer<vtkRenderer> mRenderer;




};

#endif // MAINWINDOW_H
