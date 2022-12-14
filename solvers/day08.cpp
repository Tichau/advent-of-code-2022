#include "day08.hpp"
#include <iostream>
#include <vector>
#include <assert.h>

struct tree {
    uint8_t height;
    bool visible;

    tree(uint8_t _height)
    {
        height = _height;
        visible = false;
    }

    bool isVisibleAndSmallerThan(tree& other)
    {
        return visible && height < other.height;
    }
};

struct forest {
    std::vector<tree> data;
    uint32_t cols;
    uint32_t rows;

    forest()
    {
        data = std::vector<tree>();
        cols = 0;
        rows = 0;
    }

    tree& getTree(uint32_t row, uint32_t col)
    {
        return data[row * cols + col];
    }
};

void parse(std::ifstream& input, forest& forest)
{
    const int MAX_LEN = 128;

    while (!input.eof())
    {
        char line[MAX_LEN];
        input.getline(line, MAX_LEN);

        auto len = strlen(line);
        forest.cols = (uint32_t)len;

        for (auto i = 0; i < len; ++i)
        {
            forest.data.push_back(tree(line[i] - '0'));
        }

        forest.rows++;
    }
}

uint32_t day08_part1(std::ifstream& input)
{
    forest data;
    parse(input, data);

    // Left to right
    for (uint32_t row = 0; row < data.rows; ++row)
    {
        int height = -1;
        for (uint32_t col = 0; col < data.cols; ++col)
        {
            tree& tree = data.getTree(row, col);
            if (tree.height > height)
            {
                tree.visible = true;
            }
            
            height = tree.height > height ? tree.height : height;
        }
    }

    // Right to left
    for (uint32_t row = 0; row < data.rows; ++row)
    {
        int height = -1;
        for (uint32_t col = 0; col < data.cols; ++col)
        {
            tree& tree = data.getTree(row, data.cols - 1 - col);
            if (tree.height > height)
            {
                tree.visible = true;
            }
            
            height = tree.height > height ? tree.height : height;
        }
    }
    
    // Top to bottom
    for (uint32_t col = 0; col < data.cols; ++col)
    {
        int height = -1;
        for (uint32_t row = 0; row < data.rows; ++row)
        {
            tree& tree = data.getTree(row, col);
            if (tree.height > height)
            {
                tree.visible = true;
            }
            
            height = tree.height > height ? tree.height : height;
        }
    }

    // Right to left
    for (uint32_t col = 0; col < data.cols; ++col)
    {
        int height = -1;
        for (uint32_t row = 0; row < data.rows; ++row)
        {
            tree& tree = data.getTree(data.rows - 1 - row, col);
            if (tree.height > height)
            {
                tree.visible = true;
            }
            
            height = tree.height > height ? tree.height : height;
        }
    }

    int result = 0;
    for (auto i = 0; i < data.data.size(); ++i)
    {
        if (data.data[i].visible)
        {
            result++;
        }
    }

    return result;
}

uint32_t day08_part2(std::ifstream& input)
{
    forest data;
    parse(input, data);

    int maxScore = 0;
    for (uint32_t row = 0; row < data.rows; ++row)
    {
        for (uint32_t col = 0; col < data.cols; ++col)
        {
            tree& house = data.getTree(row, col);
            int score = 0;

            // Left
            int leftDistance = 0;
            for (int i = col - 1; i >= 0; i--)
            {
                tree& other = data.getTree(row, i);
                leftDistance++;
                if (other.height >= house.height)
                {
                    break;
                }
            }

            // Right
            int rightDistance = 0;
            for (int i = col + 1; i < (int)data.cols; i++)
            {
                tree& other = data.getTree(row, i);
                rightDistance++;
                if (other.height >= house.height)
                {
                    break;
                }
            }

            // Top
            int topDistance = 0;
            for (int i = row - 1; i >= 0; i--)
            {
                tree& other = data.getTree(i, col);
                topDistance++;
                if (other.height >= house.height)
                {
                    break;
                }
            }

            // Bottom
            int bottomDistance = 0;
            for (int i = row + 1; i < (int)data.rows; i++)
            {
                tree& other = data.getTree(i, col);
                bottomDistance++;
                if (other.height >= house.height)
                {
                    break;
                }
            }

            score = leftDistance * rightDistance * topDistance * bottomDistance;

            if (score > maxScore)
            {
                maxScore = score;
            }
        }
    }

    return maxScore;
}
