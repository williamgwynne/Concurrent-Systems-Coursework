#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <fstream>
#include <mutex>
#include "Competitor.h"
#include "ThreadMap.h"
#include "SyncAgent.h"

std::mutex mu_cout; //to prevent multiple threads from having cout operations interleaved


void run(Competitor& c, ThreadMap& tm, SyncAgent& lineUp, SyncAgent& nextRunner) { //uses parent class type SyncAgent as StartAgent used when first runner is passed, EZAgent used for subsequent threads
    //store thread id and competitor in a map
    tm.insertThreadPair(c);

    lineUp.pause(); //as lineUp is passed as object its parent class, this line works both for StartAgent and EZAgent

    //simulate the race
    std::this_thread::sleep_for(std::chrono::milliseconds(c.getRaceTime_millis()));


    nextRunner.proceed(); //when 1 runner finishes their 100m, the next waiting thread is released - i.e. the baton is exchanged

    //prints result AFTER releasing next thread so it is not waiting on another thread to output before it releases
    std::lock_guard<std::mutex> locker(mu_cout); //treats cout as a critical section so integrity of printed data is preserved; lock_guard (or unique_lock) has unlock in its destructor so guarantees unlocking
    //std::cout << "Athlete : " << c.getPerson() << endl << "Team : " << c.getTeam() << endl << "Time : " << c.getRaceTime() << endl << endl;
}

int main() {
    const int NO_TEAMS = 4;
    const int NO_MEMBERS = 4;

    srand(time(0));
    const int NO_EXCHANGES = (NO_MEMBERS - 1);

    Competitor c[NO_MEMBERS][NO_TEAMS];
    ThreadMap tm;

    std::thread Comps[NO_MEMBERS][NO_TEAMS]; //declaring threads, but not initialising

    StartAgent StartingGun; //named appropriately, used to release threads at the start of the race
    EZAgent BatonExchange[NO_EXCHANGES][NO_TEAMS]; //used at the end of each thread to unlock the next
    FinishAgent FinishLine(ref(tm)); //used after final runner per team to store race results


    string teamName, competitorName;
    ifstream Names("names.txt"); //text file filled with first-names: downloaded from https://www.usna.edu/Users/cs/roche/courses/s15si335/proj1/files.php%3Ff=names.txt.html

    for (int runner=0; runner<NO_MEMBERS; runner++) //concurrent code begins
        for (int team=0; team<NO_TEAMS; team++)
        {
            switch (team) {
                case 0:
                    teamName = "Red";
                    break;
                case 1:
                    teamName = "Blue";
                    break;
                case 2:
                    teamName = "Green";
                    break;
                case 3:
                    teamName = "Yellow";
                    break;
                default:
                    teamName = "Team #" + std::to_string(team) + " (unnamed)";
            }
            getline(Names, competitorName);
            c[runner][team] = Competitor(teamName, competitorName);

            c[runner][team].generateRaceTime();
            if (runner == 0)
                Comps[runner][team] = std::thread(run, ref(c[runner][team]), ref(tm), ref(StartingGun), ref(BatonExchange[runner][team]));

            else if (runner == NO_EXCHANGES) //WHEN CALLING FINAL RUNNER IN EACH TEAM
                Comps[runner][team] = std::thread(run, ref(c[runner][team]), ref(tm), ref(BatonExchange[runner-1][team]), ref(FinishLine)); //Next SyncAgent is the race end
            else
                Comps[runner][team] = std::thread(run, ref(c[runner][team]), ref(tm), ref(BatonExchange[runner-1][team]), ref(BatonExchange[runner][team])); //initialising threads, waits on its EZAgent and unlocks the next
        }
    Names.close(); //closes name file
    StartingGun.proceed(); //After all threads are created and suspended, one from each team must be released which happens in proceed

    for (int i=0; i<NO_MEMBERS; i++)
        for (int j=0; j<NO_TEAMS; j++)
        {
            Comps[i][j].join(); //Concurrent code ends
        }

        FinishLine.returnResults().printResults(tm);
        //tm.printMapContents();
}
