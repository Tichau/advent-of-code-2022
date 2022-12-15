#include "day02.h"

int day02_part1(std::ifstream& input)
{
    int score = 0;
    while (!input.eof())
    {
        char line[4];
        input.getline(line, 4);

        char opponentPlay = line[0] - 'A';
        char myPlay = line[2] - 'X';

        if (opponentPlay == myPlay)
        {
            score += 3;
        }
        else if ((opponentPlay + 1) % 3 == myPlay)
        {
            score += 6;
        }

        score += myPlay + 1;
    }

    return score;
}

int day02_part2(std::ifstream& input)
{
    int score = 0;
    while (!input.eof())
    {
        char line[4];
        input.getline(line, 4);

        char opponentPlay = line[0] - 'A';
        char result = line[2];
        
        char myPlay;

        switch (result)
        {
            case 'X': // Lose
                myPlay = (opponentPlay + 2) % 3;
                break;

            case 'Y': // Draw
                myPlay = opponentPlay;
                score += 3;
                break;
        
            case 'Z': // Win
                myPlay = (opponentPlay + 1) % 3;
                score += 6;
                break;
        }

        score += myPlay + 1;
    }

    return score;
}
