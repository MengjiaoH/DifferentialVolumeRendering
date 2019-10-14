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
    
    return 0;
}