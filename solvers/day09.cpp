#include "day09.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <regex>

#include "../utils/pos.h"

using std::vector;
using std::unordered_set;

struct Move {
    Direction direction;
    uint8_t steps;

    Move(Direction _direction, uint8_t _steps)
    {
        direction = _direction;
        steps = _steps;
    }
};

void parse(std::ifstream& input, vector<Move>& moves)
{
    const int MAX_LEN = 8;

    while (!input.eof())
    {
        char line[MAX_LEN];
        input.getline(line, MAX_LEN);

        std::cmatch matches;
        if (!std::regex_match(line, matches, std::regex("(R|U|L|D)\\s([0-9]+)")))
        {
            std::cerr << "Failed to parse line: " << line;
            exit(1);
        }

        Direction direction;
        switch (*matches[1].first)
        {
            case 'R':
                direction = Direction::right;
                break;

            case 'U':
                direction = Direction::up;
                break;

            case 'L':
                direction = Direction::left;
                break;

            case 'D':
                direction = Direction::down;
                break;
        }

        moves.push_back(Move(direction, stoi(matches[2])));
    }
}

uint32_t day09_part1(std::ifstream& input)
{
    vector<Move> moves;
    parse(input, moves);

    unordered_set<Pos, PosHashFunction> tail_positions;

    Pos head = Pos(0, 0);
    Pos tail = Pos(0, 0);
    tail_positions.insert(tail);

    for (int i = 0; i < moves.size(); ++i)
    {
        Move& move = moves[i];
        for (int step = 0; step < move.steps; ++step)
        {
            head.moveToward(move.direction);
            tail.moveToward(head);
            
            tail_positions.insert(tail);
        }
    }
    
    return (uint32_t)tail_positions.size();
}

uint32_t day09_part2(std::ifstream& input)
{
    vector<Move> moves;
    parse(input, moves);

    unordered_set<Pos, PosHashFunction> tail_positions;

    const uint8_t knots_count = 10;
    Pos knots[knots_count];
    tail_positions.insert(knots[knots_count - 1]);

    for (int i = 0; i < moves.size(); ++i)
    {
        Move& move = moves[i];
        for (int step = 0; step < move.steps; ++step)
        {
            knots[0].moveToward(move.direction);

            for (int k = 1; k < knots_count; ++k)
            {
                knots[k].moveToward(knots[k-1]);
            }

            tail_positions.insert(knots[knots_count - 1]);
        }
    }
    
    return (uint32_t)tail_positions.size();
}
