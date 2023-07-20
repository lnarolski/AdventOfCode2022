#include "Solutions.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>
#include <limits>

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

[[nodiscard]] std::vector<std::string> Solutions::Split(const std::string& string, const std::string& delimiter) noexcept
{
    std::vector<std::string> toReturn{};

    size_t strStart = 0;

    try
    {
        size_t found = string.find(delimiter);
        while (found != std::string::npos)
        {
            toReturn.push_back(string.substr(strStart, found - strStart));
            strStart = found + delimiter.size();
            found = string.find(delimiter, strStart);
        }
    }
    catch (...)
    {
        std::cout << "Exception occured during Split method" << std::endl;
    }

    toReturn.push_back(string.substr(strStart));

    return toReturn;
}

[[nodiscard]] int Solutions::CharToInt(const char& c) noexcept
{
    return static_cast<int>(c - '0');
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

    auto CalculatePoints = [](const char& letter)
    {
        if (std::isupper(letter))
        {
            return letter - 'A' + 27;
        }
        else
        {
            return letter - 'a' + 1;
        }
    };

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
                    sum += CalculatePoints(rucksack[i1]);

                    found = true;
                }
            }
        }
    }

    std::cout << "Day 3 Star 1: " << sum << std::endl;

    sum = 0;

    for (size_t i = 0; i < fileLines.size(); i += 3)
    {
        bool found = false;
        for (size_t i1 = 0; i1 < fileLines[i].size() && !found; ++i1)
        {
            std::string::iterator result = std::find(fileLines[i + 1].begin(), fileLines[i + 1].end(), fileLines[i][i1]);
            if (result == fileLines[i + 1].end())
            {
                continue;
            }
            result = std::find(fileLines[i + 2].begin(), fileLines[i + 2].end(), fileLines[i][i1]);
            if (result == fileLines[i + 2].end())
            {
                continue;
            }

            found = true;
            sum += CalculatePoints(fileLines[i][i1]);
        }
    }

    std::cout << "Day 3 Star 2: " << sum << std::endl;

    return;
}

void Solutions::Day4() noexcept
{
    //std::vector<std::string> fileLines = LoadTxtFile("test.txt");
    std::vector<std::string> fileLines = LoadTxtFile("adventofcode.com_2022_day_4_input.txt");

    auto StringToPair = [](const std::string& string, const std::string& delimiter) -> std::pair<int, int>
    {
        std::pair<int, int> toReturn{};

        toReturn.first = std::stoi(string);
        toReturn.second = std::stoi(string.substr(string.find(delimiter) + delimiter.size()));

        return toReturn;
    };

    long pairsCount = 0;

    for (const std::string& sectionAssignmentPair : fileLines)
    {
        auto pairs = Split(sectionAssignmentPair, ",");
        auto pair1 = StringToPair(pairs[0], "-");
        auto pair2 = StringToPair(pairs[1], "-");

        if ((pair1.first >= pair2.first && pair1.second <= pair2.second) ||
            (pair2.first >= pair1.first && pair2.second <= pair1.second))
        {
            ++pairsCount;
        }
    }

    std::cout << "Day 4 Star 1: " << pairsCount << std::endl;

    pairsCount = 0;

    for (const std::string& sectionAssignmentPair : fileLines)
    {
        auto pairs = Split(sectionAssignmentPair, ",");
        auto pair1 = StringToPair(pairs[0], "-");
        auto pair2 = StringToPair(pairs[1], "-");

        if ((pair1.second <= pair2.second && pair1.second >= pair2.first) ||
            (pair2.second <= pair1.second && pair2.second >= pair1.second) ||
            (pair1.first <= pair2.second && pair1.first >= pair2.first) ||
            (pair2.first <= pair1.second && pair2.first >= pair1.first))
        {
            ++pairsCount;
        }
    }

    std::cout << "Day 4 Star 2: " << pairsCount << std::endl;

    return;
}

