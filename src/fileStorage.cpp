#include "fileStorage.h"
#include <fstream>
#include "jsonSerializer.h"

bool saveConfiguration(const std::string& filename, const std::vector<PollTarget>& targets){

    std::ofstream file(filename);

    if(!file) return false;

    file << pollEndpointsToConfig(targets);

    return true;
}