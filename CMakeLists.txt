cmake_minimum_required(VERSION 3.11)
project(DifferentialVolumeRendering)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

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
find_package(ospray REQUIRED)

add_library(libs dataType.h
                 parseArgs.h
                 parseArgs.cpp)

target_link_libraries(libs ${PIDX_LIBRARIES} ospray::ospray ospcommon::ospcommon)

add_executable(vtk-analysis VTKMain.cpp)

set_target_properties(vtk-analysis PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON)

add_library(vtk_libs SHARED loadVTK.h
                            loadVTK.cpp)

target_link_libraries(vtk_libs ospcommon::ospcommon ${VTK_LIBRARIES})

target_link_libraries(vtk-analysis vtk_libs libs)     


add_executable(pidx-analysis pidxMain.cpp)
set_target_properties(pidx-analysis PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED ON)

add_library(pidx_libs SHARED pidxUtils.h
                             loadPIDX.h
                             loadPIDX.cpp)

target_link_libraries(pidx_libs ospcommon::ospcommon ${PIDX_LIBRARIES} ${MPI_CXX_LIBRARIES})

target_link_libraries(pidx-analysis pidx_libs libs)   
