#pragma once
#include <iostream>
#include <string>
#include "Competitor.h"
#include "ThreadMap.h"

class Results {
private:
    std::string resArr[4][2];
public:
    Results();
    void setPosition(Competitor c);
    void printResults(ThreadMap& tm);
};
