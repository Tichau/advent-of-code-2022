#include "day07.hpp"
#include <iostream>
#include <string>
#include <regex>
#include <array>
#include <assert.h>

using std::string;

struct entry {
    string name;
    bool isDir;
    uint32_t size;
    entry* parent;

    entry()
    {
        name = string();
        isDir = false;
        size = 0;
        parent = nullptr;
    }

    entry(string _name, bool _isDir, uint32_t _size, entry* _parent)
    {
        name = _name;
        isDir = _isDir;
        size = _size;
        parent = _parent;
    }
};

enum command 
{
    ls, 
    cd,
};

const int MAX_ENTRY = 4096;

void parse(std::ifstream& input, std::array<entry, MAX_ENTRY>& entries, uint32_t& entriesCount)
{
    const int MAX_LEN = 32;
    
    command currentCmd;
    entry* currentDir = nullptr;

    entries[entriesCount++] = entry("/", true, 0, nullptr);

    while (!input.eof())
    {
        char line[MAX_LEN];
        input.getline(line, MAX_LEN);

        if (line[0] == '$')
        {
            std::cmatch matches;
            if (!std::regex_match(line, matches, std::regex("\\$\\s(cd|ls)(?:\\s(\\/|[a-z]+|\\.\\.))?")))
            {
                std::cerr << "Failed to parse line: " << line;
                exit(1);
            }

            const auto cmdName = matches[1].str();
            if (cmdName == "ls")
            {
                currentCmd = command::ls;
            }
            else if (cmdName == "cd")
            {
                currentCmd = command::cd;
                string commandArg = matches[2].str();
                if (commandArg == "..")
                {
                    currentDir = currentDir->parent;
                }
                else
                {
                    auto result = std::find_if(entries.begin(), entries.end(), [&commandArg, currentDir](const entry &arg) { return arg.name == commandArg && arg.parent == currentDir; });
                    if (result == std::end(entries))
                    {
                        std::cerr << "Can't go to directory: " << commandArg;
                        exit(1);
                    }

                    currentDir = &(*result);
                }
                
                if (!currentDir->isDir)
                {
                    std::cerr << commandArg << "is not a directory.";
                    exit(1);
                }
            }
            else
            {
                std::cerr << "Unknown command: " << cmdName;
                exit(1);
            }
        }
        else if (currentCmd == command::ls)
        {
            std::cmatch matches;
            if (std::regex_match(line, matches, std::regex("dir\\s([a-z]+)")))
            {
                auto folderName = matches[1].str();

                auto result = std::find_if(entries.begin(), entries.end(), [&folderName, currentDir](const entry &arg) { return arg.name == folderName && arg.parent == currentDir; });
                if (result == std::end(entries))
                {
                    entries[entriesCount++] = entry(folderName, true, 0, currentDir);
                }
            }
            else if (std::regex_match(line, matches, std::regex("([0-9]+)\\s([a-z\\.]+)")))
            {
                uint32_t fileSize = stoi(matches[1].str());
                auto fileName = matches[2].str();

                auto result = std::find_if(entries.begin(), entries.end(), [&fileName, currentDir](const entry &arg) { return arg.name == fileName && arg.parent == currentDir; });
                if (result == std::end(entries))
                {
                    entries[entriesCount++] = entry(fileName, false, fileSize, currentDir);
                    // propagate size.
                    entry* folder = currentDir;
                    while (folder != nullptr)
                    {
                        folder->size += fileSize;
                        folder = folder->parent;
                    }
                }
            }
            else
            {
                std::cerr << "Can't parse result: " << line;
                exit(1);
            }
        }
        else
        {
            std::cerr << "Invalid command: " << currentCmd;
            exit(1);
        }
    }
}

uint32_t day07_part1(std::ifstream& input)
{
    std::array<entry, MAX_ENTRY> entries;
    uint32_t entriesCount = 0;

    parse(input, entries, entriesCount);

    int totalSize = 0;
    for (uint32_t i = 1; i < entriesCount; ++i)
    {
        if (entries[i].isDir && entries[i].size <= 100000)
        {
            totalSize += entries[i].size;
        }
    }

    return totalSize;
}

uint32_t day07_part2(std::ifstream& input)
{
    std::array<entry, MAX_ENTRY> entries;
    uint32_t entriesCount = 0;

    parse(input, entries, entriesCount);

    uint32_t totalDiskSpace = 70000000;
    uint32_t needSpace = 30000000;

    uint32_t remainingSpace = totalDiskSpace - entries[0].size;
    uint32_t missingSpace = needSpace - remainingSpace;

    uint32_t minFolderSize = UINT32_MAX;
    for (uint32_t i = 0; i < entriesCount; ++i)
    {
        if (entries[i].isDir && entries[i].size >= missingSpace && entries[i].size < minFolderSize)
        {
            minFolderSize = entries[i].size;
        }
    }

    return minFolderSize;
}
