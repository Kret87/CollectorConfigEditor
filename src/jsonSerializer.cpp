#include "jsonSerializer.h"
#include <stdexcept>

json pollTargetToJson(const PollTarget& target){

        json json_target;

        json_target["description"] = target.description;
        json_target["enabled"] = target.enabled;
        json_target["interface"] = target.interface;
        json_target["url"] = target.url;
        json_target["interval_ms"] = target.interval_ms;

        return json_target;

}

json pollTargetsToConfig(const std::vector<PollTarget>& targets){

        json json_targets;

        for(const PollTarget& target:targets){
                json_targets["endpoints"].push_back(pollTargetToJson(target));
        }

        return json_targets;
}

std::vector<PollTarget> configToPollTargets(const json& config){

        std::vector<PollTarget> targets;

        if(!config.contains("endpoints"))
                throw std::runtime_error("Missing 'endpoints' array.");

        if(!config["endpoints"].is_array())
                throw std::runtime_error("'endpoints' is not an array.");

        for (std::size_t i = 0; i < config["endpoints"].size(); ++i){

                PollTarget target;

                try{
                        target.description = config["endpoints"][i]["description"];
                        target.enabled = config["endpoints"][i]["enabled"];
                        target.interface = config["endpoints"][i]["interface"];
                        target.url = config["endpoints"][i]["url"];
                        target.interval_ms = config["endpoints"][i]["interval_ms"];
                }catch(const std::exception& e){

                        throw std::runtime_error("Error while parsing endpoint #" + std::to_string(i + 1) + ": " + e.what());
                }

                targets.push_back(target);
        }

        return targets;
}