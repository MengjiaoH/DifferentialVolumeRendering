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

struct tileList
{
    std::vector<ospcommon::math::vec2i> tileID;
    tileList(std::vector<ospcommon::math::vec2i> tileID);
};

tileList::tileList(std::vector<ospcommon::math::vec2i> tileID) 
    :tileID(tileID)
{}


timesteps::timesteps(const int timeStep, const std::string &fileDir)
    : timeStep(timeStep), fileDir(fileDir)
{}


using vec3sz = ospcommon::math::vec_t<size_t, 3>;

struct IDXVar {
    size_t components;
    std::string type;
};

struct sort_timestep
{
    inline bool operator() (const timesteps &a, const timesteps &b) {
        return a.timeStep < b.timeStep;
    }
};
