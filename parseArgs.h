#pragma once


#include <iostream>
#include <vector>

struct Args
{
    std::string extension;
    std::string filename;
    std::vector<std::string> timeStepPaths;
    std::string variableName;
    int timeStep = 0;
};

std::string getFileExt(const std::string& s);

void parseArgs(int argc, const char **argv, Args &args);