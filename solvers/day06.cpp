#include "day06.h"
#include <unordered_set>

uint32_t day06_part1(std::ifstream& input)
{
    const int MAX_LEN = 4096;
    char line[MAX_LEN];
    input.getline(line, MAX_LEN);

    for (uint32_t i = 4; i < MAX_LEN; ++i)
    {
        bool valid = true;
        std::unordered_set<char> content;
        content.insert(line[i]);
        for (uint32_t offset = 1; offset < 4; ++offset)
        {
            if (content.contains(line[i - offset]))
            {
                valid = false;
                break;
            }

            content.insert(line[i - offset]);
        }

        if (valid)
        {
            return i + 1;
        }
    }

    return 0;
}

uint32_t day06_part2(std::ifstream& input)
{
    const int MAX_LEN = 4096;
    char line[MAX_LEN];
    input.getline(line, MAX_LEN);

    for (uint32_t i = 4; i < MAX_LEN; ++i)
    {
        bool valid = true;
        std::unordered_set<char> content;
        content.insert(line[i]);
        for (uint32_t offset = 1; offset < 14; ++offset)
        {
            if (content.contains(line[i - offset]))
            {
                valid = false;
                break;
            }

            content.insert(line[i - offset]);
        }

        if (valid)
        {
            return i + 1;
        }
    }

    return 0;
}
