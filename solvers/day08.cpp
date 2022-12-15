#include "day08.h"
#include <iostream>
#include <vector>
#include <assert.h>

struct Tree {
    uint8_t height;
    bool visible;

    Tree(uint8_t _height)
    {
        height = _height;
        visible = false;
    }

    bool isVisibleAndSmallerThan(Tree& other)
    {
        return visible && height < other.height;
    }
};

struct Forest {
    std::vector<Tree> data;
    uint32_t cols;
    uint32_t rows;

    Forest()
    {
        data = std::vector<Tree>();
        cols = 0;
        rows = 0;
    }

    Tree& getTree(uint32_t row, uint32_t col)
    {
        return data[row * cols + col];
    }
};

void parse(std::ifstream& input, Forest& forest)
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
            forest.data.push_back(Tree(line[i] - '0'));
        }

        forest.rows++;
    }
}

uint32_t day08_part1(std::ifstream& input)
{
    Forest data;
    parse(input, data);

    // Left to right
    for (uint32_t row = 0; row < data.rows; ++row)
    {
        int height = -1;
        for (uint32_t col = 0; col < data.cols; ++col)
        {
            Tree& tree = data.getTree(row, col);
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
            Tree& tree = data.getTree(row, data.cols - 1 - col);
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
            Tree& tree = data.getTree(row, col);
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
            Tree& tree = data.getTree(data.rows - 1 - row, col);
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
    Forest data;
    parse(input, data);

    int maxScore = 0;
    for (uint32_t row = 0; row < data.rows; ++row)
    {
        for (uint32_t col = 0; col < data.cols; ++col)
        {
            Tree& house = data.getTree(row, col);
            int score = 0;

            // Left
            int leftDistance = 0;
            for (int i = col - 1; i >= 0; i--)
            {
                Tree& other = data.getTree(row, i);
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
                Tree& other = data.getTree(row, i);
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
                Tree& other = data.getTree(i, col);
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
                Tree& other = data.getTree(i, col);
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
