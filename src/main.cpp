#include <iostream>
#include <vector>
#include "PollTarget.h"
#include "Menu.h"
#include <nlohmann/json.hpp>
#include "jsonSerializer.h"

using json = nlohmann::json;

std::vector<PollTarget> targets;
json json_targets;

int main(){

    {
        PollTarget target;

        target.description = "mikrotik home";
        target.enabled = 1;
        target.interface = "wg0-mikrotik";
        target.url = "http://192.168.0.1/awg/api/api.html";
        target.interval_ms = 1000;

        json_targets["endpoints"].push_back(pollTargetToJson(target));

        targets.push_back(target);

        target.description = "mikrotik 3AP";
        target.enabled = 1;
        target.interface = "wg0-3AP";
        target.url = "http://192.168.0.1/awg/api/api.html";
        target.interval_ms = 900;

        json_targets["endpoints"].push_back(pollTargetToJson(target));

        targets.push_back(target);

        std::cout << json_targets.dump(4) << '\n';
    }

 /*   {
        json j;

        json endpoint;

        endpoint["description"] = "mikrotik json";
        endpoint["enabled"] = true;
        endpoint["interface"] = "wg510";
        endpoint["url"] = "http://www.wp.pl";
        endpoint["interval_ms"] = 1000;

        j["endpoints"].push_back(endpoint);

        std::cout << j.dump(4) << '\n';

    }*/

    while(1){


    int choice = showMenu();

    switch (choice)
    {
    case 1:
        showTargetList(targets);
        break;
    case 2:
        targets.push_back(createPollTarget());
        break;
    case 3:
        removePollTarget(targets);
        break;
    case 4:
        return 0;

    default:
        break;
    }
}

const char* p = "ABC";

std::cout << p << '\n';
std::cout << *p << '\n';
std::cout << &p << '\n';

    return 0;
}