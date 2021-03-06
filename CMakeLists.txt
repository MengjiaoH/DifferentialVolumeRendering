cmake_minimum_required(VERSION 3.11)
project(DifferentialVolumeRendering)

set (CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

option (BUILD_VTK "Build VTK Analysis" OFF)
option (BUILD_PIDX "Builg PIDX Analysis" ON)

## Find ospcommon
find_package(ospcommon REQUIRED)
## Find MPI
find_package(MPI REQUIRED)

## Find PIDX
find_package(PIDX REQUIRED)

include_directories(${MPI_CXX_INCLUDE_PATH} ${PIDX_INCLUDE_DIRS})

add_library(libs dataType.h
                 parseArgs.h
                 parseArgs.cpp
                 arcballCamera.h
                 arcballCamera.cpp
                 writePIDX.h
                 writePIDX.cpp)

target_link_libraries(libs ospcommon::ospcommon ${PIDX_LIBRARIES} ${MPI_CXX_LIBRARIES})

if(BUILD_PIDX)
    add_executable(pidx-analysis pidxMain.cpp)
    set_target_properties(pidx-analysis PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON)

    add_library(pidx_libs SHARED pidxUtils.h
                                 loadPIDX.h
                                 loadPIDX.cpp)

    target_link_libraries(pidx_libs libs)

    target_link_libraries(pidx-analysis pidx_libs)   
endif()

if(BUILD_VTK)
    ## Find VTK
    find_package(VTK REQUIRED)
    include(${VTK_USE_FILE})
    include_directories(${VTK_INCLUDE_DIRS})
    
    add_executable(vtk-analysis VTKMain.cpp)

    set_target_properties(vtk-analysis PROPERTIES
        CXX_STANDARD 11
        CXX_STANDARD_REQUIRED ON)

    add_library(vtk_libs SHARED loadVTK.h
                                loadVTK.cpp)

    target_link_libraries(vtk_libs ${VTK_LIBRARIES} pidx_libs)

    target_link_libraries(vtk-analysis vtk_libs)     
endif()