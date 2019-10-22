#pragma once 

#include <iostream>
#include <vector>
#include <chrono>

#include "PIDX.h"

#include "dataType.h"
#include "pidxUtils.h"

IDXVar parse_idx_type(const std::string &type);

ospcommon::math::vec3i computeGrid(int num);

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

    std::vector<double> voxels;
    // UI data
    std::string currentVariableName;
    int currentVariable;
    size_t currentTimestep;
                            
    PIDXVolume(const std::string &path, 
               const std::string &currentVariableName, 
               size_t currentTimestep);
    
    //PIDXVolume(const PIDXVolume &p) = delete;
    // PIDXVolume& operator=(const PIDXVolume &p) = delete;
    ~PIDXVolume();
                            
    private:
        void update();
        void set_pidx_file(int ts);
        void set_pidx_variable();
};
