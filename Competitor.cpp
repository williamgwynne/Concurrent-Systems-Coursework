#include "Competitor.h"
#include <iostream>

Competitor::Competitor() {}

Competitor::Competitor(string tN, string pN) : teamName(tN), personName(pN) {}

void Competitor::setTeam(string tN) { teamName = tN; }
string Competitor::getTeam() { return teamName; }

void Competitor::setPerson(string pN) { personName = pN; }
string Competitor::getPerson() { return personName; }

Competitor Competitor::makeNull() {
    return *(new Competitor(" ", " "));
}

void Competitor::printCompetitor() {
    std::cout << "Team = " << teamName << " Person = " << personName << std::endl;
}

void Competitor::generateRaceTime()
{
    //using team times for both men's and women's 4x100m sprint from Tokyo 2020 (excluding DNFs/Disqualifications)
    //mean team time = 40.3675 seconds, so mean individual time ~=10.092 seconds
    //team standard deviation = 2.3691, so standard deviation to individual time ~=0.592 seconds
    //therefore to cover 95% of the normal distribution, the random time should be calcualted as mean+-2*standard deviation
    //(equavalent as rand()%4*standard deviation+(mean-2*standard deviation):
    raceTime_millis = rand()%2368 + 8908;
    //baton exchanges can occur within a 20 metre zone so average individual time is reduced (speed of team mate can be matched)
    //which is why it is possible to "beat" Usain Bolt's 9.58 seconds
}

int Competitor::getRaceTime_millis()
{
    return raceTime_millis;
}

float Competitor::getRaceTime()
{
    return raceTime_millis/1000.0;
}

