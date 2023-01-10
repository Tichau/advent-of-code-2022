#include "day12.h"
#include <iostream>
#include <unordered_set>
#include <queue>
#include <vector>
#include <assert.h>

#include "../utils/pos.h"

using std::vector;
using std::queue;
using std::priority_queue;
using std::cout;
using std::endl;

struct Map
{
    Pos start_position;
    Pos goal_position;

    uint8_t* cells;
    uint16_t width;
    uint16_t height;

    Map()
    {
        start_position = Pos();
        goal_position = Pos();
        cells = nullptr;
        width = 0;
        height = 0;
    }

    ~Map()
    {
        if (cells != nullptr)
        {
            delete cells;
        }
    }

    void setElevation(const Pos& position, uint8_t elevation)
    {
        cells[position.x + width * position.y] = elevation;
    }

    uint8_t getElevation(const Pos& position) const
    {
        return cells[position.x + width * position.y];
    }

    void display()
    {
        for (uint8_t y = 0; y < height; ++y)
        {
            for (uint8_t x = 0; x < width; ++x)
            {
                char elevation = 'a' + getElevation(Pos(x, y));
                cout << elevation;
            }

            cout << endl;
        }
    }

    uint32_t heuristic(const Pos& from) const
    {
        return 0;
    }

    bool contains(const Pos& pos) const
    {
        if (pos.x < 0 || pos.y < 0 || pos.x >= width || pos.y >= height)
        {
            return false;
        }

        return true;
    }

    bool isTransitionValid(const Pos& from, const Pos& to) const
    {
        if (from.distance(to) > 1)
        {
            return false;
        }

        int diff = getElevation(to) - getElevation(from);
        return diff <= 1;
    }
};

void parse(std::ifstream& input, Map& map)
{
    const int MAX_LEN = 256;
    const int MAX_LINES = 64;

    while (!input.eof())
    {
        char line[MAX_LEN];
        input.getline(line, MAX_LEN);

        uint16_t width = static_cast<uint16_t>(strlen(line));
        if (map.width == 0) {
            map.width = width;
            map.cells = new uint8_t[width * MAX_LINES];
        }

        assert(map.width == width);

        for (auto i = 0; i < width; ++i)
        {
            if (line[i] == 'S')
            {
                line[i] = 'a';
                map.start_position = Pos(i, map.height);
            }
            else if (line[i] == 'E')
            {
                line[i] = 'z';
                map.goal_position = Pos(i, map.height);
            } 

            uint8_t elevation = line[i] - 'a';
            map.setElevation(Pos(i, map.height), elevation);
        }
        
        map.height++;
    }
}

struct Node
{
    Pos pos;
    int cost;
    int heuristic;
    bool isClosed;
    bool isOpened;

    Node()
    {
        pos = Pos();
        cost = 0;
        heuristic = 0;
        isClosed = false;
        isOpened = false;
    }

    Node(Pos _pos, int _cost, int _heuristic)
    {
        pos = _pos;
        cost = _cost;
        heuristic = _heuristic;
        isClosed = false;
        isOpened = false;
    }
};

// https://en.wikipedia.org/wiki/A*_search_algorithm
uint32_t findPathCost(Pos start, const Map& map, Node* nodes)
{
    for (int y = 0; y < map.height; ++y)
    {
        for (int x = 0; x < map.width; ++x)
        {
            nodes[x + y * map.width] = Node(Pos(x, y), 0, 0);
        }
    }

    auto compare = [nodes, &map](Pos left, Pos right) { return nodes[left.x + left.y * map.width].heuristic > nodes[right.x + right.y * map.width].heuristic; };
    priority_queue<Pos, vector<Pos>, decltype(compare)> open_set(compare);

    open_set.push(start);
    nodes[start.x + start.y * map.width].isOpened = true;
    nodes[start.x + start.y * map.width].heuristic = map.heuristic(start);

    uint32_t pathCost = UINT32_MAX;
    while (!open_set.empty())
    {
        Pos pos = open_set.top();
        open_set.pop();

        Node& node = nodes[pos.x + pos.y * map.width];

        if (pos == map.goal_position)
        {
            pathCost = node.cost;
            break;
        }

        for (Direction direction = Direction::right; 
            direction <= Direction::down;
            direction = static_cast<Direction>((size_t)direction + 1)) 
        {
            Pos nextPos = node.pos;
            nextPos.moveToward(direction);

            if (!map.contains(nextPos))
            {
                continue;
            }

            if (!map.isTransitionValid(pos, nextPos))
            {
                continue;
            }

            Node& nextNode = nodes[nextPos.x + nextPos.y * map.width];
            assert(nextNode.pos == nextPos);
            if (nextNode.isClosed)
            {
                continue;
            }

            int cost = node.cost + 1;

            if (!nextNode.isOpened || cost < nextNode.cost)
            {
                nextNode.cost = cost;
                nextNode.heuristic = cost + map.heuristic(nextPos);
                if (!nextNode.isOpened)
                {
                    nextNode.isOpened = true;
                    open_set.push(nextPos);
                }
            }
        }

        node.isClosed = true;
    }

    return pathCost;
}

uint32_t day12_part1(std::ifstream& input)
{
    Map map;
    parse(input, map);

    Node* nodes = new Node[map.width * map.height];
    
    auto pathCost = findPathCost(map.start_position, map, nodes);

    delete nodes;

    return pathCost;
}

uint32_t day12_part2(std::ifstream& input)
{
    Map map;
    parse(input, map);

    Node* nodes = new Node[map.width * map.height];
    
    auto minPathCost = UINT32_MAX;
    for (int y = 0; y < map.height; ++y)
    {
        for (int x = 0; x < map.width; ++x)
        {
            if (map.getElevation(Pos(x, y)) == 0)
            {
                auto pathCost = findPathCost(Pos(x, y), map, nodes);
                if (pathCost < minPathCost)
                {
                    minPathCost = pathCost;
                }
            }
        }
    }

    delete nodes;

    return minPathCost;
}