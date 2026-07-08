#include <iostream>
#include <vector>
#include "PollTarget.h"
#include "Menu.h"
#include <nlohmann/json.hpp>
#include "jsonSerializer.h"
#include "fileStorage.h"

using json = nlohmann::json;

int main(){

    std::vector<PollTarget> targets;
    json json_targets;

    {
        PollTarget target;

        target.description = "mikrotik home";
        target.enabled = 1;
        target.interface = "wg0-mikrotik";
        target.url = "http://192.168.0.1/awg/api/api.html";
        target.interval_ms = 1000;

        targets.push_back(target);

        target.description = "mikrotik 3AP";
        target.enabled = 1;
        target.interface = "wg0-3AP";
        target.url = "http://192.168.0.1/awg/api/api.html";
        target.interval_ms = 900;

        targets.push_back(target);

    }

    {
        json_targets = pollEndpointsToConfig(targets);
        std::cout << json_targets.dump(4) << '\n';
    }

    while(true){


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
        if(saveConfiguration("config.json", targets))
            std::cout << "Configuration saved.";
        else 
            std::cout << "Configuration could not be saved.\n\n";
        break;
    case 5:
        return 0;

    default:
        break;
    }
}

    return 0;
}