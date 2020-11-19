#include "myvtkimagesource.h"
#include <vtkImageData.h>
#include <vtkObjectFactory.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkInformationVector.h>
#include <vtkInformation.h>
#include <vtkDataObject.h>
#include <vtkSmartPointer.h>


vtkStandardNewMacro(MyVTKImageSource);
MyVTKImageSource::MyVTKImageSource()
{
    this->SetNumberOfInputPorts(0);
    this->SetNumberOfOutputPorts(1);
}
int MyVTKImageSource::RequestData(vtkInformation *vtkNotUsed(request),
                                             vtkInformationVector **inputVector,
                                             vtkInformationVector *outputVector)
{
  // Get the info objects
  vtkInformation *outInfo = outputVector->GetInformationObject(0);

  vtkImageData *output = dynamic_cast<vtkImageData*>(
      outInfo->Get(vtkDataObject::DATA_OBJECT()));

  vtkNew<vtkImageData> data;

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

  output->ShallowCopy(data);

  // Without these lines, the output will appear real but will not work as the input to any other filters
  output->SetExtent(extent);
  outInfo->Set(vtkStreamingDemandDrivenPipeline::UPDATE_EXTENT(),
               extent,
               6);
  outInfo->Set(vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT(),
               extent,
               6);
  return 1;
}
