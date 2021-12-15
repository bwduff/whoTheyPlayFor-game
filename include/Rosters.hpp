/** @file Rosters.hpp
 * Who they play for: Roster functions
 * Author: Brent Duff
 * Dec 15 2021
 * LICENSE: GNU GPLv3
 */

#include <string>
#include <vector>

using namespace std; //I don't love doing this but it will make cpp easier to read

class Player{
    public: //Can eval privilege later
    std::string name;
    //TODO: Add picture
    Team team;
};

class Team{
    public: //Can eval privilege later
    std::string name;
    std::string abbrev;
    std::string csvPath;
    //TODO: add team logo
};

void SetRostersFromCSV(std::string filename);

std::vector<Team> importTeamsFromCSV(std::string filename);

bool fillRosterBook(Team);
