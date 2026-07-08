#include <nlohmann/json.hpp>
#include "PollTarget.h"

using json = nlohmann::json;

json pollTargetToJson(const PollTarget& target);

json pollEndpointsToConfig(const std::vector<PollTarget>& targets);