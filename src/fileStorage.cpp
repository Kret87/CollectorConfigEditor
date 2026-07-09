#include "fileStorage.h"
#include <fstream>
#include "jsonSerializer.h"

bool saveConfiguration(const std::string& filename, const std::vector<PollTarget>& targets){

    std::ofstream file(filename);

    if(!file) 
        return false;

    file << pollTargetsToConfig(targets);

    return true;
}

bool loadConfiguration(const std::string& filename, std::vector<PollTarget>& targets){

    std::ifstream file(filename);

    if(!file)
        return false;

    json config;

    file >> config;
    targets = configToPollTargets(config);
        
    return true;
}