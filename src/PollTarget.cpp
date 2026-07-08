#include "PollTarget.h"
#include <iostream>
#include "Console.h"

void showPollTarget(const PollTarget& target){
        std::cout << "Description: " << target.description << " | Enabled: "
         << target.enabled << " | Interface: "
          << target.interface << " | URL:"
           << target.url << " | Interval: " << target.interval_ms << "\n";
}

void showTargetList(const std::vector<PollTarget>& targets){
    for(const PollTarget& target:targets){
        showPollTarget(target);
    }
}

PollTarget createPollTarget(){
    PollTarget target;

    std::cout << "Add entry\n\n";
    target.description = readString("Description: ");

    target.interval_ms = readInt("Interval: ");

    target.enabled = readString("Enabled[y/n]: ");

    target.interface = readString("Interface: ");

    target.url = readString("URL: ");

    return target;
}