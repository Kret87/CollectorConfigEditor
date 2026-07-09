#pragma once

#include <nlohmann/json.hpp>
#include "PollTarget.h"

using json = nlohmann::json;

json pollTargetToJson(const PollTarget& target);

json pollTargetsToConfig(const std::vector<PollTarget>& targets);

std::vector<PollTarget> configToPollTargets(const json& config);