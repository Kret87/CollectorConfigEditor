#pragma once

#include <string>
#include <vector>
#include "PollTarget.h"

bool saveConfiguration(const std::string& filename, const std::vector<PollTarget>& targets);

bool loadConfiguration(const std::string& filename, std::vector<PollTarget>& targets);