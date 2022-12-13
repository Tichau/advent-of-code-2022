#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <chrono>

#include "solvers/day01.hpp"
#include "solvers/day02.hpp"
#include "solvers/day03.hpp"

namespace fs = std::filesystem;

int main(int argc, char *argv[]) 
{
    int day = 0;
    std::string file;
    switch (argc)
    {       
        case 2:
            if (sscanf_s(argv[1], "%d", &day) != 1)
            {
                file = std::string(argv[1]);
            }

            break;

        case 3:
            if (sscanf_s(argv[1], "%d", &day) != 1)
            {
                std::cout << "usage: aoc2021 [day] [input-path]\n";
            }

            file = std::string(argv[2]);
            break;

        default:
            std::cout << "usage: aoc2021 [day] [input-path]\n";
            break;
    }

    if (day == 0)
    {
        using namespace std::chrono;
        auto tp = zoned_time{current_zone(), system_clock::now()}.get_local_time();
        auto dp = floor<days>(tp);
        year_month_day ymd{dp};
        hh_mm_ss time{floor<milliseconds>(tp-dp)};
        day = static_cast<unsigned>(ymd.day());
    }

    std::string filePath(std::filesystem::current_path().string());
    if (file.empty())
    {
        filePath += "\\data\\day";
        if (day >= 10)
        {
            filePath += std::to_string(day);
        }
        else
        {
            filePath += "0" + std::to_string(day);
        }

        filePath += ".txt";
    }
    else
    {
        filePath += "\\" + file;
    }

    std::cout << "### Day " << day << " ###\n";
    std::cout << "### Parsing input ###\n";
    std::cout << "Reading: " << filePath << '\n';

    std::ifstream fileStream(filePath, std::ios_base::in);

    if (!fileStream.is_open()) 
    {
        std::cout << "Failed to open " << filePath << '\n';
        return -1;
    }

    std::cout << "### Running Part 1 ###\n";
    std::cout << "Result: " << day03_part1(fileStream) << "\n";

    fileStream.seekg(0);

    std::cout << "\n";
    std::cout << "### Running Part 2 ###\n";
    std::cout << "Result: " << day03_part2(fileStream) << "\n";
}
