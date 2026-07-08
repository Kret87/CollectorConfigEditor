#include <iostream>
#include <vector>
#include "PollTarget.h"
#include "Menu.h"

std::vector<PollTarget> targets;

int main(){

    {
    PollTarget target;

    target.description = "mikrotik home";
    target.enabled = 1;
    target.interface = "wg0-mikrotik";
    target.url = "http://192.168.0.1/awg/api/api.html";
    target.interval_ms = 1000;

    targets.push_back(target);
    }

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