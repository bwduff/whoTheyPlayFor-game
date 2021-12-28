/** @file Rosters.cpp
 * Who they play for: Roster functions
 * Author: Brent Duff
 * Dec 12 2021
 * LICENSE: GNU GPLv3
 */
#include <string>
#include <vector>
#include <fstream>
#include <utility> // std::pair
#include <stdexcept> // std::runtime_error
#include <sstream> // std::stringstream
#include <unordered_set> //RosterBook
#include <iostream> //std::cout

#include "Rosters.hpp"
#define TEST_FILENAME "../data/csv/LeagueRosterPullTest.csv"
 //TODO: Find out how to parse CSV from BBRef.com into dictionary
 /*
 No.,Player,Pos,Ht,Wt,Birth Date,,Exp,College
,,,,,,,,
22,Andrew Wiggins,SF,6-7,197,February 23 1995,ca,7,Kansas
3,Jordan Poole,SG,6-4,194,June 19 1999,us,2,Michigan
8,Nemanja Bjelica,C,6-10,234,May 9 1988,rs,6,
5,Kevon Looney,C,6-9,222,February 6 1996,us,6,UCLA
30,Stephen Curry,PG,6-2,185,March 14 1988,us,12,Davidson
23,Draymond Green,PF,6-6,230,March 4 1990,us,9,Michigan State
0,Gary Payton II,PG,6-3,190,December 1 1992,us,5,Oregon State
95,Juan Toscano-Anderson,SF,6-6,209,April 10 1993,us,2,Marquette
32,Otto Porter,PF,6-8,198,June 3 1993,us,8,Georgetown
1,Damion Lee,SG,6-5,210,October 21 1992,us,4,Drexel Louisville
4,Moses Moody,SG,6-6,205,May 31 2002,us,R,Arkansas
00,Jonathan Kuminga,SF,6-8,210,October 6 2002,cd,R,
9,Andre Iguodala,SF,6-6,215,January 28 1984,us,17,Arizona
2,Chris Chiozza  (TW),PG,5-11,175,November 21 1995,us,3,Florida
21,Jeff Dowtin  (TW),PG,6-3,185,May 10 1997,us,R,Rhode Island
,James Wiseman,C,7-0,240,March 31 2001,us,1,Memphis
,Klay Thompson,SG,6-6,215,February 8 1990,us,8,Washington State
*/

/*Roster global variable. Used to look up key (player name) and match with team*/
//I have mixed thoughts on Player / Team class usage, but lets go with this for now.
//unordered_set<string,Team> RosterBook;

bool InitRosters(void){
	 //TODO: Implement by looking up CSV file in data dir.
     SetRostersFromCSV(TEST_FILENAME);
     return true;
}

//TODO: Add error checking & return status
void SetRostersFromCSV(string filename){
    //RosterBook is global var that we store data in. Encapsulating in class might be better.

    //BB-ref CSV files have format:
    //No.,Player,Pos,Ht,Wt,Birth Date,,Exp,College
    //We don't care about any column except #1
    //Due to lack of leaguewide CSV matching players to teams, 30 CSVs need to be processed...
    //That is not ideal. OH well, I guess that's what I need to do. I can always write a script to merge them later.

    //Initially I will pass in a CSV list of team CSVs to read. This allows me to maximize reuse of i/o parsing code.
    //League CSV will contain columns: Team Name, Team Abbreviation, file path
    //Therefore I'd really like a generic CSV function that reads arbitrary # of columns for arbitrary # of strings.

    //When reading in League CSV, I can set Team name and abbreviation which can be used to find logo too.
    //Lets just return team objects.
    vector<Team> teamList = importTeamsFromCSV(filename);
    
    //OK, now that we have team list we can iterate through and read player names and insert into RosterBook object.
    int importFailCount=0;
    for(auto& t : teamList){
        //Go through team CSVs and create players. Store players solely in RosterBook
        if(fillRosterBook(&t)){
            cout << "WARNING! Error encountered when filling roster book with Team: " << t.name \
            << " who has filepath: '" << t.csvPath << "'" << endl;
            importFailCount++;
        } else
            cout << "Team: " << t.name << "imported from: '"<< t.csvPath \
            << "', with abbreviation " <<  t.abbrev << endl;
    }
    if(importFailCount) cout << "WARNING: Failed to load " << importFailCount \
    << "teams! Search database will be limited." << endl;
}

//TODO: Test
std::vector<Team> importTeamsFromCSV(std::string filename){
    vector<Team> teams; 
    //Go through CSV and parse into team objects.
    //Column format is Team Name, Abbrev, CSV.
    //Need to write generic csv2string function to enable easy reads of team CSVs + player
    vector<string> csvContents = csv2String(filename);
    //Becuase we know by design the table's dimensions are 3xN, we can easily pop values
    //into team objects
    
    //Vector layout: 
    //[0] Load team, [1] Abbrev
    //[2] Team Name, [3] CSV path
    //Iterate x4
    for(uint i=0; i < csvContents.size();i+=4){
            string loadTeam = csvContents[i];
            string abbrev = csvContents[i+1];
            string teamName = csvContents[i+2];
            string csvPath = csvContents[i+3];
    
            if (loadTeam != "")
                teams.push_back(Team(teamName,abbrev,csvPath)); 
    }

    return teams;
}

