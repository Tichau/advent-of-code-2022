#include "day09.h"
#include <iostream>
#include <vector>
#include <unordered_set>
#include <regex>

using std::vector;
using std::unordered_set;

enum class Direction {
    right,
    up, 
    left,
    down,
};

struct Move {
    Direction direction;
    uint8_t steps;

    Move(Direction _direction, uint8_t _steps)
    {
        direction = _direction;
        steps = _steps;
    }
};

struct Pos {
    int16_t x;
    int16_t y;

    Pos()
    {
        x = 0;
        y = 0;
    }

    Pos(int16_t _x, int16_t _y)
    {
        x = _x;
        y = _y;
    }

    int16_t distance(const Pos& other)
    {
        return __max(abs(x - other.x), abs(y - other.y));
    }

    void move_toward(Direction direction)
    {
        switch (direction)
        {
            case Direction::right:
                x++;
                break;

            case Direction::up:
                y++;
                break;

            case Direction::left:
                x--;
                break;

            case Direction::down:
                y--;
                break;
        }
    }

    void move_toward(const Pos& head)
    {
        if (distance(head) <= 1)
        {
            return;
        }
        
        if (head.x - x > 0)
        {
            x += 1;
        }
        else if (x - head.x > 0)
        {
            x -= 1;
        }

        if (head.y - y > 0)
        {
            y += 1;
        }
        else if (y - head.y > 0)
        {
            y -= 1;
        }
    }
};

constexpr bool operator==(const Pos& lhs, const Pos& rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

constexpr bool operator!=(const Pos& lhs, const Pos& rhs)
{
    return lhs.x != rhs.x || lhs.y != rhs.y;
}

struct PosHashFunction {
    size_t operator()(const Pos& pos) const
    {
        return pos.x + (pos.y << 8);
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
            head.move_toward(move.direction);
            tail.move_toward(head);
            
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
            knots[0].move_toward(move.direction);

            for (int k = 1; k < knots_count; ++k)
            {
                knots[k].move_toward(knots[k-1]);
            }

            tail_positions.insert(knots[knots_count - 1]);
        }
    }
    
    return (uint32_t)tail_positions.size();
}
