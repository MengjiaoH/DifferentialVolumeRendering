#include "loadPIDX.h"

template<typename T>
std::pair<T, T> compute_range(const std::vector<char> &data) {
  auto minmax =
    std::minmax_element(reinterpret_cast<const T*>(data.data()),
			reinterpret_cast<const T*>(data.data()) + data.size() / sizeof(T));
  return std::make_pair(*minmax.first, *minmax.second);
}

ospcommon::vec2f compute_volume_range(const std::vector<char> &data, const std::string &type) {
  ospcommon::vec2f range(0, 0);
  if (type == "uchar") {
    auto minmax = compute_range<uint8_t>(data);
    range.x = static_cast<float>(minmax.first);
    range.y = static_cast<float>(minmax.second);
  } else if (type == "short") {
    auto minmax = compute_range<int16_t>(data);
    range.x = static_cast<float>(minmax.first);
    range.y = static_cast<float>(minmax.second);
  } else if (type == "ushort") {
    auto minmax = compute_range<uint16_t>(data);
    range.x = static_cast<float>(minmax.first);
    range.y = static_cast<float>(minmax.second);
  } else if (type == "float") {
    auto minmax = compute_range<float>(data);
    range.x = minmax.first;
    range.y = minmax.second;
  } else if (type == "double") {
    auto minmax = compute_range<double>(data);
    range.x = static_cast<float>(minmax.first);
    range.y = static_cast<float>(minmax.second);
    std::cout << "range = " << range << "\n";
  }
  return range;
}

bool computeDivisor(int x, int &divisor) {
    int upperBound = std::sqrt(x);
    for (int i = 2; i <= upperBound; ++i) {
        if (x % i == 0) {
            divisor = i;
            return true;
        }
    }
    return false;
}

ospcommon::vec3i computeGrid(int num)
{
    ospcommon::vec3i grid(1);
    int axis = 0;
    int divisor = 0;
    while (computeDivisor(num, divisor)) {
        grid[axis] *= divisor;
        num /= divisor;
        axis = (axis + 1) % 3;
    }
    if (num != 1) {
        grid[axis] *= num;
    }
    return grid;
}

IDXVar parse_idx_type(const std::string &type) {
    IDXVar var;
    const auto pos = type.find('*');
    if (pos == std::string::npos) {
        var.components = 1;
        var.type = type;
    } else {
        var.components = std::stol(type);
        var.type = type.substr(pos + 1);
    }
    // Convert the type string to one we can give ospray
    if (var.type == "uint8" || var.type == "int8") {
        var.type = "uchar";
    } else if (var.type == "int16") {
        var.type = "short";
    } else if (var.type == "uint16") {
        var.type = "ushort";
    } else if (var.type == "float32") {
        var.type = "float";
    } else if (var.type == "float64") {
        var.type = "double";
    } else {
        throw std::runtime_error("Unsupported IDX datatype!");
    }
    return var;
}

PIDXVolume::PIDXVolume(const std::string &path, const std::string &currentVariableName, size_t currentTimestep)
    : datasetPath(path),currentVariableName(currentVariableName), currentTimestep(currentTimestep)
{
    PIDX_CHECK(PIDX_create_access(&pidxAccess));
    PIDX_CHECK(PIDX_set_mpi_access(pidxAccess, MPI_COMM_WORLD));
    PIDX_create_metadata_cache(&cache);
    currentVariable = -1;
    update();
}

PIDXVolume::~PIDXVolume() {
    PIDX_close_access(pidxAccess);
    //volume.release();
}

