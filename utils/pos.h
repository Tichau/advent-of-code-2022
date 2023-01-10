#pragma once
#include <iostream>

enum class Direction {
    right,
    up, 
    left,
    down,
};

struct Pos {
    int16_t x;
    int16_t y;

    Pos();
    Pos(int16_t _x, int16_t _y);

    int16_t distance(const Pos& other) const;
    int16_t manhattanDistance(const Pos& other) const;
    void moveToward(Direction direction);
    void moveToward(const Pos& head);
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
        return pos.x + (pos.y << 16);
    }
};
