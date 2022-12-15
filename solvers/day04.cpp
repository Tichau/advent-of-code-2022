#include "day04.h"
#include <iostream>
#include <regex>

struct Interval {
    int min;
    int max;

    int isIn(Interval &other) 
    { 
        return min >= other.min && max <= other.max; 
    }

    int intersect(Interval &other) 
    { 
        return max >= other.min && min <= other.max; 
    }
};

int day04_part1(std::ifstream& input)
{
    const int MAX_LEN = 15;

    int score = 0;
    while (!input.eof())
    {
        char line[MAX_LEN];
        input.getline(line, MAX_LEN);
    
        std::cmatch matches;
        if (!std::regex_match(line, matches, std::regex("([0-9]+)-([0-9]+),([0-9]+)-([0-9]+)")))
        {
            std::cout << "Failed to parse line: " << line;
        }

        Interval first, second;
        first.min = stoi(matches[1]);
        first.max = stoi(matches[2]);
        second.min = stoi(matches[3]);
        second.max = stoi(matches[4]);

        if (first.isIn(second) || second.isIn(first))
        {
            score++;
        }
    }

    return score;
}

int day04_part2(std::ifstream& input)
{
    const int MAX_LEN = 15;

    int score = 0;
    while (!input.eof())
    {
        char line[MAX_LEN];
        input.getline(line, MAX_LEN);
    
        std::cmatch matches;
        if (!std::regex_match(line, matches, std::regex("([0-9]+)-([0-9]+),([0-9]+)-([0-9]+)")))
        {
            std::cout << "Failed to parse line: " << line;
        }

        Interval first, second;
        first.min = stoi(matches[1]);
        first.max = stoi(matches[2]);
        second.min = stoi(matches[3]);
        second.max = stoi(matches[4]);

        if (first.intersect(second))
        {
            score++;
        }
    }

    return score;
}
