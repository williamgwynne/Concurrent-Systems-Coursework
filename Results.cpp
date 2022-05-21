# include "Results.h"

Results::Results() {
    resArr[0][0] = "First: ";
    resArr[1][0] = "Second: ";
    resArr[2][0] = "Third: ";
    resArr[3][0] = "Fourth: ";
}

void Results::setPosition(Competitor c) {
    if (resArr[0][1].empty())
        resArr[0][1] = c.getTeam();
    else if (resArr[1][1].empty())
        resArr[1][1] = c.getTeam();
    else if (resArr[2][1].empty())
        resArr[2][1] = c.getTeam();
    else if (resArr[3][1].empty())
        resArr[3][1] = c.getTeam();
}

void Results::printResults(ThreadMap& tm) {
    std::cout << "Race Results" << endl;
    std::cout << "\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%" <<endl;
    for (int i = 0; i < 4; i++) {
        //needs to total and print all team times at some point
        std::cout << resArr[i][0] << resArr[i][1] << std::endl;
    }
    std::cout << "\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%\%" <<endl <<endl;

    tm.printTeamTimes(resArr[0][1], resArr[1][1], resArr[2][1], resArr[3][1]);
    tm.printIndividualTimes(resArr[0][1], resArr[1][1], resArr[2][1], resArr[3][1]);
}
