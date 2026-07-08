#include "jsonSerializer.h"

json pollTargetToJson(const PollTarget& target){

        json endpoint;

        endpoint["description"] = target.description;
        endpoint["enabled"] = target.enabled;
        endpoint["interface"] = target.interface;
        endpoint["url"] = target.url;
        endpoint["interval_ms"] = target.interval_ms;

        return endpoint;

}

json pollEndpointsToConfig(const std::vector<PollTarget>& targets){

        json json_endpoints;

        for(const PollTarget& target:targets){
                json_endpoints["endpoints"].push_back(pollTargetToJson(target));
        }

        return json_endpoints;
}