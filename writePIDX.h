#pragma once

#include <iostream>
#include <vector>

#include "PIDX.h"

#include "ospcommon/math/vec.h"

#include "pidxUtils.h"

using vec3sz = ospcommon::math::vec_t<size_t, 3>;


struct writePIDX
{
    PIDX_access pidxAccess;
    PIDX_file outpidxFile;

    PIDX_metadata_cache cache;

    vec3sz fullDims, localDims, localOffset;
    PIDX_point global_size, pLocalOffset, pLocalDims;

    // std::vector<std::vector<float>> volumes;

    writePIDX(ospcommon::math::vec3i globalDims);


    // data
    void calculate_per_process_offsets();

    void create_pidx_point_and_access();

    void set_pidx_file(int ts, std::string outputDir);
    void set_pidx_variable(std::vector<char> data, std::string currentVariableName, const std::string dataType);

    void writeOutFile(std::vector<std::vector<float>> volumes, std::string dataType);
    void writeOutPIDXFile(std::vector<std::vector<double>> volumes, std::string dataType);
};