void Solutions::Day5() noexcept
{
    //std::vector<std::string> fileLines = LoadTxtFile("test.txt");
    std::vector<std::string> fileLines = LoadTxtFile("adventofcode.com_2022_day_5_input.txt");

    size_t lineWithCratesNumbers = 0;
    for (int i = 0; i < fileLines.size(); ++i) {
        if (fileLines[i].find("1") != std::string::npos)
        {
            lineWithCratesNumbers = i;
            break;
        }
    }

    std::vector<std::string> crateNumbersStr = Split(fileLines[lineWithCratesNumbers], "   ");
    int lastCrateNumber = stoi(crateNumbersStr.back());

    std::vector<std::stack<char>> stacks(lastCrateNumber);

    // Fill crates
    for (int i = lineWithCratesNumbers - 1; i >= 0; --i)
    {
        for (int j = 0; j < lastCrateNumber; ++j)
        {
            if (fileLines[i][4 * j + 1] == ' ')
            {
                continue;
            }

            stacks[j].push(fileLines[i][4 * j + 1]);
        }
    }

    std::vector<std::stack<char>> stacksStar2(stacks);

    // Find solution
    for (int i = lineWithCratesNumbers + 2; i < fileLines.size(); ++i) {
        std::vector<std::string> cmd = Split(fileLines[i], " ");

        for (int j = 0; j < stoi(cmd[1]); ++j)
        {
            stacks[stoi(cmd[5]) - 1].push(stacks[stoi(cmd[3]) - 1].top());
            stacks[stoi(cmd[3]) - 1].pop();
        }
    }

    // Print solution
    std::cout << "Day 5 Star 1: ";
    for (auto stack : stacks)
    {
        std::cout << stack.top();
    }
    std::cout << std::endl;

    // Solution for CrateMover 9001
    for (int i = lineWithCratesNumbers + 2; i < fileLines.size(); ++i) {
        std::vector<std::string> cmd = Split(fileLines[i], " ");

        std::stack<char> tmpStack{};
        for (int j = 0; j < stoi(cmd[1]); ++j)
        {
            tmpStack.push(stacksStar2[stoi(cmd[3]) - 1].top());
            stacksStar2[stoi(cmd[3]) - 1].pop();
        }
        for (int j = 0; j < stoi(cmd[1]); ++j)
        {
            stacksStar2[stoi(cmd[5]) - 1].push(tmpStack.top());
            tmpStack.pop();
        }
    }

    // Print solution
    std::cout << "Day 5 Star 2: ";
    for (auto stack : stacksStar2)
    {
        std::cout << stack.top();
    }
    std::cout << std::endl;

    return;
}

void Solutions::Day6() noexcept
{
//    std::vector<std::string> fileLines = LoadTxtFile("test.txt"); // 7
//    std::vector<std::string> fileLines = LoadTxtFile("test2.txt"); // 5
//    std::vector<std::string> fileLines = LoadTxtFile("test3.txt"); // 6
//    std::vector<std::string> fileLines = LoadTxtFile("test4.txt"); // 10
//    std::vector<std::string> fileLines = LoadTxtFile("test5.txt"); // 11
    std::vector<std::string> fileLines = LoadTxtFile("adventofcode.com_2022_day_6_input.txt");

    size_t foundIndex = 0;
    for (int i = 3; i < fileLines[0].size(); ++i)
    {
        std::vector<char> temp(4);

        std::copy(fileLines[0].begin() + i - 3, fileLines[0].begin() + i + 1, temp.begin());
        std::sort(temp.begin(), temp.end());
        std::vector<char>::iterator last = std::unique(temp.begin(), temp.end());
        if (last == temp.end())
        {
            foundIndex = i + 1;
            break;
        }
    }

    std::cout << "Day 6 Star 1: " << foundIndex << std::endl;

    foundIndex = 0;
    for (int i = 13; i < fileLines[0].size(); ++i)
    {
        std::vector<char> temp(14);

        std::copy(fileLines[0].begin() + i - 13, fileLines[0].begin() + i + 1, temp.begin());
        std::sort(temp.begin(), temp.end());
        std::vector<char>::iterator last = std::unique(temp.begin(), temp.end());
        if (last == temp.end())
        {
            foundIndex = i + 1;
            break;
        }
    }

    std::cout << "Day 6 Star 2: " << foundIndex << std::endl;

    return;
}

struct Element
{
    std::string name;
    size_t size;
    bool isDirectory;
    std::vector<Element> elements;
    Element* upperElement;
};

