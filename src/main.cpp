#include <iostream>
#include <vector>
#include "PollTarget.h"
#include "Menu.h"
#include "fileStorage.h"

int main(){

    std::vector<PollTarget> targets;

    try{
       if(!loadConfiguration("config.json", targets)){
           std::cout << "* Could not open a file. Starting with empty configuration. *\n\n";
       }
    }catch(const std::runtime_error& e){
        std::cout << e.what() << '\n';
        std::cout << "Starting with an empty configuration.\n";
        std::cout << "Saving will overwrite the existing file.\n";
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