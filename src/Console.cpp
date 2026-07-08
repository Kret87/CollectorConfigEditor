#include "Console.h"
#include <iostream>
#include <limits>

std::string readString(const std::string& prompt){
    std::cout << prompt;

    std::string input = "";
    std::getline(std::cin,input);

    return input;
}

int readInt(const std::string& prompt){
    
    while(true){
        std::cout << prompt;

        int value = 0;

        if(std::cin >> value){
            int test_char = std::cin.peek();
            if(test_char == '\n') return value;
            else std::cout << "Poza liczbą wpisałeś coś innego.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }else{
            std::cout << "To nie jest wartość liczbowa.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}