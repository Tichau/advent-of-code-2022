#include "day01.h"
#include <string>

int day01_part1(std::ifstream& input)
{
    std::string line;
    int calories = 0;
    int maxCalories = 0;

    while (!input.eof())
    {
        std::getline(input, line);
        if (line == "")
        {
            if (calories > maxCalories)
            {
                maxCalories = calories;
            }

            calories = 0;
        }
        else
        {
            int number = std::stoi(line);
            calories += number;
        }
    }

    if (calories > maxCalories)
    {
        maxCalories = calories;
    }

    return maxCalories;
}

int day01_part2(std::ifstream& input)
{
    std::string line;
    int calories = 0;
    int maxCalories[3];
    maxCalories[0] = maxCalories[1] = maxCalories[2] = 0;

    while (!input.eof())
    {
        std::getline(input, line);
        if (line == "")
        {
            int lowestId = maxCalories[0] < maxCalories[1] ? (maxCalories[0] < maxCalories[2] ? 0 : maxCalories[1] < maxCalories[2] ? 1 : 2) : (maxCalories[1] < maxCalories[2] ? 1 : maxCalories[0] < maxCalories[2] ? 0 : 2);
            if (calories > maxCalories[lowestId])
            {
                maxCalories[lowestId] = calories;
            }

            calories = 0;
        }
        else
        {
            int number = std::stoi(line);
            calories += number;
        }
    }

    int lowestId = maxCalories[0] < maxCalories[1] ? (maxCalories[0] < maxCalories[2] ? 0 : maxCalories[1] < maxCalories[2] ? 1 : 2) : (maxCalories[1] < maxCalories[2] ? 1 : maxCalories[0] < maxCalories[2] ? 0 : 2);
    if (calories > maxCalories[lowestId])
    {
        maxCalories[lowestId] = calories;
    }

    int sum = 0;
    for (int i = 0; i < 3; i++)
    {
        sum += maxCalories[i];
    }

    return sum;
}
