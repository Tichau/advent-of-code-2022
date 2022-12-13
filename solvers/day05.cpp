#include "day05.hpp"
#include <iostream>
#include <regex>
#include <stack>

std::string day05_part1(std::ifstream& input)
{
    const int MAX_LEN = 40;
    const int MAX_STACK = 10;

    std::stack<char> stacks[MAX_STACK];
    
    bool parsingStacks = true;
    while (!input.eof())
    {
        char line[MAX_LEN];
        input.getline(line, MAX_LEN);
    
        if (parsingStacks)
        {
            if (line[1] == '1')
            {
                // Reverse stacks
                for (uint32_t i = 0; i < MAX_STACK; ++i)
                {
                    std::stack<char> buf;
                    while (!stacks[i].empty())
                    {
                        buf.push(stacks[i].top());
                        stacks[i].pop();
                    }
                    
                    stacks[i] = buf;
                }

                parsingStacks = false;
                input.getline(line, MAX_LEN); // blank line
            }
            else
            {
                std::regex stack_regex("\\s?(\\s\\s\\s|\\[[A-Z]\\])");
                auto stack_begin = std::cregex_iterator(line, line + MAX_LEN, stack_regex);
                auto stack_end = std::cregex_iterator();

                int stack = 1;
                for (std::cregex_iterator it = stack_begin; it != stack_end; ++it) {
                    std::cmatch match = *it;    
                    std::string match_str = match[1].str();
                    if (match_str != "   ")
                    {
                        stacks[stack].push(match_str[1]);
                    }

                    stack++;
                }

            }
        }
        else
        {
            std::cmatch matches;
            if (!std::regex_match(line, matches, std::regex("move ([0-9]+) from ([1-9]) to ([1-9])")))
            {
                std::cout << "Failed to parse line: " << line;
            }
            
            int count = stoi(matches[1]);
            int from = stoi(matches[2]);
            int to = stoi(matches[3]);

            for (uint32_t c = 0; c < count; ++c)
            {
                stacks[to].push(stacks[from].top());
                stacks[from].pop();
            }
        }
    }

    std::string result = "";

    for (uint32_t i = 0; i < MAX_STACK; ++i)
    {
        if (!stacks[i].empty())
        {
            result += stacks[i].top();
        }
    }

    return result;
}

std::string day05_part2(std::ifstream& input)
{
    const int MAX_LEN = 40;
    const int MAX_STACK = 10;

    std::stack<char> stacks[MAX_STACK];
    
    bool parsingStacks = true;
    while (!input.eof())
    {
        char line[MAX_LEN];
        input.getline(line, MAX_LEN);
    
        if (parsingStacks)
        {
            if (line[1] == '1')
            {
                // Reverse stacks
                for (uint32_t i = 0; i < MAX_STACK; ++i)
                {
                    std::stack<char> buf;
                    while (!stacks[i].empty())
                    {
                        buf.push(stacks[i].top());
                        stacks[i].pop();
                    }
                    
                    stacks[i] = buf;
                }

                parsingStacks = false;
                input.getline(line, MAX_LEN); // blank line
            }
            else
            {
                std::regex stack_regex("\\s?(\\s\\s\\s|\\[[A-Z]\\])");
                auto stack_begin = std::cregex_iterator(line, line + MAX_LEN, stack_regex);
                auto stack_end = std::cregex_iterator();

                int stack = 1;
                for (std::cregex_iterator it = stack_begin; it != stack_end; ++it) {
                    std::cmatch match = *it;    
                    std::string match_str = match[1].str();
                    if (match_str != "   ")
                    {
                        stacks[stack].push(match_str[1]);
                    }

                    stack++;
                }

            }
        }
        else
        {
            std::cmatch matches;
            if (!std::regex_match(line, matches, std::regex("move ([0-9]+) from ([1-9]) to ([1-9])")))
            {
                std::cout << "Failed to parse line: " << line;
            }
            
            int count = stoi(matches[1]);
            int from = stoi(matches[2]);
            int to = stoi(matches[3]);

            std::stack<char> buf;
            for (uint32_t c = 0; c < count; ++c)
            {
                buf.push(stacks[from].top());
                stacks[from].pop();
            }

            while (!buf.empty())
            {
                stacks[to].push(buf.top());
                buf.pop();
            }
        }
    }

    std::string result = "";

    for (uint32_t i = 0; i < MAX_STACK; ++i)
    {
        if (!stacks[i].empty())
        {
            result += stacks[i].top();
        }
    }

    return result;
}
