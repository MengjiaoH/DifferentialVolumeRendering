#include <iostream>
#include <chrono>
#include <vector>
#include <dirent.h>

#include "loadVTK.h"
#include "parseArgs.h"


int main(int argc, const char** argv)
{
    // Parse arguments loading a list of dataset
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
            if(std::string(e ->d_name).length() > 3){
                const std::string vtkFile = dir + "/" + std::string(e->d_name);
                std::string ext = getFileExt(std::string(e->d_name));
                timesteps t(std::stoi(ext), vtkFile);
                files.push_back(t);
            }
        }
    }
    // Sort time steps 
    std::sort(files.begin(), files.end(), sort_timestep());

    std::vector<Volume<float>> volumes;
    std::vector<DifferentialVolume<float>> differentialVolumes;
    // only load 2 time steps for testing now 
    int count = 16;

    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    for(auto t : files){
        if(t.timeStep < count){
            // std::cout << "file dir " << t.fileDir << " time step = " << t.timeStep << std::endl;
            // load all volumes 
            Volume<float> v;
            loadVTK(t.fileDir, v);
            volumes.push_back(v);
        }
    }
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    std::cout << "It took " << time_span.count() << " seconds loading " << count - 1 << " time step." << std::endl;

    // Extracting differential volume
    for(int i = 1; i < volumes.size(); i++){
        DifferentialVolume<float> differentialVolume;
        for(int v = 0; v < volumes[i].voxels.size(); ++v){
            if(volumes[i].voxels[v] != volumes[i - 1].voxels[v]){
                differentialVolume.indices.push_back(v);
                differentialVolume.values.push_back(volumes[i].voxels[v]);
            }
            // if(std::abs(volumes[i].voxels[v] - volumes[i - 1].voxels[v]) > 0.1f){
            //     differentialVolume.indices.push_back(v);
            //     differentialVolume.values.push_back(volumes[i].voxels[v]);
            // }else{
            //     // std::cout << volumes[i].voxels[v] - volumes[i - 1].voxels[v] << " ";
            // }
        }
        differentialVolumes.push_back(differentialVolume);
    }
    std::cout << std::endl;
    std::cout << "There are " << volumes[0].voxels.size() << " voxels in total." << std::endl;
    for(auto d : differentialVolumes){
        float percentage = d.indices.size() / (float)volumes[0].voxels.size() * 100;
        std::cout << "differential volume has " << d.indices.size() << " differences. Changed " <<  percentage << " percentage" << std::endl;
    }

    return 0;
}