void PIDXVolume::update(){

    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    
    PIDX_CHECK(PIDX_file_open(datasetPath.c_str(), PIDX_MODE_RDONLY,
                              pidxAccess, pdims, &pidxFile));
    fullDims.x = pdims[0];
    fullDims.y = pdims[1];
    fullDims.z = pdims[2];
    if (world_rank == 0) {
        std::cout << "currentimestep = " << currentTimestep << std::endl;
        std::cout << "dims " << fullDims.x << " " << fullDims.y << " " << fullDims.z << "\n";
    }
    
    PIDX_CHECK(PIDX_set_current_time_step(pidxFile, currentTimestep));

    if (pidxVars.empty()) {
        int variableCount = 0;
        PIDX_CHECK(PIDX_get_variable_count(pidxFile, &variableCount));
        if (world_rank == 0) {
            std::cout << "Variable count = " << variableCount << "\n";
        }

        for (int i = 0; i < variableCount; ++i) {
            PIDX_CHECK(PIDX_set_current_variable_index(pidxFile, i));
            PIDX_variable variable;
            PIDX_CHECK(PIDX_get_current_variable(pidxFile, &variable));
            pidxVars.push_back(variable->var_name);
            if (currentVariableName.compare(variable->var_name) == 0) {
                if(world_rank == 0)
                    std::cout << "variable name " << variable ->var_name << "\n";
                currentVariable = i;
            }
        }

        if (currentVariable == -1) {
            currentVariable = 0;
            std::cerr << "Variable name is not set. "
                         "Loading the first variable by default" << std::endl;
        }
    }

    MPI_Bcast(&currentVariable, 1, MPI_INT, 0, MPI_COMM_WORLD);

    PIDX_CHECK(PIDX_set_current_variable_index(pidxFile, currentVariable));
    PIDX_CHECK(PIDX_get_current_variable(pidxFile, &var));

    PIDX_CHECK(PIDX_values_per_datatype(var->type_name, &valuesPerSample,
                                        &bitsPerSample));
    const int bytesPerSample = bitsPerSample / 8;

    if (world_rank == 0) {
        std::cout << "Variable type name: " << var->type_name << "\n"
                  << "Values per sample: " << valuesPerSample << "\n"
                  << "Bits per sample: " << bitsPerSample << std::endl;
    }

    const IDXVar idx_var = parse_idx_type(var->type_name);
    type = idx_var.type;
    
    const vec3sz grid = vec3sz(computeGrid(world_size));
    const vec3sz brickDims = vec3sz(fullDims) / grid;
    const vec3sz brickId(world_rank % grid.x, (world_rank / grid.x) % grid.y, world_rank / (grid.x * grid.y));
    
    std::cout << "Rank #" << world_rank << "  brickId = (" << brickId.x << " "
                                                           << brickId.y << " "
                                                           << brickId.z << ")\n";
    std::cout << "Rank #" << world_rank << " brickDims = (" << brickDims.x << " "
                                                            << brickDims.y << " " 
                                                            << brickDims.z << ")\n";
    localDims = brickDims;
    localOffset.x = brickId.x * brickDims.x;
    localOffset.y = brickId.y * brickDims.y;
    localOffset.z = brickId.z * brickDims.z;

    PIDX_point pLocalOffset, pLocalDims;
    PIDX_set_point(pLocalOffset, localOffset.x, localOffset.y, localOffset.z);
    PIDX_set_point(pLocalDims, localDims.x, localDims.y, localDims.z);

    const size_t nLocalVals = localDims.x * localDims.y * localDims.z;
    data.resize(bytesPerSample * valuesPerSample * nLocalVals, 0);
    PIDX_CHECK(PIDX_variable_read_data_layout(var, pLocalOffset, pLocalDims,
                                              data.data(), PIDX_row_major));

    using namespace std::chrono;
    auto startLoad = high_resolution_clock::now();
    PIDX_CHECK(PIDX_close(pidxFile));
    auto endLoad = high_resolution_clock::now();
    const double loadTime = duration_cast<milliseconds>(endLoad - startLoad).count() * 0.001;
    const double bandwidthMB = (data.size() * 1e-6) / loadTime;
    
    if (world_rank == 0) {
        std::cout << "Rank " << world_rank << " load time: " << loadTime << "s\n" << "bandwidth: " << bandwidthMB << " MB/s\n";
        const size_t totalBytes = fullDims.x * fullDims.y * fullDims.z * bytesPerSample * valuesPerSample;
        std::cout << "Aggregate bandwidth: " << (totalBytes * 1e-6) / loadTime << " MB/s\n";
    }

    if (idx_var.components != 1) {
        throw std::runtime_error("Unsupported # of components in type, "
            "only scalar types are supported!");
    }

    ospcommon::vec2f localValueRange = compute_volume_range(data, idx_var.type);
    MPI_Allreduce(&localValueRange.x, &valueRange.x, 1, MPI_FLOAT, MPI_MIN, MPI_COMM_WORLD);
    MPI_Allreduce(&localValueRange.y, &valueRange.y, 1, MPI_FLOAT, MPI_MAX, MPI_COMM_WORLD);

    if(PIDX_close_access(pidxAccess) != PIDX_success)
        throw std::runtime_error("PIDX_close_access");
    if (PIDX_free_metadata_cache(cache) != PIDX_success)
        throw std::runtime_error("PIDX_free_meta_data_cache");
}

