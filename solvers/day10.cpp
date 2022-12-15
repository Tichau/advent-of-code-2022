#include "day10.h"
#include <iostream>
#include <queue>
#include <regex>

using std::queue;
using std::cout;
using std::endl;

enum class Operation {
    noop,
    addx, 
};

struct Instruction {
    Operation operation;
    int16_t arg;
};

void parse(std::ifstream& input, queue<Instruction>& program)
{
    const int MAX_LEN = 16;

    while (!input.eof())
    {
        char line[MAX_LEN];
        input.getline(line, MAX_LEN);

        std::cmatch matches;
        if (!std::regex_match(line, matches, std::regex("(noop|addx)(:?\\s(-?[0-9]+))?")))
        {
            std::cerr << "Failed to parse line: " << line;
            exit(1);
        }

        Instruction instruction;
        if (matches[1].str() == "noop")
        {
            instruction.operation = Operation::noop;
        }
        else if (matches[1].str() == "addx")
        {
            instruction.operation = Operation::addx;
            instruction.arg = stoi(matches[2]);
        }
        else
        {
            std::cerr << "Unknown operation";
            exit(1);
        }
        
        program.push(instruction);
    }
}

uint32_t day10_part1(std::ifstream& input)
{
    queue<Instruction> program;
    parse(input, program);

    int x = 1;
    int cycle = 1;
    int strength = 0;

    int remainingCycles = 0;
    while (!program.empty())
    {
        if ((cycle - 20) % 40 == 0)
        {
            strength += cycle * x;
        }

        if (remainingCycles <= 0)
        {
            switch (program.front().operation)
            {
                case Operation::noop:
                    remainingCycles = 1;
                    break;

                case Operation::addx:
                    remainingCycles = 2;
                    break;
            }
        }

        remainingCycles--;

        if (remainingCycles == 0)
        {
            if (program.front().operation == Operation::addx)
            {
                x += program.front().arg;
            }

            program.pop();
        }

        cycle++;
    }
    
    return strength;
}

uint32_t day10_part2(std::ifstream& input)
{
    queue<Instruction> program;
    parse(input, program);

    cout << endl;

    int x = 1;
    int cycle = 1;
    int strength = 0;

    int remainingCycles = 0;
    while (!program.empty())
    {
        int index = (cycle - 1) % 40;
        if (abs(x - index) < 2)
        {
            cout << "#";
        }
        else
        {
            cout << ".";
        }

        if (cycle % 40 == 0)
        {
            cout << endl;
        }

        if (remainingCycles <= 0)
        {
            switch (program.front().operation)
            {
                case Operation::noop:
                    remainingCycles = 1;
                    break;

                case Operation::addx:
                    remainingCycles = 2;
                    break;
            }
        }

        remainingCycles--;

        if (remainingCycles == 0)
        {
            if (program.front().operation == Operation::addx)
            {
                x += program.front().arg;
            }

            program.pop();
        }

        cycle++;
    }
    
    cout << endl;
    
    return 0;
}
