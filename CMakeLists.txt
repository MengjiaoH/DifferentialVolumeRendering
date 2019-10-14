cmake_minimum_required(VERSION 3.11)
project(DifferentialVolumeRendering)

## Find VTK
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})
include_directories(${VTK_INCLUDE_DIRS})

## Find MPI
find_package(MPI REQUIRED)

## Find PIDX
find_package(PIDX REQUIRED)
include_directories(${MPI_CXX_INCLUDE_PATH} ${PIDX_INCLUDE_DIRS})

## Find ospcommon
find_package(ospcommon REQUIRED)

add_executable(vtk-analysis VTKMain.cpp)


set_target_properties(vtk-analysis PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON)

add_library(vtk_libs SHARED dataType.h
                        loadVTK.h
                        loadVTK.cpp
                        parseArgs.h
                        parseArgs.cpp)
target_link_libraries(vtk_libs ospcommon::ospcommon ${VTK_LIBRARIES})

target_link_libraries(vtk-analysis vtk_libs)     


add_executable(pidx-analysis pidxMain.cpp)
set_target_properties(pidx-analysis PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON)

add_library(pidx_libs SHARED pidxUtils.h
                             dataType.h
                             loadPIDX.h
                             loadPIDX.cpp
                             parseArgs.h
                             parseArgs.cpp)

target_link_libraries(pidx_libs ospcommon::ospcommon ${PIDX_LIBRARIES} ${MPI_CXX_LIBRARIES})

target_link_libraries(vtk-analysis vtk_libs)   