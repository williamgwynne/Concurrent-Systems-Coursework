#include "ThreadMap.h"

ThreadMap::ThreadMap() {};

// ThreadMap will compile but won't do anyhing useful until code is added to insertThreadPair and printMapContents
void ThreadMap::insertThreadPair(Competitor c) {
    // create a threadID, Competitor pair using a call to std::make_pair
    // store the pair in the map using the map insert member function
    threadComp.insert(std::pair<std::thread::id, Competitor>(std::this_thread::get_id(), c));
}

Competitor ThreadMap::getCompetitor() {
	std::map <std::thread::id, Competitor>::iterator it = threadComp.find(std::this_thread::get_id());
	if (it == threadComp.end())
		return Competitor::makeNull();						//	alternatively	return *(new Competitor(" ", " "));
	else
		return it->second;								// i.e. the second item in the pair
}

void ThreadMap::printMapContents() {
	std::cout << "MAP CONTENTS:" << std::endl;
	// you need to write the rest!
	for(auto it = threadComp.begin(); it != threadComp.end(); it++) { //iterates through each index of the thread map
        std::cout << "Thread ID: " << it->first << endl << "Competitor: " << it->second.getPerson() << endl << "Team: " << it->second.getTeam() << endl << "Time: " << it->second.getRaceTime() << endl << endl; //the thread id is stored first then the Competitor c object is stored in the second so member function can be accessed as such
    }

	cout << "END MAP CONTENTS" << endl;
}

void ThreadMap::printTeamTimes(string first, string second, string third, string fourth) {
    //first calculates total times for each team
    float team_times[4] = {0};
    float time;
    string team;
    for(auto it = threadComp.begin(); it != threadComp.end(); it++) { //iterates through each index of the thread map
        time = it->second.getRaceTime();
        team = it->second.getTeam();
        if (team == first)
            team_times[0] += time;
        else if (team == second)
            team_times[1] += time;
        else if (team == third)
            team_times[2] += time;
        else if (team == fourth)
            team_times[3] += time;
    }

    //then display data
    std::cout << "Total Team Times" <<endl;
    std::cout << "\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%" <<endl;
    std::cout << first << " Team: " << team_times[0] << " s" << endl;
    std::cout << second << " Team: " << team_times[1] << " s" << endl;
    std::cout << third << " Team: " << team_times[2] << " s" << endl;
    std::cout << fourth << " Team: " << team_times[3] << " s" << endl;
    std::cout << "\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%" <<endl <<endl;
}

void ThreadMap::printTimes(string team) {
    std::cout << team << " Team:" << endl;
    for(auto it = threadComp.begin(); it != threadComp.end(); it++) { //iterates through each index of the thread map
        if (it->second.getTeam() == team)
        {
            std::cout << it->second.getPerson() << ": " << it->second.getRaceTime() << " s" <<endl;
        }
    }
}

void ThreadMap::printIndividualTimes(string first, string second, string third, string fourth) {
    std::cout << "Individual Times" << endl;
    std::cout << "\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%" <<endl;


    printTimes(first);
    std::cout <<endl << "\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%" <<endl <<endl;
    printTimes(second);
    std::cout <<endl << "\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%" <<endl <<endl;
    printTimes(third);
    std::cout <<endl << "\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%" <<endl <<endl;
    printTimes(fourth);
    std::cout << endl << "\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%" <<endl <<endl;

}

int ThreadMap::ThreadMapSize() { return threadComp.size(); }
