#include "pos.h"

Pos::Pos()
{
    x = 0;
    y = 0;
}

Pos::Pos(int16_t _x, int16_t _y)
{
    x = _x;
    y = _y;
}

int16_t Pos::distance(const Pos& other) const
{
    return __max(abs(x - other.x), abs(y - other.y));
}

int16_t Pos::manhattanDistance(const Pos& other) const
{
    return abs(x - other.x) + abs(y - other.y);
}

void Pos::moveToward(Direction direction)
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

void Pos::moveToward(const Pos& head)
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