void UpdateSizes(Element* el, size_t size)
{
    if (el == nullptr)
        return;

    el->size += size;
    UpdateSizes(el->upperElement, size);
};

size_t TotalSize(Element* root, const size_t limit)
{
    static size_t totalSize = 0;

    for (auto el : root->elements)
    {
        if (el.isDirectory && el.size <= limit)
            totalSize += el.size;

        TotalSize(&el, limit);
    }

    return totalSize;
}

size_t FindTheSmallestDirectory(Element* root, const size_t freeSpace)
{
    static const size_t neededSpace =  30000000 - freeSpace;
    static size_t foundEnoughSize = std::numeric_limits<size_t>().max();

    for (auto el : root->elements)
    {
        if (el.isDirectory && el.size > neededSpace && el.size < foundEnoughSize)
            foundEnoughSize = el.size;

        FindTheSmallestDirectory(&el, freeSpace);
    }

    return foundEnoughSize;
}

void Solutions::Day7() noexcept
{
//    auto fileLines = Solutions::LoadTxtFile("test.txt");
    auto fileLines = Solutions::LoadTxtFile("adventofcode.com_2022_day_7_input.txt");

    Element filesTree
    {
        "/",
        0,
        true,
        {},
        nullptr
    };
    auto CreateListOfFiles = [&fileLines, this](Element& root)
    {
        size_t linesI = 0;
        Element* currentElement = &root;
        std::vector<Element> elementsToAdd{};
        bool directoryListing = false;
        while (linesI < fileLines.size())
        {
            auto splittedLine = Split(fileLines[linesI], " ");

            if (splittedLine[0] == "$")
            {
                if (directoryListing)
                {
                    currentElement->elements = elementsToAdd;

                    elementsToAdd.clear();
                    directoryListing = false;
                }

                if (splittedLine[1] == "cd")
                {
                    if (splittedLine[2] == "/")
                    {
                        currentElement = &root;
                    }
                    else if (splittedLine[2] == "..")
                    {
                        if (currentElement != nullptr && currentElement->upperElement != nullptr)
                            currentElement = currentElement->upperElement;
                    }
                    else
                    {
                        auto it = std::find_if(currentElement->elements.begin(), currentElement->elements.end(), [&splittedLine](const Element& el) { return el.name == splittedLine[2]; });
                        if (it != currentElement->elements.end())
                            currentElement = &(*it);
                    }
                }
                else if (splittedLine[1] == "ls")
                {
                    directoryListing = true;
                }

                ++linesI;
            }
            else
            {
                Element temp{};
                temp.upperElement = currentElement;
                temp.name = splittedLine[1];

                if (splittedLine[0] != "dir")
                {
                    temp.isDirectory = false;
                    size_t tempSize = stoi(splittedLine[0]);
                    temp.size = tempSize;
                    UpdateSizes(currentElement, tempSize);
                }
                else
                {
                    temp.isDirectory = true;
                }

                elementsToAdd.push_back(temp);

                ++linesI;
            }
        }
    };

    CreateListOfFiles(filesTree);

    std::cout << "Day 7 Star 1: " << TotalSize(&filesTree, 100000) << std::endl;

    size_t freeSpace = 70000000 - filesTree.size;

    std::cout << "Day 7 Star 2: " << FindTheSmallestDirectory(&filesTree, freeSpace) << std::endl;

    return;
}

