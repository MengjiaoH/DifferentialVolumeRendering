#include "writePIDX.h"

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


ospcommon::math::vec3i computeGrid(int num)
{
    ospcommon::math::vec3i grid(1);
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

writePIDX::writePIDX(ospcommon::math::vec3i globalDims)
{
    fullDims.x = globalDims.x;
    fullDims.y = globalDims.y;
    fullDims.z = globalDims.z;   
    // volumes = volumes;

    calculate_per_process_offsets();
    create_pidx_point_and_access();
}

void writePIDX::calculate_per_process_offsets()
{
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

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
}

void writePIDX::create_pidx_point_and_access()
{
    PIDX_set_point(global_size, fullDims.x, fullDims.y, fullDims.z);
    PIDX_set_point(pLocalOffset, localOffset.x, localOffset.y, localOffset.z);
    PIDX_set_point(pLocalDims, localDims.x, localDims.y, localDims.z);
    
    //  Creating access
    PIDX_CHECK(PIDX_create_access(&pidxAccess));
    PIDX_CHECK(PIDX_set_mpi_access(pidxAccess, MPI_COMM_WORLD));
    PIDX_create_metadata_cache(&cache);
}


void writePIDX::set_pidx_file(int ts, std::string outputDir)
{
    PIDX_return_code ret;
    // Create IDX file
    // std::string output_file_name = "/home/sci/mengjiao/Desktop/pidx_loader/data/" + std::to_string(currentTimestep) + ".idx";
    // PIDX_point global_size;
    // PIDX_set_point(global_size, fullDims.x, fullDims.y, fullDims.z);

    ret = PIDX_file_create(outputDir.c_str(), PIDX_MODE_CREATE, pidxAccess, global_size, &outpidxFile);
    if (ret != PIDX_success) throw std::runtime_error("PIDX_file_create\n");
    
    PIDX_set_current_time_step(outpidxFile, ts);
    PIDX_set_variable_count(outpidxFile, 1);

    PIDX_set_meta_data_cache(outpidxFile, cache);
    PIDX_set_io_mode(outpidxFile, PIDX_IDX_IO);
    
    PIDX_set_block_count(outpidxFile, 128);
    PIDX_set_block_size(outpidxFile, 15);

    PIDX_set_cache_time_step(outpidxFile, 0);
    
    PIDX_set_compression_type(outpidxFile, PIDX_CHUNKING_ZFP);
}

void writePIDX::set_pidx_variable(std::vector<char> data, std::string currentVariableName, const std::string dataType)
{
    PIDX_return_code ret = 0;
    std::vector<char> name(currentVariableName.c_str(), currentVariableName.c_str() + currentVariableName.size() + 1);
    // create variable 
    PIDX_variable var;
    
    if(dataType == "float"){
        char* temp_type_name = "1*float32";
        ret = PIDX_variable_create(name.data(), sizeof(float) * 1 * 8, temp_type_name, &var);
    }else{
        char* temp_type_name = "1*float64";
        ret = PIDX_variable_create(name.data(), sizeof(double) * 1 * 8, temp_type_name, &var);
    }
    
    if(ret != PIDX_success) throw std::runtime_error("PIDX_variable_create");

    ret = PIDX_variable_write_data_layout(var, pLocalOffset, pLocalDims, data.data(), PIDX_row_major);
    if(ret != PIDX_success) throw std::runtime_error("PIDX_variable_write_data_layout");
    
    ret = PIDX_append_and_write_variable(outpidxFile, var);
    if(ret != PIDX_success) throw std::runtime_error("PIDX_append_and_write_variable");

    return;
}

void writePIDX::writeOutFile(std::vector<std::vector<float>> volumes, std::string dataType){
    // std::cout << "debug " << std::endl;
    // std::cout << "volumes size " << volumes.size() <<std::endl;
    for(int i = 0; i < volumes.size(); i++){
        const std::string path = "/home/mengjiao/Desktop/data/vtk-pidx/voulme" + std::to_string(i) + ".idx";
        const std::string variable = "test";
        std::vector<char> data;
        std::copy(volumes[i].begin(), volumes[i].end(), std::back_inserter(data));
        set_pidx_file(i, path);
        set_pidx_variable(data, variable, dataType);
        PIDX_close(outpidxFile);
    }
}

 void writePIDX::writeOutPIDXFile(std::vector<std::vector<double>> volumes, std::string dataType){
    for(int i = 0; i < volumes.size(); i++){
        const std::string path = "/home/mengjiao/Desktop/data/vtk-pidx/voulme" + std::to_string(i) + ".idx";
        const std::string variable = "test";
        std::vector<char> data;
        std::copy(volumes[i].begin(), volumes[i].end(), std::back_inserter(data));
        set_pidx_file(i, path);
        set_pidx_variable(data, variable, dataType);
        PIDX_close(outpidxFile);
    }
 }
