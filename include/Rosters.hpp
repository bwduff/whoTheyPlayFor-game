/** @file Rosters.hpp
 * Who they play for: Roster functions
 * Author: Brent Duff
 * Dec 15 2021
 * LICENSE: GNU GPLv3
 */
#ifndef ROSTERS_HPP
#define ROSTERS_HPP

#include <string>
#include <vector>
#include <unordered_set>

using namespace std; //I don't love doing this but it will make cpp easier to read

class Team{
    public: //Can eval privilege later
    std::string name;
    std::string abbrev;
    std::string csvPath;
    //TODO: Add team logo

    Team(){
        
    };

    Team(std::string Name, std::string Abbrev, std::string Path){
        this->name=Name;
        this->abbrev=Abbrev;
        this->csvPath=Path;
    }
};

class Player{
    public: //Can eval privilege later
    std::string name;
    //TODO: Add picture
    //TODO: Add pronoun attrib to correctly refer to players
    //TODO: Somehow, think of way to rate/rank obscurity of player, so that we can add difficulty level. 
    //      Total games played seems like a statistic that could at least be useful to distinguish vets from rookies, which usually correlates with name recognition.
    //      If rosters are imported between seasons (as is spirit of the game), then we can use Team's Per game table to get Games Played (GP) for each player.
    Team* team;

    Player(){

    }

    Player(std::string Name, Team* t){
        this->name = Name;
        this->team = new Team(t->name,t->abbrev,t->csvPath);
    }
};

bool InitRosters(void);
void SetRostersFromCSV(std::string filename);

std::vector<Team> importTeamsFromCSV(std::string filename);

bool fillRosterBook(Team*);

Player* QueryPlayerName(std::string qStr);

Player* GetRandomPlayer(void);

vector<string> csv2String(std::string filename, unordered_set<int> cs = {});

#endif // ROSTERS_HPP