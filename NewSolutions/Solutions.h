#include "ISolutions.h"
#include <vector>
#include <string>

class Solutions : ISolutions
{
private:
    template <typename T>
    void Print(const T& collection);

    [[nodiscard]] std::vector<std::string> LoadTxtFile(const std::string& path) noexcept;
    [[nodiscard]] std::vector<std::string> Split(const std::string& string, const std::string& delimiter) noexcept;
    
public:
    void Day2() noexcept override;
    void Day3() noexcept override;
    void Day4() noexcept override;
    void Day5() override {};
    void Day6() override {};
    void Day7() override {};
    void Day8() override {};
    void Day9() override {};
    void Day10() override {};
    void Day11() override {};
    void Day12() override {};
    void Day13() override {};
    void Day14() override {};
    void Day15() override {};
    void Day16() override {};
    void Day17() override {};
    void Day18() override {};
    void Day19() override {};
    void Day20() override {};
    void Day21() override {};
    void Day22() override {};
    void Day23() override {};
    void Day24() override {};
    void Day25() override {};
};
