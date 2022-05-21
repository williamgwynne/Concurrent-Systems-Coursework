#pragma once
#include <iostream>
#include <thread>
#include <map>
#include <string>
#include "Competitor.h"
class ThreadMap {
private:
    std::map <std::thread::id, Competitor> threadComp;  //map of thread ids v. Competitors
    void printTimes(string team);
public:
    ThreadMap();
    void insertThreadPair(Competitor c);
    Competitor getCompetitor();
    void printMapContents();
    void printTeamTimes(string first, string second, string third, string fourth);
    void printIndividualTimes(string first, string second, string third, string fourth);
    int ThreadMapSize();
};
