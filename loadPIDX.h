#pragma once 

#include <iostream>
#include <vector>
#include <chrono>

#include "dataType.h"
#include "pidxUtils.h"

IDXVar parse_idx_type(const std::string &type);

ospcommon::math::vec3i computeGrid(int num);

