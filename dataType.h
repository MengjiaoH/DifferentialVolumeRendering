#pragma once 

#include <iostream>
#include <vector>

#include "ospcommon/math/vec.h"
#include "ospcommon/math/box.h"

#include "PIDX.h"

struct timesteps
{
    int timeStep;
    std::string fileDir;
    timesteps(const int timestep, const std::string &fileDir);
};

template<typename T> struct Volume
{
    std::vector<T> voxels;
    ospcommon::math::vec2f range;
    ospcommon::math::vec3i dim;
};

template<typename T> struct DifferentialVolume
{
    std::vector<int> indices;
    std::vector<T> values;
};


timesteps::timesteps(const int timeStep, const std::string &fileDir)
    : timeStep(timeStep), fileDir(fileDir)
{}


using vec3sz = ospcommon::math::vec_t<size_t, 3>;

struct IDXVar {
    size_t components;
    std::string type;
};

struct PIDXVolume {
    std::string datasetPath;
    PIDX_access pidxAccess;
    PIDX_file pidxFile;
    PIDX_file outpidxFile;
    PIDX_metadata_cache cache;
    PIDX_point pdims;
    std::vector<std::string> pidxVars;

    PIDX_variable var;
    int resolution;
    vec3sz fullDims, localDims, localOffset;
    ospcommon::math::box3f localRegion;
    ospcommon::math::vec2f valueRange;
    std::vector<char> data; 
    int valuesPerSample = 0;
    int bitsPerSample = 0;
    std::string type;

    // UI data
    std::string currentVariableName;
    int currentVariable;
    size_t currentTimestep;
                            
    PIDXVolume(const std::string &path, 
               const std::string &currentVariableName, 
               size_t currentTimestep);
    
    PIDXVolume(const PIDXVolume &p) = delete;
    PIDXVolume& operator=(const PIDXVolume &p) = delete;
    ~PIDXVolume();
                            
    private:
        void update();
        void set_pidx_file(int ts);
        void set_pidx_variable();
};