void Solutions::Day8() noexcept
{
//    auto fileLines = Solutions::LoadTxtFile("test.txt");
    auto fileLines = Solutions::LoadTxtFile("adventofcode.com_2022_day_8_input.txt");

    enum class Direction
    {
        up,
        right,
        down,
        left
    };

    auto IsVisible = [this]
            (const std::vector<std::string>& grid, const int& y, const int& x) -> bool
    {
        std::vector<Direction> directionsToCheck = { Direction::up, Direction::right, Direction::down, Direction::left };

        for (auto direction : directionsToCheck)
        {
            bool visibleDirection = true;
            switch (direction)
            {
                case Direction::up:
                {
                    for (int i = y - 1; i >= 0 && visibleDirection; --i) {
                        if (CharToInt(grid[i][x]) >= CharToInt(grid[y][x]))
                            visibleDirection = false;
                    }

                    if (visibleDirection)
                    {
                        return true;
                    }
                    break;
                }
                case Direction::right:
                {
                    for (int i = x + 1; i < grid[0].size() && visibleDirection; ++i)
                    {
                        if (CharToInt(grid[y][i]) >= CharToInt(grid[y][x]))
                            visibleDirection = false;
                    }

                    if (visibleDirection)
                    {
                        return true;
                    }
                    break;
                }
                case Direction::down:
                {
                    for (int i = y + 1; i < grid.size() && visibleDirection; ++i)
                    {
                        if (CharToInt(grid[i][x]) >= CharToInt(grid[y][x]))
                            visibleDirection = false;
                    }

                    if (visibleDirection)
                    {
                        return true;
                    }
                    break;
                }
                case Direction::left:
                {
                    for (int i = x - 1; i >= 0 && visibleDirection; --i)
                    {
                        if (CharToInt(grid[y][i]) >= CharToInt(grid[y][x]))
                            visibleDirection = false;
                    }

                    if (visibleDirection)
                    {
                        return true;
                    }
                    break;
                }
            }
        }

        return false;
    };

    size_t visibleTrees = 2 * fileLines.size() + 2 * fileLines[0].size() - 4;

    for (size_t y = 1; y < fileLines.size() - 1; ++y)
    {
        for (size_t x = 1; x < fileLines[0].size() - 1; ++x)
        {
            if (IsVisible(fileLines, y, x))
            {
                ++visibleTrees;
            }
        }
    }

    std::cout << "Day 8 Star 1: " << visibleTrees << std::endl;

    auto CalculateScenicScore = [this]
            (const std::vector<std::string>& grid, const int& y, const int& x) -> unsigned int
    {
        std::vector<Direction> directionsToCheck = { Direction::up, Direction::right, Direction::down, Direction::left };
        unsigned int scenicScore = 1;

        for (auto direction : directionsToCheck)
        {
            unsigned int tempScenicScore = 0;
            switch (direction)
            {
                case Direction::up:
                {
                    for (int i = y - 1; i >= 0; --i) {
                        if (CharToInt(grid[i][x]) >= CharToInt(grid[y][x]))
                        {
                            ++tempScenicScore;
                            break;
                        }
                        else
                            ++tempScenicScore;
                    }

                    if (tempScenicScore != 0)
                    {
                        scenicScore *= tempScenicScore;
                    }
                    break;
                }
                case Direction::right:
                {
                    for (int i = x + 1; i < grid[0].size(); ++i)
                    {
                        if (CharToInt(grid[y][i]) >= CharToInt(grid[y][x]))
                        {
                            ++tempScenicScore;
                            break;
                        }
                        else
                            ++tempScenicScore;
                    }

                    if (tempScenicScore != 0)
                    {
                        scenicScore *= tempScenicScore;
                    }
                    break;
                }
                case Direction::down:
                {
                    for (int i = y + 1; i < grid.size(); ++i)
                    {
                        if (CharToInt(grid[i][x]) >= CharToInt(grid[y][x]))
                        {
                            ++tempScenicScore;
                            break;
                        }
                        else
                            ++tempScenicScore;
                    }

                    if (tempScenicScore != 0)
                    {
                        scenicScore *= tempScenicScore;
                    }
                    break;
                }
                case Direction::left:
                {
                    for (int i = x - 1; i >= 0; --i)
                    {
                        if (CharToInt(grid[y][i]) >= CharToInt(grid[y][x]))
                        {
                            ++tempScenicScore;
                            break;
                        }
                        else
                            ++tempScenicScore;
                    }

                    if (tempScenicScore != 0)
                    {
                        scenicScore *= tempScenicScore;
                    }
                    break;
                }
            }
        }

        return scenicScore;
    };

    unsigned int maxScenicScoreValue = 0;
    for (size_t y = 0; y < fileLines.size() - 1; ++y)
    {
        for (size_t x = 0; x < fileLines[0].size() - 1; ++x)
        {
            unsigned int scenicScoreValue = CalculateScenicScore(fileLines, y, x);
            if (scenicScoreValue > maxScenicScoreValue)
            {
                maxScenicScoreValue = scenicScoreValue;
            }
        }
    }

    std::cout << "Day 8 Star 2: " << maxScenicScoreValue << std::endl;
};