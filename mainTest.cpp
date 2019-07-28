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


int main(){

	GameState * game = new GameState();

	cout << "Oxygen Levels: " << game->getOxygen() << endl;
	cout << "gameWon: " << game->getGameWon() << endl;
	cout << "gameQuit: " << game->getGameQuit() << endl;
	cout << "Inventory Size: " << game->getInventorySize() << endl;
	cout << "Game Intro: ";
	game->printIntro();
	cout << "Win Description: "; 
	game->printWinDesc();
	cout << "Loss Description: ";
	game->printLossDesc();

	
	game->setOxygen(1);
	cout << "Oxygen Set to 1: " << game->getOxygen() << endl;

	game->decOxygen();
	cout << "Oxygen decremented to 0: " << game->getOxygen() << endl;

	game->setInventorySize(7);
	cout << "Set inventory to 7: " << game->getInventorySize() << endl;

	game->incInventorySize();
	cout << "Increment inventory to 8: " << game->getInventorySize() << endl;

	game->decInventorySize();
	cout << "Decrement inventory to 7: " << game->getInventorySize() << endl;

	cout << "Current Room Name: " << game->getPosition()->getName() << endl;

	cout << "Item count in current Room: " << game->getPosition()->getItemCount() << endl;

	cout << "Item name in current Room: " << game->getPosition()->getItem("Employee Manual")->getName() << endl;

	//added for room and item testing
/*
	Room * newRoom = new Room();
	Item * newItem = new Item();

	cout << "\nRoom Name: ";
	cout << newRoom->getName() << "\n";

	cout << "Room description:\n";
	cout << newRoom->getLongDesc() << "\n";

	cout << "Item name:  ";
	cout << newItem->getName() << "\n";

	cout << "Item Description: ";
	cout << newItem->getDesc1() << "\n";
*/
	return 0;
}
