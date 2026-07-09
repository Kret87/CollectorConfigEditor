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
            if(test_char == '\n') 
                return value;

            std::cout << "Please enter a valid integer.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }else{
            std::cout << "Not a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

bool readYesNo(const std::string& prompt){

    while(true){
        std::cout << prompt;

        char answer = 0;
        
        std::cin >> answer;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        
        if(answer == 'n' || answer == 'N')
            return false;
        else if (answer == 'y' || answer == 'Y')
            return true;

        std::cout << "Please enter y or n.\n";
    }
    
}