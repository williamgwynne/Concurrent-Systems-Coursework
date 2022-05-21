#pragma once
#include <string>
using namespace std;
class Competitor { // created in main and never updated, passed to a thread, placed in map
private:
    string teamName;
    string personName;
    int raceTime_millis;
public:
    Competitor();
    Competitor(string tN, string pN);
    void setTeam(string tN);
    string getTeam();
    void setPerson(string pN);
    string getPerson();
    static Competitor makeNull();
    void printCompetitor();
    void generateRaceTime();
    int getRaceTime_millis();
    float getRaceTime();
};

