#ifndef UTILITIES_H
#define UTILITIES_H


#include <iostream>
#include <vector>
#include <stdio.h>
#include <sstream>

class Utilities
{
    public:
        static std::vector<std::string> split(std::string text,char charac);

    private:
        Utilities(){}


};

#endif