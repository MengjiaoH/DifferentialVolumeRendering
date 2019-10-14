#include "loadVTK.h"

void loadVTK(std::string file, Volume<float> &volume)
{
    std::cout << "Start Loading " << file << std::endl;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    vtkSmartPointer<vtkStructuredGridReader> reader = vtkSmartPointer<vtkStructuredGridReader>::New();
    reader ->SetFileName(file.c_str());
    reader ->Update();
    auto grid = reader ->GetOutput();
    //Get Dimensions
    int dim[3] = {0, 0, 0};
    grid -> GetDimensions(dim);
    // std::cout << " Dimensions " << dim[0] << " " << dim[1] << " " << dim[2] << std::endl;
    volume.dim.x = dim[0]; volume.dim.y = dim[1]; volume.dim.z = dim[2];
    //Get Data Array
    vtkSmartPointer<vtkGeometryFilter> geometryFilter = vtkSmartPointer<vtkGeometryFilter>::New();
    geometryFilter ->SetInputData(grid);
    geometryFilter ->Update();

    vtkPolyData* polydata = geometryFilter ->GetOutput();
    // vtkIdType numberofPointArray = polydata ->GetPointData() ->GetNumberOfArrays();
    // for(vtkIdType i = 0; i < numberofPointArray; i++){
    //     int dataTypeID = polydata ->GetPointData() ->GetArray(i) ->GetDataType();
    //     std::cout << "Array " << i << ": " << polydata ->GetPointData() ->GetArrayName(i)
    //               << " (type: " << dataTypeID << " )" << std::endl;
    // }
    std::string arrayName = "Magnitude";
    // std::string arrayName = "Directions";
    vtkSmartPointer<vtkFloatArray> array = vtkFloatArray::SafeDownCast(polydata->GetPointData()->GetArray(arrayName.c_str()));
    vtkIdType idNumPointsInFile = polydata->GetNumberOfPoints();
    float Max = -1 * std::numeric_limits<float>::infinity();
    float Min = std::numeric_limits<float>::infinity();

    if(array){
        std::cout << "Got array " << arrayName
                << " with " << idNumPointsInFile << " values"
                << std::endl;
        for(int i = 0; i < idNumPointsInFile; i++){
            float value;
            value = array->GetValue(i);
            volume.voxels.push_back(value);
            // std::cout << i << ": " << value << std::endl;
            if(value < Min){
                Min = value;
            }
            if(value > Max){
                Max = value;
            }
        }
    }else{
        std::cout << "The file " << file
                << " does not have a PointData array named " << arrayName
                << std::endl;
    }
    volume.range.x = Min;
    volume.range.y = Max;
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    std::cout << "It took " << time_span.count() << " seconds loading one time step." << std::endl;
}
