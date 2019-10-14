#pragma once 

#include <iostream>
#include <vector>

#include "ospcommon/math/vec.h"
#include "ospcommon/math/box.h"


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


