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

using namespace std;


int main() {

	GameState * game = new GameState();

	game->printIntro();

	game->printCurRoomDesc();

	while(game->getGameQuit() == false){
	
		string input; 
		vector<string> parsedLine;

		cout << "> ";

		getline(cin, input);

		if(input == "quit"){
			game->_quitGame();
		} 

		parsedLine = parse(input, ' ');

		cout << "**parsed input: " << endl;
		for( auto token: parsedLine){
			cout << token << endl;
		}
		

		if(parsedLine[0] == "look"){
			game->printCurRoomDesc();
		}
		else if(parsedLine[0] == "grab"){
			game->_takeItem(parsedLine[1]);
		}
		else if(parsedLine[0] == "look at"){
			game->getPosition()->getItem(parsedLine[1])->getDesc1();
		}
		else if(parsedLine[0] == "drop"){
			game->_dropItem(parsedLine[1]);
		}
		else{
			cout << "Invalid entry" << endl;
		}	
	

		input.clear();

	}


	return 0;
}

