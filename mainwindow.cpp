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
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vtkCamera.h>

#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkInteractorStyleUser.h>
#include <vtkProperty.h>
#include <vtkOutlineFilter.h>
#include <vtkCommand.h>
#include <vtkImageData.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkContourFilter.h>
#include <vtkXMLImageDataWriter.h>
#include <vtkNamedColors.h>
#include <QVTKOpenGLWidget.h>
#include <vtkImageData.h>
#include <vtkGenericOpenGLRenderWindow.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mQVtkWidget= new QVTKOpenGLWidget(this);

    QGridLayout* layout = new QGridLayout(ui->frame);
    layout->addWidget(mQVtkWidget,1,1);
    ui->frame->setLayout(layout);

    vtkNew<vtkGenericOpenGLRenderWindow> window;
    mQVtkWidget->SetRenderWindow(window);
    window->AddRenderer(mRenderer);
    setup();
}

void MainWindow::save_data_to_file(vtkImageData* data)
{
    vtkNew<vtkXMLImageDataWriter> writer;
    writer->SetFileName("data.vti");
    writer->SetInputData(data);
    writer->Write();
}

void MainWindow::create_data(vtkImageData* data)
{
    data->SetExtent(-25,25,-25,25,0,0);

    data->AllocateScalars(VTK_DOUBLE,1);

    int* extent = data->GetExtent();

    for (int y = extent[2]; y <= extent[3]; y++)
    {
        for (int x = extent[0]; x <= extent[1]; x++)
        {
            double* pixel = static_cast<double*>(data->GetScalarPointer(x,y,0));
            pixel[0] = sqrt(pow(x,2.0) + pow(y,2.0));
        }
    }

    // save_data_to_file(data);
}
void MainWindow::setup()
{
    vtkNew<vtkNamedColors> colors;

    vtkNew<vtkImageData> data;
    create_data(data);

    // Create an isosurface
    mContourFilter->SetInputData(data);
    mContourFilter->GenerateValues(1, 10, 10); // (numContours, rangeStart, rangeEnd)


    // Map the contours to graphical primitives
    vtkNew<vtkPolyDataMapper> contourMapper;
    contourMapper->SetInputConnection(mContourFilter->GetOutputPort());

    // Create an actor for the contours
    vtkNew<vtkActor> contourActor;
    contourActor->SetMapper(contourMapper);
    contourActor->GetProperty()->SetLineWidth(5);

    // Create the outline
    vtkNew<vtkOutlineFilter> outlineFilter;

    outlineFilter->SetInputData(data);

    vtkNew<vtkPolyDataMapper> outlineMapper;
    outlineMapper->SetInputConnection(outlineFilter->GetOutputPort());
    vtkNew<vtkActor> outlineActor;
    outlineActor->SetMapper(outlineMapper);
    outlineActor->GetProperty()->SetColor(colors->GetColor3d("Gray").GetData());
    outlineActor->GetProperty()->SetLineWidth(3);

    mRenderer->AddActor(contourActor);
    mRenderer->AddActor(outlineActor);
    mRenderer->GradientBackgroundOn();
    mRenderer->SetBackground(1,1,1);
    mRenderer->SetBackground2(0,0,0);

    mRenderer->ResetCamera();
    this->mQVtkWidget->GetRenderWindow()->Render();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_contourSlider_valueChanged(int value)
{
    mContourFilter->GenerateValues(1, value, value);
    this->mQVtkWidget->GetRenderWindow()->Render();
}


