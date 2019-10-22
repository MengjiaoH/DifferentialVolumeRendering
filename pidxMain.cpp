#include <iostream>
#include <chrono>
#include <vector>
#include <dirent.h>

#include "loadPIDX.h"
#include "parseArgs.h"
#include "arcballCamera.h"
#include "helper.h"

#include "ospcommon/math/vec.h"
#include "ospcommon/math/box.h"

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
    ospcommon::math::box3f worldBound = ospcommon::math::empty;

    // only load 2 time steps for testing now 
    int count = 25;
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    int numFiles = 0;
    for(auto t : files){
        //if(numFiles < count){
            std::cout << "file dir " << t.fileDir << " time step = " << t.timeStep << std::endl;
            // load all volumes
            std::string variablename = "";
            PIDXVolume v(t.fileDir,  variablename.c_str(), (size_t)t.timeStep);
            volumes.push_back(v);
        //}
        //numFiles++;
    }
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);

    std::cout << "It took " << time_span.count() << " seconds loading " << count << " time step." << std::endl;

    worldBound = ospcommon::math::box3f(ospcommon::math::vec3f(0, 0, 0), ospcommon::math::vec3f(volumes[0].fullDims.x, volumes[0].fullDims.y, volumes[0].fullDims.z));
    
    // Set frameBuffer size and tile size
    ospcommon::math::vec2i imgSize(1900, 1200);
    ospcommon::math::vec2i tileSize(256);

    // Set camera 
    ArcballCamera arcballCamera(worldBound, imgSize);
    std::vector<ospcommon::math::vec2i> tileIDs;
    std::vector<tileList> tileLists;

    std::cout << "================================================" << std::endl;
    std::cout << "Experiments on changing time steps " << std::endl;
    
    // Extracting differential volume
    for(int i = 1; i < volumes.size(); i++){
        DifferentialVolume<double> differentialVolume;
        for(int v = 0; v < volumes[i].voxels.size(); ++v){
            //std::cout << volumes[i].voxels[v] << " ";
            if(volumes[i].voxels[v] != volumes[i-1].voxels[v]){
                differentialVolume.indices.push_back(v);
                differentialVolume.values.push_back(volumes[i].voxels[v]);
                
                ospcommon::math::vec3i voxelPos = indexToPosition(v, (ospcommon::math::vec3i)volumes[0].fullDims);
                // std::cout << " voxel pos (" << voxelPos.x << ", " << voxelPos.y << ", " << voxelPos.z << ")\n"; 
                ospcommon::math::vec2f pixel = arcballCamera.worldToPixel((ospcommon::math::vec3f)voxelPos, imgSize);
                ospcommon::math::vec2i tileID = pixelToTileID(pixel, tileSize);
                tileIDs.push_back(tileID);
            }
        }
        std::cout << "tileId size before remove = " << tileIDs.size() << std::endl;
        // Debug
        // for(int x = 0; x < 500; x++){
        //     std::cout << "x = " << x << " tile id = " << tileIDs[x].x << " " << tileIDs[x].y << std::endl;
        // }

        // Remove duplicated tileIDs
        remove(tileIDs);

        std::cout << "tileId size after remove = " << tileIDs.size() << std::endl;
        for(int s = 0; s < tileIDs.size(); s++){
            std::cout << "tile id = (" << tileIDs[s].x << ", " << tileIDs[s].y << ")" << std::endl;
        }

        std::cout << "tileId size after remove = " << tileIDs.size()  << " tile ID = (" << tileIDs[0].x << ", " << tileIDs[0].y << ")" << std::endl;
        tileList tile_list(tileIDs);
        tileLists.push_back(tile_list);
        differentialVolumes.push_back(differentialVolume);
        tileIDs.clear();
    }

    // Remove all other volumes and only keep the first timestep
    volumes.erase (volumes.begin() + 1, volumes.end() - 1);

    std::cout << "================================================" << std::endl;
    std::cout << std::endl;

    std::cout << "================================================" << std::endl;
    std::cout << "Experiments on zooming camera " << std::endl;
    
    // Zoom in and out camera and check tiles 
    for(int z = 0; z < 10; z++){
        arcballCamera.zoom(-1);
        // for(int i = 0; i < differentialVolumes.size(); i++){
            std::vector<int> indices = differentialVolumes[1].indices;
            for(int j = 0; j < indices.size(); j++){
                ospcommon::math::vec3i voxelPos = indexToPosition(indices[j], (ospcommon::math::vec3i)volumes[0].fullDims);
                // std::cout << " voxel pos (" << voxelPos.x << ", " << voxelPos.y << ", " << voxelPos.z << ")\n"; 
                ospcommon::math::vec2f pixel = arcballCamera.worldToPixel((ospcommon::math::vec3f)voxelPos, imgSize);
                ospcommon::math::vec2i tileID = pixelToTileID(pixel, tileSize);
                tileIDs.push_back(tileID);
            }
        // }
        std::cout << "tileId size before remove = " << tileIDs.size() << std::endl;
        // Debug
        // for(int x = 0; x < 500; x++){
        //     std::cout << "x = " << x << " tile id = " << tileIDs[x].x << " " << tileIDs[x].y << std::endl;
        // }
        remove(tileIDs);
        // std::vector<ospcommon::math::vec2i>::iterator ip = std::unique(tileIDs.begin(), tileIDs.begin() + tileIDs.size()); 
        // tileIDs.resize(std::distance(tileIDs.begin(), ip)); 
        // Remove duplicated tileIDs
        std::cout << "tileId size after remove = " << tileIDs.size() << std::endl;
        for(int s = 0; s < tileIDs.size(); s++){
            std::cout << "tile id = (" << tileIDs[s].x << ", " << tileIDs[s].y << ")" << std::endl;
        }
        tileIDs.clear();
    }

    std::cout << "================================================" << std::endl;

    std::cout << std::endl;
    std::cout << "There are " << volumes[0].voxels.size() << " voxels in total." << std::endl;
    for(auto d : differentialVolumes){
        float percentage = d.indices.size() / (float)volumes[0].voxels.size() * 100.f;
        std::cout << "differential volume has " << d.indices.size() << " differences. Changed " <<  percentage << " percentage" << std::endl;
    }

    // for(int i = 1; i < differentialVolumes.size(); i++){
    //     DifferentialVolume<double> pre = differentialVolumes[i - 1];
    //     DifferentialVolume<double> post = differentialVolumes[i];
    //     if(pre.indices == post.indices){
    //         std::cout << "Differences indices between time step " << i << " and " << i - 1 << " is equal." << std::endl;
    //     }else{
    //         std::cout << "Differences indices between time step " << i << " and " << i - 1 << " is not equal." << std::endl;
    //     }
    //     if(pre.values == post.values){
    //         std::cout << "Differences values between time step " << i << " and " << i - 1 << " is equal." << std::endl;
    //     }else{
    //         std::cout << "Differences values between time step " << i << " and " << i - 1 << " is not equal." << std::endl;
    //     }

    // }
    

    MPI_Finalize();    
    return 0;
}
