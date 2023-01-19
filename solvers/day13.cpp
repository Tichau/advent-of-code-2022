#include "day13.h"
#include <iostream>
#include <regex>
#include <vector>
#include <assert.h>

#include "../utils/pos.h"

using std::vector;
using std::cout;
using std::endl;

struct Element
{
    enum {
        value,
        list,
    } type;
    union
    {
        uint32_t value;
        vector<Element>* list;
    } content;

    Element()
    {
        type = value;
        content.value = 0;
    }

    Element(const Element& other)
    {
        type = other.type;
        if (type == value)
        {
            content.value = other.content.value;
        }
        else if (type == list)
        {
            content.list = other.content.list;
        }
    }

    static Element Value(uint32_t _value) 
    {
        auto element = Element();
        element.type = value;
        element.content.value = _value;
        return element;
    }

    static Element List() 
    {
        auto element = Element();
        element.type = list;
        element.content.list = new vector<Element>();
        return element;
    }
};

size_t parse(const char* line, size_t startIndex, const size_t lineLength, vector<Element>& elements);

struct Packet
{
    bool isDivider;
    Element root;

    Packet(const char* _encoded, bool _divider)
    {
        isDivider = _divider;
        root = Element::List();
        
        auto lineLength = strlen(_encoded);
        size_t i = parse(_encoded, 0, lineLength, *root.content.list);

        assert(i == lineLength - 1);
    }
};

void parse(std::ifstream& input, vector<Packet>& packets)
{
    const int MAX_LEN = 256;

    while (!input.eof())
    {
        char line[MAX_LEN];
        input.getline(line, MAX_LEN);
        auto lineLength = strlen(line);
        assert(lineLength < MAX_LEN);
        if (lineLength > 0)
        {
            packets.push_back(Packet(line, false));
        }
    }
}

size_t parse(const char* line, size_t startIndex, const size_t lineLength, vector<Element>& elements)
{
    assert(line[startIndex] == '[');
    startIndex++;
    for (size_t i = startIndex; i < lineLength; ++i)
    {
        auto c = line[i];

        std::cmatch matches;
        if (std::regex_match(&line[i], &line[lineLength - 1], matches, std::regex("^([0-9]+).*")))
        {
            auto number = stoi(matches[1].str());
            elements.push_back(Element::Value(number));
            i += matches[1].str().length() - 1;
        }
        else if (c == '[')
        {
            elements.push_back(Element::List());
            vector<Element>& subElement = *elements[elements.size() - 1].content.list;
            i = parse(line, i, lineLength, subElement);
        }
        else if (c == ']')
        {
            return i;
        }
    }

    return lineLength;
}

int compare(vector<Element>& leftList, vector<Element>& rightList)
{
    for (int i = 0; i < leftList.size() && i < rightList.size(); ++i)
    {
        Element& leftElement = leftList[i];
        Element& rightElement = rightList[i];
        if (leftElement.type == Element::value && rightElement.type == Element::value)
        {
            if (leftElement.content.value < rightElement.content.value)
            {
                return -1;
            }
            else if (leftElement.content.value > rightElement.content.value)
            {
                return 1;
            }
        }
        else if (leftElement.type == Element::value && rightElement.type == Element::list)
        {
            int leftValue = leftElement.content.value;
            leftList[i] = Element::List();
            leftList[i].content.list->push_back(Element::Value(leftValue));
        }
        else if (leftElement.type == Element::list && rightElement.type == Element::value)
        {
            int rightValue = rightElement.content.value;
            rightList[i] = Element::List();
            rightList[i].content.list->push_back(Element::Value(rightValue));
        }
        
        if (leftElement.type == Element::list && rightElement.type == Element::list)
        {
            int result = compare(*(leftElement.content.list), *(rightElement.content.list));
            if (result != 0)
            {
                return result;
            }
        }
    }

    if (leftList.size() == rightList.size())
    {
        return 0;
    }
    else if (leftList.size() < rightList.size())
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

uint32_t day13_part1(std::ifstream& input)
{
    vector<Packet> packets;
    parse(input, packets);

    int score = 0;
    for (int i = 0; i < packets.size(); ++i)
    {
        int id = i / 2 + 1;
        Packet& left = packets[i++];
        Packet& right = packets[i];

        if (compare(*(left.root.content.list), *(right.root.content.list)) < 0)
        {
            score += id;
        }
    }

    return score;
}

uint32_t day13_part2(std::ifstream& input)
{
    vector<Packet> packets;
    parse(input, packets);
    packets.push_back(Packet("[[2]]", true));
    packets.push_back(Packet("[[6]]", true));

    std::sort(packets.begin(), packets.end(), [](Packet& left, Packet& right) { return compare(*left.root.content.list, *right.root.content.list) < 0; });

    int result = 1;
    for (int i = 0; i < packets.size(); ++i)
    {
        if (packets[i].isDivider)
        {
            result *= (i + 1);
        }
    }

    return result;
}
