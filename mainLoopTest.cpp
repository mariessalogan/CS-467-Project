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

	while(game->getGameQuit() == false){

		game->printCurRoomDesc();

		game->_takeItem("Employee Manual");

		game->_dropItem("Employee Manual");

		string input; 

		cout << "To quit type quit" << endl;

		cin >> input ;


		if(input == "quit"){
			game->_quitGame();
		} 

	}


	return 0;
}