//TODO: Impl
bool fillRosterBook(Team* t){
    //Go to team Ccsv2StringSV, read all contents, then parse.
    unordered_set<int> columnSelect = {1};
    vector<string> csvContents = csv2String(t->csvPath,columnSelect);
    
    //csv will have BBRef format:
    //0  , 1    , 2 ,3, 4 , 5        ,6,7,8
    //No.,Player,Pos,Ht,Wt,Birth Date,,Exp,College
 
    //for(int i=0; i < csvContents.size();i++){
    //   Player* p = new Player(csvContents[i],t);
       //std::pair<unordered_set<string,Team>::iterator,bool> ret;
       //ret = RosterBook.insert(p->name,t);
       //TODO: I'm using a lot of pointers to objects. At what point do I replace this with
       //objects instead?
    //}


    return true;
}

vector<std::string> csv2String(std::string filename, unordered_set<int> cs){
    vector<string> result;
    bool exportAllCols = true;
    
    //Creating in file stream
    std::ifstream file;


    // Make sure the file is open
    file.open(filename.c_str(),std::ifstream::in);
    //file.open(filename,std::ifstream::in);
    if(!file.is_open()) throw std::runtime_error("Could not open file");

    //Helper vars
    std::string line, cellVal;
    int numCols=0;
    char ch;
    
    //Error check
    if(!file.good()) std::cout << "ERROR! File is corrupted." << std::endl;
    
    // Extract the first line in the file
    std::getline(file, line);
    // FIles must have a header row with each column filled to be valid, otherwise undefined behavior
    std::stringstream firstline(line);
    
    // Create a stringstream from lines &
    // cycle through each cell to count cols to correct empty last col
    while(std::getline(firstline,cellVal, ',')){
        //Calculate numCols 
        numCols++;
    }
    //Check Col Select vector before proceeding. If CS > numCols return error.
    if(cs.size()){
      //null means report all columns
      //Technically i have to check each entry of CS
      exportAllCols = false;
      for(auto& i : cs){
          if(i>numCols){
              exit(-1);
          } //otherwise, valid selection
          //how to use any of this to select?
      }
    }

    while(std::getline(file,line)){
        //Issue when CSV path (last column) is blank. I could just load marked teams, but I'd like to keep this function generic.
        //So lets index instead.
        std::stringstream ss(line);
        int colIdx=0;
        while(std::getline(ss, cellVal, ',')){
            //Push values suntil we exit loop.
            //Check col ID vs CS and optionally push back
            //if export all cols, then we don't do find and push regardless
            //otherwise, find col
            int pushedCnt=0;
            if(exportAllCols){
               result.push_back(cellVal);
               pushedCnt++;
            }else{
               if(cs.find(colIdx)!=cs.end()){
                   result.push_back(cellVal);
                   pushedCnt++;
               }
            }
            colIdx++;
        } 
        if(exportAllCols){
            if(colIdx!=numCols) result.push_back("");
            //Takes care of empty last columns being lost 
        }
        else if((colIdx != numCols)&&(cs.find(numCols)!=cs.end())){
            //Blank cell at end of row is explicitly requested.
            result.push_back("");
        }
            
    }
    // Close file
    file.close();
    return result;
}



//EXTODO: Make Generic with templates just as an exercise.
/*Example function for reading CSV*/
std::vector<std::pair<std::string, std::vector<int>>> read_csv(std::string filename){
    // Reads a CSV file into a vector of <string, vector<int>> pairs where
    // each pair represents <column name, column values>

    // Create a vector of <string, int vector> pairs to store the result
    std::vector<std::pair<std::string, std::vector<int>>> result;

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) throw std::runtime_error("Could not open file");

    // Helper vars
    std::string line, colname;
    int val;

    // Read the column names
    if(myFile.good()) //TODO: Consider adding error check here?
    {
        // Extract the first line in the file
        std::getline(myFile, line);

        // Create a stringstream from line
        std::stringstream ss(line);

        // Extract each column name
        while(std::getline(ss, colname, ',')){
            
            // Initialize and add <colname, int vector> pairs to result
            result.push_back({colname, std::vector<int> {}});
        }
    }
    

    // Read data, line by line
    while(std::getline(myFile, line))
    {
        // Create a stringstream of the current line
        std::stringstream ss(line);
        
        // Keep track of the current column index
        int colIdx = 0;
        
        // Extract each integer
        while(ss >> val){
            
            // Add the current integer to the 'colIdx' column's values vector
            result.at(colIdx).second.push_back(val);
            
            // If the next token is a comma, ignore it and move on
            if(ss.peek() == ',') ss.ignore();
            
            // Increment the column index
            colIdx++;
        }
    }

    // Close file
    myFile.close();

    return result;
}
