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

using namespace std; //I don't love doing this but it will make cpp easier to read

class Team{
    public: //Can eval privilege later
    std::string name;
    std::string abbrev;
    std::string csvPath;
    //TODO: add team logo

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
    Team* team;

    Player(){

    }

    Player(std::string Name, Team* t){
        this->name = Name;
        this->team = t;
    }
};

bool InitRosters(void);
void SetRostersFromCSV(std::string filename);

std::vector<Team> importTeamsFromCSV(std::string filename);

bool fillRosterBook(Team*);

vector<string> csv2String(std::string filename);

//Overloaded version with arr[] specified columns to extract
//vector<string> csv2String(std::string filename, vector<int>* cs);

#endif // ROSTERS_HPP