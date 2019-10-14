#include <iostream>
#include <chrono>
#include <vector>
#include <dirent.h>

#include "loadPIDX.h"
#include "parseArgs.h"


int main(int argc, const char** argv)
{
    MPI_Init(NULL, NULL);
    // Parse arguments 
    Args args;
    parseArgs(argc, argv, args);

    std::cout << "Files Dir: " << args.timeStepPaths[0] << std::endl;
    
    // Read all files dir
    std::vector<timesteps> files;
    for (const auto &dir : args.timeStepPaths) {
        DIR *dp = opendir(dir.c_str());
        if (!dp) {
            throw std::runtime_error("failed to open directory: " + dir);
        }
        for (dirent *e = readdir(dp); e; e = readdir(dp)) {
            if(std::string(e ->d_name).at(0) == 't' && std::string(e ->d_name).length() <= 10){
                const std::string idxFile = dir + "/" + std::string(e->d_name) + "/l0/CCVars.idx";
                std::string temp = e ->d_name + 1;
                timesteps t(std::stoi(temp), idxFile);
                files.push_back(t);
            }
        }
    }
    // Sort time steps 
    std::sort(files.begin(), files.end(), sort_timestep());
    
    std::vector<PIDXVolume> volumes;
    std::vector<DifferentialVolume<double>> differentialVolumes;
    // only load 2 time steps for testing now 
    int count = 25;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    int numFiles = 0;
    for(auto t : files){
        if(numFiles < count){
            std::cout << "file dir " << t.fileDir << " time step = " << t.timeStep << std::endl;
            // load all volumes
            std::string variablename = "";
            PIDXVolume v(t.fileDir,  variablename.c_str(), (size_t)t.timeStep);
            volumes.push_back(v);
        }
        numFiles++;
    }
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    std::cout << "It took " << time_span.count() << " seconds loading " << count << " time step." << std::endl;
    
    // Extracting differential volume
    for(int i = 1; i < volumes.size(); i++){
        DifferentialVolume<double> differentialVolume;
        for(int v = 0; v < volumes[i].voxels.size(); ++v){
            //std::cout << volumes[i].voxels[v] << " ";
            if(volumes[i].voxels[v] != volumes[i-1].voxels[v]){
                differentialVolume.indices.push_back(v);
                differentialVolume.values.push_back(volumes[i].voxels[v]);
            }
        }
        differentialVolumes.push_back(differentialVolume);
    }
    std::cout << std::endl;
    std::cout << "There are " << volumes[0].voxels.size() << " voxels in total." << std::endl;
    for(auto d : differentialVolumes){
        float percentage = d.indices.size() / (float)volumes[0].voxels.size() * 100.f;
        std::cout << "differential volume has " << d.indices.size() << " differences. Changed " <<  percentage << " percentage" << std::endl;
    }

    for(int i = 1; i < differentialVolumes.size(); i++){
        DifferentialVolume<double> pre = differentialVolumes[i - 1];
        DifferentialVolume<double> post = differentialVolumes[i];
        if(pre.indices == post.indices){
            std::cout << "Differences indices between time step " << i << " and " << i - 1 << " is equal." << std::endl;
        }else{
            std::cout << "Differences indices between time step " << i << " and " << i - 1 << " is not equal." << std::endl;
        }
    }
    

    MPI_Finalize();    
    return 0;
}
