/** @file main.cpp
 * Who they play for, main program
 * Author: Brent Duff
 * Dec 12 2021
 * LICENSE: GNU GPLv3
 */

#include <iostream>
#include <vector>
#include <string>

#include "Rosters.hpp"
#include "Inferencer.hpp"


using namespace std;

enum SystemModes {
	textmode, //REFERENCE MODE. Used to pull player information and test roster data.
	usertextquizmode, //GAME MODE. User is quizzed on players.
	inferencetestmode, //REFERENCE MODE. Used to test DNN model directly with user control.
	gamemode}; //GAME MODE. User is quizzed on players--possibly vs computer--with full graphical output and sound.

struct Settings{
	int mode=textmode;
	std::string modelpath="";
	string imgpath="";
};
	
void show_usage(){
	cout << "USAGE: ./whoTheyPlayFor [-m [MODEL_FILE] -d [IMG_DIR]]" << endl;
	cout << "Program can run in two modes: \n \
				1. text query mode \n \
				2. DNN inference mode \n \
			-m and -d flags are *required* if running in inference mode. \n \
			Specify mode via these two flags." << endl;
}
int main(int argc, char* argv[])
{
	Settings s;
	
	if(argc > 1){ // I.e. it has options
	//Set mode and path accordingly.
	//FT-TODO: Parse options
	}
	//Otherwise, proceed.
	
	/*Program Init*/
	if(!InitRosters()){
		cout << "CRITICAL ERROR! Roster initialization FAILED. Exiting..." << endl;
		exit(-1);
	}
	if(s.mode==inferencetestmode){
		if(!InitInferencer()){
			cout << "CRITICAL ERROR! Inference system initialization FAILED. Exiting..." << endl;
			exit(-1);
		}
	}
	
	while(1){ //Main loop
		//Query user, depending on mode, for either text query or image file for inferencer.
		if(s.mode==textmode){
			std::string queryStr;
			cout << "Enter player name to look up: " << endl;
			std::getline(cin,queryStr);

			Player* res = QueryPlayerName(queryStr);
			if(res==nullptr){
				cout << "PLAYER: "<< queryStr << "not found!!" << endl;
			}else{
				cout << "PLAYER: " << queryStr << " FOUND." <<endl;
				cout << "INFO: " << res->name << "plays for the " << res->team->name << "." << std::endl;
			}
		}else if(s.mode==usertextquizmode){
			cout << "Beginning user quiz mode! GAME ON!!" << endl;
			//Game flow should go: Pick random member of RosterBook and quiz player or DNN model on it.
			//Abstract the game flow such that we can use same functions with different inputs regardless of mode.

		}else if(s.mode==inferencetestmode){
			cout << "Launching inference test mode..." << endl;	
			//Inference test mode has following flow:
			//1. User provides keyed input naming a player who has test image sets in some ${DATA_DIR}
			//2. Keyed input is used with QueryPlayerName to retrieve test set location,
			// these images will be used to calculate accuracy of a given model for a given player.
			//3. The images are run through inferencer along with label information. Error tracking will be reported.
		}else{ // GAME MODE, default condition
			//But also most feature filled, so will be last to implement.
		}
			

		}
		//BKMP-TODO: Investigate if cleanup on key-quit is worthwhile?
	}
  
    return 0;
}
