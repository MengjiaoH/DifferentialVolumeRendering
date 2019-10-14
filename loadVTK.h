#pragma once 

#include <iostream>
#include <fstream>
#include <limits>
#include <chrono>

#include <vtkSmartPointer.h>
#include <vtkStructuredGrid.h>
#include <vtkPolyData.h>
#include <vtkPointData.h>
#include <vtkFloatArray.h>
#include <vtkStructuredGridReader.h>
#include <vtkGeometryFilter.h>

#include "dataType.h"

void loadVTK(std::string file, Volume<float> &volume);


