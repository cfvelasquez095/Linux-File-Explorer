#include "../headers/Utilities.h"

std::vector<std::string> Utilities::split(std::string text, char charac)
{
    std::stringstream test(text);
    std::string segment;
    std::vector<std::string> seglist;

    while(getline(test, segment, charac))
    {
       seglist.push_back(segment);
    }
    return seglist;
}