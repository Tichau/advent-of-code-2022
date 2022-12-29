#include "day11.h"
#include <iostream>
#include <queue>
#include <vector>
#include <regex>
#include <assert.h>

using std::queue;
using std::vector;
using std::cout;
using std::endl;

enum class Operation {
    add,
    mul,
};

struct Monkey {
    int index;

    queue<uint32_t> items;
    int inspected_items;

    int left;
    Operation operation;
    int right;

    uint32_t test_divider;
    int true_monkey_index;
    int false_monkey_index;
};

void parse(std::ifstream& input, vector<Monkey>& monkeys)
{
    const int MAX_LEN = 64;

    while (!input.eof())
    {
        char line[MAX_LEN];
        input.getline(line, MAX_LEN);

        std::cmatch matches;
        if (!std::regex_match(line, matches, std::regex("Monkey\\s([0-9]+):")))
        {
            std::cerr << "Failed to parse line: " << line;
            exit(1);
        }

        Monkey monkey;
        monkey.index = stoi(matches[1]);
        monkey.inspected_items = 0;

        input.getline(line, MAX_LEN);
        auto item_regex = std::regex("([0-9]+)");
        auto stack_begin = std::cregex_iterator(line, line + strlen(line), item_regex);
        auto stack_end = std::cregex_iterator();

        for (std::cregex_iterator it = stack_begin; it != stack_end; ++it) {
            std::cmatch match = *it;    
            std::string match_str = match[1].str();

            monkey.items.push(stoi(match_str));
        }

        input.getline(line, MAX_LEN);
        if (!std::regex_match(line, matches, std::regex("  Operation: new = (old|[0-9]+) (\\+|\\*) (old|[0-9]+)")))
        {
            std::cerr << "Failed to parse line: " << line;
            exit(1);
        }

        monkey.left = matches[1].str() == "old" ? -1 : stoi(matches[1].str());
        monkey.right = matches[3].str() == "old" ? -1 : stoi(matches[3].str());

        if (matches[2].str() == "+")
        {
            monkey.operation = Operation::add;
        }
        else if (matches[2].str() == "*")
        {
            monkey.operation = Operation::mul;
        }
        else
        {
            std::cerr << "Unknown operation";
            exit(1);
        }

        input.getline(line, MAX_LEN);
        if (!std::regex_match(line, matches, std::regex("  Test: divisible by ([0-9]+)")))
        {
            std::cerr << "Failed to parse line: " << line;
            exit(1);
        }

        monkey.test_divider = stoi(matches[1].str());

        input.getline(line, MAX_LEN);
        if (!std::regex_match(line, matches, std::regex("    If true: throw to monkey ([0-9]+)")))
        {
            std::cerr << "Failed to parse line: " << line;
            exit(1);
        }

        monkey.true_monkey_index = stoi(matches[1].str());
        
        input.getline(line, MAX_LEN);
        if (!std::regex_match(line, matches, std::regex("    If false: throw to monkey ([0-9]+)")))
        {
            std::cerr << "Failed to parse line: " << line;
            exit(1);
        }

        monkey.false_monkey_index = stoi(matches[1].str());

        monkeys.push_back(monkey);
        
        if (!input.eof())
        {
            input.getline(line, MAX_LEN);
        }
    }
}

uint32_t day11_part1(std::ifstream& input)
{
    vector<Monkey> monkeys;
    parse(input, monkeys);

    for (int round = 1; round <= 20; ++round)
    {
        for (auto& monkey : monkeys)
        {
            while (!monkey.items.empty())
            {
                auto item = monkey.items.front();

                auto left = monkey.left < 0 ? item : monkey.left;
                auto right = monkey.right < 0 ? item : monkey.right;

                switch (monkey.operation)
                {
                case Operation::add:
                    item = left + right;
                    break;
                
                case Operation::mul:
                    item = left * right;
                    break;
                }

                item /= 3;

                if ((item % monkey.test_divider) == 0)
                {
                    monkeys[monkey.true_monkey_index].items.push(item);
                }
                else
                {
                    monkeys[monkey.false_monkey_index].items.push(item);
                }

                monkey.inspected_items++;
                monkey.items.pop();
            }
        }
        
        cout << endl;
    }

    int active_monkey_0 = -1;
    int active_monkey_1 = -1;

    for (auto& monkey : monkeys)
    {
        if (monkey.inspected_items > active_monkey_0)
        {
            if (active_monkey_0 > active_monkey_1)
            {
                active_monkey_1 = active_monkey_0;
            }

            active_monkey_0 = monkey.inspected_items;
        }
        else if (monkey.inspected_items > active_monkey_1)
        {
            if (active_monkey_1 > active_monkey_0)
            {
                active_monkey_0 = active_monkey_1;
            }

            active_monkey_1 = monkey.inspected_items;
        }
    }

    return active_monkey_0 * active_monkey_1;
}

uint64_t day11_part2(std::ifstream& input)
{
    vector<Monkey> monkeys;
    parse(input, monkeys);

    uint32_t common_divider = 1;
    for (auto monkey : monkeys)
    {
        common_divider *= monkey.test_divider;
    }

    for (int round = 1; round <= 10000; ++round)
    {
        for (auto& monkey : monkeys)
        {
            while (!monkey.items.empty())
            {
                uint64_t item = monkey.items.front();

                auto left = monkey.left < 0 ? item : monkey.left;
                auto right = monkey.right < 0 ? item : monkey.right;

                switch (monkey.operation)
                {
                case Operation::add:
                    item = left + right;
                    break;
                
                case Operation::mul:
                    item = left * right;
                    break;
                }

                item %= common_divider;

                if ((item % monkey.test_divider) == 0)
                {
                    monkeys[monkey.true_monkey_index].items.push((uint32_t)item);
                }
                else
                {
                    monkeys[monkey.false_monkey_index].items.push((uint32_t)item);
                }

                monkey.inspected_items++;
                monkey.items.pop();
            }
        }
        
        if (round == 1 || round == 20 || round % 1000 == 0)
        {
            cout << "Round: " << round << endl;
            for (auto& monkey : monkeys)
            {
                cout << "Monkey " << monkey.index << " inspected items " << monkey.inspected_items << " times." << endl;
            }

            cout << endl;
        }
    }

    int64_t active_monkey_0 = -1;
    int64_t active_monkey_1 = -1;

    for (auto& monkey : monkeys)
    {
        if (monkey.inspected_items > active_monkey_0)
        {
            if (active_monkey_0 > active_monkey_1)
            {
                active_monkey_1 = active_monkey_0;
            }

            active_monkey_0 = monkey.inspected_items;
        }
        else if (monkey.inspected_items > active_monkey_1)
        {
            if (active_monkey_1 > active_monkey_0)
            {
                active_monkey_0 = active_monkey_1;
            }

            active_monkey_1 = monkey.inspected_items;
        }
    }

    return active_monkey_0 * active_monkey_1;
}
