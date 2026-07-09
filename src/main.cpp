#include <iostream>
#include <vector>
#include "PollTarget.h"
#include "Menu.h"
#include "fileStorage.h"

int main(){

    std::vector<PollTarget> targets;

    if(!loadConfiguration("config.json", targets)){
        PollTarget target;

        target.description = "example";
        target.enabled = true;
        target.interface = "wg0-mikrotik";
        target.url = "http://192.168.0.1/awg/api/api.html";
        target.interval_ms = 1000;

        targets.push_back(target);
    }

    while(true){


        int answer = showMenu();

        switch (answer)
        {
        case 1:
            showPollTargetsList(targets);
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
}