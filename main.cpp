#include <iostream>
#include <fstream>
#include <vector>
#include "Day1/Star1.h"
#include "Day1/Star2.h"

std::vector<std::string>* LoadFile(std::string fileName)
{
    std::vector<std::string>* data = new std::vector<std::string>();

    std::fstream input;
    input.open(fileName, std::fstream::in);
    std::string fileLine;

    while (std::getline(input, fileLine))
    {
        data->push_back(fileLine);
    }
    input.close();

    return data;
}

int main() {
    Day1::Star1* d1s1 = new Day1::Star1(LoadFile("./Day1/inputDay1.txt"));
    Day1::Star2* d1s2 = new Day1::Star2(LoadFile("./Day1/inputDay1.txt"));

    return 0;
}
