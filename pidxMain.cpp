#include <iostream>
#include <chrono>
#include <vector>
#include <dirent.h>

#include "loadPIDX.h"
#include "parseArgs.h"


int main(int argc, const char** argv)
{
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
            std::cout << e ->d_name << std::endl;
            // if(std::string(e ->d_name).length() > 3){
            //     const std::string vtkFile = dir + "/" + std::string(e->d_name);
            //     std::string ext = getFileExt(std::string(e->d_name));
            //     timesteps t(std::stoi(ext), vtkFile);
            //     files.push_back(t);
            // }
        }
    }
    // Sort time steps 
    // std::sort(files.begin(), files.end(), sort_timestep());

    return 0;
}