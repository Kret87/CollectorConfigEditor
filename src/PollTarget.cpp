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
    /*
    for(const PollTarget& target:targets){
        showPollTarget(target);
    }*/
    std::cout << "List Entries \n\n";

    for(std::size_t i = 0; i < targets.size(); i++){
        std::cout << i + 1 <<". ";
        showPollTarget(targets.at(i));
    }

    std::cout << '\n';
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

void removePollTarget(std::vector<PollTarget>& targets){
    while (true)
    {
        if (targets.empty()){
            std::cout << "\nNo entries.\n\n";
            return;
        }
    
        showTargetList(targets);

        int choice = readInt("\nRemove (0 = back): ");

        if(!choice) return;
        else{
            if(choice > 0 && choice <= static_cast<int>(targets.size()))
                targets.erase(targets.begin() + choice - 1);
            break;
        }
    }
}
