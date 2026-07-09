#include "jsonSerializer.h"

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

        for(const json& element:config["endpoints"]){

                PollTarget target;

                target.description = element["description"];
                target.enabled = element["enabled"];
                target.interface = element["interface"];
                target.url = element["url"];
                target.interval_ms = element["interval_ms"];

                targets.push_back(target);
        }

        return targets;

}