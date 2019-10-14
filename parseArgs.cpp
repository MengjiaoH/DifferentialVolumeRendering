#include "parseArgs.h"

std::string getFileExt(const std::string& s) 
{

   size_t i = s.rfind('.', s.length());
   if (i != std::string::npos) {
      return(s.substr(i+1, s.length() - i));
   }

   return("");
}

void parseArgs(int argc, const char **argv, Args &args)
{
    for(int i = 0; i < argc; i++)
    {
        std::string arg = argv[i];
        if(arg == "-f"){
            args.filename = argv[++i];
        }else if(arg == "-time-step"){
            args.timeStep = std::atoi(argv[++i]);
        }else if(arg == "-variable"){
            args.variableName = argv[++i];
        }else if(arg == "-mul-time-steps"){
            for(; i + 1 < argc; ++i){
                if(argv[i+1][0] == '-'){
                    break;
                }
                args.timeStepPaths.push_back(argv[++i]);
            }
        }
    }
    // find file extension
    std::string extension = getFileExt(args.filename);
    args.extension = extension;
}