/************************************************************************************************
* Program: Adventure Time Text Based Game
* Author: Justin Azevedo
* Last Modified: 7-28-19
* Class: CS 467 Capstone Summer '19
* Description: Test main file for midway project evalution.
************************************************************************************************/
#include "GameState.hpp"
#include "Room.hpp"
#include "Item.hpp"
#include "parser.hpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unistd.h>

using namespace std;


int main() {

	cout << R"(	
  _________                             ________                     ._.
 /   _____/__________    ____  ____    /  _____/_____    _____   ____| |
 \_____  \\____ \__  \ _/ ___\/ __ \  /   \  ___\__  \  /     \_/ __ \ |
 /        \  |_> > __ \\  \__\  ___/  \    \_\  \/ __ \|  Y Y  \  ___/\|
/_______  /   __(____  /\___  >___  >  \______  (____  /__|_|  /\___  >_
        \/|__|       \/     \/    \/          \/     \/      \/     \/\/
)" << endl << endl;

	GameState * game = new GameState();
	bool menu = false;
	char * path;

	
 	char cwdName [1000];
	memset(cwdName, '\0', sizeof(cwdName));
	getcwd(cwdName, sizeof(cwdName));

	cout << "\t1) New Game" << endl;
	cout << "\t2) Load Game" << endl;
	cout << "\t3) Exit " << endl << endl;

	while(!menu){
		string menuChoice;

		cout << "> ";

		getline(cin, menuChoice);

		if(menuChoice == "1"){
			char newPathName [] = "/default";
		 	strcat(cwdName, newPathName);
 			path = cwdName;
			menu = true;
		}
		else if(menuChoice == "2"){
			char savePathName [] = "/saves";
 			strcat(cwdName, savePathName);
 			path = cwdName;
			menu = true;
		}
		else if(menuChoice == "3"){
			exit(0);
		}
		else{
			cout << "Invalid Entry..." << endl;
		}
	}
//--------------------------------------------------------------------
	
	game->readInGameState(path);
	game->readInRooms(path);

	game->printIntro();

	while(game->getGameQuit() == false){
	

		string input; 
		vector<string> parsedLine;
		
		game->printCurRoomDesc();

		//PRINT STATEMENT FOR DEBUGGING
		cout << "Current room Name: " << game->getPosition()->getName() << endl;
		cout << "O2 Level: " << game->getOxygen() << endl;
		
		game->printExits();

		cout << "> ";

		getline(cin, input);

		cout << "\n";

		parsedLine = parse(input, ' ');

		game->enactVerb(parsedLine);

		input.clear();

	}


	return 0;
}

