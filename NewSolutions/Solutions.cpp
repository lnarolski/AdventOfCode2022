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

[[nodiscard]] std::vector<std::string> Solutions::LoadTxtFile(const std::string& path) noexcept
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

void Solutions::Day2() noexcept
{
    //std::vector<std::string> fileVector = LoadTxtFile("test.txt");
    std::vector<std::string> fileVector = LoadTxtFile("adventofcode.com_2022_day_2_input.txt");

    enum class Shapes
    {
        Rock = 1,
        Paper = 2,
        Scissors = 3
    };
    auto LetterToShape = [](const char& letter) -> Shapes {
        if (letter == 'A' || letter == 'X')
            return Shapes::Rock;
        else if (letter == 'B' || letter == 'Y')
            return Shapes::Paper;
        else
            return Shapes::Scissors;
    };
    auto ShapeToScore = [](const Shapes& shape) -> long
    {
        switch (shape) {
            case Shapes::Rock:
                return 1;
            case Shapes::Paper:
                return 2;
            default:
                return 3;
        }
    };
    auto CalculateResult = [&ShapeToScore](const Shapes& opponent, const Shapes& _me) -> long
    {
        if (opponent == _me)
        {
            return 3 + ShapeToScore(_me);
        }
        else if ((opponent == Shapes::Rock && _me == Shapes::Paper) ||
                 (opponent == Shapes::Paper && _me == Shapes::Scissors) ||
                 (opponent == Shapes::Scissors && _me == Shapes::Rock))
        {
            return 6 + ShapeToScore(_me);
        }
        else
        {
            return ShapeToScore(_me);
        }
    };

    long points = 0;
    for (auto line : fileVector)
    {
        Shapes opponent = LetterToShape(line[0]);
        Shapes _me = LetterToShape(line[2]);

        points += CalculateResult(opponent, _me);
    }

    std::cout << "Day 2 Star 1: " << points << std::endl;

    enum class Result
    {
        Loose = 1,
        Draw = 2,
        Win = 3
    };
    auto LetterToResult = [](const char& letter) -> Result {
        if (letter == 'X')
            return Result::Loose;
        else if (letter == 'Y')
            return Result::Draw;
        else
            return Result::Win;
    };
    auto LetterToCorrectShape = [&LetterToResult](const char& letter, const Shapes& opponent) -> Shapes
    {
        Result result = LetterToResult(letter);

        switch (opponent) {
            case Shapes::Rock:
                if (result == Result::Draw)
                    return Shapes::Rock;
                else if (result == Result::Win)
                    return Shapes::Paper;
                else
                    return Shapes::Scissors;
            case Shapes::Paper:
                if (result == Result::Draw)
                    return Shapes::Paper;
                else if (result == Result::Win)
                    return Shapes::Scissors;
                else
                    return Shapes::Rock;
            case Shapes::Scissors:
                if (result == Result::Draw)
                    return Shapes::Scissors;
                else if (result == Result::Win)
                    return Shapes::Rock;
                else
                    return Shapes::Paper;
        }

        return Shapes{};
    };

    points = 0;
    for (auto line : fileVector)
    {
        Shapes opponent = LetterToShape(line[0]);
        Shapes _me = LetterToCorrectShape(line[2], opponent);

        points += CalculateResult(opponent, _me);
    }

    std::cout << "Day 2 Star 2: " << points << std::endl;

    return;
}

void Solutions::Day3() noexcept
{
//    std::vector<std::string> fileLines = LoadTxtFile("test.txt");
    std::vector<std::string> fileLines = LoadTxtFile("adventofcode.com_2022_day_3_input.txt");

    long sum = 0;

    for (const std::string& rucksack : fileLines)
    {
        bool found = false;
        for (size_t i1 = 0; i1 < rucksack.size() && !found; ++i1)
        {
            for (size_t i2 = rucksack.size() / 2; i2 < rucksack.size() && !found; ++i2)
            {
                if (rucksack[i1] == rucksack[i2])
                {
                    if (std::isupper(rucksack[i1]))
                    {
                        sum += rucksack[i1] - 'A' + 27;
                    }
                    else
                    {
                        sum += rucksack[i1] - 'a' + 1;
                    }

                    found = true;
                }
            }
        }
    }

    std::cout << "Day 3 Star 1: " << sum << std::endl;

    return;
}