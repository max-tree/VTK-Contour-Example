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





MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    vtkwidget= new QVTKWidget(this);
    QGridLayout* layout = new QGridLayout(ui->frame);
    layout->addWidget(vtkwidget,1,1);
    ui->frame->setLayout(layout);

    mRenderer =
            vtkSmartPointer<vtkRenderer>::New();
    this->vtkwidget->GetRenderWindow()->AddRenderer(mRenderer);

    QTimer::singleShot(200, this, SLOT(setup()));

}

void MainWindow::CreateData(vtkImageData* data)
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

    vtkSmartPointer<vtkXMLImageDataWriter> writer =
            vtkSmartPointer<vtkXMLImageDataWriter>::New();
    writer->SetFileName("data.vti");

    writer->SetInputData(data);

    writer->Write();
}
void MainWindow::setup()
{
    vtkSmartPointer<vtkNamedColors> colors =
            vtkSmartPointer<vtkNamedColors>::New();


    vtkSmartPointer<vtkImageData> data =
            vtkSmartPointer<vtkImageData>::New();
    CreateData(data);

    // Create an isosurface
    mContourFilter =
            vtkSmartPointer<vtkContourFilter>::New();

    mContourFilter->SetInputData(data);

    mContourFilter->GenerateValues(1, 10, 10); // (numContours, rangeStart, rangeEnd)


    // Map the contours to graphical primitives
    vtkSmartPointer<vtkPolyDataMapper> contourMapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    contourMapper->SetInputConnection(mContourFilter->GetOutputPort());

    // Create an actor for the contours
    vtkSmartPointer<vtkActor> contourActor =
            vtkSmartPointer<vtkActor>::New();
    contourActor->SetMapper(contourMapper);
    contourActor->GetProperty()->SetLineWidth(5);

    // Create the outline
    vtkSmartPointer<vtkOutlineFilter> outlineFilter =
            vtkSmartPointer<vtkOutlineFilter>::New();

    outlineFilter->SetInputData(data);

    vtkSmartPointer<vtkPolyDataMapper> outlineMapper =
            vtkSmartPointer<vtkPolyDataMapper>::New();
    outlineMapper->SetInputConnection(outlineFilter->GetOutputPort());
    vtkSmartPointer<vtkActor> outlineActor =
            vtkSmartPointer<vtkActor>::New();
    outlineActor->SetMapper(outlineMapper);
    outlineActor->GetProperty()->SetColor(colors->GetColor3d("Gray").GetData());
    outlineActor->GetProperty()->SetLineWidth(3);

    mRenderer->AddActor(contourActor);
    mRenderer->AddActor(outlineActor);
    mRenderer->GradientBackgroundOn();
    mRenderer->SetBackground(1,1,1);
    mRenderer->SetBackground2(0,0,0);

    mRenderer->ResetCamera();

    this->vtkwidget->update();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_contourSlider_valueChanged(int value)
{
    mContourFilter->GenerateValues(1, value, value);
    this->vtkwidget->update();
}


