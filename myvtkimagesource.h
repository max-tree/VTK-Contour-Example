#ifndef MYVTKIMAGESOURCE_H
#define MYVTKIMAGESOURCE_H

#include <vtkImageAlgorithm.h>
#include <vtkImageData.h>

class MyVTKImageSource : public vtkImageAlgorithm
{
public:
  static MyVTKImageSource *New();
  vtkTypeMacro(MyVTKImageSource,vtkImageAlgorithm);

  MyVTKImageSource();

protected:

  int RequestData(vtkInformation *, vtkInformationVector **, vtkInformationVector *) override;

private:
  MyVTKImageSource(const MyVTKImageSource&);  // Not implemented.
  void operator=(const MyVTKImageSource&);  // Not implemented.
};


#endif // MYVTKIMAGESOURCE_H
