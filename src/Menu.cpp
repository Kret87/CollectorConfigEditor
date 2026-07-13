#include "Menu.h"
#include <iostream>
#include <limits>
#include "HttpServer.h"

int showMenu(){

    HttpServer server;
    server.run();

    return true;

    std::cout << "Collector Config Editor\n\n";
    std::cout << "1. List entries\n";
    std::cout << "2. Add entry\n";
    std::cout << "3. Remove entry\n";
    std::cout << "4. Save to file\n";
    std::cout << "5. Exit\n\n";

    int choice = 0;

    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    return  choice;
}