#include "day03.hpp"
#include <vector>
#include <unordered_set>

int day03_part1(std::ifstream& input)
{
    const int MAX_ITEMS = 100;
    const int LETTERS = 53;

    char itemCount[LETTERS];

    int score = 0;
    while (!input.eof())
    {
        for (int i = 1; i < LETTERS; i++)
        {
            itemCount[i] = 0;
        }
        
        char line[MAX_ITEMS];
        input.getline(line, MAX_ITEMS);

        int backpack_size = static_cast<int>(strlen(line)) / 2;

        for (int i = 0; i < backpack_size; i++)
        {
            char prio = line[i] >= 'a' ? line[i] - 'a' + 1 : line[i] - 'A' + 27;
            if (itemCount[prio] == 0)
            {
                itemCount[prio]++;
            }
        }

        for (int i = backpack_size; i < backpack_size * 2; i++)
        {
            char prio = line[i] >= 'a' ? line[i] - 'a' + 1 : line[i] - 'A' + 27;
            if (itemCount[prio] == 1)
            {
                score += prio;
                break;
            }
        }
    }

    return score;
}

int day03_part2(std::ifstream& input)
{
    const int MAX_ITEMS = 100;
    const int LETTERS = 53;

    char itemCount[LETTERS];

    int groupIndex = 0;
    int score = 0;
    while (!input.eof())
    {
        if (groupIndex == 0)
        {
            groupIndex = 3;
            for (int i = 1; i < LETTERS; i++)
            {
                itemCount[i] = 0;
            }
        }
        
        char line[MAX_ITEMS];
        input.getline(line, MAX_ITEMS);

        int backpack_size = static_cast<int>(strlen(line));

        {
            std::unordered_set<char> content;
            for (int i = 0; i < backpack_size; i++)
            {
                char prio = line[i] >= 'a' ? line[i] - 'a' + 1 : line[i] - 'A' + 27;
                content.insert(prio);
            }

            for (const auto& prio: content) {
                itemCount[prio]++;
                if (itemCount[prio] == 3)
                {
                    score += prio;
                    break;
                }
            }
        }

        groupIndex--;
    }

    return score;
}
