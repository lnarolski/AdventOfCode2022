#include "Solutions.h"
#include <iostream>
#include <fstream>

template <typename T>
void Solutions::Print(const T& collection)
{
    for (const auto& element : collection)
    {
        std::cout << element << std::endl;
    }
}

std::vector<std::string> Solutions::LoadTxtFile(const std::string& path)
{
    std::vector<std::string> toReturn{};
    
    std::ifstream file(path);
    std::string fileLine{};
    while(std::getline(file, fileLine))
    {
        toReturn.push_back(fileLine);
    }
    
    return toReturn;
}

void Solutions::Day2()
{
    std::vector<std::string> fileVector = LoadTxtFile("adventofcode.com_2022_day_2_input.txt");
    Print(fileVector);
    
    return;
}
