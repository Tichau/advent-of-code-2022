#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <chrono>

#include "solvers/day01.h"
#include "solvers/day02.h"
#include "solvers/day03.h"
#include "solvers/day04.h"
#include "solvers/day05.h"
#include "solvers/day06.h"
#include "solvers/day07.h"
#include "solvers/day08.h"
#include "solvers/day09.h"
#include "solvers/day10.h"
#include "solvers/day11.h"
#include "solvers/day12.h"
#include "solvers/day13.h"

using std::cout;

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
                cout << "usage: aoc2021 [day] [input-path]\n";
            }

            file = std::string(argv[2]);
            break;

        default:
            cout << "usage: aoc2021 [day] [input-path]\n";
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

    cout << "### Day " << day << " ###\n";
    cout << "### Parsing input ###\n";
    cout << "Reading: " << filePath << '\n';

    std::ifstream fileStream(filePath, std::ios_base::in);

    if (!fileStream.is_open()) 
    {
        cout << "Failed to open " << filePath << '\n';
        return -1;
    }

    cout << "### Running Part 1 ###\n";
    cout << "Result: " << day13_part1(fileStream) << "\n";

    fileStream.seekg(0);

    cout << "\n";
    cout << "### Running Part 2 ###\n";
    cout << "Result: " << day13_part2(fileStream) << "\n";
}
